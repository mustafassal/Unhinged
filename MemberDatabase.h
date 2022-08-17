#ifndef _MEMBERDATABASE_H_
#define _MEMBERDATABASE_H_

#include "RadixTree.h"
#include "provided.h"
#include "PersonProfile.h"
#include <iostream>
#include <fstream>

using namespace std;

class MemberDatabase
{
public:
	MemberDatabase();
	~MemberDatabase();
	bool LoadDatabase(string filename);
	vector<string> FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(string email) const;
private:
	set<string>* m_email;
	set<string>* m_pairs;
	RadixTree<PersonProfile*>* m_profiles;
	RadixTree<vector<string>*>* m_tEmails;
};

#endif // _MEMBERDATABASE_H_