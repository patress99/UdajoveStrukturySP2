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

	//Vyhladaj* hladacik = new Vyhladaj();	
	//hladacik->setFilterNazov(true);
	
	spusti();


	return 0;
};

void spusti()
{
	Vyhladaj* hladacik = new Vyhladaj();
	bool spravnyTyp = false;
	while(spravnyTyp == false)
	{	
		char filter1, filter2, filter3, filter4, filter5, typUJ;
		string prislusnost, nazovHladanejObce;
		double dolnaHUcast = 0.0;
		double hornaHUcast = 0.0;
		int dolnaHVolici = 0;
		int hornaHVolici = 0;
		TypUzemnejJednotky typ;

		cout << u8"Zvo¾ si, ktoré filtre chceš ma zapnuté: " << endl;
		cout << u8"0 - vypnú, 1 - zapnú" << endl;
		cout << u8"Filter typ: " << endl;
		cin >> filter1;
		cout << u8"Filter príslušnosti: " << endl;
		cin >> filter2;		
		cout << u8"Filter úèas: " << endl;
		cin >> filter3;
		cout << u8"Filter volièi: " << endl;
		cin >> filter4;
		cout << u8"Filter názov: " << endl;
		cin >> filter5;
		
		
		if (filter1 == '1')
		{ 
			hladacik->setFilterTyp(true);			
			cout << u8"Zadaj typ územnej jednotky, ktorú chceš nájs: 1-OBEC, 2-OKRES, 3-KRAJ, 4-ŠTÁT" << endl;
			cin >> typUJ;
			if (typUJ == '1')
				typ = OBEC;
			if (typUJ == '2')
				typ = OKRES;
			if (typUJ == '3')
				typ = KRAJ;
			if (typUJ == '4')
				typ = STAT;			
		}


		if (filter2 == '1')
		{
			hladacik->setFilterPrislusnost(true);
			cout << u8"Zadaj príslušnos danej územnej jednotky: " << endl;
			cin >> prislusnost;
		}
			
		if (filter3 == '1')
		{ 
			hladacik->setFilterUcast(true);			
			cout << u8"Zadaj dolnú a hornú hranicu úèasti: " << endl;
			cin >> dolnaHUcast;
			cin >> hornaHUcast;
			if (dolnaHUcast > hornaHUcast || hornaHUcast < 0)
			{
				cout << u8"Zadal si neplatnú úèas." << endl;
			}//TODO while aby pýtal znova, v prípade ze zada neplatnu ucast
		}


		if (filter4 == '1')
		{			
			hladacik->setFilterVolici(true);
			cout << u8"Zadaj dolnú a hornú hranicu volièov: " << endl;
			cin >> dolnaHVolici;
			cin >> hornaHVolici;
		}

		if (filter5 == '1')
		{
			cout << u8"Zadaj názov h¾adanej územnej jednotky: " << endl;

			hladacik->setFilterNazov(true);
			cin >> nazovHladanejObce;
		}


		hladacik->uloha3a(nazovHladanejObce, prislusnost, typ, dolnaHUcast, hornaHUcast, dolnaHVolici, hornaHVolici);		
		spravnyTyp = true;
		delete hladacik;	;

	}
}