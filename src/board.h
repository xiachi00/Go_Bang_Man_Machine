#include <vector>

class Board {
public:
    static short SIZE;
    short cnt;
    std::vector<std::vector<short>> board;
};

// 落子
short judge(short x, short y, short player) {
    DEBUG("ENTER JUDGE");

    cnt += 1;
    board[x][y] = player;
    short L_R, U_D, LU_RD, LD_RU, i, j;
    L_R = U_D = LU_RD = LD_RU = 1;

    for (j = y - 1; j >= 0 && board[x][j] == player; j--) L_R += 1;        
    for (j = y + 1; j < SIZE && board[x][j] == player; j++) L_R += 1;
    mx = max(mx, x), my = max(my, y);
    lx = min(lx, x), ly = min(ly, y);

    for (i = x - 1; i >= 0 && board[i][y] == player; i--) U_D += 1;
    for (i = x + 1; i < SIZE && board[i][y] == player; i++) U_D += 1;

    for (i = x - 1, j = y - 1; i >= 0 && j >= 0 && board[i][j] == player; i--, j--) LU_RD += 1;
    for (i = x + 1, j = y + 1; i < SIZE && j < SIZE && board[i][j] == player; i++, j++) LU_RD += 1;

    for (i = x + 1, j = y - 1; i < SIZE && j >= 0 && board[i][j] == player; i++, j--) LD_RU += 1;
    for (i = x - 1, j = y + 1; i >= 0 && j < SIZE && board[i][j] == player; i--, j++) LD_RU += 1;

    for (i = 0; i < 19; i++) cout << "--";
    for (i = 0; i < 19; i++) cout << "  ";
    for (i = 0; i < 19; i++) cout << "  ";
    cout << endl;
    for (i = 0; i < SIZE; i++) {
        cout << "|   ";
        for (j = 0; j < SIZE; j++)
            cout << (board[i][j] == 0 ? ' ' : "OX"[board[i][j] == 2]) << ' ';
        cout << "   |" << endl;
    }
    for (i = 0; i < 19; i++) cout << "  ";
    for (i = 0; i < 19; i++) cout << "  ";
    for (i = 0; i < 19; i++) cout << "--";
    cout << endl;
        
    short max_length = max({L_R, U_D, LU_RD, LD_RU});
    cout << "Player" << player  << ' ' << x << ' ' << y << endl;
    cout << "MaxLength: " << max_length << endl << endl;

    DEBUG("ENTER JUDGE");

    if (max_length < 5) return 0;
    if (max_length >= 5) return player;
    if (cnt == SIZE * SIZE) return -1;
}


