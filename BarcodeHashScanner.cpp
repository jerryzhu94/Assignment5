#include <iostream>
#include <fstream>
#include <cmath>
#include "BarcodeHashScanner.h"


//constructor that takes in csv text file
BarcodeHashScanner::BarcodeHashScanner(string file)
{
	string upc, name;
	ifstream inFile;
	inFile.open (file);

	//initialize hashtable as an array of HashNode pointers
	m_hashTable = new HashNode*[TABLE_SIZE];
	for(int i = 0; i < TABLE_SIZE; i++)
		m_hashTable[i] = nullptr;

	//parse csv file and insert new entry into hashtable
	while(getline(inFile, upc, ',') && getline(inFile, name, '\n'))
	{
		if(isNumeric(upc))
			insert(stod(upc), name);
	}
	inFile.close();
}

//destructor
BarcodeHashScanner::~BarcodeHashScanner()
{
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		HashNode* entry = m_hashTable[i];
		HashNode* temp;
		while(entry != nullptr)
		{
			temp = entry;
			entry = entry->next;
			delete temp;
		}
	}
	delete m_hashTable;
}

//insert new entry into hashtable
void BarcodeHashScanner::insert(double upc, string name)
{
	//get hashkey
	int hashKey = hashFunction(upc);
	HashNode* newEntry = new HashNode(upc, name);
	//if there is collision, insert newEntry to the front of the list
	if(m_hashTable[hashKey] != nullptr)
		newEntry->next = m_hashTable[hashKey];

	m_hashTable[hashKey] = newEntry;
}

void BarcodeHashScanner::search(double upc)
{
	int hashKey = hashFunction(upc);
	HashNode* entry = m_hashTable[hashKey];
	while(entry != nullptr)
	{
		if(entry->upc == upc)
		{
			cout << entry->name << endl;
			return;
		}
		entry = entry->next;
	}
	cout << "Item not found" << endl;
}


int BarcodeHashScanner::hashFunction(double upc)
{
	return fmod(upc, TABLE_SIZE);
}

//isNumeric returns true if the entire string consists of only numbers (0-9).
bool BarcodeHashScanner::isNumeric(string str)
{
	string::iterator it = str.begin();
	for(it = str.begin(); it != str.end(); it++)
	{
		if((*it) < '0' || (*it) > '9')
			return false;
	}
	return true;
}