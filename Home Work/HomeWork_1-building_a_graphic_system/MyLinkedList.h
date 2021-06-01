#ifndef EX_1_MYLINKEDLIST_H
#define EX_1_MYLINKEDLIST_H
#include <string>

using namespace std;

class MyLinkedList {
private:
    typedef struct node{
        string name;
        char** data;
        int rows;
        int cols;
        node* next;

    }* nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;

public:
    MyLinkedList();
    void addNode(string name,int rows,int cols);
    bool containNode(string name);
    char** giveBoard(string name);
    int giveRows(string name);
    int giveCols(string name);
    void setBoard(string name,char** board);
    void deletNode(string delData);
    void printBoard(string name);

};


#endif //EX_1_MYLINKEDLIST_H
