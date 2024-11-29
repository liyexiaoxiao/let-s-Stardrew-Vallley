#include "Crop.h"

Crop::Crop(const std::string& name, int growthTime)
    : name(name), growthTime(growthTime), currentAge(0) {}

void Crop::grow() {
    if (currentAge < growthTime) {
        ++currentAge;
    }
}

bool Crop::isMature() const {
    return currentAge >= growthTime;
}

std::string Crop::getName() const {
    return name;
}
