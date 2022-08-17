#ifndef _PERSONPROFILE_H_
#define _PERSONPROFILE_H_

#include "RadixTree.h"
#include "provided.h"

using namespace std;

class PersonProfile
{
public:
	PersonProfile(string name, string email);
	~PersonProfile();
	string GetName() const;
	string GetEmail() const;
	void AddAttValPair(const AttValPair& attVal);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;

private:
	string m_name;
	string m_email;
	int m_numPairs;
	RadixTree<set<string>>* m_attValPairs; 
	vector<AttValPair*> m_pairs;
};

#endif // _PERSONPROFILE_H_