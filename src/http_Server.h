#include "dtbs.h"
#include "board.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <iostream>
#include <ostream>
#include <errno.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>


const int SERVER_PORT = 8888;
const std::string END = "\r\n";

// 套接字捆绑 并监听
void bind_listen();

// 接收客户端请求
void accept_client_req_info();

// 判断是否为 '/r' 或者 '/n'
inline bool isline(char &w);

// 格式化请求头每一行
void Format(std::string &s);

// 将str依照c分隔, 结果存在vector中并返回
std::vector<std::string> split(std::string &str, char c);

// 格式化请求报文 (目前只实现GET请求)
void request_format();

// 解析客户端请求, 并将请求所需内容填充在rsp中
void analysis_req_info();

std::string cat_html_file(std::string path);

std::string cat_js_file(std::string path);

std::string cat_binary_file(std::string path);

void send_to_client();