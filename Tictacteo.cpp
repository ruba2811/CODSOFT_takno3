#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char player_marker, computer_marker;
int current_player;
void XOBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "--|---|--\n";
    }
    cout << "\n";
}
bool placeMarker(int slot, char marker) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = marker;
        return true;
    }
    return false;
}
int checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) 
            return (board[i][0] == player_marker) ? 1 : 2;
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) 
            return (board[0][i] == player_marker) ? 1 : 2;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
        return (board[0][0] == player_marker) ? 1 : 2;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
        return (board[0][2] == player_marker) ? 1 : 2;

    return 0;
}

int computerMove() {
    srand(time(0));
    int slot;
    do {
        slot = rand() % 9 + 1;
    } while (!placeMarker(slot, computer_marker));
    return slot;
}

void game() {
    cout << "Choose your marker (X or O): ";
    cin >> player_marker;
    computer_marker = (player_marker == 'X') ? 'O' : 'X';
    current_player = 1;

    XOBoard();
    int player_won;

    for (int i = 0; i < 9; i++) {
        if (current_player == 1) {
            int slot;
            cout << "Your turn. Enter your slot: ";
            cin >> slot;
            if (slot < 1 || slot > 9 || !placeMarker(slot, player_marker)) {
                cout << "Invalid slot! Try again.\n";
                i--;
                continue;
            }
        } else {
            int computer_choice = computerMove();
            cout << "Computer chose slot " << computer_choice << "\n";
        }
        
        XOBoard();
        player_won = checkWinner();

        if (player_won == 1) {
            cout << "You win!\n";
            break;
        } else if (player_won == 2) {
            cout << "Computer wins!\n";
            break;
        }

        current_player = (current_player == 1) ? 2 : 1;
    }
    if (player_won == 0) cout << "It's a draw!\n";
}

int main() {
    game();
    return 0;
}