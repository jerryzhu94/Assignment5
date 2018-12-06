#ifndef HASHSCANNER_H
#define HASHSCANNER_H
#include <string>
#define TABLE_SIZE 1000
using namespace std;


struct HashNode
{
    HashNode(double upc, string name)
    {
        this->upc = upc;
		this->name = name;
		this->next = nullptr;
    }
	double upc;
	string name;
	HashNode* next;
};


class BarcodeHashScanner
{
public:
	BarcodeHashScanner(string file);
	~BarcodeHashScanner();
	void insert(double upc, string name);
	void search(double upc);

private:
	HashNode** m_hashTable;
	int hashFunction(double upc);

	//helper function
	bool isNumeric(string str);

};

#endif