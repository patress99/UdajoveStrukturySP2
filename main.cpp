#include <cstdio>
#include <windows.h>
#include <locale>
#include <clocale>
//#include "Roztried.h"
#include "heap_monitor.h"
#include "FilterBasic.h"
#include "Vyhladaj.h"


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
	/*Roztried* roz =  new Roztried();
	roz->roztriedUzemneJednotky();
	roz->priradDataObciam();
	roz->patrim("kkt");*/
	
	Vyhladaj* hladacik = new Vyhladaj();
	string nacitalSom = "Poltár";
	hladacik->filtruj(u8"Lúèky" , u8"Banskobystrický kraj", OBEC);
	////filter->filtrujPodlaNazvu(u8"Selce");
	///filter->filterVolici(800, 1500);
	//filter->vypisPodlaNazvu();
	//filter->vypisPodlaNazvu();
	//delete hladacik;
	delete hladacik;

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
						FilterBasic* f = new FilterBasic();
						f->filtrujPodlaNazvu(nazov);
			
					}
			} while (opakuj1);
			break;
		default:
			break;
		}

	} while (moznost != '5');
}