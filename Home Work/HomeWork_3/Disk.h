#ifndef EX_3_DISK_H
#define EX_3_DISK_H
#include "Vector2D.h"
#include <iostream>
#include <cstdlib>
#include "Wall.h"

using namespace std;

class Disk {
private:
    Vector2D x_y;
    Vector2D vx_vy;
    double r;
    double m;
public:
    //Constructors
    Disk(Vector2D x_y, Vector2D vx_vy, double r);

    /* big three */
    Disk(const Disk& d); // copy c'tor
    Disk& operator=(Disk &other);
    ~Disk();

    //set spot of the disc
    void setSpot(double dT);

    //Get x_y Vector2D
    const Vector2D &getXY() const;

    //Find the close point of disc and wall
    Vector2D findClosePoint(Vector2D p1,Vector2D p2);

    //Update the speed after collision with other disc
    void updateSpeed(Disk &d2);

    //Update the speed of the disc after collision with wall
    void updateSpeedAfterWall(Wall &w2);

    //Check if there is a collision between 2 Disc or not
    bool checkCollision(Disk &d2);

    //Check collision between disc and wall
    bool checkCollisionWall(Wall &w2);

    //Setters
    void setVX_VY(Vector2D newV);
    void setXY(const Vector2D &xY);

    //Operators
    friend ostream& operator<<(ostream& out, const Disk& disk);
    friend bool operator==(const Disk& d1,const Disk& d2);
    friend bool operator!=(const Disk& d1,const Disk& d2);

};




#endif //EX_3_DISK_H
