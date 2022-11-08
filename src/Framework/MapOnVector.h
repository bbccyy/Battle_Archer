/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wuqilin
* @date $Date$
* @version $Revision$
* @brief Timer”ÎTImerπ‹¿Ì∆˜
*
**/

#pragma once
#include <vector>

template<typename K, typename V>
class MapOnVector
{
public:
	struct Item
	{
		K first;
		V second;
		void Set(const Item& aOther)
		{
			this->first = aOther.first;
			this->second = aOther.second;
		}
	};

	class ConstIterator;

	class Iterator
	{
	public:
		Iterator(std::vector<Item> * aVectPtr, size_t aIndex) : mVectPtr(aVectPtr), mIndex(aIndex)
		{ }
		Iterator& operator++()
		{
			mIndex++;
			return *this;
		}
		Item& operator*()
		{
			return (*mVectPtr)[mIndex];
		}
		Item* operator->()
		{
			return &(*mVectPtr)[mIndex];
		}
		bool operator==(const Iterator& aOther)
		{
			return mVectPtr == aOther.mVectPtr && mIndex == aOther.mIndex;
		}
		bool operator!=(const Iterator& aOther)
		{
			return mVectPtr != aOther.mVectPtr || mIndex != aOther.mIndex;
		}
		bool operator==(const ConstIterator& aOther)
		{
			return mVectPtr == aOther.mVectPtr && mIndex == aOther.mIndex;
		}
		bool operator!=(const ConstIterator& aOther)
		{
			return mVectPtr != aOther.mVectPtr || mIndex != aOther.mIndex;
		}
		friend class ConstIterator;
	private:
		std::vector<Item>* mVectPtr;
		size_t mIndex;
	};

	class ConstIterator
	{
	public:
		ConstIterator(const std::vector<Item> * aVectPtr, size_t aIndex) : mVectPtr(aVectPtr), mIndex(aIndex)
		{ }
		ConstIterator& operator++()
		{
			mIndex++;
			return *this;
		}
		const Item& operator*() const
		{
			return (*mVectPtr)[mIndex];
		}
		const Item* operator->()
		{
			return &(*mVectPtr)[mIndex];
		}
		bool operator==(const ConstIterator& aOther)
		{
			return mVectPtr == aOther.mVectPtr && mIndex == aOther.mIndex;
		}
		bool operator!=(const ConstIterator& aOther)
		{
			return mVectPtr != aOther.mVectPtr || mIndex != aOther.mIndex;
		}
		bool operator==(const Iterator& aOther)
		{
			return mVectPtr == aOther.mVectPtr && mIndex == aOther.mIndex;
		}
		bool operator!=(const Iterator& aOther)
		{
			return mVectPtr != aOther.mVectPtr || mIndex != aOther.mIndex;
		}
		friend class Iterator;
	private:
		const std::vector<Item>* mVectPtr;
		size_t mIndex;
	};



public:
	MapOnVector() {};
	~MapOnVector() {};

	ConstIterator find(K aKey) const
	{
		size_t num = mArr.size();
		for (size_t i = 0; i < num; i++)
		{
			if (mArr[i].first == aKey)
			{
				return ConstIterator(&mArr, i);
			}
		}
		return end();
	}

	bool insert(K aKey, V aVal)
	{
		size_t num = mArr.size();
		for (size_t i = 0; i < num; i++)
		{
			if (mArr[i].first == aKey)
			{
				return false;
			}
		}
		Item item;
		item.first = aKey;
		item.second = aVal;
		mArr.push_back(item);
		return true;
	}

	bool erase(K aKey)
	{
		size_t num = mArr.size();
		for (size_t i = 0; i < num; i++)
		{
			if (mArr[i].first == aKey)
			{
				if (i < num - 1)
				{
					mArr[i] = mArr[num - 1];
				}
				mArr.resize(num - 1);
				return true;
			}
		}
		return false;
	}

	void clear()
	{
		mArr.clear();
	}

	int size()
	{
		return mArr.size();
	}

	std::vector<V> tovector()
	{
		std::vector<V> arr;
		size_t num = mArr.size();
		arr.reserve(num);
		for (size_t i = 0; i < num; ++i)
		{
			arr.push_back(mArr[i].second);
		}
		return arr;
	}

	MapOnVector<K,V> copy2()
	{  //TODO: Optimize this code, do not return temp value 
		MapOnVector<K, V> tmp;
		size_t num = mArr.size();
		tmp.mArr.reserve(num);
		for (size_t i = 0; i < num; ++i)
		{
			tmp.mArr.push_back(mArr[i]);
		}
		return tmp;
	}

	void copy(MapOnVector<K, V>& aVec)
	{  
		size_t num = mArr.size();
		aVec.mArr.reserve(num);
		for (size_t i = 0; i < num; ++i)
		{
			aVec.mArr.push_back(mArr[i]);
		}
	}

	Iterator begin()
	{
		return Iterator(&mArr, 0);
	}
	Iterator end()
	{
		return Iterator(&mArr, mArr.size());
	}
	ConstIterator begin() const
	{
		return ConstIterator(&mArr, 0);
	}
	ConstIterator end() const
	{
		return ConstIterator(&mArr, mArr.size());
	}

	typedef bool(*Pred)(const V&, const V&);  // return true if left > right

	void sort(Pred aPred)
	{
		if (mArr.size() <= 0)
			return;
		Item tmp;  //for common use 
		//first ver: brute force 
		for (int i = 0; i < int(mArr.size())-1; i++)
		{
			int max = i;
			for (int j = i+1; j < mArr.size(); j++)
			{
				if ((*aPred)(mArr[j].second, mArr[max].second))
				{
					max = j;
				}
			}
			if (i != max)
			{
				tmp.Set(mArr[i]);
				mArr[i].Set(mArr[max]);
				mArr[max].Set(tmp);
				/*Item& toMax = mArr[i];
				mArr[i] = mArr[max];
				mArr[max] = toMax;*/
			}
		}
	}

	typedef bool(*Filter)(const V&);  // return true if need to filter out

	void filter(Filter aFilter)
	{
		int size = mArr.size();
		for (int i = 0; i < size; )
		{
			if ((*aFilter)(mArr[i].second))
			{
				mArr[i] = mArr[size - 1];
				size--;
			}
			else
			{
				i++;
			}
		}
		mArr.resize(size);
	}

protected:
	std::vector<Item> mArr;
};
