#pragma once
#include "Kriterium.h"
#include "sorted_sequence_table.h"
#include "linked_list.h"

template <typename O, typename T>
class Filter
{
protected:
	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* result_;

public:
	Filter(){};	
	~Filter() 
	{	
		cout << result_->size() << "scottie";
	if (!result_->isEmpty())
		{

			for (const auto& temp : *result_)
			{
				//string kluc = temp->getKey();
				if (temp->accessData() != nullptr)
				{
					delete temp->accessData();
				}
				//delete (*result_)[kluc];
			}
		}
		delete result_;

	};
	virtual bool ohodnot(const O& o, const Kriterium<O, T>& k) const = 0;
	
};



template< typename O, typename T>
class Filter_fi : public Filter<O, T>
{
protected: 
	T alpha_;

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
	~FilterNazov()
	{
	};

	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* vyfiltrujNazov(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaFiltrovanie, bool vypis)
	{
		this->result_ = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
		KriteriumNazov* kriterium = new KriteriumNazov();
		LinkedList<UzemnaJednotka*>* result = new LinkedList<UzemnaJednotka*>();		
		LinkedList<UzemnaJednotka*>* uJ;
		
		if (tabulkaNaFiltrovanie->containsKey(this->alpha_))
		{
			uJ = tabulkaNaFiltrovanie->operator[](this->alpha_);
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
				{
					result->add(filtrovanaUJ);
				}
			}
		}

		this->result_->insert(this->alpha_, result);		
		delete kriterium;
		return this->result_;
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

	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* vyfiltrujVolicov(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaFiltrovanie, bool vypis)
	{
		KriteriumVolici* kriterium = new KriteriumVolici();
		this->result_ = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
		LinkedList<UzemnaJednotka*> *resultList = nullptr;


		string nazov;
		for (auto temp : *tabulkaNaFiltrovanie)
		{
			for (size_t i = 0; i < temp->accessData()->size(); i++)
			{
				UzemnaJednotka* filtrovanaUJ = temp->accessData()->operator[](i);
				if (this->ohodnot(*filtrovanaUJ, *kriterium))
				{
					
					nazov = temp->accessData()->operator[](i)->getNazov();
					if (!this->result_->containsKey(nazov))
					{
						resultList = new LinkedList<UzemnaJednotka*>();
						resultList->add(filtrovanaUJ);
						this->result_->insert(nazov, resultList);
					}
					else
					{
						resultList = result_->operator[](nazov);
						resultList->add(filtrovanaUJ);
					}					
				}
			}

		}

		delete kriterium;
		return this->result_;
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
	~FilterPrislusnost() {};
	void setUJ(UzemnaJednotka* uJ)
	{
		this->kriterium_->setUJ(uJ);
	}

	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* vyfiltrujPrislusnost(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaFiltrovanie, bool vypis)
	{	
		LinkedList<UzemnaJednotka*>* resultList = nullptr;		
		this->result_ = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();		
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
						if (!this->result_->containsKey(nazov))
						{
							resultList = new LinkedList<UzemnaJednotka*>();
							resultList->add(filtrovanaUJ);
							this->result_->insert(nazov, resultList);
						}
						else
						{
							resultList = result_->operator[](nazov);
							resultList->add(filtrovanaUJ);
						}
					}
				}
			}
		}
		delete kriterium_;
		return this->result_;
	};


};


class FilterTypUzemnaJednotka : public Filter_fi<UzemnaJednotka, TypUzemnejJednotky>
{
public:
	FilterTypUzemnaJednotka()
	{};
	~FilterTypUzemnaJednotka() {};

	SequenceTable<string, LinkedList<UzemnaJednotka*>*>* vyfiltrujTypUzemnejJednotky(SequenceTable<string, LinkedList<UzemnaJednotka*>*>* tabulkaNaFiltrovanie, bool vypis)
	{
		this->result_ = new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>();
		LinkedList<UzemnaJednotka*>* resultList = nullptr;		
		int pocitadlo = 0;
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
						if (!this->result_->containsKey(nazov))
						{
							resultList = new LinkedList<UzemnaJednotka*>();
							resultList->add(filtrovanaUJ);
							this->result_->insert(nazov, resultList);
						}
						else
						{
							resultList = this->result_->operator[](nazov);
							resultList->add(filtrovanaUJ);

						}
					
					}

				}
			}			
		}
		delete kriterium;		
		return this->result_;
	};


};