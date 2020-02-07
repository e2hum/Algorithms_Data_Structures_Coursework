#include "lab2_drones_manager.hpp"
// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}

DronesManager::~DronesManager() {
	while(size > 0){
		remove_back();
	}
	delete(first);
	delete(last);
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	bool equal = (lhs.droneID == rhs.droneID);
	equal = (equal && (lhs.range == rhs.range));
	equal = (equal && (lhs.yearBought == rhs.yearBought));
	equal = (equal && (lhs.droneType == rhs.droneType));
	equal = (equal && (lhs.manufacturer == rhs.manufacturer));
	equal = (equal && (lhs.description == rhs.description));
	equal = (equal && (lhs.batteryType == rhs.batteryType));
	return equal;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
		if (size == 0)
		return true;
	else
		return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	DroneRecord* value = first;
	if (index > size) {
		return *last;
	}
	else if (size == 0)
		return DroneRecord(0);
	else {
		for (int count = 0; count < index; count++) {
			value->next = value->next->next;
		}
		return *value;
	}
}

unsigned int DronesManager::search(DroneRecord value) const {
	DroneRecord* position = first;
	if (size == 0)
		return 0;
	else {
		for (int index = 0; index < size; index++) {
			if (*position == value)
				return index;
			else
				return size;
		}
	}
}

void DronesManager::print() const {
	DroneRecord* printer = first;
	for (int index = 0; index < size; index++) {
		cout << first->droneID << endl;
		printer = printer->next;
	}
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	return false;
}

bool DronesManager::insert_front(DroneRecord value) {
	//case 1, empty
	if(!first){
		first = &value;
		last = &value;
	}
	//general case, nonempty
	else {
		//updates value's pointers
		value->prev = NULL;
		value->next = first;
		//update first
		first->prev = value;
		//updates manager's pointer
		first = value;
	}
	size++;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	//Case 1, empty list
	if (!first){
		first = &value;
		last = &value;
	}
	//general case, nonempty
	else {
		//updates value's pinters
		value->prev = last;
		value->next = NULL;
		//update last
		last->next = &value;
		//updates manager's pointer
		last = &value;
	}
	size++;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	return false;
}

bool DronesManager::remove_front() {
	return false;
}

bool DronesManager::remove_back() {
	return false;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	return false;
}

bool DronesManager::reverse_list() {
	return false;
}

