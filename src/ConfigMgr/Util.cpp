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

#include "Util.h"


string bin2hex(const char* aBuf, int aLen)
{
    static char hexArray[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
            'D', 'E', 'F' };
    std::string ret(aLen * 2, 0);
    for (int i = 0; i < aLen; i++)
    {
        ret[i * 2] = hexArray[(0xF0 & aBuf[i]) >> 4];
        ret[i * 2 + 1] = hexArray[(0x0F & aBuf[i])];
    }
    return ret;
}



void splitStr(const std::string& aStr, const std::string& aDelim, std::vector<std::string>& aResult)
{
	size_t pos = 0;
	size_t len = aStr.length();
	size_t delimLen = aDelim.length();
	if (delimLen == 0)
		return;
	while (pos < len)
	{
		int findPos = aStr.find(aDelim, pos);
		if (findPos < 0)
		{
			aResult.push_back(aStr.substr(pos, len - pos));
			break;
		}
		aResult.push_back(aStr.substr(pos, findPos - pos));
		pos = findPos + delimLen;
	}
	return;
}