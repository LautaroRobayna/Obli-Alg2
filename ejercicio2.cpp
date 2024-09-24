#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <tads/HashLibro.cpp>

using namespace std;

int main()
{
    int n;
    HashBook* library = new HashBook(n);
    cin >> n;
    while(n--){
        string command;
        cin >> command;
        if(command == "ADD"){
            int id;
            string title;
            cin >> id >> title;
            library->ADD(id, title);
        }
        else if (command == "FIND") {
            int id;
            cin >> id;
            library->FIND(id);
        } 
        else if (command == "TOGGLE") {
            int id;
            cin >> id;
            library->TOGGLE(id);
        } 
        else if (command == "COUNT") {
            library->COUNT();
        }
    }

    return 0;
}