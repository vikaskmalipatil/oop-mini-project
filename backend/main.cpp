#include <iostream>
#include "SimpleServer.h"
#include "Tracker.h"
#include "Workout.h"
#include "Storage.h"

Tracker tracker;

std::string sendOK(std::string body) {
    return "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Type: text/plain\r\n\r\n" + body;
}

// Extract URL parameter
// std::string getParam(std::string req, std::string key) {
//     size_t pos = req.find(key + "=");
//     if (pos == std::string::npos) return "";
//     pos += key.length() + 1;
//     return req.substr(pos, req.find(" ", pos) - pos);
// }
std::string getParam(const std::string& req, const std::string& key) {
    size_t start = req.find(key + "=");
    if (start == std::string::npos) return "";

    start += key.length() + 1;
    size_t end = req.find_first_of("& \r\n", start);

    return req.substr(start, end - start);
}

std::string handle(std::string req) {

    // ADD USER
  if (req.find("POST /addUser") != std::string::npos) {

    std::string name = getParam(req, "name");
    std::string ageS = getParam(req, "age");
    std::string heightS = getParam(req, "height");
    std::string weightS = getParam(req, "weight");

    if (name == "" || ageS == "" || heightS == "" || weightS == "")
        return sendOK("Missing parameters");

    int age = std::stoi(ageS);
    float height = std::stof(heightS);
    float weight = std::stof(weightS);

    tracker.addUser(Person(name, age, height, weight));
    Storage::save(tracker);

    return sendOK("User Added: " + name);
}


    // ADD WORKOUT
 if (req.find("POST /addWorkout") != std::string::npos) {

    std::string name = getParam(req, "name");
    std::string type = getParam(req, "type");
    std::string durS = getParam(req, "duration");
    std::string calS = getParam(req, "calories");

    Person* p = tracker.getUser(name);
    if (!p) return sendOK("User does not exist");

    p->workouts.push_back(Workout(type, std::stoi(durS), std::stoi(calS)));
    Storage::save(tracker);

    return sendOK("Workout added to: " + name);
}


    // GET STATS
    if (req.find("GET /stats") != std::string::npos) {
        std::string name = getParam(req, "name");
        Person* p = tracker.getUser(name);
        if (!p) return sendOK("User not found");

        std::string out =
            "Name: " + p->name + "\n" +
            "BMI: " + std::to_string(p->getBMI()) + "\n" +
            "Workouts: " + std::to_string(p->workouts.size()) + "\n";

        return sendOK(out);
    }

    return sendOK("Invalid Request");
}

int main() {
    Storage::load(tracker);
    SimpleServer server;
    server.start(8080, handle);
}
