#include <fstream>
#include <memory>

#include "Task.cpp"

class TaskManager {
   private:
    using TaskPtr = std::unique_ptr<Task>;
    std::vector<TaskPtr> vector;

   public:
    TaskManager() {
        std::fstream file("data.json");
        if (file.is_open()) {
            nlohmann::json jsonData;
            file >> jsonData;
            for (const auto &item : jsonData) {
                TaskPtr task = std::make_unique<Task>();
                task->fromJson(item);
                vector.push_back(std::move(task));
            }
        }
    }

    ~TaskManager() {
        if (!vector.empty()) {
            std::ofstream file("data.json", std::ios::out, std::ios::trunc);
            nlohmann::json jsonData;
            for (const TaskPtr &task : vector) {
                jsonData.push_back(task->toJson());
            }
            file << jsonData.dump(4);
        }
    }

    void addTask(std::string &&name, Priority priority, int hours) {
        TaskPtr task = std::make_unique<Task>(name, priority, hours, true);
        vector.push_back(std::move(task));
        // if (vector.size() > 1) {
        //     std::sort(
        //         vector.begin(), vector.end(),
        //         [](const TaskPtr &l, const TaskPtr &r) {
        //             if (!l || !r) {
        //                 throw std::runtime_error("Null pointer in sorting");
        //             }
        //             return *l < *r;
        //         });
        // }
    }

    const std::vector<TaskPtr> &getAllTask() const { return vector; }

    void taskCompleted(size_t taskId) {
        if (taskId < vector.size()) {
            vector.at(taskId)->setIsActive(false);
        } else {
            throw std::out_of_range("Task ID out of range");
        }
    }

    void deleteTask(size_t taskId) {
        if (taskId < vector.size()) {
            vector.erase(vector.begin() + taskId);
        } else {
            throw std::out_of_range("Task ID out of range");
        }
    }
};
