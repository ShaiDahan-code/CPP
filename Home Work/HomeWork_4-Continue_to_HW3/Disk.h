#ifndef EX_3_DISK_H
#define EX_3_DISK_H
#include "Vector2D.h"
#include <iostream>
#include <cstdlib>
#include "Wall.h"
#include <string>

using namespace std;

class Disk {

private:
    Vector2D x_y;
    Vector2D vx_vy;
    double r;
    double m;
    bool wasCollision;
    string type;

public:
    //Constructors
    Disk(Vector2D& x_y, Vector2D& vx_vy, double r,double mass);

    /* big three */
    Disk(const Disk& d); // copy c'tor
    virtual Disk& operator=(Disk &other);
    virtual ~Disk();

    //set spot of the disc
    void setSpot(double dT);

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

    virtual Disk* clone() const {return new Disk(*this);}

    //Special command that make on every kind of disc something different
    virtual int special_commend();

    //Setters
    void setXY(const Vector2D &xY);
    void setR(double radius) { this->r = radius;}
    virtual void setWasCollision(bool wasCollision);

    //Getters
    virtual bool isWasCollision() const;
    virtual double getR() const { return r;}
    virtual const string getType() const { return type;}
    virtual const Vector2D &getVxVy() const {return vx_vy;}
    virtual double getM() const { return m;}
    const Vector2D &getXY() const;


    //Operators
    friend ostream& operator<<(ostream& out, const Disk& disk);
    friend bool operator==(const Disk& d1,const Disk& d2);
    friend bool operator!=(const Disk& d1,const Disk& d2);
};
#endif //EX_3_DISK_H
