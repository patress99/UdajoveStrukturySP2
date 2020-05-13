#pragma once
#include "UzemnaJednotka.h"

template <typename O, typename T>
class Kriterium
{
protected:
	UzemnaJednotka* uJ;

public:
	Kriterium<O, T>() {};
	~Kriterium<O, T>() {};

	virtual T ohodnot(const O& object) const = 0;

	void setUJ(UzemnaJednotka* paUJ)
	{
		uJ = paUJ;
	}
	
};




class KriteriumNazov : public Kriterium<UzemnaJednotka, std::string> {
public:
	KriteriumNazov() : Kriterium() {};
	~KriteriumNazov() {};

	string ohodnot(const UzemnaJednotka& o)const override
	{		
		return o.getNazov();
	}

};

class KriteriumUcast : public Kriterium<UzemnaJednotka, double> {
public:
	KriteriumUcast() : Kriterium() {};
	~KriteriumUcast() {};

	double ohodnot(const UzemnaJednotka& o)const override
	{
		return o.getUcast();
	}

};

class KriteriumVolici : public Kriterium<UzemnaJednotka, int> {
public:
	KriteriumVolici() : Kriterium() {};
	~KriteriumVolici() {};

	int ohodnot(const UzemnaJednotka& o)const override
	{
		return o.getPocetZapisanychVolicov();
	}

};

class KriteriumPrislusnost : public Kriterium<UzemnaJednotka, bool> {
public:
	KriteriumPrislusnost() : Kriterium() {};
	~KriteriumPrislusnost() {};

	bool ohodnot(const UzemnaJednotka& o)const override
	{	
		return o.patriPod(uJ);
	}
};

class KriteriumTyp : public Kriterium<UzemnaJednotka, TypUzemnejJednotky> {
public:
	KriteriumTyp() : Kriterium() {};
	~KriteriumTyp() {};

	TypUzemnejJednotky ohodnot(const UzemnaJednotka& o)const override
	{	
		
		return o.getTypUzemnejJednotky();
	}
};