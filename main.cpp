#include <cstdio>
#include <windows.h>
#include <locale>
#include <clocale>
//#include "Roztried.h"
#include "heap_monitor.h"
#include "FilterBasic.h"
#include "Vyhladaj.h"
#define MAX_INPUT_LENGTH 255



using namespace structures;

void spusti();

int main()
{
	initHeapMonitor();
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	/*wchar_t wstr[MAX_INPUT_LENGTH];
	char mb_str[MAX_INPUT_LENGTH * 3 + 1];

	unsigned long read;
	void* con = GetStdHandle(STD_INPUT_HANDLE);

	ReadConsole(con, wstr, MAX_INPUT_LENGTH, &read, NULL);

	int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, mb_str, sizeof(mb_str), NULL, NULL);
	mb_str[size] = 0;

	std::printf("ENTERED: %s\n", mb_str);
	string s = mb_str;*/

	Vyhladaj* hladacik = new Vyhladaj();	

	hladacik->uloha3a(u8"Zvolen" , u8"Zvolen", OBEC);
	delete hladacik;
	//	
	//	//hladacik->uloha3b(60000, 92000, u8"Banskobystrický kraj", OBEC);
	//	//hladacik->uloha3c(89.2, 92.0, u8"Slovensko", OBEC);


	return 0;

///*
//	initHeapMonitor();
//	/*std::locale::global(std::locale("")); // for C++
//	std::cout.imbue(std::locale());*/
//	setlocale(LC_NUMERIC, "de_DE.UTF-8");
//	SetConsoleOutputCP(CP_UTF8);
//	setvbuf(stdout, nullptr, _IOFBF, 1000);
//
//	//spusti();
//	/*Roztried* roz =  new Roztried();
//	roz->roztriedUzemneJednotky();
//	roz->priradDataObciam();
//	roz->patrim("kkt");*/
//	
//	Vyhladaj* hladacik = new Vyhladaj();
//	
//	hladacik->uloha3a(u8"Zvolen" , u8"Zvolen", OBEC);
//	
//	//hladacik->uloha3b(60000, 92000, u8"Banskobystrický kraj", OBEC);
//	//hladacik->uloha3c(89.2, 92.0, u8"Slovensko", OBEC);
//		
//	////filter->filtrujPodlaNazvu(u8"Selce");
//	///filter->filterVolici(800, 1500);
//	//filter->vypisPodlaNazvu();
//	//filter->vypisPodlaNazvu();
//	//delete hladacik;
//	delete hladacik;
//
//	return 0;*/
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