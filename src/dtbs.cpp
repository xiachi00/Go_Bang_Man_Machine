#include "dtbs.h"
using namespace std;


DTBS* DTBS::getDefault() {
    static DTBS obj;
    return &obj;
}

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

bool DTBS::Put(const std::string& key, const Board& value) {
    std::string value_str = value.serialize();
    leveldb::Status status = db_->Put(leveldb::WriteOptions(), key, value_str);
    return status.ok();
}

bool DTBS::Get(const std::string& key, Board& value) {
    std::string value_str;
    leveldb::Status status = db_->Get(leveldb::ReadOptions(), key, &value_str);
    value.deserialize(value_str);
    return status.ok();
}

bool DTBS::Delete(const std::string& key) {
    leveldb::Status status = db_->Delete(leveldb::WriteOptions(), key);
    return status.ok();
}
