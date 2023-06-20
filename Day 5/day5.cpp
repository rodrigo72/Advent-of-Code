#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <sstream>
#include <vector>
// #include <regex>

const int STACK_COUNT = 9;

int main (void) {

    std::deque<char> stackArray[STACK_COUNT];

    std::ifstream inputFile("input.txt");
    std::string line;

    bool readingInitialState = true;

    while (std::getline(inputFile, line)) {
        if (!line.empty() && readingInitialState) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '[') {
                    int stack_number = i / 4;
                    stackArray[stack_number].push_back(line[i+1]);
                    i += 2;
                }
            }
        } else if (readingInitialState) {
            readingInitialState = false;
        } else if (!line.empty()) {

            // REGEX
            // const std::regex pattern(R"(move ([0-9]+) from ([0-9]+) to ([0-9]+))");
            // std::smatch match;
            // std::regex_match(line, match, pattern);
            // const auto quantity = std::stoi(match[1]); // AUTO -> compiler determines the appropriate data type
            // const auto fromStack = std::stoi(match[2]) - 1;
            // const auto toStack = std::stoi(match[3]) - 1;

            std::istringstream iss(line);
            std::string command, number1, from, number2, to, number3;
            iss >> command >> number1 >> from >> number2 >> to >> number3; // separates by whitespace by default

            const auto quantity = std::stoi(number1);
            const auto fromStack = std::stoi(number2) - 1;
            const auto toStack = std::stoi(number3) - 1;

            // for part 2
            std::vector<char> tempVector;

            for (int j = 0; j < quantity; j++) {
                if (!stackArray[fromStack].empty()) {
                    char c = stackArray[fromStack].front();
                    stackArray[fromStack].pop_front();
                    tempVector.push_back(c);
                }
            }

            // for part 2
            for (int k = tempVector.size() - 1; k >= 0; k--) {
                stackArray[toStack].push_front(tempVector[k]);
            }

        }
    }

    for (int i = 0; i < STACK_COUNT; i++) {
        std::cout << stackArray[i].front();
    }
    std::cout << std::endl;

    return 0;
}