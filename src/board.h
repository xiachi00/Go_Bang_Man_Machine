#include <vector>

class Board {
public:
    static int SIZE;
    std::vector<std::vector<int>> board;
    Board();
    inline void placing(int x, int y, int player);
    void clear();
    void analysis_greedy();
    void analysis_alpha_beta();
};

int Board::SIZE = 15;

// 新建棋盘
Board::Board() {
    board = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE));
}

// 落子
inline void Board::placing(int x, int y, int player) {
    board[x][y] = player;
}

// 释放棋盘
void Board::clear() {
    for (auto &v : board) v.clear();
    board.clear();
    std::vector<std::vector<int>>().swap(board);
}

// 贪心AI
void Board::analysis_greedy() {

}

// 高级AI
void Board::analysis_alpha_beta() {
    
}

