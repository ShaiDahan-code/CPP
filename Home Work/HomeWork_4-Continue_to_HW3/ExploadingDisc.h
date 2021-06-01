#ifndef COMPARE_OUTPUTS_PY_EXPLOADINGDISC_H
#define COMPARE_OUTPUTS_PY_EXPLOADINGDISC_H

#include <iostream>
#include "Disk.h"
#include <string>

class ExploadingDisc : public Disk{

private:
    Vector2D vx_vy;
    double r;
    double m;
    int counter;
    bool wasCollision;
    string type;

public:
    //Constructors
    ExploadingDisc(Vector2D x_y, Vector2D vx_vy, double r, int counter,double m);

    /* big three */
    ExploadingDisc(const ExploadingDisc& d); // copy c'tor
    ExploadingDisc& operator=(ExploadingDisc &other);

    virtual ExploadingDisc* clone() const {return new ExploadingDisc(*this);}

    ~ExploadingDisc() {}

    //Special command that make on every kind of disc something different
    virtual int special_commend();

    //Getters
    int getCounter() const { return counter;}
    virtual const string getType() const { return type;}
    virtual double getM() const {return this->m;}

};


#endif //COMPARE_OUTPUTS_PY_EXPLOADINGDISC_H
