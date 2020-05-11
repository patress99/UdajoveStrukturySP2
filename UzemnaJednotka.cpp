#include "UzemnaJednotka.h"

UzemnaJednotka::UzemnaJednotka(string nazov, TypUzemnejJednotky typ, UzemnaJednotka* kamPatrim) :
	nazov_(nazov), typUzemnejJednotky_(typ), kamPatrimJa_(kamPatrim)
{
	this->ktoPatriDoMna_ = new SortedSequenceTable<int, UzemnaJednotka*>();
	this->pocet_zap_volicov_ = 0;
	this->ucast_ = 0.0;
	this->pocet_zuc_volicov_ = 0;
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
	this->ucast_ += ucast;
}

double UzemnaJednotka::getUcast()
{
	return this->ucast_;
}


void UzemnaJednotka::setPocetZapisanychVolicov(int pocet)
{
	this->pocet_zap_volicov_ +=  pocet;
}

int UzemnaJednotka::getPocetZapisanychVolicov()
{
	return pocet_zap_volicov_;
}

void UzemnaJednotka::setPocetZucastnenych(int pocet)
{
	this->pocet_zuc_volicov_ += pocet;
}

int UzemnaJednotka::getPocetZUcastnenych()
{
	return this->pocet_zuc_volicov_;
}

double UzemnaJednotka::ucastVPct()
{
	return ((this->pocet_zuc_volicov_/this->pocet_zap_volicov_)*100.00);
}



SortedSequenceTable<int, UzemnaJednotka*>* UzemnaJednotka::getKtoPatriDoMna()
{
	return ktoPatriDoMna_;
}

UzemnaJednotka* UzemnaJednotka::getkamPatrimJa()
{
	if (kamPatrimJa_ != nullptr)
	{
		return kamPatrimJa_;
	}
	else
	{
		return nullptr;
	}

}

string UzemnaJednotka::getNazov()
{
	return nazov_;
}

TypUzemnejJednotky UzemnaJednotka::getTypUzemnejJednotky()
{
	return typUzemnejJednotky_;
}
