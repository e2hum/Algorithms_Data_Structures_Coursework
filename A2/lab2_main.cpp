#include <iostream>
#include <string>

#include "lab2_drones_manager_test.hpp"

using namespace std;

string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}

int main() {
	
    DronesManagerTest drones_manager_test;

	string test_descriptions[12] = {
      "Test1: new empty list is valid",
      "Test2: insert_front() and insert_back() on zero-element list",
      "Test3: select() and search() work properly",
	  "Test4: remove_front() and remove_back() on one-element list",
      "Test5: replace() and reverse_list() work properly",
      "Test6: insert_front() keeps moving elements forward",
      "Test7: inserting at different positions in the list",
      "Test8: try to remove too many elements, then add a few elements",
      "Test9: lots of inserts and deletes, some of them invalid",
      "Test10: lots of inserts, reverse the list, and then lots of removes until empty"
	};
	cout<<"yes";
	bool test_results[10];
    test_results[0] = drones_manager_test.test1();
    cout<<"wack";
    cout<<test_results[0];
    cout << (drones_manager_test.test2());
	test_results[1] = drones_manager_test.test2();
    cout<<"hellllo";
    test_results[2] = drones_manager_test.test3();
    
    test_results[3] = drones_manager_test.test4();
    test_results[4] = drones_manager_test.test5();
    test_results[5] = drones_manager_test.test6();
    test_results[6] = drones_manager_test.test7();
    test_results[7] = drones_manager_test.test8();
    test_results[8] = drones_manager_test.test9();
    test_results[9] = drones_manager_test.test10();
    
	cout << "DRONES MANAGER TEST RESULTS \n";
	cout << "*************************** \n";
	for (int index = 0; index < 10; ++index) {
    	cout << test_descriptions[index] << endl << get_status_str(test_results[index]) << endl;
	}
    system("pause");
}
