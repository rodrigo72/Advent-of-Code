#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>

enum class visibility           { visible,  not_visible };
enum class visibility_direction { up, down, left, right };

class tree {
    private:
        int height;
        visibility vis;
        std::map<visibility_direction, int> views; // direction -> distance
    
    public:
        tree (int height) : height(height), vis(visibility::not_visible) {
            views[visibility_direction::up   ] = 1;
            views[visibility_direction::down ] = 1;
            views[visibility_direction::left ] = 1;
            views[visibility_direction::right] = 1;
        }

        int get_height () const                                               { return height;                  }
        visibility get_visibility () const                                    { return vis;                     }
        void set_height (int height)                                          { this->height = height;          }
        void set_visibility (visibility vis)                                  { this->vis = vis;                }
        void add_direction (visibility_direction vis_direction, int distance) { views[vis_direction] = distance;}
        int get_view (visibility_direction vis_direction) const               { return views.at(vis_direction); }
};

int updateView (std::vector<tree *>& grid, visibility_direction direction, 
                int value0, int value1, int value2, int tallest,
                std::function<int(int)> inc, std::function<int(int)> calc) {

    if (tallest < grid[value0]->get_height()) {
        grid[value0]->set_visibility(visibility::visible);
        grid[value0]->add_direction(direction, value1);
        return grid[value0]->get_height();
    } else {
        int max = 0, aux = value2;
        while (grid[value0]->get_height() > grid[calc(aux)]->get_height()) {
            aux = inc(aux);
            max++; 
        }
        grid[value0]->add_direction(direction, max + 1);
    }
    return tallest;
}

int main (void) {

    std::ifstream input_file("input.txt");
    std::string line;
    int line_count = 0;
    int tree_count = 0;
    std::vector<tree *> grid(10000);

    while (std::getline(input_file, line)) {
        if (!line.empty()) {
            for (int i = 0; i < line.length(); i++) {
                tree *t = new tree(std::stoi(std::string(1, line[i])));
                if (line_count == 0) {
                    t->set_visibility(visibility::visible); 
                    t->add_direction(visibility_direction::up, 0);
                }
                if (input_file.eof()) {
                    t->set_visibility(visibility::visible);
                    t->add_direction(visibility_direction::down, 0);
                }
                if (i == 0) {
                    t->set_visibility(visibility::visible); 
                    t->add_direction(visibility_direction::left, 0);
                }
                if (i == line.length() - 1) {
                    t->set_visibility(visibility::visible); 
                    t->add_direction(visibility_direction::right, 0);
                }
                grid[line_count * line.length() + i] = t;
                tree_count++;
            }
            line_count++;
        }
    }

    input_file.close();
    int line_length = line.length();

    for (int line = 1; line < line_count - 1; line++) {
        int tallest_left = grid[line * line_length]->get_height();
        int tallest_right = grid[line * line_length + line_length - 1]->get_height();
        for (int col = 1; col < line_length - 1; col++) {
            tallest_left = updateView(grid, visibility_direction::left, line * line_length + col, col, col - 1, tallest_left,
            [](int aux) -> int { return aux + 1; }, [line, line_length](int aux) -> int { return line * line_length + aux; });

            tallest_right = updateView(grid, visibility_direction::right, line * line_length + line_length - col - 1, col, line_length - col, tallest_right,
            [](int aux) -> int { return aux - 1; }, [line, line_length](int aux) -> int { return line * line_length + aux; });
        }
    }

    for (int col = 1; col < line_length - 1; col++) {
        int tallest_up = grid[col]->get_height();
        int tallest_down = grid[(line_count - 1) * line_length + col]->get_height();
        for (int line = 1; line < line_count - 1; line++) {
            tallest_up = updateView(grid, visibility_direction::up, line * line_length + col, line, line - 1, tallest_up,
            [](int aux) -> int { return aux - 1; }, [line_length, col](int aux) -> int { return line_length * aux + col; });

            tallest_down = updateView(grid, visibility_direction::down, (line_count - line - 1) * line_length + col, line, line_count - line, tallest_down,
            [](int aux) -> int { return aux + 1; }, [line_length, col](int aux) -> int { return line_length * aux + col; });
        }
    }

    int count = 0;
    for (int i = 0; i < tree_count; i++)
        if (grid[i]->get_visibility() == visibility::visible) count++;
    std::cout << "Part 1: " << count << std::endl; // Part 1

    int max_view = 0;
    for (int i = 0; i < tree_count; i++) {
        int view = grid[i]->get_view(visibility_direction::right) * grid[i]->get_view(visibility_direction::left) *
                   grid[i]->get_view(visibility_direction::up)    * grid[i]->get_view(visibility_direction::down);
        if (view > max_view) max_view = view;
    }

    std::cout << "Part 2: " << max_view << std::endl; // Part 2

    for (auto& tree_ptr : grid) delete tree_ptr;
    grid.clear();
    return 0;
}