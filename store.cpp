//	File Name: store.cpp
//	Programmer: Tabitha Roemish & Prathyusha Pillari
//	Date: March 2, 2018
//	File contains: store class definitions

#include "store.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "binarysearchtree.h"



//initialize static variables in store
std::set<std::string> Store::commandCodes = { "B", "R", "I", "H" };
std::set<std::string> Store::mediaCodes = { "D" };
std::set<std::string> Store::movieCodes = { "C", "D", "F" };
HashMap Store::customerList;
std::map< std::string, std::map<std::string, BinarySearchTree<Movie*>>> Store::collection;

//store destructor
Store::~Store()
{
	//hashmap customerList releases space made for hash elements and Customers
}

//reads DVDs specifically because it adds all files to collection["D"]
//reads input string and sends it to movie create function
void Store::readDVDMovies(std::string filename)
{
  /*F, 10, Nora Ephron, You've Got Mail, 1998       
	D, 10, Steven Spielberg, Schindler's List, 1993       
	C, 10, George Cukor, Holiday, Katherine Hepburn 9 1938       
	C, 10, George Cukor, Holiday, Cary Grant 9 1938       
	Z, 10, Hal Ashby, Harold and Maude, Ruth Gordon 2 1971       
	D, 10, Phillippe De Broca, King of Hearts, 1967*/

	std::ifstream toRead(filename);

	std::string input;

	if (toRead.is_open())

	{
		std::getline(toRead, input);
		while (std::getline(toRead, input))
		{
			Movie * mvPtr = nullptr; //Movie::create(input);
			if (mvPtr != nullptr)
			{
				std::string code = input.substr(1, 1);
				collection["D"][code].add(mvPtr);
			}
		}
	}
	else
		std::cerr << "Could not open file: " << filename;

	toRead.close();
	
}

//reads customers from file, adds customers to hashtable
void Store::readCustomers(std::string filename)
{
	//1111 Mouse Mickey 
	//1000 Mouse Minnie
	std::ifstream toRead(filename);
	std::string input;
	std::stringstream ss;
	int custId = 0;
	std::string custName = "";
	
	if (toRead.is_open())
	{
		while (std::getline(toRead, input))
		{

			ss << input;
			ss >> custId;
			std::getline(ss,custName);
		//check if customer is in list, if not (nullptr returned) then add
			if (customerList.search(custId) == nullptr) 
			{
				Customer * cust = nullptr;
				cust = new Customer(custId, custName);
				customerList.insert(custId, cust);
				input = "";
				custId = 0;
				custName = "";
				ss.clear();
			}//else continue without comment
		}
		customerList.print(); // used for testing
	}
	else
		std::cerr << "Could not open file: " << filename;
	toRead.close();
}

//reads input string and sends it to command.create to make specific commands
void Store::readCommands(std::string filename)
{
	std::ifstream toRead(filename);
	std::string input;

	if (toRead.is_open())
	{
		while (std::getline(toRead, input))
			Command * cmd = Command::create(input);
	}
	else
		std::cerr << "Could not open file: " << filename;
	toRead.close();
}

//iterates through collection
//prints string value for mediaType, then string value for Genre type
//then prints contents of BST
//ex
// D:  
//   C:  
//	   Title Year
//	   Title Year
void Store::printInventory()
{
	for (std::map<std::string, std::map<std::string, BinarySearchTree<Movie*>>>
		::iterator mediaTypeIt = collection.begin(); mediaTypeIt != collection.end(); mediaTypeIt++)
	{
		std::cout << mediaTypeIt->first << ": " << endl;
		auto genreIt = mediaTypeIt->second.begin();
		for (genreIt; genreIt != mediaTypeIt->second.end(); genreIt++)
		{
			std::cout << "   " << genreIt->first << ": " << endl;
			genreIt->second.print();
		}
	}
}




