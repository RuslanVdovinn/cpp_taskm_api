#include <fstream>
#include "Task.cpp"

class TaskManager {
private:
    std::vector<Task> vector;

public:

    TaskManager() {
        std::fstream file("data.json");
        if (file.is_open()) {
            nlohmann::json jsonData;
            file >> jsonData;
            for (const auto &item : jsonData) {
                Task task;
                task.fromJson(item);
                vector.push_back(task);
            }
        }
    }

    ~TaskManager() {
        if (!vector.empty()) {
            std::ofstream file("data.json", std::ios::out, std::ios::trunc);
            nlohmann::json jsonData;
            for (const Task &task : vector) {
                jsonData.push_back(task.toJson());
            }
            file << jsonData.dump(4);
        }
    }

    void addTask(std::string &&name, Priority priority, int hours) {
        Task task(name, priority, hours, true);
        vector.push_back(task);
        std::sort(vector.begin(), vector.end(), [](const Task &l, const Task &r) { return l < r; });
    }

    const std::vector<Task> getAllTask() const {
        return vector;
    }

    void taskCompleted(size_t taskId) {
        if (taskId < vector.size()) {
            vector.at(taskId).setIsActive(false);
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
