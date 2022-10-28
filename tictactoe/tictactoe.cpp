#include <iostream>
#include <limits>

#define underline "\033[4m"
#define escape "\033[0m"

void render(char state[9]) {
    std::cout << " " << underline << "     " << std::endl;
    std::cout << escape << "|" << underline << state[0] << "|" << state[1] << "|" << state[2] << escape << "|" << std::endl;
    std::cout << escape << "|" << underline << state[3] << "|" << state[4] << "|" << state[5] << escape << "|" << std::endl;
    std::cout << escape << "|" << underline << state[6] << "|" << state[7] << "|" << state[8] << escape << "|" << std::endl;
    std::cout << std::endl;
};

void game_input(char turn, char state[9]) {
    int choice {};
    std::cout << "Player " << turn << ", please select where you want to go (1-9): ";
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (choice < 1 || choice > 9) {
            std::cout << "Please enter a number from 1-9: ";
        } else if (state[choice - 1] != ' ') {
            std::cout << "This spot is already taken. Enter a different spot (1-9): ";
        } else break;
    }
    
    state[choice - 1] = turn;
}

void switch_turn(char* ptr) {
    if (*ptr == 'X') {
        *ptr = 'O';
    } else if (*ptr == 'O') {
        *ptr = 'X';
    }
}

bool compare_3(char v[3]) {
    if (v[0] == v[1] && v[1] == v[2] && v[0] != ' ') {
        return true;
    }
    return false;
}

bool check_winner(char s[9]) {
    char comparisons[8][3] {
        {s[0], s[1], s[2]}, {s[3], s[4], s[5]}, {s[6], s[7], s[8]}, // across
        {s[0], s[3], s[6]}, {s[1], s[4], s[7]}, {s[2], s[5], s[8]}, // down
        {s[0], s[4], s[8]}, {s[2], s[4], s[6]}                      // diagonal
    };
    for (int i=0; i<8; i++) {
        if (comparisons[i][0] == comparisons[i][1] && comparisons[i][0] == comparisons[i][2] && comparisons[i][0] != ' ') {
            return true;
        }
    }

    return false;
}

int main() {
    char game_state[9] {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char turn {'X'};

    while (check_winner(game_state) != true) {
        render(game_state);
        game_input(turn, game_state);
        switch_turn(&turn);
    }

    render(game_state);
    switch_turn(&turn);

    std::cout << "Player " << turn << " has won the game!";


    return 0;
}