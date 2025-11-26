#include "Person.h"

Person::Person(std::string n, int a, float h, float w)
    : name(n), age(a), height(h), weight(w) {}

float Person::getBMI() const {
    return weight / (height * height);
}
