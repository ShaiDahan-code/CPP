#include "BackgammonBoard.h"
#include <iostream>
#include <cstring>

using namespace std;

//Set all the variable.
BackgammonBoard::BackgammonBoard(int seed) {
    black_move = true;
    X=seed;
    top_num = 5;
    bot_num = 5;
    black_win = false;
    white_win=false;
    captive_disk_white=false;
    captive_disk_black=false;
    white_can_start_out = false;
    black_can_start_out = false;

    for(int i = 0 ;i < 27;i++){
        diks[i] = 0;
        diks_color[i] = ' ';
        if(i==0||i==2||i==3||i==4||i==5||i==7||i==9||i==10||i==11||i==14||i==15||i==16||i==18||i==20||i==21||i==22||i==23){
            setAmount(i,0,' ');
        }
    }

    setAmount(1,2,'W');
    setAmount(3,0,' ');
    setAmount(6,5,'B');
    setAmount(8,3,'B');

    setAmount(12,5,'W');
    setAmount(13,5,'B');

    setAmount(17,3,'W');
    setAmount(19,5,'W');
    setAmount(24,2,'B');
}

//Create the random number
int BackgammonBoard::genretRandomNumber() {
    const unsigned int a = 22695477;
    const unsigned int c = 1;
    X = a*X + c;
    return (X & 0x7fffffff)>>16;
}

//Set the flag black_can_start_out
void BackgammonBoard::setBlackCanOut(bool is_he){black_can_start_out = is_he;}

//Set the flag white_can_start_out
void BackgammonBoard::setWhiteCanOut(bool is_he){white_can_start_out = is_he;}

//Set the flag black_move
void BackgammonBoard::setBlackMove(bool bm) {black_move = bm;}

//return the flag black_move
bool BackgammonBoard::getBlackMove() const {return black_move;}

//return the flag black_win
bool BackgammonBoard::getBlackWin() const {return black_win;}

//return the flag white_win
bool BackgammonBoard::getWhiteWin() const {return white_win;}

//Return if one of the side win or not
bool BackgammonBoard::getGameIsFinish() const{return black_win&&white_win;}

//Set the flag captive_disk_black
void BackgammonBoard::setCaptiveBlackDisk(bool bd){captive_disk_black = bd;}

//Set the flag captive_disk_white
void BackgammonBoard::setCaptiveWhiteDisk(bool wd){captive_disk_white = wd;}

//Print the board row by row, the Array of int and char make where everything will be.
void BackgammonBoard::printBoard() {
    string zero_12 = " 12 11 10  9  8  7     6  5  4  3  2  1"; // string for the top and bottom
    string thirteen_twenty_four = " 13 14 15 16 17 18    19 20 21 22 23 24"; // string for the top and bottom
    string side = "+------------------+-+------------------+"; // Limits of the board from bottom and top

    if(black_move)
        cout <<zero_12 << endl;
    else
        cout << thirteen_twenty_four << endl;

    cout << side << endl;
        for(int i =0 ; i < top_num ;i++){
        cout << "+ ";
        for(int j=12; j > 0; j--){
            if(j>7) {
                if(diks[j] == 0)
                    cout << "|  ";
                else{
                    if(diks[j] > i)
                        cout << diks_color[j] << "  ";
                    else
                        cout << "|  ";
                }
            }

            if(j == 7){
                if (diks[j] == 0) {
                    if (diks[25] > i)
                        cout << "| +" << diks_color[25] << "+ ";
                    else
                        cout << "| + + ";
                }
                else{
                    if(diks[j] >i) {
                        if (diks[25] > i)
                            cout << diks_color[j] << " +" << diks_color[25] << "+ ";                           //Here4
                        else
                            cout << diks_color[j] << " + + ";
                    }

                    else {
                        if (diks[25] > i)
                            cout << "| +" << diks_color[25] << "+ ";
                        else
                            cout << "| + + ";
                    }

                }
            }
            if(j <7 && j!=1) {
                if (diks[j] == 0)
                    cout << "|  ";
                else {
                    if (diks[j] > i)
                        cout << diks_color[j] << "  ";
                    else
                        cout << "|  ";
                }
            }
            if (j == 1) {
                //cout << "Diks is: " << diks[j];
                if (diks[j] == 0)
                    cout << "| ";
                else {
                    if (diks[j] > i)

                        cout << diks_color[j] << " ";
                    else
                        cout << "| ";
                }
            }
        }
        cout << "+";
        cout << endl;
    }
    cout << "+                  + +                  +" << endl;
    for (int i=bot_num;i>0;i--){
        cout << "+ ";
        for(int j=13; j < 25; j++){
            if(j<18) {
                if (diks[j] == 0)
                    cout << "|  ";
                else {
                    if (diks[j]+1 > i)
                        cout << diks_color[j] << "  ";
                    else
                        cout << "|  ";
                }
            }
            if(j == 18){
                if (diks[j] == 0) {
                    if(diks[26]+1 > i)
                        cout << "| +" << diks_color[26] << "+ ";
                    else
                        cout << "| + + ";
                }
                else{
                    if(diks[j] +1>i){
                        if(diks[26]+1 > i)
                            cout << diks_color[j] << " +" << diks_color[26] << "+ ";
                        else
                            cout << diks_color[j] << " + + ";
                    }                                                                                        //Here
                    else {
                        if(diks[26]+1 > i)
                            cout << "| +" << diks_color[26] << "+ ";
                        else
                            cout << "| + + ";
                    }
                }
            }
            if(j>18 && j!= 24) {
                if (diks[j] == 0)
                    cout << "|  ";
                else {
                    if (diks[j]+1 > i)
                        cout << diks_color[j] << "  ";
                    else
                        cout << "|  ";
                }            }
            if (j == 24) {
                if (diks[j] == 0)
                    cout << "| ";
                else {
                    if (diks[j]+1 > i)
                        cout << diks_color[j] << " ";
                    else
                        cout << "| ";
                }
            }
        }
        cout << "+";
        cout << endl;
    }
    cout << side << endl;
    if(!black_move)
        cout <<zero_12 << endl;
    else
        cout << thirteen_twenty_four << endl;

}

