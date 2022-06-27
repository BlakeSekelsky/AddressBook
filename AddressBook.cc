#include "AddressBook.h"

AddressBook::AddressBook(){}

// Get the number of entries in the save file
int AddressBook::get_num_entries(){
    std::fstream BookFile;
    BookFile.open("book.csv", std::ios::in);
    
    std::string line;
    int counter=1;
    if(BookFile.is_open()){
        while(getline(BookFile, line)){
            counter++;
        }
        return counter;
    } else {
        return 1;
    }
}

// Read file into vector of entries
std::vector<AddressBook::Entry> AddressBook::get_entries(){
    std::vector<AddressBook::Entry> entries;

    std::fstream BookFile;
    BookFile.open("book.csv", std::ios::in);

    std::string line;
    if(BookFile.is_open()){
        while(getline(BookFile, line)){
            AddressBook::Entry entry;
            std::string entry_num;

            std::stringstream sstream(line);
            getline(sstream, entry_num, ',');
            entry.id = stoi(entry_num);
            getline(sstream, entry.name, ',');
            getline(sstream, entry.phone, ',');
            getline(sstream, entry.email, ',');
            getline(sstream, entry.address, ',');

            entries.push_back(entry);
        }
        BookFile.close();
    } 

    return entries;
}

// Fill address book file with vector of entries
bool AddressBook::fill_entries(std::vector<AddressBook::Entry> entries){
    std::fstream BookFile;
    BookFile.open("book.csv", std::ios::out);
    if(BookFile.is_open()){
        for(AddressBook::Entry entry : entries){
            BookFile << entry.id << "," << 
                        entry.name << "," << 
                        entry.phone << "," << 
                        entry.email << "," << 
                        entry.address << "\n";
        }
        BookFile.close();
        return true;
    }
    return false;
}

// Append address book with single entry
bool AddressBook::fill_entries(AddressBook::Entry entry){
    std::fstream BookFile;
    BookFile.open("book.csv", std::ios::app);
    if(BookFile.is_open()){
        BookFile << entry.id << "," << 
                    entry.name << "," << 
                    entry.phone << "," << 
                    entry.email << "," << 
                    entry.address << "\n";
        BookFile.close();
        return true;
    }
    return false;
}

// Accept input and store new contact into address book file
void AddressBook::create_entry(){
    AddressBook::Entry entry;
    entry.id = get_num_entries();
    std::cout << "Name: "; getline(std::cin, entry.name, '\n');
    std::cout << "Phone Number: "; getline(std::cin, entry.phone, '\n');
    std::cout << "Email: "; getline(std::cin, entry.email, '\n');
    std::cout << "Address: "; getline(std::cin, entry.address, '\n');

    if(fill_entries(entry)){
        std::cout << "Entry created!\n";
    } else {
        std::cout << "Entry could not be created.\n";
    }
}

// Format address book file and output to console        
void AddressBook::read_entries(){
    std::vector<AddressBook::Entry> entries = get_entries();

    if(!entries.empty()){             
        std::cout << "# / NAME / PHONE / EMAIL / ADDRESS\n";
        for(AddressBook::Entry entry : entries){
            std::cout << entry.id << " / " << entry.name << " / " << entry.phone << " / " << entry.email << " / " << entry.address << "\n";
        }
    } else {
        std::cout << "Could not read address book, does the file exist?\n";
    }
    
}

// Select id from address book and update it
void AddressBook::update_entry(){
    std::string id_str;
    std::cout << "Which entry would you like to replace?: "; getline(std::cin, id_str, '\n');

    std::vector<AddressBook::Entry> entries = get_entries();

    if(!entries.empty()){
        for(AddressBook::Entry entry : entries){
            if(stoi(id_str) == entry.id){
                std::cout << "Name: "; getline(std::cin, entry.name, '\n');
                std::cout << "Phone Number: "; getline(std::cin, entry.phone, '\n');
                std::cout << "Email: "; getline(std::cin, entry.email, '\n');
                std::cout << "Address: "; getline(std::cin, entry.address, '\n');
                entries[stoi(id_str)-1] = entry;
                if(AddressBook::fill_entries(entries)){
                    std::cout << "Entry updated!\n";
                    break;
                }
            } else {
                std::cout << "Entry could not be updated.\n";
                break;
            }
        }
    } else {
        std::cout << "Could not read address book, does the file exist?\n";
    }
    
    
}

// Removes entry by id
void AddressBook::remove_entry(){
    std::string id_str;
    std::cout << "Which entry would you like to remove?: "; getline(std::cin, id_str, '\n');

    std::vector<AddressBook::Entry> entries = get_entries();
    if(!entries.empty()){
        for(AddressBook::Entry entry : entries){
            if(stoi(id_str) == entry.id){
                int id = stoi(id_str) - 1;
                entries.erase(entries.begin() + id);
                std::cout << "Entry has been removed if existed.\n";
            }else {
                std::cout << "Entry could not be found.\n";
                break;
            }
        }
    } else {
        std::cout << "File already empty.\n";
    }
    

    AddressBook::fill_entries(entries);
}

// Delete the address book file
void AddressBook::wipe_file(){
    if(remove("book.csv") != 1){
        std::cout << "Couldn't wipe save file. Maybe it's already deleted?\n";
    } else {
        std::cout << "Successfully wiped save file.\n";
    }
}

void AddressBook::help(){
    std::cout << "Menu:\nc - Create Entry\nr - Read Address Book\nu - Update Entry\nd - Delete Entry\nw - Wipe Book File\nh - Help\nq - Quit\n";
}
