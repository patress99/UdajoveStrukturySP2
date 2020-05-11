#pragma once
#include "Informacia.h"
#include "UzemnaJednotka.h"
#include "linked_list.h"
#include <fstream>
#include <sstream> 
#include <iomanip>

using namespace structures;
class Roztried
{

public:
	Roztried();
	~Roztried();

	void roztriedUzemneJednotky();
	void priradDataObciam();
	SortedSequenceTable<int, UzemnaJednotka*> getTabulkaVsetkeho();
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> getTabulkaVsetkehoPodlaNazvu();
	void najdiPodlaNazvu(string nazov);



private:

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaVsetkehoPodlaNazvu_;
	SortedSequenceTable<int, UzemnaJednotka*>* tabulkaVsetkeho_;
	UzemnaJednotka* stat;


};




