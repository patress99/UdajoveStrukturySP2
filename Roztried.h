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
	SortedSequenceTable<int, UzemnaJednotka*> getTabulkaObci();
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> getTabulkaObciPodlaNazvu();
	SortedSequenceTable<int, UzemnaJednotka*> getTabulkaVsetkeho();
	void najdiObec(string nazovObce);
	void najdiPodlaNazvu(string nazov);



private:
	SortedSequenceTable<int, UzemnaJednotka*>* tabulkaObci_;
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaObciPodlaNazvu_;
	SortedSequenceTable<int, UzemnaJednotka*>* tabulkaKrajov_;
	SortedSequenceTable<int, UzemnaJednotka*>* tabulkaOkresov_;

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaVsetkehoPodlaNazvu_;
	SortedSequenceTable<int, UzemnaJednotka*>* tabulkaVsetkeho_;
	UzemnaJednotka* stat;


};




