#include "MemberDatabase.h"

MemberDatabase::MemberDatabase()
{
	m_email = new set<string>;
	m_pairs = new set<string>;
	m_profiles = new RadixTree<PersonProfile*>;
	m_tEmails = new RadixTree<vector<string>*>;
}

MemberDatabase::~MemberDatabase() 
{
	for (set<string>::iterator it = m_email->begin(); it != m_email->end(); it++) 
	{
		PersonProfile** x = m_profiles->search(*it);

		if (x != nullptr)
			delete (*x);
	}

	delete m_email;
	delete m_profiles;

	for (set<string>::iterator it = m_pairs->begin(); it != m_pairs->end(); it++) 
	{
		vector<string>** y = m_tEmails->search(*it);

		if (y != nullptr)
			delete (*y);
	}
	delete m_pairs;
	delete m_tEmails;
}

bool MemberDatabase::LoadDatabase(string filename)
{
	
	ifstream file(filename);

	if (!file)
		return false;

	if (file.is_open()) 
	{
		int ctr = 0;
		string ignore, name, email, attr, val;

		while (file.good()) 
		{
			getline(file, name);
			getline(file, email);

			if (m_profiles->search(email) != nullptr)
				return false;

			m_email->insert(email);
			PersonProfile* add = new PersonProfile(name, email);
			file >> ctr;
			getline(file, ignore);

			for (int i = 0; i != ctr; i++) 
			{
				getline(file, attr, ',');
				getline(file, val);
				add->AddAttValPair(AttValPair(attr, val));
				std::string key = attr + val;
				std::vector<std::string>** v_email = m_tEmails->search(key);
				if (v_email == nullptr) 
				{
					m_tEmails->insert(key, new std::vector<std::string>);
					m_pairs->insert(key);
					v_email = m_tEmails->search(key);
				}
				(*v_email)->push_back(email);
			}
			getline(file, ignore);
			m_profiles->insert(email, add);
		}
	}
	return true;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	string target = input.attribute + input.value;
	vector<string>** match = m_tEmails->search(target);

	if (match != nullptr) 
		return **match;

	return vector<string>(); 
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const 
{
	PersonProfile** x = m_profiles->search(email);
	
	if (x != nullptr)
		return *x;

	return nullptr;
}