#include "UzemnaJednotka.h"

UzemnaJednotka::UzemnaJednotka(wstring nazov, TypUzemnejJednotky typ, UzemnaJednotka* kamPatrim) : 
	nazov_(nazov), typUzemnejJednotky_(typ), kamPatrimJa_(kamPatrim)
{
	this->ktoPatriDoMna_ = new SortedSequenceTable<int, UzemnaJednotka*>();
}

UzemnaJednotka::~UzemnaJednotka()
{
	if (this->ktoPatriDoMna_ != nullptr)
	{
		delete this->ktoPatriDoMna_;
	}	
}

void UzemnaJednotka::pridajPotomka(int key, UzemnaJednotka* uJ)
{
	this->ktoPatriDoMna_->insert(key, uJ);	
	
}

void UzemnaJednotka::setUcast(double ucast)
{
	this->ucast_ = ucast;
}

double UzemnaJednotka::getUcast()
{
	return this->ucast_;
}

void UzemnaJednotka::setCisloOkrsku(int cisloOkrsku)
{
	cisloOkrsku_ = cisloOkrsku;
}

int UzemnaJednotka::getCisloOkrsku()
{
	return cisloOkrsku_;
}

void UzemnaJednotka::setPocetZapisanychVolicov(int pocet)
{
	pocet_zap_volicov_ = pocet;
}

int UzemnaJednotka::getPocetZapisanychVolicov()
{
	return pocet_zap_volicov_;
}

void UzemnaJednotka::setPocetZucastnenychVolicov(int pocet)
{
	pocet_zuc_volicov_ = pocet;
}

int UzemnaJednotka::getPocetZucastnenychVolicov()
{
	return pocet_zuc_volicov_;
}

void UzemnaJednotka::setPOOO(int pocet)
{
	p_ooo = pocet;
}

int UzemnaJednotka::getPOOO()
{
	return p_ooo;
}

void UzemnaJednotka::setPNOC(int pocet)
{
	p_noc = pocet;
}

int UzemnaJednotka::getPNOC()
{
	return p_noc;
}

void UzemnaJednotka::setPHL(int pocet)
{
	p_hl = pocet;
}

int UzemnaJednotka::getPHL()
{
	return p_hl;
}

void UzemnaJednotka::setP_ooo_pct(double pct)
{
	p_ooo_pct = pct;
}

double UzemnaJednotka::getP_ooo_pct()
{
	return p_ooo_pct;
}

void UzemnaJednotka::setP_noc_pct(double pct)
{
	p_noc_pct = pct;
}

double UzemnaJednotka::getP_noc_pct()
{
	return p_noc_pct;
}

void UzemnaJednotka::setP_hl_pct(double pct)
{
	p_hl_pct = pct;
}

double UzemnaJednotka::getP_hl_pct()
{
	return p_hl_pct;
}

SortedSequenceTable<int, UzemnaJednotka*>* UzemnaJednotka::getKtoPatriDoMna()
{
	return ktoPatriDoMna_;
}

wstring UzemnaJednotka::getNazov()
{
	return nazov_;
}

TypUzemnejJednotky UzemnaJednotka::getTypUzemnejJednotky()
{
	return typUzemnejJednotky_;
}
