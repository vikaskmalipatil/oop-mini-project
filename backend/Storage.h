#pragma once
#include <fstream>
#include <sstream>
#include "Tracker.h"

class Storage {
public:
    static void save(const Tracker& tracker) {
        std::ofstream file("data.txt");

        for (const auto& u : tracker.users) {
            file << "USER," << u.name << "," << u.age << ","
                 << u.height << "," << u.weight << "\n";

            for (const auto& w : u.workouts) {
                file << "WORKOUT," << u.name << ","
                     << w.type << "," << w.duration << "," << w.calories << "\n";
            }
        }
    }

    static void load(Tracker& tracker) {
        std::ifstream file("data.txt");
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string tag; getline(ss, tag, ',');

            if (tag == "USER") {
                std::string name, ageS, hS, wS;
                getline(ss, name, ',');
                getline(ss, ageS, ',');
                getline(ss, hS, ',');
                getline(ss, wS, ',');

                tracker.addUser(Person(name, std::stoi(ageS), std::stof(hS), std::stof(wS)));
            }
            else if (tag == "WORKOUT") {
                std::string username, type, durS, calS;
                getline(ss, username, ',');
                getline(ss, type, ',');
                getline(ss, durS, ',');
                getline(ss, calS, ',');

                Person* p = tracker.getUser(username);
                if (p)
                    p->workouts.push_back(Workout(type, std::stoi(durS), std::stoi(calS)));
            }
        }
    }
};
