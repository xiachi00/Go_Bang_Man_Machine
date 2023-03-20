#pragma once
#include <string>
#include <sstream>
#include <vector>

class Board {
public:
    static short SIZE;
    short cnt;
    std::vector<std::vector<short>> board;

    // 序列化为字符串
    std::string serialize() const;

    // 从字符串反序列化
    bool deserialize(const std::string& json_str);
};


Board create_Board();
short place_and_judge(Board& B, short x, short y, short player);
int analysis_greedy(Board &B);
int analysis_alpha_beta(Board &B);