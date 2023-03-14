#include "board.h"
using namespace std;

Board::SIZE = 15;

Board create_Board() {
    Board new_board = Board();
    new_board.cnt = 0;
    new_board.board = board = vector<vector<short>>(SIZE, std::vector<short>(SIZE));
    return new_board;
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

    if (max_length >= 5) return player;
    if (B.cnt == SIZE * SIZE) return -1;
    return 0;
}

// 贪心AI
void analysis_greedy(Board &B) {

}

// 高级AI
void analysis_alpha_beta(Board &B) {
    
}
