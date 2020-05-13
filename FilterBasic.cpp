#include "FilterBasic.h"

FilterBasic::FilterBasic() :
	roztried_(new Roztried())
{
	roztried_->roztriedUzemneJednotky();
	roztried_->priradDataObciam();
}

FilterBasic::~FilterBasic()
{
	delete roztried_;
}

void FilterBasic::filtrujPodlaNazvu(string nazovObce)
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
				cout << (*uj)[i]->getNazov() << u8", patr� do: " << (*uj)[i]->getkamPatrimJa()->getNazov() << u8", po�et zap�san�ch voli�ov " << (*uj)[i]->getPocetZapisanychVolicov() << 
				u8" volebn� ��as�:"  << (*uj)[i]->ucastVPct() << endl;
			}
			else
			{
				cout << "Stat: " << (*uj)[i]->getNazov() << ", pocet zapisanych volicov: " << (*uj)[i]->getPocetZapisanychVolicov() << u8" ��as�: " << (*uj)[i]->ucastVPct() << endl;
			}

		}
	}
}

void FilterBasic::filterVolici(int dolnaHranica, int hornaHranica)
{
	for (TableItem<int, UzemnaJednotka*>* temp : roztried_->getTabulkaVsetkeho())
	{
		if (temp->accessData()->getPocetZapisanychVolicov() >= dolnaHranica && temp->accessData()->getPocetZapisanychVolicov() <= hornaHranica)
		{
			cout << temp->accessData()->getNazov() << " " << temp->accessData()->getkamPatrimJa()->getNazov() << " " << temp->accessData()->getPocetZapisanychVolicov() << endl;
		}

	}
}

void FilterBasic::vypisPodlaNazvu()
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
