#include "List_Wall.h"
#include <cstdlib>
#include <iostream>

List_Wall::List_Wall() : head(NULL), count(0) {}

void List_Wall::insert(Wall wall) {
    head = new Node(wall, head);
    count++;
}

void List_Wall::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
    head = NULL;
}

List_Wall::List_Wall(const List_Wall& other) : head(NULL), count(0) {
    Node* temp = other.head;
    while (temp) {
        insert(temp->wall);
        temp = temp->next;
    }
}

List_Wall& List_Wall::operator=(const List_Wall& rhs) {
    if (this != &rhs) {
        clear();
        Node* temp = rhs.head;
        while (temp) {
            insert(temp->wall);
            temp = temp->next;
        }
    }
    return *this;
}

List_Wall::~List_Wall() {
    clear();
}

Wall& List_Wall::operator[](int index) {
    if (index < 0 || index >= count) {
        cerr << "whoa there buddy!" << endl;
        exit(1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->wall;
}

const Wall& List_Wall::operator[](int index) const {
    if (index < 0 || index >= count) {
        cerr << "whoa there buddy" << endl;
        exit(1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->wall;
}

//ostream& operator<<(ostream& out, const List_Wall& List_Disk) {
//    List_Wall::Node* temp = List_Disk.head;
//    while (temp) {
//        if (temp != List_Disk.head) {
//            out << ",";
//        }
//        out << temp->wall;
//        temp = temp->next;
//    }
//    return out;
//}



int List_Wall::size() const {
    return count;
}

List_Wall::Node::Node(Wall wall, Node* next) : wall(wall), next(next) {}