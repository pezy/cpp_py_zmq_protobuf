#include <zmq.h>
#include <build/msg.pb.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <thread>

int main ()
{
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5560");

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    int i = 0;
    while (true) {
        //  Get values that will fool the boss
        RL::DataSet msg;
        msg.set_count(i++);
        msg.add_joint_position(1.1);
        msg.add_joint_position(2.1);
        msg.add_joint_velocity(-1.1);
        msg.add_joint_velocity(-2.1); 
        
        //  Send message to all subscribers
        std::string out;
        msg.SerializeToString(&out); 
        zmq_send(publisher, out.data(), out.size(), 0);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}
