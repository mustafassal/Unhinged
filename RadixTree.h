#ifndef _RADIXTREE_H_
#define _RADIXTREE_H_

#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>

using namespace std;

template <typename ValueType>
class RadixTree
{
public:
	RadixTree();
	~RadixTree();
	void insert(string key, const ValueType& value);
	ValueType* search(string key) const;
private:
	map<string, ValueType*> m_pairs;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
{
	m_pairs = map<string, ValueType*>();
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
	for (auto it = m_pairs.begin(); it != m_pairs.end(); it++)
		delete it->second;
}

template <typename ValueType>
void RadixTree<ValueType>::insert(string key, const ValueType& value)
{
	auto it = m_pairs.find(key);
	if (it != m_pairs.end())
		delete it->second;

	ValueType* newVal = new ValueType(value);
	m_pairs[key] = newVal;
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(string key) const
{
	auto it = m_pairs.find(key);
	if (it != m_pairs.end())
		return it->second;

	return nullptr;
}

#endif // _RADIXTREE_H_