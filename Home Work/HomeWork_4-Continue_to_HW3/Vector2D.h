#ifndef EX_3_VECTOR2D_H
#define EX_3_VECTOR2D_H
#include <iostream>

using namespace std;

class Vector2D {
private:

    double x,y;
public:
    //Constructors
    Vector2D();
    Vector2D(double x,double y);

    //Vector2D(Vector2D &v2);
    Vector2D& operator=(const Vector2D& rhs);
    ~Vector2D(){}

    //Getters and Setters
    double getX() {return x;}
    double getY() {return y;}
    void setX(double x1) { this->x = x1;}
    void setY(double y1) { this->y = y1;}

    //Get the Normal of the Point
    double getNormal();

    //Operators
    Vector2D operator+(const Vector2D& v2);
    Vector2D operator-(const Vector2D& v2);
    Vector2D operator*(double num) const;
    double operator*(const Vector2D& v2);
    Vector2D operator/(double d2);
    friend ostream& operator<<(ostream& out, const Vector2D& disk);
    friend bool operator==(const Vector2D& v1,const Vector2D& v2) {return ( (v1.x == v2.x) && (v1.y == v2.y) );}
    friend bool operator!=(const Vector2D& v1,const Vector2D& v2) {return !(v1 == v2);}

};


#endif //EX_3_VECTOR2D_H
