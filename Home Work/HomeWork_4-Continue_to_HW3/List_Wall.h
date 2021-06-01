#ifndef EX_3_LIST_WALL_H
#define EX_3_LIST_WALL_H
#include "Wall.h"
#include <iostream>

using namespace std;

class List_Wall {
public:
    //Constractor
    List_Wall();

    /* big three */
    List_Wall(const List_Wall& other);
    List_Wall& operator=(const List_Wall& rhs);
    ~List_Wall();


    //Function for the List
    void insert(Wall wall);
    void clear();
    int size() const;
    Wall& operator[](int index);
    const Wall& operator[](int index) const;


private:
    struct Node {
        Wall wall;
        Node* next;
        Node(Wall wall, Node* next);
    };

    Node* head;
    int count;
};


#endif //EX_3_LIST_WALL_H
