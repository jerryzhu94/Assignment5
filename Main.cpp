#include <iostream>
#include <time.h>
#include "BarcodeHashScanner.h"
using namespace std;


//entry point of the program
int main(int argc, char* argv[])
{
	double upc;
	clock_t t;
	BarcodeHashScanner table(argv[1]);

	//prompt use to input upc
	cout << "UPC Code:";
	cin >> upc;

	//search and print
	t = clock();
	table.search(upc);
	t = clock() - t;

	cout << "Hashing time: " << t << " miliseconds" << endl;
	return 0;
}
