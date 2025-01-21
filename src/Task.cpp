#include <chrono>
#include <stdexcept>
#include <string>

#include "nlohmann/json.hpp"

enum class Priority { LOW, MIDDLE, HIGH };

class Task {
   private:
    std::string name;
    Priority priority;
    int hours;
    bool isActive;
    std::chrono::system_clock::time_point start;

    static std::string priorityToString(Priority _priority) {
        switch (_priority) {
            case Priority::LOW:
                return "Low";
            case Priority::MIDDLE:
                return "Middle";
            case Priority::HIGH:
                return "High";
            default:
                throw std::invalid_argument("Invalid priority value");
        }
    }

   public:
    Task()
        : name("Untitled"),
          priority(Priority::LOW),
          hours(0),
          isActive(false),
          start(std::chrono::system_clock::now()) {}

    Task(std::string name, Priority priority, int hours, bool isActive)
        : name(std::move(name)),
          priority(priority),
          isActive(isActive),
          start(std::chrono::system_clock::now()) {
        if (hours < 0) {
            throw std::invalid_argument("Hours cannot be negative");
        }
        this->hours = hours;
    }

    ~Task() = default;

    nlohmann::json toJson() const {
        auto time = std::chrono::duration_cast<std::chrono::seconds>(
                        start.time_since_epoch())
                        .count();
        return {{"name", name},
                {"priority", priorityToString(priority)},
                {"hours", hours},
                {"isActive", isActive},
                {"start", time}};
    }

    static Priority stringToPriority(const std::string &str) {
        if (str == "Low") return Priority::LOW;
        if (str == "Middle") return Priority::MIDDLE;
        if (str == "High") return Priority::HIGH;
        throw std::invalid_argument("Invalid priority string");
    }

    void fromJson(const nlohmann::json &j) {
        name = j.at("name").get<std::string>();
        priority = stringToPriority(j.at("priority").get<std::string>());
        hours = j.at("hours").get<int>();
        isActive = j.at("isActive").get<bool>();
        start = std::chrono::system_clock::time_point(
            std::chrono::seconds(j.at("start").get<long long>()));
    }

    void setStartTime(const std::chrono::system_clock::time_point &time) {
        start = time;
    }

    std::chrono::system_clock::time_point getStartTime() const { return start; }

    bool operator<(const Task &other) const {
        if (priority != other.priority) return priority < other.priority;
        return hours < other.hours;
    }

    const std::string &getName() const { return name; }

    void setName(const std::string &newName) { name = newName; }

    Priority getPriority() const { return priority; }

    void setPriority(Priority newPriority) { priority = newPriority; }

    int getHours() const { return hours; }

    void setHours(int newHours) {
        if (newHours < 0) {
            throw std::invalid_argument("Hours cannot be negative");
        }
        hours = newHours;
    }

    bool getIsActive() const { return isActive; }

    void setIsActive(bool newIsActive) { isActive = newIsActive; }

    std::string toString() const {
        std::ostringstream oss;
        auto timeT = std::chrono::system_clock::to_time_t(start);

        std::tm tm;
#if defined(_WIN32)
        localtime_s(&tm, &timeT);
#else
        localtime_r(&timeT, &tm);
#endif
        oss << "Task: " << name << "\n"
            << "Priority: " << priorityToString(priority) << "\n"
            << "Hours: " << hours << "\n"
            << "Active: " << (isActive ? "Yes" : "No") << "\n"
            << "Start: " << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "\n";
        return oss.str();
    }
};
