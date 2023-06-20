#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

enum class Direction {
    RIGHT, LEFT, UP, DOWN
};

std::string direction_to_string (Direction direction) {
    switch (direction) {
        case Direction::RIGHT: return "RIGHT";
        case Direction::LEFT: return "LEFT";
        case Direction::UP: return "UP";
        case Direction::DOWN: return "DOWN";
        default: return "UNKNOWN";
    }
}

struct Order {
    Direction direction;
    uint32_t count;
    
    friend std::istream& operator>>(std::istream& s, Order& order) {
        char dir;
        if (s >> dir >> order.count) switch (dir) {
            case 'R': order.direction = Direction::RIGHT; break;
            case 'L': order.direction = Direction::LEFT; break;
            case 'U': order.direction = Direction::UP; break;
            case 'D': order.direction = Direction::DOWN; break;
            default: throw std::runtime_error("Invalid direction");
        }
        return s;
    }
};

struct Position {
    int row;
    int col;
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

namespace std {
    template <>
    struct hash<Position> {
        size_t operator()(const Position& pos) const {
            return std::hash<int>{}(pos.row) ^ (std::hash<int>{}(pos.col) << 1);        
        }
    };
}

void single_step (Position& head, Direction direction) {
    switch (direction) {
        case Direction::DOWN:  head.row--; break;
        case Direction::UP:    head.row++; break;
        case Direction::LEFT:  head.col--; break;
        case Direction::RIGHT: head.col++; break;
    }
};

void follow_step (Direction dir, Position& head, Position& tail) {
    int row_difference = head.row - tail.row;
    int col_difference = head.col - tail.col;

    if (abs(row_difference) >= 2) {
        tail.row += row_difference / 2;
        if (abs(col_difference) >= 2) tail.col += col_difference / 2;
        else tail.col += col_difference;
    } else if (abs(col_difference) >= 2) {
        tail.col += (col_difference) / 2;
        if (abs(row_difference) >= 2) tail.row += row_difference / 2;
        else tail.row += row_difference;
    }
}

size_t simulate_motions (const std::vector<Order>& orders) {
    Position head { 0, 0 }, tail {0, 0};    
    std::unordered_set<Position> visited{{ 0, 0 }};
    auto single_order = [&](const Order& order) {
        for (size_t i = 0; i < order.count; i++) {
            single_step(head, order.direction);
            follow_step(order.direction, head, tail);
            visited.insert(tail);
        }
    };
    for (const auto& order : orders) single_order(order);
    return visited.size();
}

size_t simulate_motions_extended (const std::vector<Order>& orders) {
    std::vector<Position> rope(10, { 0, 0 });
    std::unordered_set<Position> visited{{ 0, 0 }};
    auto single_order = [&](const Order& order) {
        for (size_t i = 0; i < order.count; i++) {
            single_step(rope[0], order.direction);
            for (size_t j = 1; j < rope.size(); j++) {
                follow_step(order.direction, rope[j-1], rope[j]);
            }
            visited.insert(rope[9]);
        }
    };
    for (const auto& order : orders) single_order(order);
    return visited.size();
}

int main (void) {

    std::fstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open input file\n";
        return 1;
    }

    std::vector<Order> orders;
    Order order;
    while (file >> order) {
        orders.push_back(order);
    }

    std::cout << simulate_motions(orders) << std::endl; // Part 1
    std::cout << simulate_motions_extended(orders) << std::endl; // Part 2
    return 0;
}