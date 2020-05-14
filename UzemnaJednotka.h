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

	string getNazov() const;
	TypUzemnejJednotky getTypUzemnejJednotky() const;
	SortedSequenceTable<int, UzemnaJednotka*>* getKtoPatriDoMna();
	UzemnaJednotka* getkamPatrimJa();
	void vymaz();
	bool patriPod(UzemnaJednotka* uJ) const;

	void pridajPotomka(int key, UzemnaJednotka* uJ);
	void setKodUJ(int key);
	int getKodUJ() const;

	void setUcast(double ucast);
	double getUcast() const;

	void setPocetZapisanychVolicov(int pocet);
	int getPocetZapisanychVolicov() const;

	void setPocetZucastnenych(int pocet);
	int getPocetZUcastnenych();

	double ucastVPct();


private:
	string nazov_;
	SortedSequenceTable<int, UzemnaJednotka*>* ktoPatriDoMna_;
	UzemnaJednotka* kamPatrimJa_;
	TypUzemnejJednotky typUzemnejJednotky_;
	double  pocet_zap_volicov_, pocet_zuc_volicov_;
	double ucast_;
	int kodUJ_;



};

