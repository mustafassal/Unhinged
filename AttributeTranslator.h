#ifndef _ATTRIBUTTRANSLATOR_H_
#define _ATTRIBUTTRANSLATOR_H_

#include "RadixTree.h"
#include "provided.h"
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

class AttributeTranslator
{
public:
	AttributeTranslator();
	~AttributeTranslator();
	bool Load(string fileName);
	vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
	RadixTree<vector<AttValPair>*>* m_translator;
	set<string>* m_compatible;
};

#endif // _ATTRIBUTTRANSLATOR_H_