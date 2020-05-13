#pragma once
#include "Kriterium.h"
#include "sorted_sequence_table.h"
#include "linked_list.h"

template <typename O, typename T>
class Filter
{
public:
	Filter(){};	
	~Filter() {};
	virtual bool ohodnot(const O& o, const Kriterium<O, T>& k) const = 0;
	
};



template< typename O, typename T>
class Filter_fi : public Filter<O, T>
{
protected: T alpha_;

public:
	Filter_fi() : Filter<O,T>(){};
	~Filter_fi() {};	

	bool ohodnot(const O& o, const Kriterium<O, T>& k) const override
	{
		return k.ohodnot(o) == alpha_;
	}


	void setAlpha(T pAlpha)
	{
		alpha_ = pAlpha;
	}

};


template <typename O, typename T>
class Filter_FI : public Filter<O, T>
{
protected: 
	T alpha, beta;

public:

	  Filter_FI() : Filter<O, T>() {};
	  ~Filter_FI() {};

	  bool ohodnot(const O& o, const Kriterium<O, T>& c) const override
	  {
		  T result = c.ohodnot(o);
		  return result >= alpha && result <= beta;
	  }

	  void setDolnaHranica(T hodnota)
	  {
		  alpha = hodnota;
	  }
	  void setHornaHranica(T hodnota)
	  {
		  beta = hodnota;
	  }

};


class FilterNazov : public Filter_fi<UzemnaJednotka, string>
{
public:
	FilterNazov(){};
	~FilterNazov(){};

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vyfiltrujNazov(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> tabulkaNaFiltrovanie)
	{
		KriteriumNazov* kriterium = new KriteriumNazov();
		SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* pridavanaUJ = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
		
		LinkedList<UzemnaJednotka*>* uJ = tabulkaNaFiltrovanie.operator[](this->alpha_);

		for (size_t i = 0; i < uJ->size(); i++)
		{
			UzemnaJednotka* filtrovanaUJ = (*uJ)[i];
			if (this->ohodnot(*filtrovanaUJ, *kriterium))
			{
				cout << " Filter nazov: " << filtrovanaUJ->getNazov() << " " << filtrovanaUJ->getkamPatrimJa()->getNazov() << endl;				
			}
			else
			{
				uJ->removeAt(i);
			}
		}
		pridavanaUJ->insert(this->alpha_, uJ);		
		delete kriterium;
		return *pridavanaUJ;
	};
	
};


class FilterUcast : public Filter_FI<UzemnaJednotka, double>
{
	public:
		FilterUcast(){};
		~FilterUcast() {};

		SortedSequenceTable<int, UzemnaJednotka*> vyfiltrujUcast(SortedSequenceTable<int, UzemnaJednotka*> tabulkaNaFiltrovanie)
		{
			KriteriumUcast* kriterium = new KriteriumUcast();
			SortedSequenceTable<int, UzemnaJednotka*>* pridavanaUj = new SortedSequenceTable<int, UzemnaJednotka*>();
			for (const auto& temp : tabulkaNaFiltrovanie)
			{
				if (this->ohodnot(*temp->accessData(), *kriterium))
				{
					cout << temp->accessData()->getNazov() << " " << temp->accessData()->getkamPatrimJa()->getNazov() << " " << temp->accessData()->getPocetZapisanychVolicov() << endl;
					pridavanaUj->insert(temp->getKey(), temp->accessData());
				}

			}
			return *pridavanaUj;
		};
};

class FilterVolici : public Filter_FI<UzemnaJednotka, int>
{
public:
	FilterVolici() {};
	~FilterVolici() {};

	SortedSequenceTable<int, UzemnaJednotka*> vyfiltrujVolicov(SortedSequenceTable<int, UzemnaJednotka*> tabulkaNaFiltrovanie)
	{
		KriteriumVolici* kriterium = new KriteriumVolici();
		SortedSequenceTable<int, UzemnaJednotka*>* pridavanaUj = new SortedSequenceTable<int, UzemnaJednotka*>();

		for (const auto& temp : tabulkaNaFiltrovanie)
		{
			if (this->ohodnot(*temp->accessData(), *kriterium))
			{
				cout << temp->accessData()->getNazov() << " " << temp->accessData()->getkamPatrimJa()->getNazov() << " " << temp->accessData()->getPocetZapisanychVolicov() << endl;
				pridavanaUj->insert(temp->getKey(), temp->accessData());
			}

		}
		return *pridavanaUj;
	};
};


class FilterPrislusnost : public Filter_fi<UzemnaJednotka, bool>
{
protected:
	KriteriumPrislusnost* kriterium_;
public:
	FilterPrislusnost(UzemnaJednotka* uzJ) 
	{ 
	kriterium_ = new KriteriumPrislusnost(); 
	kriterium_->setUJ(uzJ);
	};
	~FilterPrislusnost() {delete kriterium_;};
	void setUJ(UzemnaJednotka* uJ)
	{
		this->kriterium_->setUJ(uJ);
	}

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vyfiltrujPrislusnost(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> tabulkaNaFiltrovanie, string nazov)	
	{
		SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* pridavanaUJ = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();	
		LinkedList<UzemnaJednotka*>* pridavanyList = new LinkedList<UzemnaJednotka*>();

		LinkedList<UzemnaJednotka*>* uJ = tabulkaNaFiltrovanie.operator[](nazov);;
		LinkedList<UzemnaJednotka*>* result = nullptr;

		for (size_t i = 0; i < uJ->size(); i++)
		{			
			
			UzemnaJednotka* filtrovanaUJ = (*uJ)[i];			
			if (this->ohodnot(*filtrovanaUJ, *kriterium_))
			{
				cout << "Filter prislusnosti : " << filtrovanaUJ->getNazov() << " " << filtrovanaUJ->getkamPatrimJa()->getNazov() << endl;
				pridavanyList->add(filtrovanaUJ);
			}
			
		}
		pridavanaUJ->insert(nazov, pridavanyList);
		return *pridavanaUJ;
	};


};


class FilterTypUzemnaJednotka : public Filter_fi<UzemnaJednotka, TypUzemnejJednotky>
{
public:
	FilterTypUzemnaJednotka()
	{};
	~FilterTypUzemnaJednotka() {};

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vyfiltrujTypUzemnejJednotky(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> tabulkaNaFiltrovanie, string nazovUJ)

	{
		SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* pridavanaUJ = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();		
		LinkedList<UzemnaJednotka*>* uJ = tabulkaNaFiltrovanie.operator[](nazovUJ);
		LinkedList<UzemnaJednotka*>* result = new LinkedList<UzemnaJednotka*>();
		KriteriumTyp* kriterium = new KriteriumTyp();		
			for (size_t i = 0; i < uJ->size(); i++)
			{			
				UzemnaJednotka* filtrovanaUJ = (*uJ)[i];

				if (this->ohodnot(*filtrovanaUJ, *kriterium))
				{
					cout << "Filter typ : " << filtrovanaUJ->getNazov() << " " << filtrovanaUJ->getkamPatrimJa()->getNazov() << endl;			
					result->add(filtrovanaUJ);
				}
			}

		pridavanaUJ->insert(nazovUJ, result);
		delete kriterium;
		return *pridavanaUJ;
	};


};