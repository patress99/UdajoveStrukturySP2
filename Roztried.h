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
	SequenceTable<int, UzemnaJednotka*>* getTabulkaVsetkeho();
	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* getTabulkaVsetkehoPodlaNazvu();
	void najdiPodlaNazvu(string nazov);
	void filterNajdiNazov(string nazov);
	void patrim(string nazov);

private:

	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaVsetkehoPodlaNazvu_;
	SequenceTable<int, UzemnaJednotka*>* tabulkaVsetkeho_;
	UzemnaJednotka* stat;


};




