#include "global.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
using namespace std;


unordered_map<string, string> httpResponse::MIME = {
    { ".html", "text/html;charset=utf-8" },
    { ".js", "text/javascript" },
    { ".txt", "text/plain" },
    { ".json", "application/json" },
    { ".xml", "application/xml" },
    { ".jpg", "image/jpeg" },
    { ".jpeg", "image/jpeg" },
    { ".png", "image/png" },
    { ".ico", "image/x-icon" },
    { ".webp", "image/webp" },
    { ".mp3", "audio/mpeg" },
    { ".mp4", "video/mp4" },
    { "data", "0" }
};

// 套接字捆绑 并监听
void bind_listen() {
    int ret;
    // 创建服务器套接字描述符
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) perror_exit("Server Socket Error");
    DEBUG("Server Socket Succeeded!");

    struct sockaddr_in server_addr;
    // 清空服务器地址信息, 并且填入协议族, IP, 端口号
    memset(&server_addr, 0, sizeof server_addr); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 本地所有IP地址, host to net
    server_addr.sin_port = htons(SERVER_PORT);

    // 实现 服务器信息 与 套接字 的绑定
    ret = bind(server_fd, (struct sockaddr*) &server_addr, sizeof server_addr);
    if (ret == -1) perror_exit("Bind Error");
    DEBUG("Bind Succeeded!");

    // 服务器开始监听, 同时最多有10个
    ret = listen(server_fd, 10);
    if (ret == -1) perror_exit("Listen Error");
    DEBUG("Waiting for connection from client......");
    DEBUG("=======================================================================================================");
}

// 接收客户端请求
void accept_client_req_info() {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    client_addr_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_len);
    if (client_fd == -1) perror_exit("Accept Error");
    char client_ip[64];
    char *client_ip = new char[64];
    // 输出客户端的网络信息
    cout << "Client's IP:     " << 
            inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, 64) << endl;
    cout << "Client's PORT:   " << ntohs(client_addr.sin_port) << endl << endl;
    delete[] ip;
}

// 判断是否为 '/r' 或者 '/n'
inline bool isline(char &w) {
    return w == '\n' || w == '\r';
}

// 格式化请求头每一行
void Format(string &s) {
    while (!s.empty() && isline(s.back())) s.pop_back();
    if (s.empty()) return;
    size_t pos = 0;
    while (pos < s.size() && isline(s[pos])) pos += 1;
    s = s.substr(pos);
}

// 将str依照c分隔, 结果存在vector中并返回
vector<string> split(string &str, char c) { // c 为分隔符
    stringstream ss(str);
    vector<string> res;
    string item;
    while (getline(ss, item, c)) res.push_back(item);
    item.clear();
    string().swap(item);
    ss.str("");
    ss.clear();
    stringstream().swap(ss);
    return res;
}

// 格式化请求报文 (目前只实现GET请求)
void request_format() {

    DEBUG("ENTER request_format");

    char* buff = new char[10240];
    int len = read(client_fd, buff, 10240 - 1);
    buff[len] = '\0';
    if (len <= 0) {
        delete[] buff;
        perror_exit("Read Error");
    }
    req.clear();
    stringstream sline(buff);
    string line;
    
    //  处理请求行
    getline(sline, line), Format(line);
    vector<string> first_line = split(line, ' ');
    req.method = first_line[0];                                // method
    req.version = first_line[2];                               // version
    vector<string> url_args = split(first_line[1], '?');
    req.url = url_args[0];                                     // url
    if (url == "/") url = "/index.html";
    size_t pos = url.find('.');
    if (pos != string::npos) {
        req.type = url.substr(pos, url.size() - pos);          // type
    } else {
        req.type = "data";
    }
    vector<string> args = split(url_args[1], '&');
    vector<string> key_value;                                  
    for (auto &item : args) {
        key_value = split(item, '=');
        key_value.resize(2);
        req.args[key_value[0]] = key_value[1];           // args[key] = value
        key_value.clear();
    }

    //  处理请求头
    while (getline(sline, line)) {
        Format(line);
        if (line == "") break;
        key_value = split(line, ':');
        key_value.resize(2);
        req.headers[key_value[0]] = key_value[1];              // headers[key] = value
        req.headers.
        key_value.clear();
    }

    body = "";
    while (getline(sline, line)) {
        body += line;
    }

    // 如果没有cookie则默认
    if (!req.headers.count("chess_Mark")) {
        req.headers["chess_Mark"] = " -1";
    }

    first_line.clear();
    url_args.clear();
    args.clear();
    key_value.clear();
    vector().swap(first_line);
    vector().swap(url_args);
    vector().swap(args);
    vector().swap(key_value);
    delete[] buff;

    DEBUG("LEAVE request_format");
}

// 解析客户端请求, 并将请求所需内容填充在rsp中
void analysis_req_info() {
    DEBUG("ENTER analysis_req_info");

    rsp.clear();
    rsp.version = req.version;
    rsp.status_code = "200";
    rsp.status_msg = "OK";

    if (req.type == ".html") {
        rsp.body = cat_text_file(req.url);
    } else if (req.type == ".ico" || req.type == ".jpg" || req.type == ".jpeg" || req.type == ".png") {
        rsp.body = cat_binary_file(req.url);
    } else if (req.type == "data") {

    }
    



    DEBUG("LEAVE analysis_req_info");
}

string cat_text_file(string path) {
    string filename = "../resource" + path;
    cout << "Request for " << filename << endl;
    string line, content = "";
    ifstream fs(filename);
    if (fs.is_open()) {
        while (getline(fs, line)) {
            content += line + '\n';
        }
        fs.close();
    } else {
        fs.close();
        cout << "Error: Cannot open html file" << endl;
        exit(-1);
    }
    line.clear();
    string().swap(line);
    return content;
}

string cat_binary_file(string path) {
    string filename = "../resource" + path;
    cout << "Request for " << filename << endl;
    string line, content = "";
    ifstream fs(filename, ios::in|ios::binary|ios::ate);
    if (fs) {
        streampos len = fs.tellg();
        content.resize(len);
        fs.seekg(0, ios::beg);
        fs.read(&content[0], len);
        fs.close();
        return content;
    } else {
        cout << "Error: Cannot open file" << endl;
        fs.close();
        exit(-1);
    }
}

void send_to_client() {
    string msg = rsp.package();
    len = send(client_fd, msg.c_str(), msg.size(), 0);
    msg.clear(), string().swap(msg);
    req.clear(), rsp.clear();
    if (len <= 0) DEBUG("Send Error!");
    else DEBUG("Send Succeeded!");
    DEBUG("--------------------------------------------------------------------------------------------");
    
    close(client_fd);
}