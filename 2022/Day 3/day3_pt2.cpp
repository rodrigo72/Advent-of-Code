#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype>

int main (void) {

    std::ifstream inputFile ("input_pt2.txt");

    if (inputFile.is_open()) {

        int group_count = 1;
        int total = 0;
        char found_char = '\0';
        std::string line;

        std::unordered_map<char, int> char_count_map;

        while (std::getline(inputFile, line)) {

            if (!line.empty()) {

                switch (group_count) {
                    case 1: {
                        for (int i = 0; i < line.length(); i++) 
                            if (char_count_map[line[i]] == 0) 
                                char_count_map[line[i]]++;
                        group_count++;
                        break;
                    }
                    case 2: {
                        for (int i = 0; i < line.length(); i++) 
                            if (char_count_map[line[i]] == 1) 
                                char_count_map[line[i]]++;
                        group_count++;
                        break;
                    }
                    case 3: {
                        for (int i = 0; i < line.length() && found_char == '\0'; i++) 
                            if (char_count_map[line[i]] == 2) 
                                found_char = line[i];

                        group_count = 1;

                        if (found_char != '\0') {
                            if (std::islower(found_char)) {
                                total += (int) found_char - 96;
                            } else {
                                total += (int) found_char - 38;
                            }   
                            char_count_map.clear();
                            found_char = '\0';
                        }

                        break;
                    }
                }

            }
        }

        std::cout << total << std::endl;
        
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
} 