#ifndef EX_2_NEW_BACKGAMMONBOARD_H
#define EX_2_NEW_BACKGAMMONBOARD_H


class BackgammonBoard {
private:
    //Those 2 arrays to know in each spot how many Disk there is and what the color.
    int diks[28];
    char diks_color[28];


    // the "top_num" and "bot_num" is an index how many rows i need.
    int top_num;
    int bot_num;

    //X get seed in his first time then use it to generate an random number
    int X;

    bool black_move;
    bool black_win;
    bool white_win;
    bool captive_disk_black;
    bool captive_disk_white;
    bool white_can_start_out;
    bool black_can_start_out;

public:
    //Constructor get seed as parameter to start with randoms number.
    BackgammonBoard(int seed);

    //Generate a random number.
    int genretRandomNumber();

    //Print the board.
    void printBoard();

    //Setters.
    void setGameIsFinish(bool finish);
    void setCaptiveBlackDisk(bool bd);
    void setCaptiveWhiteDisk(bool bd);
    void setBlackCanOut(bool is_he);
    void setWhiteCanOut(bool is_he);
    void setBlackMove(bool bm);

    //Getters.
    bool getBlackMove() const;
    bool getBlackWin() const;
    bool getWhiteWin() const;
    bool getGameIsFinish() const;
    int getAmount(int spot);
    char getColor(int spot);

    //Check if there is no possible move in the dice.
    bool noPossibleMove(int dice_1 , int dice_2);

    //Check if every move player do is Legal.
    bool isLegalMove(int from, int to,int dice_1,int dice_2);

    //Those methods return the maximum and the minimum to know if make the board more large or more small.
    int returnMaxInBottom();
    int returnMaxInTop();

    //Because the White see upside down from how Black see the board i creat a function the transfer White look to Black
    // for the array of int and array of char
    int convertWhiteLookToBlack(int spot);

    //Those methods check how many pieces are there in the "home" if it's equal to 15 so turn on the flag the player can start draw.
    int countBlackATHome();
    int countWhiteATHome();

    //This method is to set in the int array and the char array how many discs and what there color is.
    void setAmount(int spot,int amount,char c);

    //btw i didn't release any memory because i never use "new".
};


#endif //EX_2_NEW_BACKGAMMONBOARD_H
