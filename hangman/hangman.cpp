#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <limits>
#include <algorithm>
#include <iterator>


using std::cout;
using std::cin;
using std::endl; 
using std::string;

string format_guess(string answer, std::vector<char> correct_guesses) {
    std::stringstream res {};

    for (char c : answer) {
        if (c == ' ') {
            res << c;
        } else {
            if (std::find(correct_guesses.begin(), correct_guesses.end(), c) != correct_guesses.end()) {
                res << c;
            } else {
                res << "*";
            }
        }
    }

    return res.str();
}

void render(string answer, std::vector<char> correct_guesses, std::vector<char> wrong_guesses) {
    unsigned long s {wrong_guesses.size()};

    cout << "  ┏━━━━┓" << endl;
    cout << "  ┃    "<< (s >= 1 ? "O" : "") << endl;
    cout << "  ┃   " << (s >= 2 ? "╱" : "") << (s >= 3 ? "|" : "") << (s >= 4 ? "╲" : "") << endl;
    cout << "  ┃   " << (s >= 5 ? "╱" : "") << (s >= 6 ? " ╲" : "") << endl;
    cout << "  ┃" << endl;
    cout << "━━┻━━" << endl;

    string ret {format_guess(answer, correct_guesses)};
    cout << ret << " (" << ret.length() << " chars)" << endl;
}

void process_guess(string answer, std::vector<char>* correct_guesses, std::vector<char>* wrong_guesses) {
    cout << "Enter a one letter guess: ";
    while (true) {
        string guess;
        cin >> guess;

        if (guess.length() == 0 || guess.length() > 1) {
            cout << "Please enter only one letter: ";
            continue;
        }

        char real_guess {guess[0]};

        if (std::find(correct_guesses->begin(), correct_guesses->end(), real_guess) != correct_guesses->end() || 
            std::find(wrong_guesses->begin(), wrong_guesses->end(), real_guess) != wrong_guesses->end()) {
            cout << "This letter has already been guessed, enter another: ";
            continue;
        }

        if (answer.find(real_guess) != string::npos) {
            correct_guesses->push_back(real_guess);
        } else {
            wrong_guesses->push_back(real_guess);
        }

        break;
    }
}

bool is_game_over(string answer, std::vector<char> correct_guesses, std::vector<char> wrong_guesses, int wrong_guesses_allowed) {
    if (answer == format_guess(answer, correct_guesses) ||
        (wrong_guesses_allowed == wrong_guesses.size() && wrong_guesses_allowed != 0)) {
        return true;
    }
    return false;
}

string format_guesses(std::vector<char> vec) {
    std::stringstream buf {};


    buf << "[";

    for (char c : vec) {
        if (c != '~')
            buf << c << ", ";
    }    

    buf << "\b\b]";
    return buf.str();
}

int main() {
    cout << "Welcome to HANGMAN!" << endl;

    string answer {getpass("Type the answer (hidden from view): ")};

    cout << "Enter how many wrong guesses allowed (6 reccomended) (0 for infinite): ";
    int wrong_guesses_allowed {};

    while (true) {
        cin >> wrong_guesses_allowed;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Please enter a number: ";
        } else break;
    }

    std::vector<char> correct_guesses {'~',};
    std::vector<char> wrong_guesses {};

    while (!(answer == format_guess(answer, correct_guesses) ||
        (wrong_guesses_allowed == wrong_guesses.size() && wrong_guesses_allowed != 0))) {
        render(answer, correct_guesses, wrong_guesses);
        process_guess(answer, &correct_guesses, &wrong_guesses);
    }

    render(answer, correct_guesses, wrong_guesses);

    if (answer == format_guess(answer, correct_guesses)) {
        cout << "You WIN!" << endl;
    } else {
        cout << "You LOSE!" << endl;
    }

    cout << endl << "Stats: " << endl;
    cout << "    Correct Guesses: " << format_guesses(correct_guesses) << " ("<<correct_guesses.size()<<")" << endl;
    cout << "    Wrong Guesses:   " << format_guesses(wrong_guesses) << " ("<<wrong_guesses.size()<<")" << endl;

    return 0;
}