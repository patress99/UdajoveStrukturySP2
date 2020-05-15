#pragma once
#include "Filter.h"
#include "Roztried.h"
#include "unsorted_sequence_table.h"
#include "quick_sort.h"
#include "Kriterium.h"

class Vyhladaj
{
public:
	Vyhladaj();
	~Vyhladaj();

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* filterTypAPrislusnost(TypUzemnejJednotky typ, string nazovPrislusnosti);
	void uloha3a(std::string nazov, std::string nazovPrislusnosti, TypUzemnejJednotky typ);
	void uloha3b(int dolnaH, int hornaH, std::string nazovPrislusnosti, TypUzemnejJednotky typ);
	void uloha3c(double dolnaH, double hornaH, std::string nazovPrislusnosti, TypUzemnejJednotky typ);

	void clear(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaZmazanie);
private:
	Roztried* roztried_;
};



