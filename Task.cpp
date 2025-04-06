//
// Created by Rasul Mammadov on 06.04.25.
//


#include "Task.h"
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>

using std::vector, std::string, std::ofstream,std::ifstream;

void saveTasks(const vector<Task> &tasks, const string &filename = "tasks.txt") {
    ofstream ostream(filename);
    ostream << tasks.size();

    for (const auto &task: tasks) {
        string description = task.description;
        std::replace(description.begin(), description.end(), ' ', '_');

        ostream << "\n" << description << ' ' << task.done;
    }
    ostream.close();
}

vector<Task> loadTasks(const string &filename) {
    if (!std::filesystem::exists(filename)) {
        return vector<Task>();
    }

    vector<Task> tasks;
    ifstream istream(filename);

    int n;
    istream >> n;

    for (int i = 0; i < n; i++) {
        string description;
        bool done;

        istream >> description >> done;
        std::replace(description.begin(), description.end(), '_', ' ');
        tasks.push_back(Task(description, done));
    }
    istream.close();
    return tasks;
}
