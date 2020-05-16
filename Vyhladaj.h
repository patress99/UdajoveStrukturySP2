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

	void uloha3a(std::string nazov, std::string nazovPrislusnosti, TypUzemnejJednotky typ, double dolnaHUcast, double hornaHUcast, int dolnaHVolici, int hornaHVolici);
	void vyfiltruj(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaSort);
	void clear(UnsortedSequenceTable<int, UzemnaJednotka*>* tabulkaNaZmazanie);

	void setFilterNazov(bool nastav){this->filterNazov = nastav;};
	void setFilterPrislusnost(bool nastav){this->filterPrislusnost = nastav;};
	void setFilterVolici(bool nastav){this->filterVolici = nastav;};
	void setFilterUcast(bool nastav){this->filterUcast = nastav;};
	void setFilterTyp(bool nastav){this->filterTyp = nastav;};

	void setKriteriumNazov(bool nastav){this->kriteriumNazov = nastav;};
	void setKriteriumVolici(bool nastav) { this->kriteriumVolici = nastav;};
	void setKriteriumUcast(bool nastav) { this->kriteriumUcast = nastav;};



private:
	bool filterNazov,filterPrislusnost, filterVolici, filterUcast, filterTyp;
	bool kriteriumNazov, kriteriumVolici, kriteriumUcast; 
	Roztried* roztried_;
};



