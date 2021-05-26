#include "BackgammonBoard.h"
#include <iostream>
#include <cstring>
#include "MainToRun.h"

using namespace std;

MainToRun::MainToRun() {}

void MainToRun::run(){
    /*
     * I start with create an integer for every thing i need to do.
     * Get the seed from the user + chake if the cin work > if not send a error msg and exit
     */
    int seed,cast_white,cast_black,from,to,dice_1,dice_2;
    cout << "Enter seed"<<endl;
    cin >>seed;
    if(cin.fail()){
        cout << "Missing user input - quiting game." << endl;
        return ;
    }
    //Send to the BackgammonBoard class the seed to start generate a random number.
    BackgammonBoard board(seed);

    //White and Black cast to see who Start + Check if fail-> Error message.
    cast_white = (board.genretRandomNumber()%6)+1;
    cast_black = (board.genretRandomNumber()%6)+1;
    cout << "White player casts "<< cast_white <<", black player casts "<< cast_black<<endl;
    if(cin.fail()){
        cout << "Missing user input - quiting game." << endl;
        return ;
    }
    //If the dice are equal make them cast again until it's not
    while(cast_white == cast_black){
        cast_white = (board.genretRandomNumber()%6)+1;
        cast_black = (board.genretRandomNumber()%6)+1;
        cout << "White player casts "<< cast_white <<", black player casts "<< cast_black<<endl;
        if(cin.fail()){
            cout << "Missing user input - quiting game." << endl;
            return ;
        }
    }
    // Print who start and set it on the BackgammonBoard Class.
    if(cast_black > cast_white) {
        cout << "Black plays first." << endl;
        board.setBlackMove(true);
    }
    else{
        cout << "White plays first." << endl;
        board.setBlackMove(false);
    }
    board.printBoard();

    do {
        //Roll the dice and save them.
        dice_1 = (board.genretRandomNumber() % 6) + 1;
        dice_2 = (board.genretRandomNumber() % 6) + 1;
        from = 0;
        to = 0;



        if (board.getBlackMove()) {
            cout << "Black rolls " << dice_1 << "-" << dice_2 << "." << endl;

            //before we start we have to check if the black can even play or not.
            //In case of not transfer the turn to the White
            if(board.noPossibleMove(dice_1,dice_2) == false){
                board.setBlackMove(false);
                board.printBoard();
                continue;
            }


            //In case that the dice are same player need play 4 time.
            if(dice_1 == dice_2) {
                //loop for double thar run 4 time
                for(int i =0; i<4 ;i++){

                    // In every start check if all disk of Black on there "home" if yes turn on the flag to know
                    if(board.countBlackATHome() == 15){
                        board.setBlackCanOut(true);
                    }

                    //Set the flag if the Black dont have any captuve disk
                    if(board.getAmount(26) == 0)
                        board.setCaptiveBlackDisk(false);

                    cout << "Enter Black move: " << endl;
                    cin >> from >> to;
                                                                                                                //!!!!!!!!!!
                    if(cin.fail()){
                        cout << "Missing user input - quiting game." << endl;
                        return ;
                    }


                    if(from == 25)
                        from = 26;
                    while (!board.isLegalMove(from, to, dice_1, dice_2)) {
                        cout << "Enter Black move: " << endl;
                        cin >> from >> to;
                        if(from == 25)
                            from = 26;
                    }


                    /*
                     * This is for check if we captive enemy disk or not!
                     */
                    if(board.getAmount(to) == 1 && board.getColor(to) == 'W'){
                        //cout << " I Am Here! " << endl;
                        board.setAmount(from,board.getAmount(from)-1,'B');
                        board.setAmount(to,1,'B');
                        board.setAmount(25,board.getAmount(25)+1,'W');
                        //board.setAmount(to,1,'B');
                        board.setCaptiveWhiteDisk(true);
                    }
                    else {
                        board.setAmount(from, board.getAmount(from) - 1, 'B');
                        board.setAmount(to, board.getAmount(to) + 1, 'B');
                    }
                }
            }

            if(dice_2!=dice_1){


                for(int i =0; i<2;i++){

                    if(board.countBlackATHome() == 15){
                        board.setBlackCanOut(true);
                    }

                    if(board.getAmount(26) == 0)
                        board.setCaptiveBlackDisk(false);

                    cout << "Enter Black move: " << endl;
                    cin >> from >> to;
                    if(board.getBlackWin()){
                        break;
                    }
                    if(cin.fail()){
                        cout << "Missing user input - quiting game." << endl;
                        return ;
                    }

                    if(from == 25)
                        from = 26;
                    while (!board.isLegalMove(from, to, dice_1, dice_2)) {
                        cout << "Enter Black move: " << endl;
                        cin >> from >> to;
                        if(from == 25)
                            from = 26;
                    }
                    if(board.getBlackWin())
                        break;



                    /*
                     * This is for check if we captive enemy disk or not!
                     */
                    if(board.getAmount(to) == 1 && board.getColor(to) == 'W'){
                        board.setAmount(from,board.getAmount(from)-1,'B');
                        board.setAmount(to,board.getAmount(to)-1,' ');
                        board.setAmount(25,board.getAmount(25)+1,'W');
                        board.setAmount(to,board.getAmount(to)+1,'B');

                        board.setCaptiveWhiteDisk(true);
                    }
                    else {
                        board.setAmount(from, board.getAmount(from) - 1, 'B');
                        board.setAmount(to, board.getAmount(to) + 1, 'B');
                    }
                    if(from != 25) {
                        if ((from - to) == dice_1) dice_1 = 0;
                        else if ((from - to) == dice_2) dice_2 = 0;
                    }
                    else if(from == 25){
                        if ((from+1 - to) == dice_1) dice_1 = 0;
                        else if ((from+1 - to) == dice_2) dice_2 = 0;
                    }
                }
                if(board.getBlackWin())
                    break;
            }
            if(board.getBlackWin())
                break;

            board.setBlackMove(false);
            board.printBoard();

        }

        else{
            cout << "White rolls " << dice_1 << "-" << dice_2 << "." << endl;

            if(dice_1 == dice_2){
                for(int i =0; i<4 && !board.getWhiteWin();i++){

                    if(board.countWhiteATHome() == 15){
                        board.setWhiteCanOut(true);
                    }


                    if(board.getAmount(25) == 0)
                        board.setCaptiveWhiteDisk(false);

                    cout << "Enter White move: " << endl;
                    cin >> from >> to;
                    if(cin.fail()){
                        cout << "Missing user input - quiting game." << endl;
                        return ;
                    }
                    while (!board.isLegalMove(from, to, dice_1, dice_2)) {
                        cout << "Enter White move: " << endl;
                        cin >> from >> to;
                    }


                    /*
                     * This is for check if we captive enemy disk or not!
                     */
                    if(board.getAmount(to) == 1 && board.getColor(to) == 'B'){
                        //cout << " I Am Here! " << endl;
                        board.setAmount(from,board.getAmount(from)-1,'W');
                        board.setAmount(to,board.getAmount(to)-1,' ');
                        board.setAmount(26,board.getAmount(26)+1,'B');
                        board.setAmount(to,1,'W');
                        board.setCaptiveBlackDisk(true);
                    }
                    else {

                        board.setAmount(from, board.getAmount(from) - 1, 'W');
                        if(to == 0)
                            board.setAmount(27, board.getAmount(to) + 1, 'W');
                        else
                            board.setAmount(to, board.getAmount(to) + 1, 'W');

                    }

                    if(board.countWhiteATHome() == 15){
                        board.setWhiteCanOut(true);
                    }
                }
                if(board.getWhiteWin())
                    break;

            }
            if(dice_2!=dice_1){
                for(int i =0; i<2 && !board.getWhiteWin() ;i++){

                    if(board.countWhiteATHome() == 15){
                        board.setWhiteCanOut(true);
                    }

                    if(board.getAmount(25) == 0)
                        board.setCaptiveWhiteDisk(false);

                    cout << "Enter White move: " << endl;
                    cin >> from >> to;
                    if(cin.fail()){
                        cout << "Missing user input - quiting game." << endl;
                        return ;
                    }
                    while (!board.isLegalMove(from, to, dice_1, dice_2)) {
                        cout << "Enter White move: " << endl;
                        cin >> from >> to;
                    }

                    if(board.getWhiteWin())
                        break;



                    if(board.getAmount(to) == 1 && board.getColor(to) == 'B'){
                        cout << " I Am Here! " << endl;
                        board.setAmount(from,board.getAmount(from)-1,'W');
                        cout << "Check: 26 amount :  " << board.getAmount(26) <<endl;
                        board.setAmount(to,board.getAmount(to)-1,' ');
                        board.setAmount(26,board.getAmount(26)+1,'B');
                        cout << "Check: 26 amount :  " << board.getAmount(26) <<endl;
                        board.setAmount(to,1,'W');
                        board.setCaptiveBlackDisk(true);
                    }
                    else {
                        board.setAmount(from, board.getAmount(from) - 1, 'W');
                        if(to == 0)
                            board.setAmount(27, board.getAmount(to) + 1, 'W');
                        else
                            board.setAmount(to, board.getAmount(to) + 1, 'W');
                    }
                    if ((from - to) == dice_1) dice_1 = 0;
                    else if ((from - to) == dice_2) dice_2 = 0;

                    if(board.countWhiteATHome() == 15){
                        board.setWhiteCanOut(true);
                    }


                }
                if(board.getWhiteWin())
                    break;
            }
            board.setBlackMove(true);
            board.printBoard();


        }

    }while(!board.getGameIsFinish());

    if(board.getBlackWin()){
        cout << "Black player wins!"<<endl;
    }
    if(board.getWhiteWin()){
        cout << "White player wins!"<<endl;
    }


}