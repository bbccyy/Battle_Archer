#pragma once
#include <string>
#include <queue>
#include <vector>
#include <map>

#include "Framework/Transform.h"
#include "Log/Log.h"

enum PathCompleteState
{
	PathCompleteState_NotCalculated = 0,
	PathCompleteState_Error,
	PathCompleteState_Complete,
	PathCompleteState_Partial
};