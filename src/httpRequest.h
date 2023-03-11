#include <cstring>
#include <unordered_map>
#include <ostream>


class httpRequest {
public:
    std::string method;                          // 请求方法
    std::string url;                             // 要请求的URL地址
    std::string type;
    std::unordered_map<std::string, std::string> args;     // 请求参数
    std::unordered_map<std::string, std::string> headers;  // 请求头
    std::string version;                         // 版本协议号
    std::string body;                            // 请求体
    void clear();                                // 清空
    friend std::ostream & operator << (std::ostream& os, const httpRequest &obj); // 只输出头

};

void httpRequest::clear() {
    method.clear();
    url.clear();
    type.clear();
    version.clear();
    body.clear();
    args.clear();
    headers.clear();
    std::string().swap(method);
    std::string().swap(url);
    std::string().swap(type);
    std::string().swap(version);
    std::string().swap(body);
    std::unordered_map<std::string, std::string>().swap(args);
    std::unordered_map<std::string, std::string>().swap(headers);
}


