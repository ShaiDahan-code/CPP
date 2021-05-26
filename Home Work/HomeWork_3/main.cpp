#include <iostream>
#include <string>

#include "Disk.h"
#include "Wall.h"
#include "List_Disk.h"
#include "List_Wall.h"
#include "Vector2D.h"

using namespace std;

//Function to do all the jobe
void update(double T,double dT,List_Disk ld,List_Wall lw){
    cout.precision(4);
    int list_disc_size = ld.size();
    int list_wall_size = lw.size();
    Vector2D old_spot;


    //Run The simulate T with jump of dT
    for(double i=0; i <= T; i+= dT){
        if(i == 0){
            cout << fixed << "0: ";
        }
        else {
            cout << fixed << i << ": ";
        }


        for(int j=0 ; j< list_disc_size ; j++){
            cout << ld[j]<< " ";

            bool flag = false;
            Vector2D old_spot = ld[j].getXY();

            ld[j].setSpot(dT);
            //move disc by disc and check if Collision is happening
            for(int p=0; p < list_disc_size ;p++){
                if(j != p){
                    if(ld[j].checkCollision(ld[p])){
                        //cout << "\tI Hit Disc!\t";
                        ld[p].updateSpeed(ld[j]);
                        flag = true;
                    }
                }
            }

            // move all disc check f any Collision with Wall
            for(int p=0; p <list_wall_size; p++){
                if(ld[j].checkCollisionWall(lw[p])){
                    //cout << "\tI Hit Wall!\t";
                    ld[j].updateSpeedAfterWall(lw[p]);
                    flag = true;
                }
            }
            if(flag){
                ld[j].setXY(old_spot);
            }
        }
        cout << endl;

    }

}



int main() {
    //LinkedList for save the Disks and the Walls!
    List_Disk ld;
    List_Wall lw;

    //Commend
    string cmd;
    //Disc parameters
    double x,y,vx,vy,radius;
    //Wall parameters
    double x1,x2,y1,y2;
    //Simulate parameters
    double T,dT;

    // While the commend is not simulate keep goin
    while(cmd != "simulate"){
        cin >> cmd;
        if(cin.fail()){
            cerr << "Error: illegal input." << endl;
            return 0;
        }
        if(cmd != "disc" && cmd != "wall" && cmd !="simulate"){
            cerr << "Error: illegal input." << endl;
            return 0;
        }

        if(cmd == "disc"){

            cin >> x >> y >> vx >> vy >> radius;
            if(cin.fail()){
                cerr << "Error: illegal input." << endl;
                return 0;
            }


                //create a disc useing 2 Vectors.
                Vector2D x_y(x,y);
                Vector2D vx_vy(vx,vy);
                Disk disk2(x_y,vx_vy,radius);
                //Check collision when create a disc with other disc
                for(int i=0; i < ld.size();i++){
                    if(disk2.checkCollision(ld[i])) {
                        cerr << "Error: disc to disc collision detected in initial configuration" << endl;
                        return 0;
                    }
                }

            //Check collision when create a disc with other wall
                for(int j=0; j<lw.size();j++){
                    if(disk2.checkCollisionWall(lw[j])) {
                        cerr << "Error: disc to wall collision detected in initial configuration" << endl;
                        return 0;
                    }
                }
                //add disc to List
                ld.insert(disk2);
        }

        else if(cmd == "wall"){
            cin >> x1 >> y1 >> x2 >>y2;
            if(cin.fail()){
                cerr << "Error: illegal input." << endl;
                return 0;
            }

            //Create the wall with x2 vector2D
            Vector2D x1_y1(x1,y1);
            Vector2D x2_y2(x2,y2);
            Wall wall(x1_y1,x2_y2);
            //Check collision when create a wall with other wall
            for(int i=0; i < ld.size();i++){
                if(ld[i].checkCollisionWall(wall)) {
                    cerr << "Error: disc to wall collision detected in initial configuration" << endl;
                    return 0;
                }
            }
            // add to Wall list
            lw.insert(wall);

        }

        else if(cmd == "simulate"){
            cin >> T >> dT;
            if(cin.fail()){
                cerr << "Error: illegal input." << endl;
                return 0;
            }

        }

    }
    //if no disk create after create a simulate Error
    if(ld.size() == 0 || cmd != "simulate"){
        cerr << "Error: illegal input." << endl;
        return 0;
    }

    update(T,dT,ld,lw);



    return 0;
}
