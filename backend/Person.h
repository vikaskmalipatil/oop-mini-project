#pragma once
#include <string>
#include <vector>
#include "Workout.h"

class Person {
public:
    std::string name;
    int age;
    float height;
    float weight;
    std::vector<Workout> workouts;

    Person(std::string n, int a, float h, float w);
    float getBMI() const;
};
