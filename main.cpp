#include <cstdio>
#include <windows.h>
#include <locale>
#include <clocale>
//#include "Roztried.h"
#include "heap_monitor.h"
#include "Filter.h"

using namespace structures;
int main()
{

	initHeapMonitor();
	/*std::locale::global(std::locale("")); // for C++
	std::cout.imbue(std::locale());*/
	setlocale(LC_NUMERIC, "de_DE.UTF-8");
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);



	Filter* filter = new Filter();
	//filter->filtrujPodlaNazvu(u8"Slovensko");
	filter->filterVolici(89000, 91000);
	delete filter;


	return 0;
};