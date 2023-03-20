#include "http_Request.h"
#include "http_Response.h"
#include <cstring>
#include <errno.h>

extern int server_fd;
extern int client_fd;
extern httpRequest req;
extern httpResponse rsp;

void perror_exit(const char *description);
void DEBUG(std::string s);
void DEBUG(std::string s1, std::string s2);
void DEBUG(std::string s1, std::string s2, std::string s3);
