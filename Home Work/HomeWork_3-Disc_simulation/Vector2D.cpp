#include <cmath>
#include "Vector2D.h"
#include <iostream>

using namespace std;


Vector2D::Vector2D() {
    this->x = 8;
    this->y = 8;
}

Vector2D::Vector2D(double x, double y) {

    this->x = x;
    this->y = y;
    //cout << "x: " << x << " y : " << y << endl;
}

Vector2D Vector2D::operator+(const Vector2D &v2) {
    Vector2D p(x + v2.x,y + v2.y);
    return p;
}

Vector2D Vector2D::operator-(const Vector2D &v2) {
    Vector2D p(x - v2.x,y - v2.y);
    return p;
}

Vector2D Vector2D::operator*(double num) const {
    Vector2D p(x*num,y*num);
    return p;
}

double Vector2D::getNormal() {
    return sqrt((x*x)+(y*y));
}

ostream &operator<<(ostream &out, const Vector2D &vec) {

    out << vec.x << "," << vec.y;

    return out;
}

Vector2D Vector2D::operator/(double d2) {

    return *this * (1/d2) ;
}

double Vector2D::operator*(const Vector2D &v2) {
    return ((this->x * v2.x) + (this->y*v2.y));
}

Vector2D &Vector2D::operator=(const Vector2D &rhs) {
    if(*this == rhs)
        return *this;
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

