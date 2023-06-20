#include <iostream>
#include <fstream>
#include <string>
#include <queue>

// << "put to"
// using namespace std; // std::cout => cout // make names from std visible without the std:: prefix
// cout // output stream object, used to output to the standard output device, which is usually the display screen/ terminal

struct Elf {
    int number;
    int total_kal;
};

struct CompareElf {
    bool operator() (Elf const& e1, Elf const& e2) {
        return e1.total_kal < e2.total_kal;
    }   
};

int main (void) {
    
    std::priority_queue<Elf, std::vector<Elf>, CompareElf> elvesPQ;
    std::ifstream inputFile ("input.txt");

    if (inputFile.is_open()) {
        // File opened successfully
        std::string line;
        int accumulator = 0;
        int elfNumber = 1;

        while (std::getline(inputFile, line)) {
            if (!line.empty()) {
                accumulator += std::stoi(line);
            } else {
                if (accumulator != 0) {
                    elvesPQ.push({elfNumber, accumulator});
                    accumulator = 0;
                    elfNumber++;
                }
            }
        }

        if (accumulator != 0) {
            elvesPQ.push({elfNumber, accumulator});
        }

        inputFile.close();


        int top3_total_kal = 0;
        for (int i = 0; i < 3; i++) {
            top3_total_kal += elvesPQ.top().total_kal;
            elvesPQ.pop();
        }

        std::cout << "Total kal of the top 3 elves: " << top3_total_kal << std::endl;

        // while (!elvesPQ.empty()) {
        //     Elf elf = elvesPQ.top();
        //     elvesPQ.pop();
        //     std::cout << "Elf number: " << elf.number << " - Total kal: " << elf.total_kal << std::endl;
        // }
        
    } else {
        // Error opening file
        std::cout << "Unable to open file" << std::endl;
    }

}