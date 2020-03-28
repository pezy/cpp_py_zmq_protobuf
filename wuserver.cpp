#include <zmq.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define randof(num)  (int) ((float) (num) * random () / (RAND_MAX + 1.0))

int main (void)
{
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5560");
    assert (rc == 0);

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    while (1) {
        //  Get values that will fool the boss
        int zipcode, temperature, relhumidity;
        zipcode     = randof (100000);
        temperature = randof (215) - 80;
        relhumidity = randof (50) + 10;

        //  Send message to all subscribers
        char update [20];
        sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity);
        zmq_send(publisher, update, strlen(update), 0);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}
