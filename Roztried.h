#pragma once
#include "Informacia.h"
#include "UzemnaJednotka.h"
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
	SortedSequenceTable<int, UzemnaJednotka*>* getTabulkaObci();
	

private:
	SortedSequenceTable<int, UzemnaJednotka*>* tabulkaObci_;
	SortedSequenceTable<int, UzemnaJednotka*>* tabulkaKrajov_;
	SortedSequenceTable<int, UzemnaJednotka*>* tabulkaOkresov_;
	UzemnaJednotka* stat;

	
};




