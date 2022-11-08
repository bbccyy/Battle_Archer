
#include <iostream>
#include <fstream>
#include "test.h"

using namespace std;

Vector2 targetCenter, cCenter, collidePos, dir, aright, afront, halfSize;
int64 sRaidus, cRaidus, theta, thetaBase;
CollisionResults results;
bool res;
OBB obb;

bool RunTest()
{
	ifstream input;
	input.open(aFileName.c_str());

	if(!input)
	{
		cout << "Can not open CollisionTestData.txt in current direction!" << endl;
		input.close();
		return false;
	}
	string name, str;
	int64 val1 = 0, val2 = 0;
	while (input >> str)
	{
		input >> val1 >> str >> val2 >> name;
		//cout << "type = " << name << "    num = " << val1 << endl;
		input >> str >> res;
		input >> str >> collidePos.x >> collidePos.z;
		if (name == "SectorShpere")
		{
			input >> str >> targetCenter.x >> targetCenter.z;
			input >> str >> dir.x >> dir.z;
			input >> str >> sRaidus;
			input >> str >> theta;
			input >> str >> thetaBase;
			input >> str >> cCenter.x >> cCenter.z;
			input >> str >> cRaidus;
			bool isCollide = IntersectSectorSphere2D(targetCenter, dir, theta, thetaBase,
			 sRaidus, cCenter, cRaidus, results);
			if (isCollide != res)
			{
				cout << "test failure, test num = " << val1 << endl;
				cout << "isCollide = " << isCollide << endl;
				cout << "but exptect = " << res << endl;
				input.close();
				return false;
			}
			else if(isCollide == true && results.CollisionPoint != collidePos)
			{
				cout << "test failure, test num = " << val1 << endl;
				cout << "derivedPos = <" << results.CollisionPoint.x << ", " << results.CollisionPoint.z << ">" << endl;
				cout << "collidePos = <" << collidePos.x << ", " << collidePos.z << ">" << endl;
				input.close();
				return false;
			}
		}
		else if(name == "ObbSphere")
		{
			input >> str >> targetCenter.x >> targetCenter.z;
			input >> str >> aright.x >> aright.z;
			input >> str >> afront.x >> afront.z;
			input >> str >> halfSize.x >> halfSize.z;
			input >> str >> cCenter.x >> cCenter.z;
			input >> str >> cRaidus;

			obb.center.x = targetCenter.x;
			obb.center.z= targetCenter.z;
			obb.halfSize = halfSize;
			obb.front = afront;
			obb.right = aright;
			bool isCollide = IntersectOBBSphere2D( cCenter, cRaidus, &obb, results);
			if (isCollide != res)
			{
				cout << "test failure, test num = " << val1 << endl;
				cout << "isCollide = " << isCollide << endl;
				cout << "but exptect = " << res << endl;
				input.close();
				return false;
			}
			else if(isCollide == true && results.CollisionPoint != collidePos)
			{
				cout << "test failure, test num = " << val1 << endl;
				cout << "derivedPos = <" << results.CollisionPoint.x << ", " << results.CollisionPoint.z << ">" << endl;
				cout << "collidePos = <" << collidePos.x << ", " << collidePos.z << ">" << endl;
				input.close();
				return false;
			}
		}
		else
		{
			break;
		}
	}
	cout << "ALL PASS!" << endl;
	input.close();
	return true;
}

// int main()
// {
// 	RunTest();
// }