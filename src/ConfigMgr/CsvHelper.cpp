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

#include "CsvHelper.h"



string trim(const string& input)
{
    stringstream ss;
    string output;
    ss << input;
    ss >> output;
    return output;
}


int findEnclosure(const string& aIn, char aLeft, char aRight, std::size_t& start, std::size_t& end)
{
    //[start, end) 左闭右开
    start = 0;
    end = aIn.size();
     if (aIn.empty())
    {
        return 0;
    }

    if ( aLeft != 0 )
    {
        end = aIn.size() - 1;
        while( start <= end && aIn[start] == ' ' )
        {
            start++;
        }
        if(aIn[start] != aLeft )
        {
            LOG_FATAL("not found left enclosure, left:%c in %s", aLeft, aIn.c_str());
            return -1;
        }
        start++;
        while( end > start && aIn[end] == ' ' )
        {
            end--;
        }
        //同时也检查了右包围符号为空
        if( aIn[end] != aRight )
        {
            LOG_FATAL("not found right enclosure, or not set, right:%c in %s", aLeft, aIn.c_str());
            return -1;
        }
    }
    else 
    {
        if( aRight != 0 )
        {
            LOG_FATAL("set right enclosure, not set left");
            return -1;
        }
    }
    return 0;
}



int ReadCsvRow(const char*aRowStr, const int aRowSize, vector<string>& aColumnArr)
{
	if (aRowSize<=0)
	{
		return 0;
	}
	bool inQuote = false;
	bool addLast = false;
	string str = "";
	int index = 0;
	char cur;
	char nxt;
	do
	{
		cur = aRowStr[index++];
		nxt = aRowStr[index];
		if (cur == ',')
		{
			if (inQuote)
			{
				str.push_back(cur);
			}
			else
			{
				aColumnArr.push_back(trim(str));
				str.clear();
			}
		}
		else if (cur == '"')
		{
			if (inQuote)
			{
				if (nxt == '"')
				{
					str.push_back(cur);
					cur = aRowStr[index++]; //忽略一个"
				}
				else
				{
					inQuote = false;
				}
			}
			else
			{
				inQuote = true;
			}
		}
		else if (cur == '\n')
		{
			if (inQuote)
			{
				str.push_back(cur);
			}
			else
			{
				aColumnArr.push_back(trim(str));
				addLast = true;
				break;
				str = "";
			}
		}
		else if (cur == '\r')
		{
			if (inQuote)
			{
				str.push_back(cur);
			}
		}
		else
		{
			str.push_back(cur);
		}
	} while (index < aRowSize);
	if (!addLast)
	{
		aColumnArr.push_back(trim(str));
	}

	return index;
}