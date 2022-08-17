#include "AttributeTranslator.h"

AttributeTranslator::AttributeTranslator()
{
	m_compatible = new set<string>;
	m_translator = new RadixTree<vector<AttValPair>*>;
}

AttributeTranslator::~AttributeTranslator()
{

}

bool AttributeTranslator::Load(string filename)
{
	ifstream fileOpener(filename);

	if (!fileOpener)
		return false;

	if (fileOpener.is_open()) 
	{
		string sAttr, sVal, cAttr, cVal;

		while (fileOpener.good()) 
		{
			getline(fileOpener, sAttr, ',');
			getline(fileOpener, sVal, ',');
			getline(fileOpener, cAttr, ',');
			getline(fileOpener, cVal);

			string pair = sAttr + sVal;
			AttValPair pairComp(cAttr, cVal);


			vector<AttValPair>** compatible = m_translator->search(pair);
			if (compatible == nullptr)
			{
				m_translator->insert(pair, new std::vector<AttValPair>);
				compatible = m_translator->search(pair);
				m_compatible->insert(pair);
			}
			(*compatible)->push_back(pairComp);
		}
	}

	return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	string avp;
	avp += source.attribute;
	avp += source.value;
	vector<AttValPair>** compatible = m_translator->search(avp);

	if (compatible != nullptr)
		return **compatible;
	
	return vector<AttValPair>();
}