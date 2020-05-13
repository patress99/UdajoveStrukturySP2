#include "Vyhladaj.h"

Vyhladaj::Vyhladaj() :
	roztried_(new Roztried())
{
	roztried_->roztriedUzemneJednotky();
	roztried_->priradDataObciam();
}

Vyhladaj::~Vyhladaj()
{
	delete roztried_;
}

void Vyhladaj::filtruj(std::string nazov, std::string nazovPrislusnosti, TypUzemnejJednotky typ)
{
	
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vratenaTabulka = roztried_->getTabulkaVsetkehoPodlaNazvu();
	FilterTypUzemnaJednotka* fTyp = new FilterTypUzemnaJednotka();
	fTyp->setAlpha(typ);
	LinkedList<UzemnaJednotka*>* list = roztried_->getTabulkaVsetkehoPodlaNazvu().operator[](nazovPrislusnosti);
	


	for (size_t i = 0; i < list->size(); i++)
	{		
		UzemnaJednotka* uJ = (*list)[i];
		FilterPrislusnost* prislusnost = new FilterPrislusnost(uJ);
		prislusnost->setAlpha(true);
		vratenaTabulka = prislusnost->vyfiltrujPrislusnost(vratenaTabulka, nazov);
		vratenaTabulka = fTyp->vyfiltrujTypUzemnejJednotky(vratenaTabulka, nazov);
		delete prislusnost;
	
	}
	//cout << roztried_->getTabulkaVsetkeho().operator[](607)->getNazov() << endl;



	
	

	

}

void Vyhladaj::clear(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> tabulkaNaZmazanie)
{
	for (const auto& temp : tabulkaNaZmazanie)
	{
		string kluc = temp->getKey();
		delete tabulkaNaZmazanie.operator[](kluc);
	}
	tabulkaNaZmazanie.clear();	
}
