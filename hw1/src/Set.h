#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

//using ItemType = std::string;
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 140;

class Set {
public: 
	Set();  
	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int i, ItemType& value) const;
	void swap(Set& other);
	void dump() const;
private:
	ItemType m_items[DEFAULT_MAX_ITEMS];
	int m_size;
};

#endif