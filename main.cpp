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
	hladacik->uloha3a(u8"Ko��ty","", OBEC, 0, 0, 0, 0);


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

		cout << u8"Zadaj pod�a ktor�ho krit�ria chce� tabu�ku utriedi� -> 1 - pod�a n�zvu, 2 - pod�a ��asti, 3 - pod�a voli�ov: " << endl;
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