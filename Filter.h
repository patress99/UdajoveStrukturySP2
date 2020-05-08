#pragma once
#include "Roztried.h"


class Filter
{
public:
	Filter();
	~Filter();
	void filtrujPodlaNazvu(wstring nazovObce);



private:
	Roztried* roztried_;
	
};