#pragma once
#include "Roztried.h"


class Filter
{
public:
	Filter();
	~Filter();
	void filtrujPodlaNazvu(string nazovObce);
	void filterVolici(int dolnaHranica, int hornaHranica);
	void vypisPodlaNazvu();



private:
	Roztried* roztried_;

};