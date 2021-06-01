#include "Disk.h"

#include <iostream>

using namespace std;




Disk::Disk(Vector2D& x_y, Vector2D& vx_vy, double r,double mass):
x_y(x_y) , vx_vy(vx_vy), r(r), m(mass), wasCollision(false), type("Normal")
{}


Disk::Disk(const Disk &d)
{
    this->x_y = d.x_y;
    this->vx_vy = d.vx_vy;
    this->m = d.m;
    this->r = d.r;
    wasCollision = d.wasCollision;
    type = "Normal";
}
bool operator==(const Disk& d1,const Disk& d2){
    return ( (d1.x_y == d2.x_y) && (d1.vx_vy == d2.vx_vy) && (d1.r == d2.r) );
}
//For compare in the LinkedLst_Disk!
bool operator!=(const Disk& d1,const Disk& d2){
    return !(d1 == d2);
}

Disk &Disk::operator=(Disk &other) {
    if(this == &other){
        return *this;
    }
    this->x_y = other.x_y;
    this->vx_vy = other.vx_vy;
    this->r = other.r;
    this->m = other.m;
    wasCollision = false;
    type = other.type;
    return *this;
}

ostream &operator<<(ostream &out, const Disk& d) {
    out << "(" << d.x_y << ")" << "/" << d.r;
    return out;
}

Disk::~Disk() {

}

void Disk::updateSpeedAfterWall(Wall &w2) {

    Vector2D q = findClosePoint(w2.getP2(),w2.getP1());
    Vector2D p =x_y;
    Vector2D d = (p - q) / ((p - q).getNormal());
    Vector2D v =vx_vy;
    double two = 2;

    Vector2D new_speed =v - ((d * (v * d)) * two);

    vx_vy = new_speed;

}

void Disk::setSpot(double dT) {
    double set_y = x_y.getY()+ vx_vy.getY()*dT;
    double set_x = x_y.getX()+ vx_vy.getX()*dT;
    x_y.setX(set_x);
    x_y.setY(set_y);

}


bool Disk::checkCollision(Disk &d2) {
    Vector2D p = x_y;
    Vector2D p_tag = d2.x_y;
    return (((p-p_tag).getNormal()) <= r+d2.r);
}

void Disk::updateSpeed(Disk &d2) {
    Vector2D p = x_y;
    Vector2D p_tag = d2.x_y;

    Vector2D v = vx_vy;
    Vector2D v_tag = d2.vx_vy;

    double mass = m;
    double mass_tag = d2.m;

    double normal =  (p - p_tag).getNormal();
    Vector2D d =  (p - p_tag) / normal;

    Vector2D delta = d * ( (v- v_tag) * d );
    Vector2D v_new = v - ( delta*( (2*mass_tag) / ((mass + mass_tag)) ) );
    Vector2D v_tag_new =v_tag +  (delta*((2*mass) / (mass + mass_tag) ) );
    //cout << "mass: " << mass << "\tp :" << p << "\tv: " << v << "\tv_new: " << v_new << endl;
    //cout << "mass_tag: " << mass_tag << "\tp_tag :" << p_tag << "\tv_tag: " << v_tag << "\tv_tag_new: " << v_tag_new <<endl;
    vx_vy = v_new;
    d2.vx_vy = v_tag_new;
}

Vector2D Disk::findClosePoint(Vector2D p1, Vector2D p2) {
    Vector2D P1 = p1;
    Vector2D P2 = p2;
    Vector2D P = x_y;

    if(P1 == P2) {
        return P2;
    }
    else {
        double z =(P1 - P2).getNormal();
        double a = ((P - P1) * (P2 - P1)) / (z*z);
        if (a < 0)
            return P1;
        else if (a > 1)
            return P2;
        else
            return P1 + ((P2 - P1)*a) ;
    }
}

bool Disk::checkCollisionWall(Wall &w2) {
    Vector2D q = findClosePoint(w2.getP2(),w2.getP1());
    Vector2D p = x_y;
    return ( (p - q).getNormal() <= r );
}


const Vector2D &Disk::getXY() const {
    return x_y;
}

void Disk::setXY(const Vector2D &xY) {
    this->x_y = xY;
}

bool Disk::isWasCollision() const {
    return wasCollision;
}

void Disk::setWasCollision(bool wasCollision1) {
    this->wasCollision = wasCollision1;
}

int Disk::special_commend() {
    wasCollision = false;
    return 0;
}




