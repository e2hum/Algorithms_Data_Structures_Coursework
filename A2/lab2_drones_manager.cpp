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
	first = last = NULL;
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
	//cout<<"DroneID: "<<value->droneID;
	//case 1; empty
	if (!value){
		return DroneRecord(0);
	}
	//case 2; index too big
	else if (index > size || index < 0) {
		return *last;
	}
	//general case
	else {
		for (int count = 0; count < index; count++) {
			value = value->next;	
		}
		return *value;
	}
}

unsigned int DronesManager::search(DroneRecord value) const {
	DroneRecord* position = first;
	int index = 0;
	if (size == 0)
		return 0;
	else {
		while(position) {
			if (position->droneID == value.droneID)
				return index;
		position = position->next;
		index++;
		}
		return size;
	}
}

void DronesManager::print() const {
	if (size == 0){
		cout<<"Empty";
		return;
	}else{
		DroneRecord* it = first;
		int count = 1;
		while (it){
			cout<<"Drone #: "<<count<<" DroneID: " <<it->droneID<<endl;
			it = it->next;
			count++;
		}
	}
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	// if index is out of range, return false
	if (index >= size || index < 0) {
		return false;
	}
	// if index is first position, use insert_front
	else if (index == 0)
		insert_front(value);
	// if index is last position, use insert_back
	else if (index == size-1)
		insert_back(value);
	// general case
	else {
		DroneRecord* temp = new DroneRecord(value);
		DroneRecord* it = first;
		for (int position = 0; position < index; position++) {
			it = it->next;
		}
		DroneRecord* before = it->prev;
		it->prev = temp;
		temp->next = it;
		before->next = temp;
		temp->prev = before;
	}
	return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	//case 1, empty
	if(!first){
		//DONE DO THIS first = &value; SAVING POINTER (heap) TO STACK 
		//INSTEAD
		first = new DroneRecord(value);
		last = first;
	}
	//general case, nonempty
	else {
		//updates value's pointers
		DroneRecord *temp = new DroneRecord(value);
		temp->prev = NULL;
		temp->next = first;
		//update first to be second
		first->prev = temp;
		//updates manager's pointer
		first = temp;
	}
	size++;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	//Case 1, empty list
	if (!first){
		first = new DroneRecord(value);
		last = first;
	}
	//general case, nonempty
	else {
		//updates value's pinters
		DroneRecord *temp = new DroneRecord(value);
		temp->prev = last;
		temp->next = NULL;
		//update last
		last->next = temp;
		//updates manager's pointer
		last = temp;
	}
	size++;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	//empty list
	if (!first)
		return false;
	//invalid index
	else if (index>size-1 || index < 0){
		return false;
	}
	//general case
	else{
		DroneRecord * itera = first;
		for(int x = 0; x < index; x++){
			itera = itera->next;
		}
		itera->prev->next = itera->next;
		itera->next->prev = itera->prev;
		delete itera;
		itera = NULL;
	}
	return true;
}

bool DronesManager::remove_front() {
	//case 1 empty
	if(!first){
		return false;
	}
	//case 2 single element
	else if (size == 1){
		delete first;
		first = last = NULL;
	}
	//general case 
	else{
		//stores second 
		DroneRecord* temp = first->next;
		temp->prev = NULL;
		delete first;
		first = temp;
	}
	--size;
	return true;
}

bool DronesManager::remove_back() {
	//empty
	if(!first){
		return false;
	}
	//single element
	else if(!first->next){
		delete first;
		first = last = NULL;
	}
	//general case
	else{
		DroneRecord *secondLast = last->prev;
		delete last;
		last = secondLast;
		last->next = NULL;
	}
	--size;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	DroneRecord* temp = new DroneRecord(value);
	// if index is invalid, returns false
	if (index >= size || index < 0)
		return false;
	// general case
	else {
		(*this).remove(index);
		(*this).insert(value, index);
	}
	return true;
}

bool DronesManager::reverse_list() {
	//case 1 empty and single element
	//NOTE IF NO CHANGE OCCURS; RETURNS FALSE
	if(!first || !(first->next)) {
		return false;
	}
	//general case
	else{
		DroneRecord* temp_first = first;
		DroneRecord* temp_last = last;
		DroneRecord *curr = first;
		DroneRecord *before = NULL;
		DroneRecord *after = NULL;
		while(curr){
			after = curr->next;
			curr->next = before;
			curr->prev = after;
			before = curr;
			curr = after;
		}
		first = temp_last;
		last = temp_first;
	}
	return true;
}

