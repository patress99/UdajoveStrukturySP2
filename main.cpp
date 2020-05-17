#include <cstdio>
#include <windows.h>
#include <locale>
#include <clocale>
//#include "Roztried.h"
#include "heap_monitor.h"
#include "FilterBasic.h"
#include "Vyhladaj.h"
#include <codecvt>
#include <string>
#include <io.h>
#include <fcntl.h>
#pragma execution_character_set( "utf-8" )

#define MAX_INPUT_LENGTH 255

using namespace structures;
std::string wstring_to_utf8(const std::wstring& str);
std::wstring utf8_to_wstring(const std::string& str);
std::string utf8_encode(const std::wstring& wstr);
std::wstring utf8_decode(const std::string& str);

void spusti();

int wmain(int argc, wchar_t* argv[])
{
	//SetConsoleCP(1250);
	_setmode(_fileno(stdout), _O_U16TEXT);
	//SetConsoleOutputCP(65001);
	initHeapMonitor();
	//SetConsoleOutputCP(CP_UTF8);
	//SetConsoleCP(CP_UTF8);
	//setlocale(LC_ALL, "");
	//locale sk("Slovak");
	//locale::global(sk);


	Vyhladaj* hladacik = new Vyhladaj();	
	hladacik->setFilterNazov(true);

	wstring s;
	wcin >> s;

	wcout << s << endl;

	
	//spusti();
	hladacik->uloha3a(u8"Košúty","", OBEC, 0, 0, 0, 0);


	return 0;
};


std::string wstring_to_utf8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

std::wstring utf8_to_wstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}

// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring& wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

// Convert an UTF8 string to a wide Unicode String
std::wstring utf8_decode(const std::string& str)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}


void spusti()
{
	Vyhladaj* hladacik = new Vyhladaj();
	bool spravnyTyp = false;

	while(spravnyTyp == false)
	{	
		char filter1, filter2, filter3, filter4, filter5, typUJ, kriterium;
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

		cout << u8"Zadaj pod¾a ktorého kritéria chceš tabu¾ku utriedi -> 1 - pod¾a názvu, 2 - pod¾a úèasti, 3 - pod¾a volièov: " << endl;
		cin >> kriterium;

		if (kriterium == '1')
			hladacik->setKriteriumNazov(true);

		if (kriterium == '2')
			hladacik->setKriteriumUcast(true);

		if (kriterium == '3')
			hladacik->setKriteriumVolici(true);


		hladacik->uloha3a(nazovHladanejObce, prislusnost, typ, dolnaHUcast, hornaHUcast, dolnaHVolici, hornaHVolici);		
		spravnyTyp = true;
		delete hladacik;

	}
}