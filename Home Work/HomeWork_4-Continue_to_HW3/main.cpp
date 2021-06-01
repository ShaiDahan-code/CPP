#include <iostream>
#include <string>

#include "Disk.h"
    //#include "Wall.h"
#include "List_Disk.h"
#include "List_Wall.h"
//#include "Vector2D.h"
#include "ShrinkingDisc.h"
#include "ExploadingDisc.h"
#include <math.h>

using namespace std;

//Function that Split the ExposingDisc to three other disc.
void splitDiscToThree(Disk &d, int count , List_Disk &newLD){
    double c = 0.99;
    double radius = d.getR();
    double newRadius = ((2*sqrt(3) - 3)*c*radius);
    double a = (4 - 2*sqrt(3))*radius;
    double m = d.getM();
    Vector2D p = d.getXY();
    Vector2D v = d.getVxVy();
    double globalM = m/3;
    ////First Child
    //New Parameters
    Vector2D p0 = p + Vector2D(0,a);
    Vector2D v0 = v + Vector2D(0,1);
    ExploadingDisc d0(p0,v0,newRadius,count,globalM);

    ////Second Child
    //New Parameters
    Vector2D p1 = p + Vector2D(radius-a,-(a/2));
    Vector2D v1 = v + Vector2D((sqrt(3)/2),-(1.0/2.0));
    ExploadingDisc d1(p1,v1,newRadius,count,globalM);

    ////Threed Child
    //New Parameters
    Vector2D p2 = p + Vector2D(-(radius-a),-(a/2));
    Vector2D v2 = v + Vector2D(-(sqrt(3)/2),-(1.0/2.0));
    ExploadingDisc d2(p2,v2,newRadius,count,globalM);
    newLD.insert(d2);
    newLD.insert(d1);
    newLD.insert(d0);

}

//Function to run on all discs and check the things we need to check
void runSimulateDisc(List_Disk &ld,double dT, List_Wall &lw){
    for (int j = ld.size()-1; j >= 0; j--) {
        cout << ld[j] << " ";// << ld[j].getVxVy() << " ";
        bool flag = false;
        Vector2D old_spot = ld[j].getXY();

        ld[j].setSpot(dT);

        //move disc by disc and check if Collision is happening
        for (int p = 0; p < ld.size() ; p++) {
            if (j != p) {
                if (ld[j].checkCollision(ld[p])) {
                    //Set the Flag of both Disc that there colloid
                    ld[j].setWasCollision(true);
                    ld[p].setWasCollision(true);
                    ld[j].updateSpeed(ld[p]);
                    flag = true;
                }
            }
        }

        // move all disc check f any Collision with Wall
        for (int p = 0; p < lw.size(); p++) {
            if (ld[j].checkCollisionWall(lw[p])) {
                //Set the Disc flag of collision to be True after colloid with wall
                ld[j].setWasCollision(true);
                ld[j].updateSpeedAfterWall(lw[p]);
                flag = true;
            }
        }
        if(flag){
            ld[j].setXY(old_spot);
        }
    }
}

//Function to the change the old list to a new list
void runNewListCreate(List_Disk &ld){
    List_Disk newLD;
    newLD.clear();

    //Run on all the old list , check for What kind of disc it's and make what necessary for each one.
    for (int i = 0; i <  ld.size(); i++) {
        if (!ld[i].isWasCollision()) {
            newLD.insert(ld[i]);
        }
        else if (ld[i].isWasCollision()) {
            //On normal disc set the collision flag to be false and add to the new list
            if (ld[i].getType() == "Normal") {
                ld[i].special_commend();
                newLD.insert(ld[i]);
            }

            //On the Shinking disc make the "spcial_commend" that change his radius to the new one and set the flag
            else if (ld[i].getType() == "Shrinking") {
                int count = ld[i].special_commend();
                if (count < 3) {
                    newLD.insert(ld[i]);
                    //cout << count;
                }
            }
            //Split the disc to 3 the disc is Exploding disc
            else if (ld[i].getType() == "Exploading") {
                int count = ld[i].special_commend();
                if (count < 3) {
                    splitDiscToThree(ld[i], count, newLD);

                }
            }
        }
    }
    //Set the old one to be the new one!
    cout << endl;
    ld = newLD;
}

