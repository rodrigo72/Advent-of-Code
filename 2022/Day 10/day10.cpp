#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <sstream>

enum class instruction_type { ADDX, NOOP };

class instruction {
    public:
        virtual instruction_type get_type() const = 0;
        virtual std::string to_string() const = 0;
        virtual int execute() const = 0;
        virtual int get_tick_count() const = 0;
};

class noop : public instruction {
    public:
        noop () {}
        int get_tick_count() const { return 1; }
        instruction_type get_type() const { return instruction_type::NOOP; }
        int execute() const { return 0; }
        std::string to_string() const { return "noop"; }
};

class addx : public instruction {
    private:
        int value;
    public:
        addx (int value) : value(value) {}
        instruction_type get_type() const { return instruction_type::ADDX; }
        int get_tick_count() const { return 2; }
        int get_value() const { return value; }
        int execute() const { return value; }
        std::string to_string() const { return "addx "; }
};


int main (void) {

    std::ifstream input_file("input.txt");
    std::string line;

    std::vector<instruction *> instructions;

    while (std::getline(input_file, line)) {
        if (!line.empty()) {
            std::istringstream iss(line);
            std::string type_str;
            if (iss >> type_str) {
                if (type_str == "noop") {
                    instruction *n = new noop();
                    instructions.push_back(n);
                } else if (type_str == "addx") {
                    int value;
                    if (iss >> value) {
                        instruction *a = new addx(value);
                        instructions.push_back(a);
                    }
                }
            }
        }
    }

    int R = 1;
    int tick_count = 1;
    std::vector<int> signal_strength;

    for (auto i : instructions) {
        int aux = i->get_tick_count() + tick_count;
        for (; tick_count < aux; tick_count++) {
            if (tick_count == 20 || (tick_count > 20 && (tick_count - 20) % 40 == 0)) {
                signal_strength.push_back(R * tick_count);
            }
        }
        R += i->execute();
    }

    int total = 0;
    for (auto i : signal_strength) {
        total += i;
    }

    std::cout << total << std::endl; // Part 1

    return 0;
}