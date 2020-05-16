#include "Vyhladaj.h"
#include "array_list.h"
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
	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* zaciatocnaTabulka = roztried_->getTabulkaVsetkehoPodlaNazvu();
	//UnsortedSequenceTable<int, UzemnaJednotka*>* tabulkaNaZoradenie = new UnsortedSequenceTable<int, UzemnaJednotka*>();
	FilterVolici* fUc = new FilterVolici();
	fUc->setDolnaHranica(0);
	fUc->setHornaHranica(60);
	zaciatocnaTabulka = fUc->vyfiltrujVolicov(zaciatocnaTabulka, false);
	FilterPrislusnost* prislusnost = nullptr;

	LinkedList<UzemnaJednotka*>* list = (*roztried_).getTabulkaVsetkehoPodlaNazvu()->operator[](nazovPrislusnosti);

	

	FilterTypUzemnaJednotka* fTyp = new FilterTypUzemnaJednotka();
	fTyp->setAlpha(typ);
	FilterNazov* fNazov = new FilterNazov();
	
	zaciatocnaTabulka = fTyp->vyfiltrujTypUzemnejJednotky(zaciatocnaTabulka, false);
	
	for (size_t i = 0; i < list->size(); i++)
	{
		UzemnaJednotka* uJ = (*list)[i];
		if (uJ->getTypUzemnejJednotky() != typ)
		{
			prislusnost = new FilterPrislusnost(uJ);
			prislusnost->setAlpha(true);
			zaciatocnaTabulka = prislusnost->vyfiltrujPrislusnost(zaciatocnaTabulka, false);


		}
	}

	fNazov->setAlpha(nazov);
	
	zaciatocnaTabulka = fNazov->vyfiltrujNazov(zaciatocnaTabulka, true);
	


	for (auto temp : *zaciatocnaTabulka)
	{
		for (size_t i = 0; i < temp->accessData()->size(); i++)
		{
			int kod = temp->accessData()->operator[](i)->getKodUJ();
		//	tabulkaNaZoradenie->insert(kod, temp->accessData()->operator[](i));
			cout << temp->accessData()->operator[](i)->getNazov() << " " << temp->accessData()->operator[](i)->getUcast() << endl;
		}
	

	}

	cout << endl;

	KriteriumUcast* kNaz = new KriteriumUcast();
	//QuickSort<int, UzemnaJednotka*>* sort = new QuickSort<int, UzemnaJednotka*>;
	//sort->sortSKriteriom(*tabulkaNaZoradenie, *kNaz, false);

	/*for (auto temp : *tabulkaNaZoradenie)
	{
		cout << temp->accessData()->getNazov() << u8" úèas: " << temp->accessData()->getUcast() << endl;
	}*/

	
	//delete fUc;
 	delete prislusnost;
	delete fUc;
	delete fNazov;
	delete fTyp;	
	delete kNaz;






	//delete sort;


	//cout << zaciatocnaTabulka->size() << endl;
	
}

void Vyhladaj::clear(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaZmazanie)
{	
	if (tabulkaNaZmazanie->getBeginIterator() != nullptr)
	{
		for (const auto& temp : *tabulkaNaZmazanie)
		{
			string kluc = temp->getKey();
			delete (*tabulkaNaZmazanie)[kluc];
		}
		tabulkaNaZmazanie->clear();
		delete tabulkaNaZmazanie;
	}
		
		
	
	
}
