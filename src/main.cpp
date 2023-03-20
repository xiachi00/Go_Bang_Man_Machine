#include "http_Server.h"
using namespace std;


int main() {
    
    bind_listen();
    
    while (true) {
        accept_client_req_info();
        analysis_req_info();
        send_to_client();
    }
    close(server_fd);

    return 0;
}