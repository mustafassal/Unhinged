#include "PersonProfile.h"

PersonProfile::PersonProfile(string name, string email) : m_numPairs(0)
{
	m_attValPairs = new RadixTree<set<string>>;
	m_name = name;
	m_email = email;
}

PersonProfile::~PersonProfile(){}

string PersonProfile::GetName() const
{
	return m_name;
}

string PersonProfile::GetEmail() const
{
	return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
	set<string>* temp = m_attValPairs->search(attval.attribute);

	if (temp == nullptr)
	{
		m_attValPairs->insert(attval.attribute, set<string>());
		temp = m_attValPairs->search(attval.attribute);
	}

	if (temp->find(attval.attribute) == temp->end())
	{
		set<string>* newVal = new set<string>(*temp);
		newVal->insert(attval.value);
		m_attValPairs->insert(attval.attribute, *newVal);
		m_numPairs++;
		delete newVal;
	}

}

int PersonProfile::GetNumAttValPairs() const
{
	return m_numPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	if (attribute_num >= m_numPairs || attribute_num < 0)
		return false;
	attval = *m_pairs[attribute_num];
	return true;
}