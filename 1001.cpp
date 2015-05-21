#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;
std::string powern(const string& f, int n);
void multiplication(string& f0, int v1);
void TrimRight(string& s, char c)
{
	typedef string::iterator sit;
	sit it = s.end();
	it = --it;
	for ( ; s.size() > 0; )
	{
		if( c == *it )
		{
			it = s.erase(it);
			if( 0 == s.size() )
				break;

			--it;
		}
		else
			break;
	}
}
void TrimLeft(string& s, char c)
{
	typedef string::iterator sit;
	sit it = s.begin();
	for ( ; it != s.end(); )
	{
		if( c == *it )
			it = s.erase(it);
		else
			break;
	}
	return ;
}
int main()
{
	typedef std::pair<int, string> pr;
	typedef std::vector<pr> vpr;
	typedef std::vector<pr>::iterator vprit;;
	vpr mem;
	string sf("");
	int i(0), n(0);
	while (cin >> sf >> n)
	{
		if (sf.empty())
			break;

		if( string::npos != sf.find('.') )
			TrimRight(sf, '0');

		cout << powern(sf, n) << endl;
	}
}
std::string powern(const string& f, int n)
{
	string sResult(f);
	size_t nPos = sResult.find('.');
	if(nPos != string::npos)
	{
		string::iterator sit = sResult.begin() + nPos;
		sResult.erase(sit);
	}
	int v1 = atoi(sResult.c_str());
	int nCount = f.size();
	int nPoint = nCount - (int)nPos -1;
	int nPointCount = nPoint * n;
	int i = 1;
	for ( ; i < n; ++i)
		multiplication(sResult, v1);
	if(0 != nPointCount)
	{
		int nlen = sResult.size();
		if(nPointCount >= nlen)
		{
			int n = nPointCount - nlen;
			while(n>0)
			{
				sResult.insert(0, "0");
				--n;
			}
			sResult.insert(0, ".");
			sResult.insert(0, "0");
		}
		else
		{
			int nInsertPos = nlen - nPointCount;
			sResult.insert(nInsertPos, ".");
		}
	}
	TrimLeft(sResult, '0');
	return sResult;
}
vector<int> partion(const string& sv, int part_count)
{
	vector<int> ls1;
	int sz = sv.size();
	int i = sz - part_count;
	int temp = 0;
	string stemp("");
	while (i > 0)
	{
		stemp = sv.substr(i, part_count);
		temp = atoi(stemp.c_str());
		ls1.push_back(temp);
		i -= 4;
	}
	if (i <= 0)
	{
		i = 4 + i;
		stemp = sv.substr(0, i);
		temp = atoi(stemp.c_str());
		ls1.push_back(temp);
	}
	return ls1;
}
struct _multi
{
	_multi(int v)
	{
		n = v;
	}
	void operator()(int& v)
	{
		 v *= n;
	}
	int n;
};
void multiplication(string& f0, int v1)
{
	vector<int> vPart = partion(f0, 4);
	for_each(vPart.begin(), vPart.end(), _multi(v1));
	
	int i = 1;
	int nCount = vPart.size();
	for (; i < nCount; ++i)
	{
		int& n = vPart.at(i - 1);
		int nQuotient = n / 10000;
		n = n % 10000;

		int& n1 = vPart.at(i);
		n1 += nQuotient;
	}
	reverse(vPart.begin(), vPart.end());
	ostringstream os;
	for (vector<int>::iterator it = vPart.begin(); it != vPart.end(); ++it)
	{
		os.setf(ios_base::right);
		os.fill('0');
		os.width(4);
		os << *it;
	}
	f0 = os.str();
}