all: addressbook

addressbook: AddressBook.o main.o
	g++ -o addressbook AddressBook.o main.o

AddressBook.o: AddressBook.cc AddressBook.h
	g++ -c AddressBook.cc

main.o: main.cc
	g++ -c main.cc

clean:
	rm *.o book.csv addressbook