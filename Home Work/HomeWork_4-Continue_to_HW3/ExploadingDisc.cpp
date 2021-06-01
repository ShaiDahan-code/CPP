#include "ExploadingDisc.h"

ExploadingDisc::ExploadingDisc(Vector2D x_y, Vector2D vx_vy, double r, int counter,double m) : Disk(x_y, vx_vy, r,m) ,m(m), counter(counter) , wasCollision(false),
                                type("Exploading"){}

ExploadingDisc::ExploadingDisc(const ExploadingDisc &d) : Disk(d) ,m(d.m), counter(d.counter), wasCollision(false), type("Exploading"){}

ExploadingDisc &ExploadingDisc::operator=(ExploadingDisc &other) {
    if(this == &other){
        return *this;
    }
    this->vx_vy = other.vx_vy;
    this->r = other.r;
    this->m = other.m;
    counter = other.getCounter();
    wasCollision = other.wasCollision;
    this->type = other.type;
    return *this;
}


int ExploadingDisc::special_commend() {
    counter++;
    wasCollision = false;
    return counter;
}







