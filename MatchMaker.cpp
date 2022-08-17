#include "MatchMaker.h"

MatchMaker::MatchMaker(const MemberDatabase& database, const AttributeTranslator& translate)
{
	m_database = &database;
	m_translate = &translate;
}

MatchMaker::~MatchMaker(){}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const 
{
	const PersonProfile* person = m_database->GetMemberByEmail(email);

	unordered_set<AttValPair, string> findMembers; 
	for (int i = 0; i != person->GetNumAttValPairs(); i++) 
	{
		AttValPair attVal;
		person->GetAttVal(i, attVal);

		vector<AttValPair> comp = m_translate->FindCompatibleAttValPairs(attVal);
		for (vector<AttValPair>::iterator it = comp.begin(); it != comp.end(); i++) 
			findMembers.insert(*it);
	}

	unordered_map<string, int> emailCtr;
	for (unordered_set<AttValPair, string>::iterator it = findMembers.begin(); it != findMembers.end(); it++)
	{
		vector<string> mPair = m_database->FindMatchingMembers(*it);
		for (vector<string>::iterator i = mPair.begin(); i != mPair.end(); i++) 
			if (*i != person->GetEmail()) 
				emailCtr[*i]++;
	}

	vector<EmailCount> temp;
	for (unordered_map<string, int>::iterator it = emailCtr.begin(); it != emailCtr.end(); it++) 
		if (it->second >= threshold) 
			temp.push_back(EmailCount(it->first, it->second));

	sort(temp.begin(), temp.end()); 
	return temp;
}
