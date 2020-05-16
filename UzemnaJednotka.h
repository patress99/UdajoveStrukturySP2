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

	void setPlatneHlasy(double pocet){this->platneHlasy_ += pocet;};
	int getPlatneHlasy(){return this->platneHlasy_;};

	void setPocetVolicovZCudziny(int pocet){this->p_noc += pocet;};
	int getPocetVolicovZCudziny(){return this->p_noc;};

	void setPocetVolicovOsobne(int pocet){this->p_ooo += pocet;};
	int getPocetVolicovOsobne(){return this->p_ooo;};
	
	void setSpolu(int pocet){this->osobne_aj_z_cudziny_ += pocet;};

	double podielPlatnychHlasov(){return platneHlasy_/pocet_zuc_volicov_ * 100;};

	double ucastVPct();
	void splnaFilter(bool nastav);
	void vypis();

private:
	string nazov_;
	SortedSequenceTable<int, UzemnaJednotka*>* ktoPatriDoMna_;
	UzemnaJednotka* kamPatrimJa_;
	TypUzemnejJednotky typUzemnejJednotky_;
	double  pocet_zap_volicov_, pocet_zuc_volicov_, platneHlasy_;
	double ucast_;
	int kodUJ_;
	bool splnaFilter_;
	int p_ooo, p_noc, osobne_aj_z_cudziny_;



};

