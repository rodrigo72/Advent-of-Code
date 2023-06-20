#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <algorithm>

struct element {
    char c;
    int pos;
};

bool isEqual(const element& e1, const element& e2) {
    return e1.c == e2.c;
}

int main (void) {

    int marker_size = 14; // part 1 => 4; part 2 => 14
    std::ifstream inputFile("input.txt");
    std::deque<element> elements_deque;

    std::string line;
    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            for (int i = 0; i < line.length(); i++) {

                element e;
                e.c = line[i];
                e.pos = i;

                auto it = std::find_if(elements_deque.begin(), elements_deque.end(), [&](const element& element) {
                    return isEqual(element, e);
                });

                if (it != elements_deque.end()) { // Found
                    int found_pos = it->pos - elements_deque.front().pos;
                    for (int j = 0; j <= found_pos; j++) {
                        elements_deque.pop_front();
                    }
                    elements_deque.push_back(e);
                } else {
                    elements_deque.push_back(e);
                    if (elements_deque.size() == marker_size) {
                        std::cout << "Found after: " << (i + 1) << std::endl;
                        for (const auto& element : elements_deque) {
                            std::cout << element.c << " ";
                        }
                        std::cout << std::endl;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}

