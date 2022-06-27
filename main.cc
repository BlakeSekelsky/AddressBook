#include <iostream>
#include "AddressBook.h"

using namespace std;

int main(){
    AddressBook myBook;
    
    cout << "Menu:\nc - Create Entry\nr - Read Address Book\nu - Update Entry\nd - Delete Entry\nw - Wipe Book File\nh - Help\nq - Quit\n";

    bool keepAlive = true;
    while(keepAlive){
        char option;

        cin >> option;
        cin.ignore();

        switch (option){
            case 'c':
                myBook.create_entry();
                break;
            case 'r':
                myBook.read_entries();
                break;
            case 'u':
                myBook.update_entry();
                break;
            case 'd':
                myBook.remove_entry();
                break;
            case 'w':
                myBook.wipe_file();
                break;
            case 'h':
                myBook.help();
                break;
            case 'q':
                keepAlive = false;
                break;
            default:
                cout << "No action available.\n";
                break;
        };
    }
}