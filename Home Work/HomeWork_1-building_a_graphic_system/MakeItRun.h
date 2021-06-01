#ifndef EX_1_MAKEITRUN_H
#define EX_1_MAKEITRUN_H

#include "MyLinkedList.h"
#include <string>

class MakeItRun {
public:
    MakeItRun();
    void run();

private:
    bool check_name(string s);
    void plot(MyLinkedList board_list,string name,int x ,int y,int color);
    void plot8(MyLinkedList board_list,string name,int cx,int cy,int x,int y,int color);
    void flood(MyLinkedList board_list,string name,int x,int y,int color);
    void stamp(MyLinkedList board_list,string name,int x,int y,string stamp_name);
    int abs(int a,int b);


    };


#endif //EX_1_MAKEITRUN_H
