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

		cout << u8"Zvo� si, ktor� filtre chce� ma� zapnut�: " << endl;
		cout << u8"0 - vypn��, 1 - zapn��" << endl;
		cout << u8"Filter typ: " << endl;
		cin >> filter1;
		cout << u8"Filter pr�slu�nosti: " << endl;
		cin >> filter2;		
		cout << u8"Filter ��as�: " << endl;
		cin >> filter3;
		cout << u8"Filter voli�i: " << endl;
		cin >> filter4;
		cout << u8"Filter n�zov: " << endl;
		cin >> filter5;
		
		
		if (filter1 == '1')
		{ 
			hladacik->setFilterTyp(true);			
			cout << u8"Zadaj typ �zemnej jednotky, ktor� chce� n�js�: 1-OBEC, 2-OKRES, 3-KRAJ, 4-�T�T" << endl;
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
			cout << u8"Zadaj pr�slu�nos� danej �zemnej jednotky: " << endl;
			cin >> prislusnost;
		}
			
		if (filter3 == '1')
		{ 
			hladacik->setFilterUcast(true);			
			cout << u8"Zadaj doln� a horn� hranicu ��asti: " << endl;
			cin >> dolnaHUcast;
			cin >> hornaHUcast;
			if (dolnaHUcast > hornaHUcast || hornaHUcast < 0)
			{
				cout << u8"Zadal si neplatn� ��as�." << endl;
			}//TODO while aby p�tal znova, v pr�pade ze zada neplatnu ucast
		}


		if (filter4 == '1')
		{			
			hladacik->setFilterVolici(true);
			cout << u8"Zadaj doln� a horn� hranicu voli�ov: " << endl;
			cin >> dolnaHVolici;
			cin >> hornaHVolici;
		}

		if (filter5 == '1')
		{
			cout << u8"Zadaj n�zov h�adanej �zemnej jednotky: " << endl;

			hladacik->setFilterNazov(true);
			cin >> nazovHladanejObce;
		}


		hladacik->uloha3a(nazovHladanejObce, prislusnost, typ, dolnaHUcast, hornaHUcast, dolnaHVolici, hornaHVolici);		
		spravnyTyp = true;
		delete hladacik;	;

	}
}