#include <cstdio>
#include <windows.h>
//#include "Roztried.h"
#include "heap_monitor.h"
#include "Filter.h"

class My_punct : public std::numpunct<char> {
protected:
	char do_decimal_point() const { return ','; }//comma
};

using namespace structures;
int main()
{
	setlocale(LC_NUMERIC, "de_DE.UTF-8");
	initHeapMonitor();
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	/*Roztried *roztried = new Roztried();
	roztried->roztriedUzemneJednotky();
	roztried->priradDataObciam();*/
	//ArrayList<int>* arrayList = new ArrayList<int>();
	Filter* filter = new Filter();
	filter->filtrujPodlaNazvu(L"Zahranièie");
	delete filter;
	//delete roztried;
	return 0;
};