#include "global.h"
#include <iostream>
using namespace std;

void perror_exit(const char *description) {
    perror(description);
    exit(-1);
}
inline void DEBUG(std::string s) {
    cout << s << endl;
}
inline void DEBUG(std::string s1, std::string s2) {
    cout << s1 << ' ' << s2 << endl;
}
inline void DEBUG(std::string s1, std::string s2, std::string s3) {
    cout << s1 << ' ' << s2 << ' ' << s3 << endl;
}