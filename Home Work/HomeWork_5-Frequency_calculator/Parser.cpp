//
// Created by shai0 on 6/15/2021.
//
#include "Parser.h"
#include <fstream>
#include <stdlib.h>
Parser::Parser() {

}

Parser::~Parser() {

}

void Parser::menu() {
    string command;
    string nameToExecute;
    string file_name;
    string line;
    string str;


    /*****************************************************************************/
    /*                                                                           */
    /*    try on all the loop to catch if there will be any Exception            */
    /*                         if there is we catch it                           */
    /*                                                                           */
    /*****************************************************************************/
    try {
        while (getline(cin,str)) { // get line by line
            istringstream allCommands(str); // transfter it to isstream
            allCommands >> command; // get the command
            if (allCommands.fail()) { // if can't get the command throw
                throw;
            }
            if (command == "string_counter") { // in case the command is string_counter , get the name to create and create it
                allCommands >> nameToExecute;
                if (allCommands.fail()) {
                    throw ExceptionMissingCountName();
                }
                if (intNameExist(nameToExecute) || stringNameExist(nameToExecute))
                    throw ExceptionAlreadyExist();

                stringList.push_back(Counter<string>(nameToExecute));
            }

            else if (command == "int_counter") { // in case the command is int_counter , get the name to create and create it
                allCommands >> nameToExecute;
                if (allCommands.fail())
                    throw ExceptionMissingCountName();
                if (intNameExist(nameToExecute) || stringNameExist(nameToExecute))
                    throw ExceptionAlreadyExist();

                intList.push_back(Counter<int>(nameToExecute));
            }

            else if (command == "add_from_file") { // in case the command is add_from_file, we get the name to execute the command and file name
                allCommands >> nameToExecute >> file_name;
                if (allCommands.fail()) {
                    throw ExceptionMissingFileName();
                }
                if (intNameExist(nameToExecute) || stringNameExist(nameToExecute)) { // Check if it's exist at all
                    if (intNameExist(nameToExecute)) { // if it's in intList open the file
                        char *a = &file_name[0]; // we get the address of the first letter until '\0'
                        ifstream file(a);
                        if (!file.is_open()) { // in case fail to open throw Exeption
                            throw ExceptionNoFile();
                        }

                        getFromIntListByName(nameToExecute).add_from_stream(file); // then execute on the name the methode add_from_stream
                    }

                    else if (stringNameExist(nameToExecute)) { // Same case like the intNameExist.
                        char *a = &file_name[0];
                        fstream file(a);
                        if (!file.is_open()) {
                            throw ExceptionNoFile();
                        }

                        getFromStringListByName(nameToExecute).add_from_stream(file);
                    }
                }

                else { // Can't allocate the counter that refer to
                    throw ExceptionNoCounterByName(nameToExecute);
                }
            }

            else if (command == "add_from_string") {// In case the command is add_from_string , we first input the name to execute the command
                allCommands >> nameToExecute;
                if (!(intNameExist(nameToExecute) || stringNameExist(nameToExecute))) { // Check if it's exist at all.
                    throw ExceptionNoCounterByName(nameToExecute);
                }

                else if (intNameExist(nameToExecute) || stringNameExist(nameToExecute)) { // if it's exist check to who he belong
                    if (intNameExist(nameToExecute)) {// if he belong to intList get the rest of the line change it to iSStream and execute add_rom_stream
                        string s;
                        getline(allCommands, s);
                        istringstream iss(s);
                        getFromIntListByName(nameToExecute).add_from_stream(iss);
                    }

                    else if (stringNameExist(nameToExecute)) { // same thing like intNameExist!
                        string s;
                        getline(allCommands, s);
                        istringstream iss(s);
                        getFromStringListByName(nameToExecute).add_from_stream(iss);
                    }
                }
            }


            else if (command == "stats") { // if The Command is stats, we first get the name to execute the command
                allCommands >> nameToExecute;
                if (!(intNameExist(nameToExecute) || stringNameExist(nameToExecute))) { // check if exist if no throw Exeption
                    throw ExceptionNoCounterByName(nameToExecute);
                }

                else if (intNameExist(nameToExecute) || stringNameExist(nameToExecute)) { //in case it's exist check who belong and use the print_to_stream
                    if (intNameExist(nameToExecute)) {
                        getFromIntListByName(nameToExecute).print_to_stream(cout);
                    }

                    else if (stringNameExist(nameToExecute)) {
                        getFromStringListByName(nameToExecute).print_to_stream(cout);
                    }
                }

            } else if (command == "most_common") {// if the command is most_common, we first get the name to execute the command
                allCommands >> nameToExecute;
                if (!(intNameExist(nameToExecute) || stringNameExist(nameToExecute))) {//check if exist if no throw Exeption
                    throw ExceptionNoCounterByName(nameToExecute);
                }

                else if (intNameExist(nameToExecute) || stringNameExist(nameToExecute)) {//in case it's exist check who belong and use print_most_common
                    if (intNameExist(nameToExecute)) {
                        getFromIntListByName(nameToExecute).print_most_common(cout);
                    }

                    else if (stringNameExist(nameToExecute)) {
                        getFromStringListByName(nameToExecute).print_most_common(cout);
                    }
                }
            }

            else{ // in case it's was none of the above throw UnknownCMD exeption
                throw ExceptionUnknowCMD(command);
            }


        }
    }

    /*****************************************************************************/
    /*                                                                           */
    /*                     Catch all the Exceptions                              */
    /*                                                                           */
    /*****************************************************************************/

    catch (Counter<int>::ExceptionEmptyCount e){
        cerr << "Error: Counter is empty" << endl;
        exit(1);

    }
    catch (Counter<int>::ExceptionErrorWhileInput e){
        cerr << "Error: Read failed" << endl;
        exit(1);
    }
    catch (Counter<string>::ExceptionEmptyCount e){
        cerr << "Error: Counter is empty" << endl;
        exit(1);

    }
    catch (Counter<string>::ExceptionErrorWhileInput e){
        cerr << "Error: Read failed" << endl;
        exit(1);
    }
    catch (ExceptionAlreadyExist e){
        cerr << "Error: Counter name already exists" << endl;
        exit(1);
    }
    catch (ExceptionNoCounterByName e){
        cerr << "Error: No counter named " << e.name << endl;
        exit(1);
    }
    catch  (ExceptionNoFile e){
        cerr << "Error: Failed to open file" << endl;
        exit(1);
    }
    catch (ExceptionUnknowCMD e){
        cerr << "Error: Unknown command "<< e.name << endl;
        exit(1);
    }
    catch (ExceptionMissingFileName e){
        cerr << "Error: Missing file name" <<endl;
    }
    catch (ExceptionMissingCountName e){
        cerr << "Error: Missing counter name" <<endl;
    }

}

bool Parser::intNameExist(string name) {
    unsigned int i =0;
    for (i=0; i < intList.size(); ++i) {
        if(intList[i].getName() == name)
            return true;
    }
    return false;
}

bool Parser::stringNameExist(string name) {
    unsigned int i=0;
    for (i=0; i < stringList.size(); ++i) {
        if(stringList[i].getName() == name)
            return true;
    }
    return false;
}

Counter<int> &Parser::getFromIntListByName(string name) {
    unsigned int i=0;
    for (i=0; i < intList.size(); ++i) {
        if(intList[i].getName() == name)
            return intList[i];
    }
    return intList[0];
}

Counter<string> &Parser::getFromStringListByName(string name) {
    unsigned int i = 0;
    for (i=0; i < stringList.size(); ++i) {
        if(stringList[i].getName() == name)
            return stringList[i];
    }
    return stringList[0];
}