#pragma once
#include "Filter.h"
#include "Roztried.h"

class Vyhladaj
{
public:
	Vyhladaj();
	~Vyhladaj();

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* filterTypAPrislusnost(TypUzemnejJednotky typ, string nazovPrislusnosti);
	void uloha3a(std::string nazov, std::string nazovPrislusnosti, TypUzemnejJednotky typ);
	void uloha3b(int dolnaH, int hornaH, std::string nazovPrislusnosti, TypUzemnejJednotky typ);
	void uloha3c(double dolnaH, double hornaH, std::string nazovPrislusnosti, TypUzemnejJednotky typ);

	void clear(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaZmazanie);
private:
	Roztried* roztried_;
};



