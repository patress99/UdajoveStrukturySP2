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

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vyfiltrujNazov(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> tabulkaNaFiltrovanie, bool vypis, SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* vyfiltrovanaTabulka)
	{
		KriteriumNazov* kriterium = new KriteriumNazov();
		//SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* vyfiltrovanaTabulka = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
		LinkedList<UzemnaJednotka*>* result = new LinkedList<UzemnaJednotka*>();		
	//	cout << this->alpha_ << " " << tabulkaNaFiltrovanie.size() << endl;

		LinkedList<UzemnaJednotka*>* uJ;
		if (tabulkaNaFiltrovanie.containsKey(this->alpha_))
		{
			uJ = tabulkaNaFiltrovanie.operator[](this->alpha_);
		}
		else
		{
			cout << u8"Žiadny výsledok" <<endl;
			delete kriterium;
			delete result;
			return tabulkaNaFiltrovanie;
		}
		

		for (size_t i = 0; i < uJ->size(); i++)
		{
			UzemnaJednotka* filtrovanaUJ = (*uJ)[i];
			if (this->ohodnot(*filtrovanaUJ, *kriterium))
			{
				if (vypis)				
				{ 
					cout << " Filter nazov: " << filtrovanaUJ->getNazov() << " " << filtrovanaUJ->getkamPatrimJa()->getNazov() << endl;		
					result->add(filtrovanaUJ);
				}
				else			
					result->add(filtrovanaUJ);
			}
		}

		vyfiltrovanaTabulka->insert(this->alpha_, result);		
		delete kriterium;
		return *vyfiltrovanaTabulka;
	};
	
};


class FilterUcast : public Filter_FI<UzemnaJednotka, double>
{
	public:
		FilterUcast(){};
		~FilterUcast() {};

		SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vyfiltrujUcast(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> tabulkaNaFiltrovanie)
		{
			KriteriumUcast* kriterium = new KriteriumUcast();
			SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* pridavanaUj = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
			LinkedList<UzemnaJednotka*>* result = new LinkedList<UzemnaJednotka*>();

			string nazov;
			for (const auto& temp : tabulkaNaFiltrovanie)
			{
				for (size_t i = 0; i < temp->accessData()->size(); i++)
				{
					UzemnaJednotka* filtrovanaUJ = temp->accessData()->operator[](i);
					if (this->ohodnot(*filtrovanaUJ, *kriterium))
					{
						cout << filtrovanaUJ->getNazov() << " " << filtrovanaUJ->getkamPatrimJa()->getNazov() << " " << filtrovanaUJ->getUcast() << endl;
						result->add(filtrovanaUJ);
						nazov = filtrovanaUJ->getNazov();
					}

				}

			}
			pridavanaUj->insert(nazov, result);
			return *pridavanaUj;
		};
};

class FilterVolici : public Filter_FI<UzemnaJednotka, int>
{
public:
	FilterVolici() {};
	~FilterVolici() {};

	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> vyfiltrujVolicov(SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> tabulkaNaFiltrovanie, bool vypis)
	{
		KriteriumVolici* kriterium = new KriteriumVolici();
		SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* pridavanaUj = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
		LinkedList<UzemnaJednotka*> *result = new LinkedList<UzemnaJednotka*>();


		string nazov;
		for (const auto& temp : tabulkaNaFiltrovanie)
		{
			for (size_t i = 0; i < temp->accessData()->size(); i++)
			{
				UzemnaJednotka* filtrovanaUJ = temp->accessData()->operator[](i);
				if (this->ohodnot(*filtrovanaUJ, *kriterium))
				{
					if (vypis)
					{
						cout << temp->accessData()->operator[](i)->getNazov() << " " << temp->accessData()->operator[](i)->getkamPatrimJa()->getNazov() << " " << temp->accessData()->operator[](i)->getPocetZapisanychVolicov() << endl;

					}
					else
					{
						nazov = temp->accessData()->operator[](i)->getNazov();
						result->add(filtrovanaUJ);
					}

				}
			}

		}
		pridavanaUj->insert(nazov, result);
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

	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* vyfiltrujPrislusnost(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaFiltrovanie, bool vypis, SequenceTable<string, LinkedList<UzemnaJednotka*>*>* pridavanaUJ)
	{
	//	SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>* pridavanaUJ = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();	
		LinkedList<UzemnaJednotka*>* result = nullptr;
		pridavanaUJ->clear();
		string nazov;
		int pocitadlo = 0;




		for (auto temp : *tabulkaNaFiltrovanie)
		{
			for (size_t i = 0; i < temp->accessData()->size(); i++)
			{
				UzemnaJednotka* filtrovanaUJ = temp->accessData()->operator[](i);

				if (this->ohodnot(*filtrovanaUJ, *kriterium_))
				{
					if(vypis)
					cout << "Filter prislusnosti : " << filtrovanaUJ->getNazov() << " " << filtrovanaUJ->getkamPatrimJa()->getNazov() << endl;
					else
					{ 
						nazov = temp->accessData()->operator[](i)->getNazov();
						if (!pridavanaUJ->containsKey(nazov))
						{
							result = new LinkedList<UzemnaJednotka*>();
							//cout << pocitadlo++ << endl;
							//cout << filtrovanaUJ->getNazov() << endl;
							result->add(filtrovanaUJ);
							pridavanaUJ->insert(nazov, result);
						}
						else
						{
							result = pridavanaUJ->operator[](nazov);
							//cout << pocitadlo++ << endl;

							//cout << filtrovanaUJ->getNazov() << endl;
							result->add(filtrovanaUJ);
						}
					}
				}
			}
		
		}
		
		return pridavanaUJ;
	};


};


class FilterTypUzemnaJednotka : public Filter_fi<UzemnaJednotka, TypUzemnejJednotky>
{
public:
	FilterTypUzemnaJednotka()
	{};
	~FilterTypUzemnaJednotka() {};

	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* vyfiltrujTypUzemnejJednotky(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaFiltrovanie, bool vypis, SequenceTable<string, LinkedList<UzemnaJednotka*>*>* pridavanaUJ)

	{
		LinkedList<UzemnaJednotka*>* result = nullptr;
		KriteriumTyp* kriterium = new KriteriumTyp();		
		string nazov;
		for (auto temp : *tabulkaNaFiltrovanie )
		{
			for (size_t i = 0; i < temp->accessData()->size(); i++)
			{
				UzemnaJednotka* filtrovanaUJ = temp->accessData()->operator[](i);
				if (this->ohodnot(*filtrovanaUJ, *kriterium))
				{
					if (vypis)
					{
						cout << "Filter typ : " << filtrovanaUJ->getNazov() << " " << filtrovanaUJ->getkamPatrimJa()->getNazov() << endl;
					}
					else
					{
						nazov = temp->accessData()->operator[](i)->getNazov();
						if (!pridavanaUJ->containsKey(nazov))
						{
							result = new LinkedList<UzemnaJednotka*>();
							result->add(filtrovanaUJ);
							pridavanaUJ->insert(nazov, result);
						}
						else
						{
							result = pridavanaUJ->operator[](nazov);
							result->add(filtrovanaUJ);

						}
					
					}

				}
			}			
		}

		delete kriterium;
		return pridavanaUJ;
	};


};