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

void Filter::filtrujPodlaNazvu(wstring nazovObce)
{
	int pocitadlo1 = 0;
	for (TableItem<int, UzemnaJednotka*>* temp : *roztried_->getTabulkaObci())
	{
		wcout << temp->accessData()->getNazov() << " " << pocitadlo1 <<endl;
		if (temp->accessData()->getNazov() == nazovObce)
		{
			wcout << temp->accessData()->getNazov() << " " << temp->accessData()->getUcast() << endl;
		}		
		pocitadlo1++;
		if (pocitadlo1 == 2927)
		{
			wcout << nazovObce << endl;
		}
	}
}
