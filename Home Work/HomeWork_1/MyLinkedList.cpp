#include <cassert>
#include <string>
#include <iostream>
#include "MyLinkedList.h"

using namespace std;


MyLinkedList::MyLinkedList(){
    head =NULL;
    curr =NULL;
    temp =NULL;
}


void MyLinkedList::addNode(string name,int rows,int cols){ // Create a new node with name and Board
    nodePtr n = new node;
    n->name = name;
    n->rows =rows;
    n->cols = cols;
    n->next = NULL;
    char** board = new char*[rows];
    for(int i=0;i<rows;i++){
        board[i] = new char[cols];
    }
    for(int i =0;i<rows;i++){
        for(int j=0;j<cols;j++){
            board[i][j] = ' ';
        }
    }
    n->data = board;
    if(head != NULL){
        curr = head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;
    }
    else{
        head = n;
    }
}

bool MyLinkedList::containNode(string name){ // to check if the name is on the LinkedList
    temp = head;
    curr = head;
    while(curr != NULL && curr->name != name){
        temp = curr;
        curr = curr->next;

    }
    if(curr == NULL){
        return false;
    }
    else{
        return true;
    }

}
char** MyLinkedList::giveBoard(string name){ // methode to get the matrix
    char** s;
    if(containNode(name)) {
        curr = head;
        while (curr != NULL) {
            if (curr->name == name) {
                s= curr->data;
                return s;
            }
            curr = curr->next;
        }
    }
    assert(false);

    return NULL;
}

int MyLinkedList::giveRows(string name) {
    if(containNode(name)) {
        curr = head;
        while (curr != NULL) {
            if (curr->name == name) {
                return curr->rows;
            }
            curr = curr->next;
        }
    }
    assert(false);

    cerr << "Error in GiveRows" << endl;
    return 0;
}
int MyLinkedList::giveCols(string name) {
    if(containNode(name)) {
        curr = head;
        while (curr != NULL) {
            if (curr->name == name) {
                return curr->cols;
            }
            curr = curr->next;
        }
    }
    assert(false);

    cerr << "Error in GiveRows" << endl;
    return 0;

}

void MyLinkedList::setBoard(string name,char** board){
    if(containNode(name)) {
        curr = head;
        while (curr != NULL) {
            if (curr->name == name) {
                curr->data = board;
            }
            curr = curr->next;
        }
    }
}


void MyLinkedList::deletNode(string delData){
    nodePtr delptr = NULL;
    temp = head;
    curr = head;
    while(curr != NULL && curr->name != delData){
        temp = curr;
        curr = curr->next;

    }
    if(curr == NULL){
        delete delptr;
    }
    else{
        delptr = curr;
        curr = curr->next;
        temp->next = curr;
        if(delptr == head){
            head = head->next;
            temp =NULL;
        }
        delete delptr;
    }
}

void MyLinkedList::printBoard(string name){
    char** s = giveBoard(name);
    int cols = giveCols(name);
    int rows = giveRows(name);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout << s[i][j];
        }
        cout << endl;
    }
}

