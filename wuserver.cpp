#include <zmq.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

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
        std::ostringstream oss;
        oss << std::setw(5) << std::setfill('0') << zipcode;
        oss << ' ' << temperature << ' ' << relhumidity;
        std::string out = oss.str();
        zmq_send(publisher, out.data(), out.size(), 0);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}
