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
	cout << nazovObce << endl;
	//roztried_->najdiObec(nazovObce);
	roztried_->najdiPodlaNazvu(nazovObce);
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
	/*for (TableItem<string, UzemnaJednotka*>* temp : roztried_->getTabulkaObciPodlaNazvu())
	{
		if (temp->accessData()->getPocetZapisanychVolicov() >= dolnaHranica && temp->accessData()->getPocetZapisanychVolicov() <= hornaHranica)
		{

		}

	}*/
}
