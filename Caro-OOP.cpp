
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 15;

// Lop Ban co
class Board {
private:
    char board[SIZE][SIZE];

public:
    Board() {
        reset();
    }

    void reset() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                board[i][j] = '.';
    }

    void display() {
        cout << "\n   ";
        for (int i = 1; i <= SIZE; i++)
            cout << i % 10 << " ";
        cout << endl;

        for (int i = 0; i < SIZE; i++) {
            cout << i + 1;
            if (i + 1 < 10) cout << "  ";
            else cout << " ";

            for (int j = 0; j < SIZE; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }

    bool isValid(int row, int col) {
        return row >= 0 && row < SIZE &&
            col >= 0 && col < SIZE &&
            board[row][col] == '.';
    }

    void placeMove(int row, int col, char symbol) {
        board[row][col] = symbol;
    }

    bool checkWin(int row, int col, char symbol) {
        int dx[] = { 0, 1, 1, 1 };
        int dy[] = { 1, 0, 1, -1 };

        for (int i = 0; i < 4; i++) {
            int count = 1;

            // Dem theo mot huong
            for (int k = 1; k < 5; k++) {
                int r = row + dx[i] * k;
                int c = col + dy[i] * k;

                if (r < 0 || r >= SIZE ||
                    c < 0 || c >= SIZE ||
                    board[r][c] != symbol)
                    break;

                count++;
            }

            // Dem theo huong nguoc lai
            for (int k = 1; k < 5; k++) {
                int r = row - dx[i] * k;
                int c = col - dy[i] * k;

                if (r < 0 || r >= SIZE ||
                    c < 0 || c >= SIZE ||
                    board[r][c] != symbol)
                    break;

                count++;
            }

            if (count >= 5)
                return true;
        }

        return false;
    }

    bool isFull() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] == '.')
                    return false;

        return true;
    }
};

// Lop Nguoi choi
class Player {
private:
    string name;
    char symbol;

public:
    Player(string n, char s) {
        name = n;
        symbol = s;
    }

    string getName() {
        return name;
    }

    char getSymbol() {
        return symbol;
    }
};

// Lop Tro choi
class Game {
private:
    Board board;
    Player p1;
    Player p2;

public:
    Game() : p1("Nguoi choi 1", 'X'),
        p2("Nguoi choi 2", 'O') {
    }

    void start() {
        int row, col;
        int turn = 1;

        while (true) {
            board.display();

            Player current = (turn == 1) ? p1 : p2;

            cout << "\n" << current.getName()
                << " (" << current.getSymbol() << ")";
            cout << "\nNhap hang va cot (1-15): ";

            if (!(cin >> row >> col)) {
                cout << "Du lieu khong hop le!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            row--;
            col--;

            if (!board.isValid(row, col)) {
                cout << "O nay khong hop le!\n";
                continue;
            }

            board.placeMove(row, col, current.getSymbol());

            if (board.checkWin(row, col, current.getSymbol())) {
                board.display();
                cout << "\n" << current.getName()
                    << " DA CHIEN THANG!\n";
                break;
            }

            if (board.isFull()) {
                board.display();
                cout << "\nVAN CO HOA!\n";
                break;
            }

            turn = (turn == 1) ? 2 : 1;
        }
    }
};

int main() {
    Game game;
    game.start();

    return 0;
}
