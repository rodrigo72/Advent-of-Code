#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <exception>
#include <limits>

class LoopException : public std::exception {
    private:
        std::string message;
    public:
        LoopException(const std::string& errorMessage) : message(errorMessage) {}
        const char* what() const noexcept override { return message.c_str(); }
};

class file_system_element {
    public: 
        virtual std::string get_name() const = 0;
        virtual int get_size() const = 0;
};

class file : public file_system_element {
    private:
        std::string name;
        int size;

    public:
        file (std::string name, int size) : name (name), size (size) {}
        std::string get_name () const { return name; }
        int get_size () const { return size; }
        std::string to_string() { return name + " " + std::to_string(size) + "\n"; }
};

class directory : public file_system_element {
    private:
        std::string name;
        std::map<std::string, file *> files;
        directory *parent_dir;
        std::map<std::string, directory *> child_dirs;
        int size;

    public:
        directory (std::string name) : name (name), parent_dir(nullptr), size(0) {}
        std::string get_name () const { return name; }
        int get_size () const { return size; }
        std::map<std::string, file *> get_files () const { return files; }
        std::map<std::string, directory *> get_child_dirs () const { return child_dirs; }

        std::vector<directory *> get_all_child_dirs () const {
            std::vector<directory *> result;
            for (auto element : child_dirs) {
                result.push_back(element.second);
                std::vector<directory *> subdirs = element.second->get_all_child_dirs();
                result.insert(result.end(), subdirs.begin(), subdirs.end());
            }
            return result;
        }

        void add_file (file *element) {
            if (files.find(element->get_name()) == files.end()) {
                files.insert({element->get_name(), element});
            }
        }

        void add_child_dir (directory *dir) {
            if (check_loop(dir)) {
                throw LoopException("LOOP");
                return;
            }
            if (child_dirs.find(dir->get_name()) == child_dirs.end()) {
                child_dirs.insert({dir->get_name(), dir});
                dir->set_parent_dir(this);
            }
        }

        directory * find_child (std::string name) {
            if (child_dirs.find(name) != child_dirs.end()) {
                return child_dirs[name];
            }
            return nullptr;
        }

        void set_parent_dir (directory *dir) { parent_dir = dir; }
        directory *get_parent_dir () const { return parent_dir; }

        int update_size (int i) {
            int result = 0;
            if (i < 10000) {
                for (auto element : files) 
                    result += element.second->get_size();
                for (auto element : child_dirs) 
                    result += element.second->update_size(i+1);
            }
            size = result;
            return result;
        }

        directory * dir_to_remove (int total_space, int used_space, int free_space_needed) {
            int current_free_space = total_space - used_space;
            if (current_free_space >= free_space_needed) {
                return nullptr;
            }

            directory *chosen_dir = this;
            int result_min = std::numeric_limits<int>::max();

            for (auto dir : get_all_child_dirs()) {
                int calc = current_free_space + dir->get_size();
                if (calc >= free_space_needed) {
                    if (calc < result_min) {
                        result_min = calc;
                        chosen_dir = dir;
                    }
                }
            }
            return chosen_dir;
        }

    private:
        bool check_loop (directory *dir) {
            if (dir == this) return true;
            if (parent_dir == nullptr) return false;
            return parent_dir->check_loop(dir);
        }
};

int main (void) {
    
    std::ifstream input_file("input.txt");
    std::string line;

    directory *root = nullptr;
    directory *current_directory = nullptr;

    int line_count = 1;
    bool ls_mode = false;

    while (std::getline(input_file, line)) {
        if (!line.empty()) {

            std::istringstream iss(line);
            std::vector<std::string> words;
            std::string word;

            while (std::getline(iss, word, ' ')) {
                words.push_back(word);
            }

            if (words[0] == "$") {
                ls_mode = false;
                if (words[1] == "cd") {
                    directory *found;
                    if (words[2] == "..") {
                        if (current_directory == root) {
                            continue;
                        } else {
                            current_directory = current_directory->get_parent_dir();
                        }
                    } else if (current_directory == nullptr) {
                        current_directory = new directory(words[2]);
                        root = current_directory;
                    } else if ((found = current_directory->find_child(words[2])) == nullptr) {
                        directory *new_dir = new directory(words[2]);
                        try {
                            current_directory->add_child_dir(new_dir);
                            current_directory = new_dir;
                        } catch (const LoopException& e) {
                            std::cout << "(1) " << e.what() << " line: " << line_count << " " << line << std::endl;
                        }
                    } else {
                        current_directory = found;
                    }
                } else if (words[1] == "ls") {
                    ls_mode = true;
                }
            } else if (ls_mode) {
                if (words[0] == "dir") {
                    if (current_directory->find_child(words[1]) == nullptr) {
                        try {
                            directory *new_dir = new directory(words[1]);
                            current_directory->add_child_dir(new_dir);
                        } catch (const LoopException& e) {
                            std::cout << "(2) " << e.what() << " line: " << line_count << " " << line << std::endl;
                        }
                    }
                } else {
                    try {
                        int size = std::stoi(words[0]);
                        file *new_file = new file(words[1], size);
                        current_directory->add_file(new_file);
                    } catch (const std::exception& e) {
                        std::cout << "error" << std::endl;
                    }
                }
            }
        }
        line_count++;
    }
    
    input_file.close();
    root->update_size(0);

    int total_size = 0;
    for (auto element : root->get_all_child_dirs())
        if (element->get_size() <= 100000)
            total_size += element->get_size();

    std::cout << "Part 1: " << total_size << std::endl;

    int total_space = 70000000;
    int free_space_needed = 30000000;
    int used_space = root->get_size();

    directory *dir_to_remove = root->dir_to_remove(total_space, used_space, free_space_needed);

    std::cout << "Part 2: " << dir_to_remove->get_size() << std::endl;
    return 0;
}