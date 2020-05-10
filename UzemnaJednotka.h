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
	void setCisloOkrsku(int cisloOkrsku);
	int getCisloOkrsku();
	void setPocetZapisanychVolicov(int pocet);
	int getPocetZapisanychVolicov();
	void setPocetZucastnenychVolicov(int pocet);
	int getPocetZucastnenychVolicov();
	void setPOOO(int pocet);
	int getPOOO();
	void setPNOC(int pocet);
	int getPNOC();
	void setPHL(int pocet);
	int getPHL();
	void setP_ooo_pct(double pct);
	double getP_ooo_pct();
	void setP_noc_pct(double pct);
	double getP_noc_pct();
	void setP_hl_pct(double pct);
	double getP_hl_pct();


private:
	string nazov_;
	SortedSequenceTable<int, UzemnaJednotka*>* ktoPatriDoMna_;
	UzemnaJednotka* kamPatrimJa_;
	TypUzemnejJednotky typUzemnejJednotky_;

	int kodObce_, cisloOkrsku_, pocet_zap_volicov_,
		pocet_zuc_volicov_, p_ooo,
		p_noc, p_hl;
	double ucast_, p_ooo_pct, p_noc_pct, p_hl_pct;



};

