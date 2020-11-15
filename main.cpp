#include <iostream>
#include <string>

int main() {
    std::cout << "Ruach Interpreter" << "\n";

    while (true) {
        std::cout << ">> ";
        std::string input;
        std::cin >> input;

        // echo
        std::cout << input << "\n";

        if (input == "exit") {
            break;
        }
    }

    return 0;
}
