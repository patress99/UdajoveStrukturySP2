#include <cstdio>
#include <windows.h>
#include <locale>
#include <clocale>
//#include "Roztried.h"
#include "heap_monitor.h"
#include "Filter.h"

using namespace structures;

void spusti();

int main()
{

	initHeapMonitor();
	/*std::locale::global(std::locale("")); // for C++
	std::cout.imbue(std::locale());*/
	setlocale(LC_NUMERIC, "de_DE.UTF-8");
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	//spusti();

	Filter* filter = new Filter();
	filter->filtrujPodlaNazvu(u8"Selce");
	//filter->filterVolici(89000, 91000);
	//filter->vypisPodlaNazvu();
	//filter->vypisPodlaNazvu();
	//delete filter;


	return 0;
};

void spusti()
{
	char moznost;
	do
	{	
		cout << "Prosim zvol si co ides testovat: " << endl;
		cout << "1: Filter" << endl;


		cin >> moznost;

		switch (moznost)
		{
			bool opakuj1;

			do
			{
				case '1':
					{
						opakuj1 = true;
						string nazov;
						cout << u8"Zadaj názov územnej jednotky, ktorú chceš vyhlada: " << endl;
						cin  >> nazov;
						Filter* f = new Filter();
						f->filtrujPodlaNazvu(nazov);
			
					}
			} while (opakuj1);
			break;
		default:
			break;
		}

	} while (moznost != '5');
}