#include "httpRequest.h"
#include "httpResponse.h"
#include <errno.h>

int server_fd, client_fd;
httpRequest req;
httpResponse rsp;
void perror_exit(const char *description);
inline void DEBUG(string s);
inline void DEBUG(string s1, string s2);
inline void DEBUG(string s1, string s2, string s3);
