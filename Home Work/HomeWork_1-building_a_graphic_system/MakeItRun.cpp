#include <cassert>
#include <string>
#include <iostream>
#include <stdlib.h>     /* abs */
#include "MakeItRun.h"


using namespace std;

MakeItRun::MakeItRun() {}

bool MakeItRun::check_name(string s){ // private methode to check if name is ok or not
    if(s.size() > 0 && isalpha(s[0])){ // check if size >0 and if first letter is alpha
        for(unsigned  int i = 1 ; i<s.size();i++){
            if(!isalpha(s[i]) && !isdigit(s[i])){ // if any other char not alpha or not digit => error
                return false;
            }
        }
        return true; // if we pass all test return true
    }
    return false;
}

void MakeItRun::plot(MyLinkedList board_list,string name, int x, int y,int color) {
        char** s =board_list.giveBoard(name);
        int cols = board_list.giveCols(name);
        int raws = board_list.giveRows(name);
        if((x>= 0 && x<raws) && (y>= 0 && y <= cols)) {
            if (color == 0)
                s[x][y] = ' ';
            else if (color == 1)
                s[x][y] = '.';
            else if (color == 2)
                s[x][y] = '+';
            else if (color == 3)
                s[x][y] = '*';
            else if (color == 4)
                s[x][y] = '/';
            else if (color == 5)
                s[x][y] = '\\';
            else if (color == 6)
                s[x][y] = '|';
            else if (color == 7)
                s[x][y] = '-';
            board_list.setBoard(name, s);
        }
}


void MakeItRun::plot8(MyLinkedList board_list,string name,int cx,int cy,int x,int y,int color){

    plot(board_list, name, cx + x, cy + y, color);
    plot(board_list, name, cx - x, cy + y, color);
    plot(board_list, name, cx + x, cy - y, color);
    plot(board_list, name, cx - x, cy - y, color);
    plot(board_list, name, cx + y, cy + x, color);
    plot(board_list, name, cx - y, cy + x, color);
    plot(board_list, name, cx + y, cy - x, color);
    plot(board_list, name, cx - y, cy - x, color);
}

void MakeItRun::flood(MyLinkedList board_list,string name,int x,int y,int color){
    char** s = board_list.giveBoard(name);
    int cols = board_list.giveCols(name);
    int rows = board_list.giveRows(name);
    if((x>=0 && x<rows) && (y>=0 && y<cols) && s[x][y] == ' ') {
        plot(board_list,name,x,y,color);
        flood(board_list,name,x+1,y,color);
        flood(board_list,name,x-1,y,color);
        flood(board_list,name,x,y+1,color);
        flood(board_list,name,x,y-1,color);
    }
}

void MakeItRun::stamp(MyLinkedList board_list,string name,int x,int y,string stamp_name){
    int stamp_row = board_list.giveRows(stamp_name);
    int stamp_cols = board_list.giveCols(stamp_name);
    char** stamp_board = board_list.giveBoard(stamp_name);
    char** name_board = board_list.giveBoard(name);
    for(int i = 0;i<stamp_row;i++){
        for(int j = 0;j<stamp_cols;j++){
            name_board[x+i][y+j] = stamp_board[i][j];
        }
    }
    board_list.setBoard(name,name_board);
}

