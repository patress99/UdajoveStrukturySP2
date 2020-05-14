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

void Vyhladaj::uloha3a(std::string nazov, std::string nazovPrislusnosti, TypUzemnejJednotky typ)
{
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* poNazvoch = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* poPrislusnosti = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* vysledok = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
	//SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* vysledok = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> zaciatocnaTabulka = roztried_->getTabulkaVsetkehoPodlaNazvu();

	FilterTypUzemnaJednotka* fTyp = new FilterTypUzemnaJednotka();
	fTyp->setAlpha(typ);
	LinkedList<UzemnaJednotka*>* list = roztried_->getTabulkaVsetkehoPodlaNazvu().operator[](nazovPrislusnosti);
	FilterNazov* fNazov = new FilterNazov();
	


	*vysledok = fTyp->vyfiltrujTypUzemnejJednotky(zaciatocnaTabulka, false, vysledok);
	for (size_t i = 0; i < list->size(); i++)
	{
		UzemnaJednotka* uJ = (*list)[i];
		if (uJ->getTypUzemnejJednotky() != typ)
		{
			//cout << uJ->getkamPatrimJa()->getTypUzemnejJednotky() << endl;
			FilterPrislusnost* prislusnost = new FilterPrislusnost(uJ);
			prislusnost->setAlpha(true);
			*poPrislusnosti = prislusnost->vyfiltrujPrislusnost(*vysledok, false, poPrislusnosti);
			delete prislusnost;
		}
	}

	for (auto temp : *poPrislusnosti)
	{
		for (size_t i = 0; i < temp->accessData()->size(); i++)
		{
			cout << temp->accessData()->operator[](i)->getNazov() << endl;
		}
	}

	cout << poPrislusnosti->size() << endl;
	fNazov->setAlpha(nazov);
	//*poNazvoch = fNazov->vyfiltrujNazov(*poPrislusnosti, true, poNazvoch);

	this->clear(poNazvoch);
	this->clear(poPrislusnosti);
	this->clear(vysledok);

	delete fNazov;
	delete fTyp;

}

/*
void Vyhladaj::uloha3b(int dolnaH, int hornaH, std::string nazovPrislusnosti, TypUzemnejJednotky typ)
{
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vratenaTabulka = roztried_->getTabulkaVsetkehoPodlaNazvu();
	FilterTypUzemnaJednotka* fTyp = new FilterTypUzemnaJednotka();
	fTyp->setAlpha(typ);
	LinkedList<UzemnaJednotka*>* list = roztried_->getTabulkaVsetkehoPodlaNazvu().operator[](nazovPrislusnosti);
	FilterVolici* fVol = new FilterVolici();
	fVol->setDolnaHranica(dolnaH);
	fVol->setHornaHranica(hornaH);
	for (size_t i = 0; i < list->size(); i++)
	{
		UzemnaJednotka* uJ = (*list)[i];
		FilterPrislusnost* prislusnost = new FilterPrislusnost(uJ);
		prislusnost->setAlpha(true);		
		vratenaTabulka = prislusnost->vyfiltrujPrislusnost(vratenaTabulka, false);
		vratenaTabulka = fTyp->vyfiltrujTypUzemnejJednotky(vratenaTabulka, false);
		vratenaTabulka = fVol->vyfiltrujVolicov(vratenaTabulka, true);
		delete prislusnost;
	}

	if (vratenaTabulka.size() == 0)
	{
		cout << u8"Nenašiel sa žiadny výsledok! " << endl;
	}
}

void Vyhladaj::uloha3c(double dolnaH, double hornaH, std::string nazovPrislusnosti, TypUzemnejJednotky typ)
{
	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vratenaTabulka = roztried_->getTabulkaVsetkehoPodlaNazvu();
	FilterTypUzemnaJednotka* fTyp = new FilterTypUzemnaJednotka();
	fTyp->setAlpha(typ);
	LinkedList<UzemnaJednotka*>* list = roztried_->getTabulkaVsetkehoPodlaNazvu().operator[](nazovPrislusnosti);
	FilterUcast* fUc = new FilterUcast();
	fUc->setDolnaHranica(dolnaH);
	fUc->setHornaHranica(hornaH);
	for (size_t i = 0; i < list->size(); i++)
	{
		UzemnaJednotka* uJ = (*list)[i];
		FilterPrislusnost* prislusnost = new FilterPrislusnost(uJ);
		prislusnost->setAlpha(true);
		vratenaTabulka = prislusnost->vyfiltrujPrislusnost(vratenaTabulka, false);
		vratenaTabulka = fTyp->vyfiltrujTypUzemnejJednotky(vratenaTabulka, false);
		vratenaTabulka = fUc->vyfiltrujUcast(vratenaTabulka);
		delete prislusnost;
	}

}
*/
void Vyhladaj::clear(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaZmazanie)
{
	for (const auto& temp : *tabulkaNaZmazanie)
	{			
		string kluc = temp->getKey();
		delete (*tabulkaNaZmazanie)[kluc];
	}
	tabulkaNaZmazanie->clear();
	delete tabulkaNaZmazanie;
}
