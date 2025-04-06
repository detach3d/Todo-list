//
// Created by Rasul Mammadov on 06.04.25.
//

#ifndef TASK_H
#define TASK_H

#include <vector>
#include <string>

class Task {
public:
    std::string description;
    bool done;
};

void saveTasks(const std::vector<Task> &tasks, const std::string& filename);
std::vector<Task> loadTasks(const std::string& filename);


#endif //TASK_H
