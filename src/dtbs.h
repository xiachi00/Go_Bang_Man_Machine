#include "leveldb/db.h"
#include <string>

class DTBS {
public:
    DTBS()  {}
    ~DTBS() {}

    // 打开数据库
    bool Open(const std::string& dbname);

    // 关闭数据库
    void Close();

    // 写入数据
    bool Put(const std::string& key, const std::string& value);

    // 读取数据
    bool Get(const std::string& key, std::string& value);

    // 删除数据
    bool Delete(const std::string& key);

    static DTBS* getDefault() {
        static DTBS obj;
        return &obj;
    }

private:
    leveldb::DB* db_;

};

bool DTBS::Open(const std::string& dbname) {
    leveldb::Options options;
    options.create_if_missing = true;
    // 打开数据库
    leveldb::Status status = leveldb::DB::Open(options, dbname, &db_);
    if (!status.ok()) {
        return false;
    }
    return true;
}

void DTBS::Close() {
    delete db_;
}

bool DTBS::Put(const std::string& key, const std::string& value) {
    leveldb::Status status = db_->Put(leveldb::WriteOptions(), key, value);
    return status.ok();
}

bool DTBS::Get(const std::string& key, std::string& value) {
    leveldb::Status status = db_->Get(leveldb::ReadOptions(), key, &value);
    return status.ok();
}

bool DTBS::Delete(const std::string& key) {
    leveldb::Status status = db_->Delete(leveldb::WriteOptions(), key);
    return status.ok();
}
