#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
using namespace std;
typedef std::string::iterator sit;
int GetNum(char c)
{
	int n = (int)c;
	int n0 = (int)'0';
	int n9 = (int)'9';

	if( n >= n0 && n <= n9 )
		return c - n0;

	if( n >= 65 && n < 68)
		return 2;//A B C

	if( n >= 68 && n < 71)
		return 3;//DEF

	if( n >= 71 && n < 74)
		return 4;// GHI

	if( n >= 74 && n < 77)
		return 5;//JKL

	if( n >= 77 && n < 80)
		return 6;//MNO

	if(80 == n)
		return 7;//P
	if( n >= 82 && n < 84)//81-Q 82-R 83-S 84-T
		return 7;//RS

	if( n >= 84 && n < 87)
		return 8;

	if( n >= 87 && n < 90)
		return 9;

	cerr<<"error input";
	return 0;
}
int regular(string& s, char z)
{
	sit it = s.begin();
	int factor = 1000000;
	int nResult = 0;
	int nTemp = 0;
	for ( ;it != s.end(); ++it)
	{
		if(z == *it)
			continue;

		nTemp = GetNum(*it);
		nResult += nTemp * factor;
		factor /= 10;
	}

	return nResult;
}
const int LIMIT = 100000;
int main()
{
	int nRow = 0;
	cin >> nRow;	
	int i = 0;
	if(nRow > LIMIT)
		return 0;

	string sOne("");
	typedef std::map<int, int> mvn;
	typedef std::map<int, int>::iterator mvnit;
	mvn v_n;
	mvnit it;

	int nTemp = 0;
	for ( ; i < nRow; ++i)
	{
		cin>>sOne;
		nTemp = regular(sOne, '-');
		it = v_n.find( nTemp );
		if( it != v_n.end() )
			it->second++;
		else
			v_n.insert( std::make_pair(nTemp, 1) );
	}

	bool hasDuplicates = false;
	int nPart1(0), nPart2(0);
	char szTemp[9] = {'\0'};
	for (mvnit it = v_n.begin(); it != v_n.end(); ++it)
	{
		if( it->second > 1 ) 
		{
			nTemp = it->first;
			nPart1 = nTemp/10000;
			nPart2 = nTemp%10000;
			printf("%03d-%4d", nPart1, nPart2);
			hasDuplicates = true;
		}
	}

	if( !hasDuplicates )
		cout << "No duplicates." << endl;

	return 0;
}