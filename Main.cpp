#include <iostream>
#include <crow.h>
#include "TaskManager.cpp"

int main() {
    crow::SimpleApp app;

    // Базовый маршрут
    CROW_ROUTE(app, "/")([]() {
        return "Hello, Crow!";
    });

    app.port(8080).multithreaded().run();
}
