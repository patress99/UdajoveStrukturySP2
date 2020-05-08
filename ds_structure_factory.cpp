#include "ds_structure_factory.h"
#include "ds_routines.h"

using namespace std;

namespace structures {

	StructureFactory* StructureFactory::factory_ = nullptr;

	ADSFactory::ADSFactory(StructureADS ads, Structure* prototype) :
		ads_(ads),
		prototype_(prototype),
		clones_(new vector<Structure*>),
		totalCreated_(0)
	{
	}

	ADSFactory::~ADSFactory()
	{
		for (Structure* structure : *clones_)
			delete structure;
		delete clones_;
		delete prototype_;
	}

	StructureADS ADSFactory::getADS() const
	{
		return ads_;
	}

	int ADSFactory::getTotalCreated() const
	{
		return totalCreated_;
	}

	Structure* ADSFactory::operator[](const int index) const
	{
		return at(index);
	}

	Structure* ADSFactory::at(const int index) const
	{
		return DSRoutines::rangeCheck(index, size()) ? clones_->at(index) : nullptr;
	}

	size_t ADSFactory::size() const
	{
		return clones_->size();
	}

	Structure* ADSFactory::getStructureInstance()
	{
		return cloneStructure(prototype_);
	}

	Structure* ADSFactory::cloneStructure(Structure* original)
	{
		Structure* clone = original->clone();
		totalCreated_++;
		clones_->push_back(clone);
		return clone;
	}

	void ADSFactory::removeStructure(const int index)
	{
		Structure* deleted = operator[](index);
		if (deleted != nullptr)
		{
			clones_->erase(clones_->begin() + index);
			delete deleted;
		}
	}

	void ADSFactory::removeStructure(Structure* structure)
	{
		removeStructure(DSRoutines::indexInVector(*clones_, structure));
	}

	ADTFactoryManager::ADTFactoryManager(StructureADT adt) :
		adt_(adt),
		adsFactories_(new vector<ADSFactory*>),
		producedStructures_(new vector<StructureOrigin>)
	{
	}

	ADTFactoryManager::~ADTFactoryManager()
	{
		for (ADSFactory* factory : *adsFactories_)
			delete factory;
		delete adsFactories_;
		delete producedStructures_;
	}

	StructureADT ADTFactoryManager::getADT() const
	{
		return adt_;
	}

	Structure* ADTFactoryManager::operator[](const int index) const
	{
		return at(index);
	}

	Structure* ADTFactoryManager::at(const int index) const
	{
		return DSRoutines::rangeCheck(index, size()) ? producedStructures_->at(index).structure : nullptr;
	}

	size_t ADTFactoryManager::size() const
	{
		return producedStructures_->size();
	}

	void ADTFactoryManager::registerPrototype(StructureADS ads, Structure* prototype)
	{
		if (getADSFactoryByType(ads) == nullptr)
			adsFactories_->push_back(new ADSFactory(ads, prototype));
		else
			throw logic_error("Prototype for type  is already registered!");
	}

	Structure* ADTFactoryManager::getStructureInstance(StructureADS ads)
	{
		ADSFactory* adsFactory = getADSFactoryByType(ads);

		if (adsFactory != nullptr)
		{
			StructureOrigin origin;
			origin.structure = adsFactory->getStructureInstance();
			origin.adsFactory = adsFactory;

			producedStructures_->push_back(origin);
			return origin.structure;
		}
		else
			throw logic_error("error");
	}

	Structure* ADTFactoryManager::cloneStructureAtIndex(const int index)
	{
		if (DSRoutines::rangeCheck(index, producedStructures_->size()))
		{
			StructureOrigin origin = producedStructures_->at(index);
			origin.structure = origin.adsFactory->cloneStructure(origin.structure);

			producedStructures_->push_back(origin);
			return origin.structure;
		}
		else
			throw logic_error("error");
	}

	void ADTFactoryManager::removeStructure(const int index)
	{
		if (DSRoutines::rangeCheck(index, producedStructures_->size()))
		{
			StructureOrigin origin = producedStructures_->at(index);
			origin.adsFactory->removeStructure(origin.structure);
			producedStructures_->erase(producedStructures_->begin() + index);
		}
		else
			throw logic_error("error");
	}

	ADSFactory* ADTFactoryManager::getADSFactoryByType(const StructureADS ads) const
	{
		for (ADSFactory* adsFactory : *adsFactories_)
			if (adsFactory->getADS() == ads)
				return adsFactory;

		return nullptr;
	}

	ADSFactory* ADTFactoryManager::getADSFactoryByIndex(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, factoriesSize(), "Factory index out of range!");

		return adsFactories_->at(index);
	}

	size_t ADTFactoryManager::factoriesSize() const
	{
		return adsFactories_->size();
	}

	StructureFactory::StructureFactory() :
		adtManagers_(new vector<ADTFactoryManager*>)
	{
		for (int i = 0; i < StructureADT::adtCount; i++)
			adtManagers_->push_back(new ADTFactoryManager(static_cast<StructureADT>(i)));
	}

	StructureFactory::~StructureFactory()
	{
		for (ADTFactoryManager* adtManager : *adtManagers_)
			delete adtManager;
		delete adtManagers_;
	}

	StructureFactory* StructureFactory::getInstance()
	{
		if (factory_ == nullptr)
			factory_ = new StructureFactory();
		return factory_;
	}

	void StructureFactory::finalize()
	{
		delete factory_;
		factory_ = nullptr;
	}

	ADTFactoryManager* StructureFactory::getADTManagerByType(const StructureADT adt) const
	{
		return adtManagers_->at(adt);
	}

	bool StructureFactory::registerPrototype(StructureADS ads, Structure* prototype)
	{
		try
		{
			StructureADT adt = DSRoutines::convertADStoADT(ads);
			ADTFactoryManager* adtManager = (*adtManagers_)[adt];
			adtManager->registerPrototype(ads, prototype);


			return true;
		}
		catch (exception ex)
		{
			return false;
		}
	}

	Structure* StructureFactory::getStructureInstance(StructureADS ads)
	{
		try
		{
			StructureADT adt = DSRoutines::convertADStoADT(ads);
			ADTFactoryManager* adtManager = (*adtManagers_)[adt];
			return adtManager->getStructureInstance(ads);
		}
		catch (invalid_argument ex)
		{
			//UI::Logger::Error("Structure creation failed: : " + string(ex.what()));
			return nullptr;
		}
	}

}