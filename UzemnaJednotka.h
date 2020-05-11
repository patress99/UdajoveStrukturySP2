#pragma once
#include "sorted_sequence_table.h"

enum TypUzemnejJednotky
{
	OBEC,
	OKRES,
	KRAJ,
	STAT
};

using namespace structures;
using namespace std;
class UzemnaJednotka
{
public:
	UzemnaJednotka(string nazov, TypUzemnejJednotky typ, UzemnaJednotka* kamPatrim);
	~UzemnaJednotka();

	string getNazov();
	TypUzemnejJednotky getTypUzemnejJednotky();
	SortedSequenceTable<int, UzemnaJednotka*>* getKtoPatriDoMna();
	UzemnaJednotka* getkamPatrimJa();
	void pridajPotomka(int key, UzemnaJednotka* uJ);


	void setUcast(double ucast);
	double getUcast();

	void setPocetZapisanychVolicov(int pocet);
	int getPocetZapisanychVolicov();

	void setPocetZucastnenych(int pocet);
	int getPocetZUcastnenych();

	double ucastVPct();


private:
	string nazov_;
	SortedSequenceTable<int, UzemnaJednotka*>* ktoPatriDoMna_;
	UzemnaJednotka* kamPatrimJa_;
	TypUzemnejJednotky typUzemnejJednotky_;
	double kodObce_, pocet_zap_volicov_, pocet_zuc_volicov_;
	double ucast_;



};