//Function to do all the jobe
void update(double T,double dT,List_Disk &ld,List_Wall &lw){
    cout.precision(4);

    //Run The simulate T with jump of dT
    for(double i=0; i <= T; i+= dT){
        if(i == 0)  {cout << fixed << "0: ";}
        else        {cout << fixed << i << ": ";}

        //Run The Simulate for the disc
        runSimulateDisc(ld,dT,lw);

        //New Part for EX4
        runNewListCreate(ld);
    }
}

//When create the Discs check if there is collision between other disc or other wall.
bool checkCollisionWhenCreate(List_Disk &ld,List_Wall &lw , Disk &disk2){
    //Check collision when create a disc with other disc
    for(int i=0; i < ld.size();i++){
        if(disk2.checkCollision(ld[i])) {
            cerr << "Error: disc to disc collision detected in initial configuration" << endl;
            return true;
        }
    }

    //Check collision when create a disc with other wall
    for(int j=0; j<lw.size();j++){
        if(disk2.checkCollisionWall(lw[j])) {
            cerr << "Error: disc to wall collision detected in initial configuration" << endl;
            return true;
        }
    }
    return false;
}

//Create

bool CheckFail(){
    if(cin.fail()){
        cerr << "Error: illegal input." << endl;
        return 0;
    }
    return 1;
}

int main() {
    //LinkedList for save the Disks and the Walls!
    List_Disk ld;
    List_Wall lw;
    //Simulate parameters
    double T,dT;

    //Commend
    string cmd;
    //Disc parameters
    double x,y,vx,vy,radius;
    //Wall parameters
    double x1,x2,y1,y2;


    // While the commend is not simulate keep goin
    while(cmd != "simulate"){
        cin >> cmd;
        if(!CheckFail()) {return 0;}

        if(cmd != "disc" && cmd != "wall" && cmd !="simulate" && cmd != "exploding_disc" && cmd != "shrinking_disc"){
            cerr << "Error: illegal input." << endl;
            return 0;
        }

        if(cmd == "disc"){

            cin >> x >> y >> vx >> vy >> radius;
            if(!CheckFail()) {return 0;}

            //create a disc useing 2 Vectors.
            Vector2D x_y(x,y);
            Vector2D vx_vy(vx,vy);
            double m  = radius*radius;
            Disk disk2(x_y,vx_vy,radius,m);

            if(checkCollisionWhenCreate(ld,lw,disk2)) {return 0;}

            //add disc to List
            ld.insert(disk2);
        }

        else if(cmd == "exploding_disc"){
            cin >> x >> y >> vx >> vy >> radius;
            if(!CheckFail()) {return 0;}

            //Create the ExplodingDisc
            Vector2D x_y(x,y);
            Vector2D vx_vy(vx,vy);
            ExploadingDisc explodingDisc(x_y,vx_vy,radius,0,radius*radius);

            //Check collision when create a ShrinkingDisc with other types of Disc
            if(checkCollisionWhenCreate(ld,lw,explodingDisc)) {return 0;}

            ld.insert(explodingDisc);

        }

        else if(cmd == "shrinking_disc"){
            cin >> x >> y >> vx >> vy >> radius;
            if(!CheckFail()) {return 0;}

            //Create the ShrinkDisc
            Vector2D x_y(x,y);
            Vector2D vx_vy(vx,vy);
            ShrinkingDisc shrinkDisc(x_y,vx_vy,radius);

            //Check collision when create a ShrinkingDisc with other types of Disc
            if(checkCollisionWhenCreate(ld,lw,shrinkDisc)) {return 0;}

            //Add the ShinikDisc to the LinkedList
            ld.insert(shrinkDisc);


        }

        else if(cmd == "wall"){
            cin >> x1 >> y1 >> x2 >>y2;
            if(!CheckFail()) {return 0;}


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
            if(!CheckFail()) {return 0;}


        }

    }
    //if no disk create after create a simulate Error
    if(ld.size() == 0 || cmd != "simulate"){
        cerr << "Error: illegal input." << endl;
        return 0;
    }

    //Start the Simulate
    update(T,dT,ld,lw);
    return 0;
}
