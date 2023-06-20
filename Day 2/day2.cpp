#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main (void) {

    std::unordered_map<std::string, int> combinations_score_map;
    
    // Part 1
    // combinations_score_map["A X"] = 1 + 3;
    // combinations_score_map["A Y"] = 2 + 6;
    // combinations_score_map["A Z"] = 3 + 0;

    // combinations_score_map["B X"] = 1 + 0;
    // combinations_score_map["B Y"] = 2 + 3;
    // combinations_score_map["B Z"] = 3 + 6;

    // combinations_score_map["C X"] = 1 + 6;
    // combinations_score_map["C Y"] = 2 + 0;
    // combinations_score_map["C Z"] = 3 + 3;

    // Part 2
    combinations_score_map["A X"] = 3 + 0;
    combinations_score_map["A Y"] = 1 + 3;
    combinations_score_map["A Z"] = 2 + 6;

    combinations_score_map["B X"] = 1 + 0;
    combinations_score_map["B Y"] = 2 + 3;
    combinations_score_map["B Z"] = 3 + 6;

    combinations_score_map["C X"] = 2 + 0;
    combinations_score_map["C Y"] = 3 + 3;
    combinations_score_map["C Z"] = 1 + 6;

    std::ifstream inputFile ("input.txt");

    if (inputFile.is_open()) {
        std::string line;
        int score = 0;

        while (std::getline(inputFile, line)) 
            score += combinations_score_map[line];
        
        inputFile.close();
        std::cout << "Total score: " << score << std::endl;
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}
