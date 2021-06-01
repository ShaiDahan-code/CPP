#ifndef COMPARE_OUTPUTS_PY_SHRINKINGDISC_H
#define COMPARE_OUTPUTS_PY_SHRINKINGDISC_H
#include "Disk.h"
#include "List_Disk.h"
#include <string>

class ShrinkingDisc : public Disk {
private:
    Vector2D vx_vy;
    double r;
    double m;
    int counter;
    bool wasCollision;
    string type;
public:
    //Constructors
    ShrinkingDisc(Vector2D x_y, Vector2D vx_vy, double r);

    /* big three */
    ShrinkingDisc(const ShrinkingDisc& d); // copy c'tor
    ShrinkingDisc& operator=(ShrinkingDisc &other);

    virtual ShrinkingDisc* clone() const { return new ShrinkingDisc(*this);}

    ~ShrinkingDisc() {}

    //Special command that make on every kind of disc something different
    virtual int special_commend();

//    //Setters
    void setWasCollision(bool wasIt);
    //void setM1(double m) { this->m = m;}


    //Getter
    int getCounter() const {return counter;}
    bool isWasCollision() const;
    virtual const string getType() const { return type;}

};


#endif //COMPARE_OUTPUTS_PY_SHRINKINGDISC_H
