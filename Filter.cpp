#include "Filter.h"

Filter::Filter() :
	roztried_(new Roztried())
{
	roztried_->roztriedUzemneJednotky();
	roztried_->priradDataObciam();
}

Filter::~Filter()
{
	delete roztried_;
}

void Filter::filtrujPodlaNazvu(string nazovObce)
{
	
	if (!roztried_->getTabulkaVsetkehoPodlaNazvu().containsKey(nazovObce))
	{
		cout << "Zadany nazov neexistuje" << endl;

	}
	else
	{
		LinkedList<UzemnaJednotka*>* uj = roztried_->getTabulkaVsetkehoPodlaNazvu().operator[](nazovObce);
		for (size_t i = 0; i < uj->size(); i++)
		{
			if ((*uj)[i]->getkamPatrimJa() != nullptr)
			{
				cout << (*uj)[i]->getNazov() << u8", patrí do: " << (*uj)[i]->getkamPatrimJa()->getNazov() << u8", poèet zapísaných volièov " << (*uj)[i]->getPocetZapisanychVolicov() << 
				u8" volebná úèas:"  << (*uj)[i]->ucastVPct() << endl;
			}
			else
			{
				cout << "Stat: " << (*uj)[i]->getNazov() << ", pocet zapisanych volicov: " << (*uj)[i]->getPocetZapisanychVolicov() << u8" úèas: " << (*uj)[i]->ucastVPct() << endl;
			}

		}
	}
}

void Filter::filterVolici(int dolnaHranica, int hornaHranica)
{
	for (TableItem<int, UzemnaJednotka*>* temp : roztried_->getTabulkaVsetkeho())
	{
		if (temp->accessData()->getPocetZapisanychVolicov() >= dolnaHranica && temp->accessData()->getPocetZapisanychVolicov() <= hornaHranica)
		{
			cout << temp->accessData()->getNazov() << " " << temp->accessData()->getkamPatrimJa()->getNazov() << " " << temp->accessData()->getPocetZapisanychVolicov() << endl;
		}

	}
}

void Filter::vypisPodlaNazvu()
{
	int i = 0;
	for (TableItem<string, LinkedList<UzemnaJednotka*>*>* temp : roztried_->getTabulkaVsetkehoPodlaNazvu())
	{
		for (size_t i = 0; i < temp->accessData()->size(); i++)
		{
			cout  << temp->accessData()->operator[](i)->getNazov() << endl;
		}
	}
}
