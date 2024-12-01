#include "Tile.h"

Tile::Tile() : plowed(false), watered(false), crop(nullptr) {}

void Tile::plow() {
    plowed = true;
}

void Tile::plant(Crop* newCrop) {
    if (plowed && crop == nullptr) {
        crop = newCrop;
    }
}

void Tile::water() {
    if (crop != nullptr) {
        watered = true;
    }
}

bool Tile::isPlanted() const {
    return crop != nullptr;
}

bool Tile::isHarvestable() const {
    return crop != nullptr && crop->isMature();
}

Crop* Tile::getCrop() const {
    return crop;
}
