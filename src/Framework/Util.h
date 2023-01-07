/**********************************************************************************************************************
 *
 * Copyright (c) 2010 babeltime.com, Inc. All Rights Reserved
 * $Id$
 *
 **********************************************************************************************************************/
 
/**
 * @file $HeadURL$
 * @author $Author$
 * @date $Date$
 * @version $Revision$
 * @brief
 *
 **/

#pragma once

#include <string>
#include <sstream>
#include <vector>

const constexpr static char* BATTLE_CODE_VERSION = "2023-01-06 11:20:43";

#ifdef __ANDROID__

namespace std
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}
#endif

template<typename T>

bool InVector(const std::vector<T> aArr, const T& aValue)
{
	for (int i = 0; i < aArr.size(); i++)
	{
		if (aArr[i] == aValue)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
void uniqEmplaceBackToVector(std::vector<T>& aArr, const T& aValue)
{
	for (int i = 0; i < aArr.size(); i++)
	{
		if (aArr[i] == aValue)
		{
			return;
		}
	}
	aArr.emplace_back(aValue);
}

template<typename T>
void selectionSort(std::vector<T*>& aArr, bool(* aCmpFunc)(const T*, const T*))
{
	int i, j, minIndex;
	int num = aArr.size();	
	for(i = 0; i < num - 1; i++)
	{
		minIndex = i;
		for (j = i + 1; j < num; j++)
		{
			if (aCmpFunc(aArr[j], aArr[minIndex]) )
			{
				minIndex = j;
			}				
		}
		if (minIndex != i)
		{
			T* tmp = aArr[i];
			aArr[i] = aArr[minIndex];
			aArr[minIndex] = tmp;
		}		
	}
}


//为了支持lua的对象池
template<typename T>
void RestoreVectorToPool(const std::vector<T>& aObj)
{
    //nothing
}

template<typename T>
void RestoreVectorElementToPool(const std::vector<T>& aObj)
{
	//nothing
}

template<typename T>
void RestoreObjToPool(const T& aObj)
{
	//nothing
}