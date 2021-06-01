#include "Disk.h"
#include <iostream>
#include <cstdlib>

using namespace std;




Disk::Disk(Vector2D x_y, Vector2D vx_vy, double r):
x_y(x_y) , vx_vy(vx_vy), r(r), m(3*r*r)
{


}


Disk::Disk(const Disk &d)
{
    this->x_y = d.x_y;
    this->vx_vy = d.vx_vy;
    this->m = d.m;
    this->r = d.r;

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
    return *this;
}

ostream &operator<<(ostream &out, const Disk& d) {

    out << "(" << d.x_y << ")";
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
//
//
//    cout << "Old VX: " << vx_vy.getX() << "\t And VY:" << vx_vy.getY() << "\t";
//    vx_vy.setX( vx_vy.getX() - 2*(d*(d * vx_vy.getX())) );
//    vx_vy.setY( vx_vy.getY() - 2*(d*(d*vx_vy.getY())) );
//    cout << "New VX: " << vx_vy.getX() << "\t New VY:" << vx_vy.getY() << "\t";

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

void Disk::setVX_VY(Vector2D newV) {
    vx_vy = newV;

}

const Vector2D &Disk::getXY() const {
    return x_y;
}

void Disk::setXY(const Vector2D &xY) {
    x_y = xY;
}