void MakeItRun::run() {
    MyLinkedList board_list;

    string command,name,stamp_name;
    int rows, cols, x, y, x1, x2, y1, y2, cx, cy, r , color;

    while (command != "quit" && (cin >> command) ) {


        if (command == "board") {                                                                                        // creat a board
            cin >> name >> rows >> cols;
            if (rows <= 0 || cols <= 0) { // check if rows or clos are negtive number -> print error and exit
                cerr << "Board: number of rows and columns must be greater that zero" << endl;
                break;
            } else if (!check_name(name)) { // check if first letter is alphabatic if not ->Error and exit
                cerr << "Invalid board name " << "'" << name << "'" << endl;
                break;
            } else {
                board_list.addNode(name, rows, cols);
            }
        }

        else if (command == "plot") {                                                                                      // plot a dot
            cin >> name >> x >> y >> color;

            if (!check_name(name)) { // check if name is ok
                cerr << "Invalid board name " << "'" << name << "'" << endl;
                break;
            } else if (board_list.containNode(name) == false) {
                cerr << "Board named " << "'" << name << "'" << " not found" << endl;
            } else if (color < 0 || color > 7) {
                cerr << "Invalid color number " << color << endl;
                break;
            } else {
                plot(board_list, name, y, x, color);
            }

        }

        else if (command == "line") {                                                // plot a line
            cin >> name >> x1 >> y1 >> x2 >> y2 >> color;
            if (!check_name(name)) { // check if name is ok
                cerr << "Invalid board name " << "'" << name << "'" << endl;
                break;
            } else if (color < 0 || color > 7) {
                cerr << "Invalid color number " << color << endl;
                break;
            } else {
                bool plotxy = false;
                if(::abs(x2-x1) < ::abs(y2-y1)){
                    swap(x1,y1);
                    swap(x2,y2);
                    plotxy = true;
                }
                if(x2<x1){
                    swap(x1,x2);
                    swap(y1,y2);
                }

                    int dx = x2 - x1;
                    int dy = ::abs(y2 - y1);
                    dy = dy >= 0 ? dy : dy * -1;
                    int sy = (y2 - y1) > 0 ? 1 : -1; // sign(z) = 1 if z>0; -1 if z<0; 0 otherwise
                    int e = -dx;
                    int x = x1;
                    int y = y1;
                    while (x <= x2) {
                        if(plotxy){
                            plot(board_list,name,x,y,color);
                        }
                        else{
                            plot(board_list,name,y,x,color);
                        }
                        x += 1;
                        e += 2 * dy;
                        if (e > 0) {
                            y += sy;
                            e -= 2 * dx;
                        }
                    }

            }
        }

        else if (command == "circle") {                                               // plot a circle
            cin >> name >> cx >> cy >> r >> color;

            if (!check_name(name)) { // check if name is ok
                cerr << "Invalid board name " << "'" << name << "'" << endl;
                break;
            } else if (color < 0 || color > 7) {
                cerr << "Invalid color number " << color << endl;
                break;
            } else if (r < 0) {
                cerr << "Circle: radius must be non-negative" << endl;
                break;
            } else {
                int x, y, d;
                x = 0;
                y = r;
                d = 3 - 2 * r;
                plot8(board_list, name, cy, cx, x, y, color);
                while (y >= x) {
                    x += 1;
                    if (d > 0) {
                        y -= 1;
                        d += 4 * (x - y) + 10;
                    } else {
                        d += 4 * x + 6;
                    }
                    plot8(board_list, name, cy, cx, x, y, color);
                }

            }
        }

        else if (command == "fill") {                                                // draw a fill
            cin >> name >> x >> y >> color;
            if (!check_name(name)) { // check if name is ok
                cerr << "Invalid board name " << "'" << name << "'" << endl;
                break;
            } else if (color < 0 || color > 7) {
                cerr << "Invalid color number " << color << endl;
                break;
            } else if (color == 0) {
                cerr << "FloodFill: cannot flood with the background color" << endl;
                break;
            } else {
                flood(board_list, name, y, x, color);
            }

        }

        else if (command == "stamp") {                                                // draw a stamp
            cin >> name >> x >> y >> stamp_name;
            if (!check_name(name)) { // check if name is ok
                cerr << "Invalid board name " << "'" << name << "'" << endl;
                break;
            } else if (board_list.containNode(name) == false) {
                cerr << "Board named " << "'" << name << "'" << " not found" << endl;
            } else if (color < 0 || color > 7) {
                cerr << "Invalid color number " << color << endl;
                break;
            }
            else {
                stamp(board_list, name, y, x, stamp_name);
            }
        }

        else if (command == "print") {                                                // print
            cin >> name;
            if (!check_name(name)) { // check if name is ok
                cerr << "Invalid board name " << "'" << name << "'" << endl;
                break;
            }
            else if (board_list.containNode(name) == false) {
                cerr << "Board named " << "'" << name << "'" << " not found" << endl;
                break;
            }
            else{
                board_list.printBoard(name);
            }
        }

        else if (command != "quit") {
            cerr << "unknown command '" << command << "'" << endl;
            break;
        }
    }
}
