#include "ShrinkingDisc.h"


ShrinkingDisc::ShrinkingDisc(Vector2D x_y, Vector2D vx_vy, double r) : Disk(x_y, vx_vy, r,r*r) , counter(0) , wasCollision(false),type("Shrinking") {}

ShrinkingDisc::ShrinkingDisc(const ShrinkingDisc &d) : Disk(d) , counter(d.counter), wasCollision(false),type("Shrinking"){}

ShrinkingDisc &ShrinkingDisc::operator=(ShrinkingDisc &other) {
    if(this == &other){
        return *this;
    }
    this->vx_vy = other.vx_vy;
    this->r = other.r;
    this->m = other.m;
    counter = other.getCounter();
    wasCollision = other.wasCollision;
    type = other.type;

    return *this;
}


void ShrinkingDisc::setWasCollision(bool wasIt) {
    wasCollision = wasIt;
}

bool ShrinkingDisc::isWasCollision() const {
    return wasCollision;
}

int ShrinkingDisc::special_commend() {
    Disk::setR(Disk::getR()*0.9);
    counter++;
    wasCollision = false;
    return counter;
}








