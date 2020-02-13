#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.cpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	int test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))	
	    return true;
	}
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		DronesManager manager1, manager2;
		// note that when the manager is empty, select() returns DroneRecord(0)
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(0))
		// note that when the manager is empty, search returns 0
		ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(100)) == 0)
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));	
		// checks if the first DroneRecord in each manager is the same, then checks the DroneRecord value	
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
		// checks if the first DroneRecord in each manager have to same index
		ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(100)) == manager2.search(DronesManager::DroneRecord(100)))
		manager1.insert_front(DronesManager::DroneRecord(150));
		// checks if search returns size when value is not found
		ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(200)) == manager1.size)
		return true;	
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
	    DronesManager manager1, manager2;
	    // checks if remove_front when manager is empty returns false
	    ASSERT_FALSE(manager1.remove_front())
	    // checks if remove_back when manager is empty returns false
	    ASSERT_FALSE(manager1.remove_back())
		manager1.insert_front(DronesManager::DroneRecord(100));
		// checks if remove_front works when there is only one DroneRecord
		manager1.remove_front();
		ASSERT_TRUE(manager1.size == 0)
		manager1.insert_front(DronesManager::DroneRecord(100));
		// checks if remove_back works when there is only one DroneRecord
		manager1.remove_back();
		ASSERT_TRUE(manager1.size == 0)
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager1.insert_front(DronesManager::DroneRecord(300));
		manager1.insert_front(DronesManager::DroneRecord(400));
		manager1.remove_front();
		manager1.remove_back();
		manager2.insert_front(DronesManager::DroneRecord(200));
		manager2.insert_front(DronesManager::DroneRecord(300));
		// checks if manager1 has all the same DroneRecords as manager2
		// tests both remove_front and remove_back as manager2 is the expected
		// outcome after both functions have been called
		for (int num = 0; num < manager1.size; num++) {
			ASSERT_TRUE(manager1.select(num) == manager2.select(num))
		}
		return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
	    DronesManager manager1, manager2;
	    // checks if index is out of range, replace returns false
	    ASSERT_FALSE(manager1.replace(3, DronesManager::DroneRecord(123)))
	    // checks if the manager is empty, reverse returns false
	    ASSERT_FALSE(manager1.reverse_list())
	    manager1.insert_front(DronesManager::DroneRecord(100));
	    // checks if the manager has one DroneRecord, reverse returns false
	    ASSERT_FALSE(manager1.reverse_list())
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager1.insert_front(DronesManager::DroneRecord(300));
		manager1.insert_front(DronesManager::DroneRecord(400));
		manager1.replace(2, DronesManager::DroneRecord(600));
		// checks if the index of the new value matches the index parameter and that the size is still the same
		ASSERT_TRUE(manager1.search(600) == 2 && manager1.size == 4)
		// compares reversed manager1 to manager2 which represents expected result
		manager1.reverse_list();
		manager2.insert_back(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(600));
		manager2.insert_back(DronesManager::DroneRecord(300));
		manager2.insert_back(DronesManager::DroneRecord(400));
		for (int num = 0; num < manager1.size; num++) {
			ASSERT_TRUE(manager1.select(num) == manager2.select(num))
		}
		return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
	    DronesManager manager1;
	    manager1.insert_front(DronesManager::DroneRecord(100));
	    ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(100)) == 0)
	    manager1.insert_front(DronesManager::DroneRecord(200));
	    ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(100)) == 1)
	    manager1.insert_front(DronesManager::DroneRecord(300));
	    ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(100)) == 2)
	    return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
	    DronesManager manager1;
	    manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager1.insert_front(DronesManager::DroneRecord(300));
		manager1.insert_front(DronesManager::DroneRecord(400));
		manager1.insert(DronesManager::DroneRecord(500), 2);
		// checks if inserting at an index out of range returns false
		ASSERT_TRUE(manager1.insert(DronesManager::DroneRecord(123),10) == false)
		// checks if inserting at index 2 returns a search value of 2
		ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(500)) == 2)
		return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
	    DronesManager manager1;
	    manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.remove_front();
		// returns false when there is nothing left to remove
		ASSERT_FALSE(manager1.remove_front())
		// returns true when new elements are added
		ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(100)))
		ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(200)))	
		ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(300)))
		return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		DronesManager manager1;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(200));
		manager1.insert_back(DronesManager::DroneRecord(300));
		manager1.insert_front(DronesManager::DroneRecord(400));
		manager1.insert(DronesManager::DroneRecord(500), 2);
		manager1.insert(DronesManager::DroneRecord(600), 10);
		manager1.remove(3);
		manager1.remove_front();
		manager1.remove_back();
		manager1.remove(9);
		// checks that the manager only has the DroneRecords 100 and 500 left
		ASSERT_TRUE(manager1.size == 2 && manager1.search(100) == 0 && manager1.search(500) == 1)
		return true;
	}    
	    	
	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
		DronesManager m1, m2;
		// adds lots of elements to the manager
		for(int x = 0; x<10; x++)
			m1.insert_back(DronesManager::DroneRecord(x+1));
		ASSERT_TRUE(m1.size == 10)
		// reverses the list
	   	m1.reverse_list();
	   	// makes a second manager that is the expected reverse of m1
		for(int x = 0; x<10; x++)
			m2.insert_front(DronesManager::DroneRecord(x+1));
		for (int num = 0; num < m1.size; num++) {
			ASSERT_TRUE(m1.select(num) == m2.select(num))
		}
		for(int x = 0; x<10; x++)
			m1.remove_front();
		// checks if all elements were deleted
		ASSERT_TRUE(m1.size == 0)
		return true;
	} 
};

#endif
