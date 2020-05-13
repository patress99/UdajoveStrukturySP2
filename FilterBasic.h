#pragma once
#include "Roztried.h"


class FilterBasic
{
public:
	FilterBasic();
	~FilterBasic();
	void filtrujPodlaNazvu(string nazovObce);
	void filterVolici(int dolnaHranica, int hornaHranica);
	void vypisPodlaNazvu();



private:
	Roztried* roztried_;

};