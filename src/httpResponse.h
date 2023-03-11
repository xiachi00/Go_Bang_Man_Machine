#include <string>
#include <unordered_map>
#include <ostream>
#include <leveldb/db.h>
#include <leveldb/options.h>

class httpResponse {
public:
    std::string version;                              // 版本号
    std::string status_code;                          // 状态码
    std::string status_msg;                           // 状态消息
    std::unordered_map<std::string, std::string> headers;  // 响应头

    std::string body;                                 // 响应体
    static std::unordered_map<std::string, std::string> MIME;
    std::string package();
    void clear();
    friend std::ostream & operator << (std::ostream& os, const httpResponse &obj); // 只输出头
};

void httpResponse::clear() {
    version.clear();
    status_code.clear();
    status_msg.clear();
    headers.clear();
    body.clear();
    std::string().swap(version);
    std::string().swap(status_code);
    std::string().swap(status_msg);
    std::string().swap(body);
    std::string().swap(version);
    std::unordered_map<std::string, std::string>().swap(headers);
}