#ifndef EX_3_WALL_H
#define EX_3_WALL_H

#include <iostream>
#include "Vector2D.h"

using namespace std;

class Wall {
private:
    Vector2D p1 ;
    Vector2D p2;
public:
    //Constructor
    Wall();
    Wall(Vector2D x1_y1,Vector2D x2_y2);

    //3 Big
    Wall(const Wall& w);
    Wall& operator=(Wall &other);
    ~Wall(){}

    //Getters and Setters
    const Vector2D getP1() const;
    void setP1(const Vector2D p1);
    const Vector2D getP2() const;
    void setP2(const Vector2D p2);

    //Operators
    friend bool operator==(const Wall& d1,const Wall& d2);
    friend bool operator!=(const Wall& d1,const Wall& d2);
};


#endif //EX_3_WALL_H
