#ifndef _MATCHMAKER_H_
#define _MATCHMAKER_H_

#include "RadixTree.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

class MatchMaker 
{
public:
	MatchMaker(const MemberDatabase& database, const AttributeTranslator& translate);
	~MatchMaker();
	vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;
private:
	const MemberDatabase* m_database;
	const AttributeTranslator* m_translate;
};

#endif // _MATCHMAKER_H_