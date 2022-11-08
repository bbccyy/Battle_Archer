

#pragma once
#include <unordered_map>
#include "FunctionContainer.h"

using std::unordered_map;

template<typename Id, typename Event>
class EventDispatcher
{
	using Listener = const IFunctionContainer<void, Event&>*;
public:
	EventDispatcher()
		: mListeners(unordered_map<Id, vector<Listener> >(20))
	{
		//nothing
	}
	~EventDispatcher() = default;
	void AddListener(Id aId, Listener aListener) 
	{
		mListeners[aId].emplace_back(aListener);
	}
	void RemoveListener(Id aId, Listener aListener)
	{
		//auto& list = mListeners[aId];
		//for (auto it = list.begin(); it != list.end(); it++)  //take care when it==end while tring to do it++ 
		//{
		//	auto& tmp = *it;
		//	if (tmp == aListener)
		//	{
		//		it = list.erase(it);
		//		break;
		//	}
		//}

		auto& list = mListeners[aId];
		size_t size = list.size();
		for (int i = 0; i < size; i++)
		{
			if (list[i] == aListener)
			{
				list[i] = list[size - 1];
				list.resize(size - 1);
				break;
			}
		}
	}
	void Clear()
	{
		/*for (auto& pair : mListeners)
		{
			for (auto& listener : pair.second)
			{
				TryRecycleFunction(listener);
			}
		}*/
		mListeners.clear();
	}
	void Dispatch(Event& aEvent) const
	{
		if (mListeners.find(aEvent.GetEventId()) == mListeners.end())
		{
			return;
		}

		auto& list = mListeners.at(aEvent.GetEventId());  
		for (int i = 0; i < list.size(); i++)  //改用下表访问引用对象，防止在执行期间list发生变化 
		{
			auto& listener = list[i];
			if (listener)
				listener->operator()(aEvent); 
			else
				LOG_FATAL("get nil listener for eventId = %d", aEvent.GetEventId());
		}

		/*for (auto& listener : mListeners.at(aEvent->GetEventId()))
		{
			if (listener)
				listener->operator()(aEvent);
			else
				LOG_FATAL("get nil listener for eventId = %d", aEvent->GetEventId());
		}*/
	}
private:
	unordered_map<Id, vector<Listener> > mListeners;
};