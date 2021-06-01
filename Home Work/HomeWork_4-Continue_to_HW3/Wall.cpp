#include "Wall.h"

using namespace std;

Wall::Wall():
p1(0,0),p2(0,0)
{}

Wall::Wall(Vector2D x1_y1,Vector2D x2_y2){
    this->p1 = x1_y1;
    this->p2 = x2_y2;
}

Wall::Wall(const Wall& w){
    this->p1 = w.p1;
    this->p2 = w.p2;
}



bool operator==(const Wall& w1,const Wall& w2){
    return ( (w1.p1 == w2.p1) && (w1.p2 == w2.p2) );
}
//For compare in the LinkedLst_Disk!
bool operator!=(const Wall& d1,const Wall& d2){
    return !(d1 == d2);
}

const Vector2D Wall::getP1() const {
    //cout << p1 << "\t";
    return  Vector2D(p1);
}



const Vector2D Wall::getP2() const {
    //cout << p2 << "\t";
    return Vector2D(p2);
}



Wall Wall::operator=(Wall &other) {
    Wall w(other.p1,other.p2);
    return w;
}

