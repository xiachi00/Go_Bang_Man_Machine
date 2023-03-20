#include "board.h"
#include "global.h"
#include <iostream>
#include <algorithm>
using namespace std;

short Board::SIZE = 15;
const int BOARD_SIZE = 15;
const int INF = 0x3f3f3f3f;
const int MAX_DEPTH = 2;

Board create_Board() {
    Board new_board = Board();
    new_board.cnt = 0;
    new_board.board = vector<vector<short>>(Board::SIZE, vector<short>(Board::SIZE));
    return new_board;
}

string Board::serialize() const {
    ostringstream oss;
    oss << "{";
    // 将 Board 对象的状态信息写入字符串
    oss << "\"SIZE\":" << SIZE << ",";
    oss << "\"cnt\":" << cnt << ",";
    oss << "\"board\":[";
    for (auto row : board) {
        oss << "[";
        for (auto col : row) {
            oss << col << ",";
        }
        oss << "],";
    }
    oss << "]}";
    return oss.str();
}

// 从字符串反序列化
bool Board::deserialize(const string& json_str) {
    istringstream iss(json_str);
    string token;
    while(getline(iss, token, ':')) {
        if (token == "\"SIZE\"") {
            getline(iss, token, ',');
            SIZE = stoi(token);
        }
        else if (token == "\"cnt\"") {
            getline(iss, token, ',');
            cnt = stoi(token);
        }
        else if (token == "\"board\"") {
            getline(iss, token, '[');
            int row = 0, col = 0;
            while(getline(iss, token, ',')) {
                board[row][col] = stoi(token);
                ++col;
                if (col >= board[0].size()) {
                    col = 0;
                    ++row;
                }
                if (row >= board.size()) {
                    break;
                }
            }
        }
    }
    return true;
}

short place_and_judge(Board& B, short x, short y, short player) {
    DEBUG("ENTER JUDGE");

    B.cnt += 1;
    auto &board = B.board;
    board[x][y] = player;
    short L_R, U_D, LU_RD, LD_RU, i, j;
    L_R = U_D = LU_RD = LD_RU = 1;
    short SIZE = 15;

    for (j = y - 1; j >= 0 && board[x][j] == player; j--) L_R += 1;        
    for (j = y + 1; j < SIZE && board[x][j] == player; j++) L_R += 1;

    for (i = x - 1; i >= 0 && board[i][y] == player; i--) U_D += 1;
    for (i = x + 1; i < SIZE && board[i][y] == player; i++) U_D += 1;

    for (i = x - 1, j = y - 1; i >= 0 && j >= 0 && board[i][j] == player; i--, j--) LU_RD += 1;
    for (i = x + 1, j = y + 1; i < SIZE && j < SIZE && board[i][j] == player; i++, j++) LU_RD += 1;

    for (i = x + 1, j = y - 1; i < SIZE && j >= 0 && board[i][j] == player; i++, j--) LD_RU += 1;
    for (i = x - 1, j = y + 1; i >= 0 && j < SIZE && board[i][j] == player; i--, j++) LD_RU += 1;

    for (i = 0; i < 19; i++) cout << "--";
    cout << endl;
    for (i = 0; i < 19; i++) cout << "  ";
    cout << endl;
    for (i = 0; i < 19; i++) cout << "  ";
    cout << endl;
    for (i = 0; i < SIZE; i++) {
        cout << "|   ";
        for (j = 0; j < SIZE; j++)
            cout << (board[i][j] == 0 ? ' ' : "OX"[board[i][j] == 2]) << ' ';
        cout << "   |" << endl;
    }
    for (i = 0; i < 19; i++) cout << "  ";
    cout << endl;
    for (i = 0; i < 19; i++) cout << "  ";
    cout << endl;
    for (i = 0; i < 19; i++) cout << "--";
    cout << endl;
        
    short max_length = max({L_R, U_D, LU_RD, LD_RU});
    cout << "Player" << player  << ' ' << x << ' ' << y << endl;
    cout << "MaxLength: " << max_length << endl << endl;

    DEBUG("ENTER JUDGE");

    if (max_length >= 5) return 1;
    if (B.cnt == SIZE * SIZE) return -1;
    return 0;
}

// 贪心AI
int analysis_greedy(Board &B) {
    vector<vector<int>> score(15, vector<int>(15));
    
    auto &board = B.board;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != 0) continue;  // 如果该位置已经被占据，则跳过

            // 计算该位置的得分
            int s = 0;

            // 检查横线得分
            for (int k = max(0, j - 4); k <= min(j, BOARD_SIZE - 5); k++) {
                int cnt = 0;
                for (int p = 0; p < 5; p++) {
                    if (board[i][k + p] == 2) // 2 为AI棋
                        cnt += 2;
                    else if (board[i][k + p] == 1) // 1 为玩家棋
                        cnt = 0;
                }
                s += cnt;
            }

            // TODO: 检查竖线、斜线的得分

            score[i][j] = s;
        }
    }

    // 选择得分最高的位置进行落子
    int x = -1, y = -1, max_score = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (score[i][j] > max_score) {
                max_score = score[i][j];
                x = i;
                y = j;
            }
        }
    }

    for (auto &v : score) v.clear();
    score.clear();
    vector<vector<int>>().swap(score);

    return x * 15 + y;
}





// 高级AI
int analysis_alpha_beta(Board &B) {
    // test
    int cnt = 0;
    auto& board = B.board;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (!board[i][j] && ++cnt == 100) {
                return i * 15 + j;
            }
        }
    }
}
