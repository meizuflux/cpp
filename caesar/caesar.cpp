#include <iostream>
#include <sstream>

using std::cout, std::endl, std::cin;

std::string encrypt(int key, std::string text) {
    std::stringstream result {};
    std::string alphabet="abcdefghijklmnopqrstuvwxyz";

    for (char c : text) {
        if (std::isupper(c)) {
            result << char(int(c + key - 65) % 26 + 65);
        } else { 
            result << char(int(c + key - 97) % 26 + 97);
        }
    }

    return result.str();
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <encrypt|decrypt> <key> <text> [options]";
        return 1;
    }
    int key {};
    std::string text {argv[3]};

    std::istringstream iss(argv[2]);
    if (!(iss >> key)) {
        cout << "Please enter a number for the key";
        return 1;
    }

    std::string mode {argv[1]};

    if (mode == "encrypt") {
        cout << encrypt(key, text) << endl;
    } else if (mode == "decrypt") {
        cout << encrypt(26-key, text) << endl;
    } else if (mode == "crack") {
        for (int i; i < 26; i++) {
            cout << "Key " << i << (i < 10 ? ":  " : ": ") << encrypt(26-i, text) << endl;
        }
    } else {
        cout << "Unknown mode";
        return 1;
    }




    return 0;
}