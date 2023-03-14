#include "src/dtbs.h"
#include <iostream>
using namespace std;


int main() {
    DTBS::getDefault()->Open("This_is_a_Test");
    DTBS::getDefault()->Put("aa", "1yuasd");
    string value;
    bool result = DTBS::getDefault()->Get("aa", value);
    if (result) {
        cout << "获取成功:  " << value << endl;
    }
    DTBS::getDefault()->Delete("aa");
    result = DTBS::getDefault()->Get("aa", value);
    if (!result) {
        cout << "删除成功";
    }

    return 0;
}