//Check if there is no Possible move for the player
bool BackgammonBoard::noPossibleMove(int dice_1 , int dice_2){
    if(captive_disk_black && black_move){
        if(getAmount(25-dice_1) >=2 && getAmount(25-dice_2) >=2) {
            cout << "No possible move for Black" << endl;
            return false;
        }
    }
    if(captive_disk_white && !black_move){
        if(getAmount(25-dice_1) >=2 && getAmount(25-dice_2) >=2) {
            cout << "No possible move for Black" << endl;
            return false;
        }
    }
    return true;
}

//Check every time if the Move is legal
bool BackgammonBoard::isLegalMove(int from, int to,int dice_1,int dice_2) {
    if(getAmount(27) == 15){
        black_win = true;
    }
    if(getAmount(0) == 15){
        white_win = true;
    }

    //One side for the black
    if(black_move) {
        if(from == 26) {
            if (from < 1 || from > 26 || to < 0 || to > 24 || (from-1 - to) < 1 || (from-1 - to) > 6) {                            //Check number 1
                cout << "Illegal move: From/to out of bounds (from=" << from-1 << ", to=" << to << ")." << endl;
                return false;
            }
        }
        if(!captive_disk_black){
            if (from < 1 || from > 26 || to < 0 || to > 24 || (from - to) < 1 || (from - to) > 6) {                             //Check number 1
                cout << "Illegal move: From/to out of bounds (from=" << from << ", to=" << to << ")." << endl;
                return false;
            }
        }
        if(from != 26 && captive_disk_black){                                                                                   //Check number 2
            cout << "Illegal move: Player still has captured piece(s)." << endl;
            return false;
        }
        if (diks[from] == 0) {                                                                                                  //Check number 3
            cout << "Illegal move: No pieces at from location " << from << "." << endl;
            return false;
        }
        if(diks[to] >=2 && diks_color[to] == 'W'){                                                                              //Check number 4
            cout << "Illegal move: Cannot capture more that one piece at location "<< to <<"."<<endl;
            return false;
        }
        if (to == 0 && !black_can_start_out){                                                                                   //Check number 5
            cout << "Illegal move: Cannot bear off while not all pieces at home." << endl;
            return false;
        }

        if(captive_disk_black) {
            int result = from - to - 1;

            if (result != dice_1 &&
                result != dice_2) {                                                                                              //Check number 6
                cout << "Illegal move: No value of " << result << " in dice roll " << endl;
                return false;
            }
        }
        if(!captive_disk_black){
            int result = from - to;
            if(white_can_start_out && to == 0 && (dice_1 > result || dice_2 > result)){
                return true;
            }
            if (result != dice_1 && result != dice_2) {                                                                          //Check number 6
                cout << "Illegal move: No value of " << result << " in dice roll " << endl;
                return false;
            }
        }
    }

    //One side for the White
    if(!black_move){
        if(from <1 || from >25 || to <0 || to>24 ||(from-to)<1 || (from-to)>6) {                                                 //Check number 1
            cout << "Illegal move: From/to out of bounds (from=" << from << ", to=" << to << ")." << endl;
            return false;
        }

        if(from != 25 && captive_disk_white){                                                                                    //Check number 2
            cout << "Illegal move: Player still has captured piece(s)." << endl;
            return false;
        }
        int spot_from = convertWhiteLookToBlack(from);
        if (diks[spot_from] == 0) {                                                                                              //Check number 3
            cout << "Illegal move: No pieces at from location " << from << "." << endl;
            return false;
        }

        int spot_to;
        if(to != 0) {
            spot_to = convertWhiteLookToBlack(to);
        }
        if(to == 0)
            spot_to = 27;
        if (diks[spot_to] >= 2 && diks_color[spot_to] == 'B') {                                                                   //Check number 4
            cout << "Illegal move: Cannot capture more that one piece at location " << to << "." << endl;
            return false;
        }

        if (to == 0 && !white_can_start_out) {                                                                                     //Check number 5
            cout << "Illegal move: Cannot bear off while not all pieces at home." << endl;
            return false;
        }

        int result = from-to;
        if(to == 0) {
            if (white_can_start_out && to == 0 && (dice_1 > result || dice_2 > result)) {
                return true;
            }
        }
        if (result != dice_1 && result != dice_2) {                                                                                //Check number 6
            cout << "Illegal move: No value of " << result << " in dice roll " << endl;
            return false;
        }
    }
    return true;
}

