#pragma once
#include "Kriterium.h"
#include "sort.h"
#include "unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
		void quick(UnsortedSequenceTable<K, T>& table, int min, int max);
		
		template <typename O, typename H>
		void sortSKriteriom(UnsortedSequenceTable<K, T>& table, Kriterium<O, H>& k, bool vzostupne);
		
		template <typename O, typename H>
		void quickSKriteriom(UnsortedSequenceTable<K, T>& table, int min, int max, Kriterium<O, H>& k, bool vzostupne);
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		quick(table, 0, table.size() - 1);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::quick(UnsortedSequenceTable<K, T>& table, int min, int max) {
		K pivot = table.getItemAtIndex((min + max) / 2).getKey();
		int lavy = min;
		int pravy = max;

		do
		{
			while (table.getItemAtIndex(lavy).getKey() < pivot)
			{
				lavy++;
			}
			while (table.getItemAtIndex(pravy).getKey() > pivot)
			{
				pravy--;
			}
			if (lavy <= pravy)
			{
				table.swap(lavy, pravy);
				lavy++;
				pravy--;
			}
		} while (lavy <= pravy);

		if (min < pravy)
		{
			quick(table, min, pravy);
		}
		if (lavy < max)
		{
			quick(table, lavy, max);
		}
	}

	template <typename K, typename T>
	template <typename O, typename H>
	void QuickSort<K, T>::sortSKriteriom(UnsortedSequenceTable<K, T>& table, Kriterium<O, H>& k, bool vzostupne)
	{
		this->quickSKriteriom(table, 0, table.size() - 1, k, vzostupne);
	}

	template <typename K, typename T>
	template <typename O, typename H>
	void QuickSort<K, T>::quickSKriteriom(UnsortedSequenceTable<K, T>& table, int min, int max, Kriterium<O, H>& k, bool vzostupne)
	{
		O* o = table.getItemAtIndex((min + max) / 2).accessData();
		H pivot = k.ohodnot(*o);
		int lavy = min;
		int pravy = max;


		if (vzostupne) {

			do
			{
				while (k.ohodnot(*table.getItemAtIndex(lavy).accessData()) < pivot)
				{
					lavy++;

				}
				while (k.ohodnot(*table.getItemAtIndex(pravy).accessData()) > pivot)
				{
					pravy--;

				}
				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				this->quickSKriteriom(table, min, pravy, k, vzostupne);
			}
			if (lavy < max)
			{
				this->quickSKriteriom(table, lavy, max, k, vzostupne);
			}
		}
		else
		{
			do
			{
				while (k.ohodnot(*table.getItemAtIndex(lavy).accessData()) > pivot)
				{
					lavy++;

				}
				while (k.ohodnot(*table.getItemAtIndex(pravy).accessData()) < pivot)
				{
					pravy--;

				}
				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				this->quickSKriteriom(table, min, pravy, k, vzostupne);
			}
			if (lavy < max)
			{
				this->quickSKriteriom(table, lavy, max, k, vzostupne);
			}
		}
	}
}
