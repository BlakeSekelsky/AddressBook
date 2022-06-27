#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class AddressBook{
    public:
        struct Entry{
            int id;
            std::string name, phone, email, address;
        };

        AddressBook();
        int get_num_entries();
        std::vector<Entry> get_entries();
        bool fill_entries(std::vector<Entry> entries);
        bool fill_entries(Entry entry);
        void create_entry();
        void read_entries();
        void update_entry();
        void remove_entry();
        void wipe_file();
        void help();
};

#endif