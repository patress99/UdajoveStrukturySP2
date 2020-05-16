#include "Vyhladaj.h"
#include "array_list.h"
Vyhladaj::Vyhladaj() :
	roztried_(new Roztried())
{
	roztried_->roztriedUzemneJednotky();
	roztried_->priradDataObciam();
	this->filterNazov = false;
	this->filterPrislusnost = false;
	this->filterTyp = false;
	this->filterUcast = false;
	this->filterVolici = false;
	this->kriteriumNazov = false;
	this->kriteriumUcast = false;
	this->kriteriumVolici = false;
}

Vyhladaj::~Vyhladaj()
{	
	delete roztried_;
}

void Vyhladaj::uloha3a(std::string nazov, std::string nazovPrislusnosti, TypUzemnejJednotky typ, double dolnaHUcast, double hornaHUcast, int dolnaHVolici, int hornaHVolici)
{

	FilterVolici* fUc = nullptr;
	FilterPrislusnost* prislusnost = nullptr;
	FilterTypUzemnaJednotka* fTyp = nullptr;
	FilterNazov* fNazov = nullptr;
	FilterUcast* fUcast = nullptr;

	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* zaciatocnaTabulka = roztried_->getTabulkaVsetkehoPodlaNazvu();

	if (this->filterUcast)
	{
		fUcast = new FilterUcast();
		fUcast->setDolnaHranica(dolnaHUcast);
		fUcast->setHornaHranica(hornaHUcast);
		zaciatocnaTabulka = fUcast->vyfiltrujUcast(zaciatocnaTabulka);
	}
	if (this->filterVolici)
	{
		fUc = new FilterVolici();
		fUc->setDolnaHranica(dolnaHVolici);
		fUc->setHornaHranica(hornaHVolici);
		zaciatocnaTabulka = fUc->vyfiltrujVolicov(zaciatocnaTabulka);
	}
	
	if (this->filterPrislusnost)
	{
		LinkedList<UzemnaJednotka*>* list = (*roztried_).getTabulkaVsetkehoPodlaNazvu()->operator[](nazovPrislusnosti);
		for (size_t i = 0; i < list->size(); i++)
		{
			UzemnaJednotka* uJ = (*list)[i];
			if (uJ->getTypUzemnejJednotky() != typ)
			{
				prislusnost = new FilterPrislusnost(uJ);
				prislusnost->setAlpha(true);
				zaciatocnaTabulka = prislusnost->vyfiltrujPrislusnost(zaciatocnaTabulka);
			}
		}
	}

	if (this->filterTyp)
	{
		fTyp = new FilterTypUzemnaJednotka();
		fTyp->setAlpha(typ);
		zaciatocnaTabulka = fTyp->vyfiltrujTypUzemnejJednotky(zaciatocnaTabulka);
	}
	
	if (this->filterNazov)
	{
		fNazov = new FilterNazov();
		fNazov->setAlpha(nazov);
		zaciatocnaTabulka = fNazov->vyfiltrujNazov(zaciatocnaTabulka);
	}
	
	if (this->filterNazov == false && this->filterPrislusnost == false && this->filterTyp == false && this->filterUcast == false && this->filterVolici == false)
	{
		cout << "Nezapol si ziadny filter" << endl;
	}
	else if (zaciatocnaTabulka->size() != 0)
	{
		//for (auto temp : *zaciatocnaTabulka)
		//{
		//	for (size_t i = 0; i < temp->accessData()->size(); i++)
		//	{
		//		int kod = temp->accessData()->operator[](i)->getKodUJ();
		//		//	tabulkaNaZoradenie->insert(kod, temp->accessData()->operator[](i));
		//		cout << temp->accessData()->operator[](i)->getNazov() << " " << temp->accessData()->operator[](i)->getUcast() << endl;
		//	}
		//}
		this->vyfiltruj(zaciatocnaTabulka);
	}
	else
	{
		cout << "Nenasli sa ziadne vysledky! " << endl;
	}

	if (this->filterPrislusnost)	
 	delete prislusnost;

	if (this->filterVolici)	
	delete fUc;

	if (this->filterNazov)
	delete fNazov;

	if (this->filterTyp)
	delete fTyp;	

	if (this->filterUcast)
	delete fUcast;

	

	
}

void Vyhladaj::vyfiltruj(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaSort)
{
	UnsortedSequenceTable<int, UzemnaJednotka*>* tabulkaNaZoradenie = new UnsortedSequenceTable<int, UzemnaJednotka*>();
	KriteriumNazov* kNaz = new KriteriumNazov();
	QuickSort<int, UzemnaJednotka*>* sort = new QuickSort<int, UzemnaJednotka*>;
	
	for (auto temp : *tabulkaNaSort)
	{
		LinkedList<UzemnaJednotka*>* uJ = temp->accessData();
		for (size_t i = 0; i < uJ->size(); i++)
		{
			int kluc = uJ->operator[](i)->getKodUJ();
			tabulkaNaZoradenie->insert(kluc, uJ->operator[](i));			
		}
	}
	sort->sortSKriteriom(*tabulkaNaZoradenie, *kNaz, false);

	for (auto temp : *tabulkaNaZoradenie)
	{
		cout << temp->accessData()->getNazov() << endl; 
		temp->accessData()->vypis();	
	}

	delete tabulkaNaZoradenie;
	delete kNaz;
	delete sort;
	

}

void Vyhladaj::clear(UnsortedSequenceTable<int, UzemnaJednotka*>* tabulkaNaZmazanie)
{	
	if (tabulkaNaZmazanie->getBeginIterator() != nullptr)
	{
		for (const auto& temp : *tabulkaNaZmazanie)
		{
			int kluc = temp->getKey();
			delete (*tabulkaNaZmazanie)[kluc];
		}
		tabulkaNaZmazanie->clear();
		delete tabulkaNaZmazanie;
	}		
}
