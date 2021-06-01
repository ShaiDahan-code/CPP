#ifndef EX_3_LIST_DISK_H
#define EX_3_LIST_DISK_H
#include "Disk.h"
#include <iostream>

using namespace std;

class List_Disk {
public:
    List_Disk();

    /* big three */
    List_Disk(const List_Disk& other);
    List_Disk& operator=(const List_Disk& rhs);
    ~List_Disk();


    //Methods of the list
    void insert(const Disk &disk);
    void clear();
    int size() const;
    Disk& operator[](int index);
    const Disk& operator[](int index) const;

    //Operator
    friend ostream& operator<<(ostream& out, const List_Disk& list);

private:
    struct Node {
        Disk *disk;
        Node* next;
        Node(Disk *disk, Node* next);
    };

    Node* head;
    int count;
};

ostream& operator<<(ostream& out, const List_Disk& list);

#endif //EX_3_LIST_DISK_H
