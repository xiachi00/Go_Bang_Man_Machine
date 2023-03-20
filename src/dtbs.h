#pragma once
#include "leveldb/db.h"
#include <string>
#include "board.h"

class DTBS {
public:
    DTBS()  {}
    ~DTBS() {}

    // 打开数据库
    bool Open(const std::string& dbname);

    // 关闭数据库
    void Close();

    // 写入数据
    bool Put(const std::string& key, const Board& value);

    // 读取数据
    bool Get(const std::string& key, Board& value);

    // 删除数据
    bool Delete(const std::string& key);

    static DTBS* getDefault();
private:
    leveldb::DB* db_;

};

