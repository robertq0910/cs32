#include "Set.h"
#include <iostream>

Set::Set() {
	m_size = 0;
}

bool Set::empty() const {
	return m_size == 0;
}

int Set::size() const {
	return m_size;
}

bool Set::insert(const ItemType& value) {
	if (m_size >= DEFAULT_MAX_ITEMS || contains(value)) {
		return false;
	}
	m_items[m_size] = value;
	m_size++;	// Check logic bc idk if I should add another one afterwards?
	return true;
}

bool Set::erase(const ItemType& value){
for (int i = 0; i < m_size; i++) {
        if (m_items[i] == value) {
            // Shift all later items to the left
            for (int j = i; j < m_size - 1; j++) {
                m_items[j] = m_items[j + 1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (int i = 0; i < m_size; i++) {
        if (m_items[i] == value)
            return true;
    }

    return false;
}

bool Set::get(int i, ItemType& value) const {
    ItemType sorted[DEFAULT_MAX_ITEMS];
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    // Copy array "m_items" to array "sorted" 
    for (int j = 0; j < m_size; j++) {
        sorted[j] = m_items[j];
    }
    // Sort array "sorted" 
    for (int j = 0; j < m_size-1; j++) {
        int minIndex = j;
        for (int k = j + 1; k < m_size; k++) {
            if (sorted[k] < sorted[minIndex]) { // If the next value is smaller, that becomes the minimum 
                minIndex = k;
            }
        }

        ItemType temp = sorted[j];
        sorted[j] = sorted[minIndex];
        sorted[minIndex] = temp;
    }

    if (i >= 0 && i < m_size) {
        value = sorted[i];
        return true;
    }    

    return false;
}

void Set::swap(Set& other) {
    // Exchange the contents of this set with the other one.
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
        ItemType temp = m_items[i];
        m_items[i] = other.m_items[i];
        other.m_items[i] = temp;

    }

    // Swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

void Set::dump() const {
    for (int i = 0; i < m_size; i++) {
        std::cerr << m_items[i] << " ";
    }
}
