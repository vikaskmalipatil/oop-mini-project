#pragma once
#include <string>

class Workout {
public:
    std::string type;
    int duration;
    int calories;

    Workout(std::string t, int d, int c);
};
