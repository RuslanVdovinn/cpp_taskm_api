#include <crow.h>

#include <iostream>
#include <nlohmann/json.hpp>

#include "TaskManager.cpp"

int main() {
    crow::SimpleApp app;

    TaskManager manager;

    // Get all tasks
    CROW_ROUTE(app, "/tasks")
    ([&manager]() {
        nlohmann::json response;
        for (const auto& task : manager.getAllTask()) {
            response.push_back(task->toJson());
        }
        return crow::response(response.dump());
    });

    // Add task
    CROW_ROUTE(app, "/tasks/add")
        .methods("POST"_method)([&manager](const crow::request& req) {
            auto json = nlohmann::json::parse(req.body);
            manager.addTask(json["name"],
                            Task::stringToPriority(json["priority"]),
                            json["hours"]);
            return crow::response(201);
        });

    // Delete task
    CROW_ROUTE(app, "/tasks/<int>/delete")
        .methods("DELETE"_method)([&manager](int id) {
            try {
                manager.deleteTask(id);
                return crow::response(200);
            } catch (const std::out_of_range&) {
                return crow::response(404, "Task not found");
            }
        });

    app.port(8080).multithreaded().run();
}
