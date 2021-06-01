#include "List_Disk.h"
#include <cstdlib>
#include <iostream>

List_Disk::List_Disk() : head(NULL), count(0) {}

void List_Disk::insert(const Disk &disk) {
    head = new Node(disk.clone(), head);
    count++;
}

void List_Disk::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
    head = NULL;
}

List_Disk::List_Disk(const List_Disk& other) : head(NULL), count(0) {
    Node* temp = other.head;
    while (temp) {
        insert(*temp->disk);
        temp = temp->next;
    }
}

List_Disk& List_Disk::operator=(const List_Disk& rhs) {
    if (this != &rhs) {
        clear();
        Node* temp = rhs.head;
        while (temp) {
            insert(*temp->disk);
            temp = temp->next;
        }
    }
    return *this;
}

List_Disk::~List_Disk() {
    clear();
}

Disk& List_Disk::operator[](int index) {
    if (index < 0 || index >= count) {
        exit(1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return *temp->disk;
}

const Disk& List_Disk::operator[](int index) const {
    if (index < 0 || index >= count) {
        cerr << "whoa there buddy" << endl;
        exit(1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return *temp->disk;
}

ostream& operator<<(ostream& out, const List_Disk& List_Disk) {
    List_Disk::Node* temp = List_Disk.head;
    while (temp) {
        if (temp != List_Disk.head) {
            out << ",";
        }
        out << temp->disk;
        temp = temp->next;
    }
    return out;
}



int List_Disk::size() const {
    return count;
}

List_Disk::Node::Node(Disk *disk, Node* next) : disk(disk), next(next) {}