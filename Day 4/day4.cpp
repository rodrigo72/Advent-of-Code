#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main (void) {

    std::ifstream inputFile ("input.txt");

    if (inputFile.is_open()) {
        int total = 0;
        std::string line;

        while (std::getline(inputFile, line)) {
            if (!line.empty()) {
                
                std::vector<int> numbers;
                std::istringstream iss (line);
                std::string token;

                while (std::getline(iss, token, ',')) { // stores the characters up to 
                    std::istringstream iss2 (token);    // the comma in token until end of string stream
                    std::string subtoken;
                    while (std::getline(iss2, subtoken, '-')) {
                        int num = std::stoi(subtoken);
                        numbers.push_back(num);
                    }
                }

                // PART 1
                // if ((numbers[0] <= numbers[2] && numbers[1] >= numbers[3])
                //     || (numbers[0] >= numbers[2] && numbers[1] <= numbers[3])) {
                //     total++;
                // }

                // PART 2
                if (!((numbers[0] < numbers[2] && numbers[1] < numbers[2]) 
                    || (numbers[0] > numbers[2] && numbers[0] > numbers[3]))) {
                    total++;
                }
            }
        }

        std::cout << total << std::endl;

    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return 0;
}