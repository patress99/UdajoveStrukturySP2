#pragma once
#include "Filter.h"
#include "Roztried.h"

class Vyhladaj
{
public:
	Vyhladaj();
	~Vyhladaj();

	void filtruj(std::string nazov, std::string nazovPrislusnosti, TypUzemnejJednotky typ);
	void clear(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> tabulkaNaZmazanie);
private:
	Roztried* roztried_;
};



