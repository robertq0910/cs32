#include "Set.h"
#include "SerialNumberSet.h"
#include <iostream>

SerialNumberSet::SerialNumberSet() {
}

bool SerialNumberSet::add(unsigned long serialNum) {
	return data.insert(serialNum);
}

int SerialNumberSet::size() const {
	return data.size();
}

void SerialNumberSet::print() const {
	// Can write to cout
	// Can use for loop
	unsigned long serialNum;
	for (int i = 0; i < data.size(); i++) {
		if (data.get(i, serialNum)) {
			std::cout << serialNum << std::endl;
		}
	}
}
