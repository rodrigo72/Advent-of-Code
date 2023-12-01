#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype>

int main (void) {

    std::ifstream inputFile ("input.txt");

    if (inputFile.is_open()) {

        int total = 0;
        std::string line;

        while (std::getline(inputFile, line)) {

            if (!line.empty()) {

                std::unordered_map<char, int> char_count_map; // default value for int is 0

                char found_char = '\0';
                int limit = line.length() / 2;

                for (int i = 0; i < line.length() && found_char == '\0'; i++) {
                    if (i < limit) {
                        if (char_count_map[line[i]] == 0)
                            char_count_map[line[i]]++;
                    } else {
                        if (char_count_map[line[i]] == 1) 
                            found_char = line[i];
                    }
                }
                
                if (found_char != '\0') {
                    if (std::islower(found_char)) {
                        total += (int) found_char - 96;
                    } else {
                        total += (int) found_char - 38;
                    }
                }

            }
        }

        std::cout << total << std::endl;
        
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
} 