//return the Maximum disks in the bottom
int BackgammonBoard::returnMaxInBottom(){
    int max =0;
    for(int i=13;i< 25;i++){
        if(diks[i] > max){
            max = diks[i];
        }
    }
    return max;
}
//return the Maximum disks in the bottom
int BackgammonBoard::returnMaxInTop(){
    int max =0;
    for(int i=1;i< 13;i++){
        if(diks[i] > max){
            max = diks[i];
        }
    }
    return max;
}

//Set Amount of the Array in each row What color and how many disks the row got
void BackgammonBoard::setAmount(int spot,int amount,char c){
    if(!black_move&& spot != 26 && spot != 27) {
        spot = convertWhiteLookToBlack(spot);
    }


    diks[spot] = amount;
    diks_color[spot] = c;

    if(returnMaxInTop() > top_num) {
        top_num++;
    }
    else if(returnMaxInBottom() > bot_num)
        bot_num++;


    if(returnMaxInTop() < top_num && top_num>5)
        top_num--;
    else if(returnMaxInBottom() < bot_num && bot_num>5)
        bot_num--;
}

//Get the infomation of how many Disks is there on each spot that ask for, if white ask we convert the look, to look like as black.
int BackgammonBoard::getAmount(int spot) {
    if(!black_move && spot != 27 && spot != 26)
        return diks[convertWhiteLookToBlack(spot)];
    else
        return diks[spot];
}

//Return what color in the spot. like amount if white ask we convert the "look" , to look like black view.
char BackgammonBoard::getColor(int spot) {
    if(black_move)
        return diks_color[spot];
    else
        return diks_color[convertWhiteLookToBlack(spot)];
}

//This method convert the look of white be the same as Black, just find the spot and do 25-spot.
int BackgammonBoard::convertWhiteLookToBlack(int spot){
    if(!black_move) {
        for (int i = 1; i < 25; i++) {
            if (spot == i) {
                spot = 25 - i;
                break;
            }
        }
    }
    return spot;
}

//return how many Black Disks are there in the "Home" to know if can start out or not.
int BackgammonBoard::countBlackATHome() {
    int cnt =0;
    for(int i = 0 ; i < 7; i++){
        if(diks_color[i] == 'B')
            cnt += diks[i];
    }
    return cnt;
}

//return how many White Disks are there in the "Home" to know if can start out or not.
int BackgammonBoard::countWhiteATHome() {
    int cnt =0;
    for(int i = 19 ; i < 25; i++){
        if(diks_color[i] == 'W')
            cnt += diks[i];
    }
    return cnt;
}





