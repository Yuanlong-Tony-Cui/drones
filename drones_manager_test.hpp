#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "drones_manager.cpp"

#define ASSERT_TRUE(T) \
	if (!(T))          \
		return false;
#define ASSERT_FALSE(T) \
	if ((T))            \
		return false;

class DronesManagerTest
{
public:
	// PURPOSE: New empty list is valid
	bool test1()
	{
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
		return true;
	}

	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2()
	{
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

	// TODO: Implement all of the test cases below

	// PURPOSE: select() and search() work properly
	bool test3()
	{
		DronesManager manager1, manager2, manager3;
		DronesManager::DroneRecord defaultRecord(0);
		DronesManager::DroneRecord record(100);
		DronesManager::DroneRecord record2(120);
		DronesManager::DroneRecord record3(130);
		manager1.insert_front(record);
		manager1.insert_back(record2);
		manager1.insert_back(record3);
		manager2.insert_back(record2);

		ASSERT_TRUE(manager1.select(0) == record && manager1.select(1) == record2 && manager1.select(2) == record3)
		ASSERT_TRUE(manager2.select(0) == record2)
		ASSERT_TRUE(manager3.select(1000) == defaultRecord && manager3.select(0) == defaultRecord);
		ASSERT_TRUE(manager2.select(-1) == record2 && manager2.select(2) == record2);

		ASSERT_TRUE(manager3.search(record) == 0 && manager3.search(record2) == 0);
		ASSERT_TRUE(manager1.search(record) == 0 && manager1.search(record2) == 1 && manager1.search(record3) == 2);
		ASSERT_TRUE(manager2.search(record2) == 0);
		ASSERT_TRUE(manager2.search(record) == 1 && manager2.search(record3) == 1);
		return true;
	}

	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4()
	{
		DronesManager manager1;
		DronesManager::DroneRecord record(100);
		DronesManager::DroneRecord defaultRecord(0);

		manager1.insert_front(record);
		ASSERT_TRUE(manager1.get_size() == 1);
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last && manager1.select(0) == record);

		manager1.remove_front();
		ASSERT_TRUE(manager1.get_size() == 0 && manager1.select(0) == defaultRecord);
		ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL);

		manager1.insert_front(record);
		ASSERT_TRUE(manager1.get_size() == 1);
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last && manager1.select(0) == record);

		manager1.remove_back();
		ASSERT_TRUE(manager1.get_size() == 0 && manager1.select(0) == defaultRecord);
		ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL);

		return true;
	}

	// PURPOSE: replace() and reverse_list() work properly
	bool test5()
	{
		DronesManager manager1;
		DronesManager::DroneRecord record(100);
		DronesManager::DroneRecord record2(110);

		manager1.insert_front(record);
		ASSERT_TRUE(manager1.get_size() == 1);
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last && manager1.select(0) == record);

		manager1.replace(0, record2);
		ASSERT_TRUE(manager1.get_size() == 1);
		ASSERT_TRUE(*manager1.first == record2 && manager1.select(0) == record2);

		manager1.replace(2, record);
		ASSERT_TRUE(manager1.get_size() == 1);
		ASSERT_TRUE(*manager1.first == record2 && manager1.select(0) == record2);

		DronesManager manager2;
		DronesManager::DroneRecord record3(120);
		manager2.insert_front(record);
		manager2.insert_back(record2);
		manager2.insert_back(record3);

		ASSERT_TRUE(manager2.get_size() == 3);
		ASSERT_TRUE(manager2.first != NULL && manager2.last != NULL && *manager2.first == record && *manager2.last == record3);

		manager2.reverse_list();
		ASSERT_TRUE(manager2.get_size() == 3);
		ASSERT_TRUE(manager2.first != NULL && manager2.last != NULL && *manager2.first == record3 && *manager2.last == record && manager2.select(1) == record2);

		DronesManager manager3;
		manager3.insert_front(record);

		manager3.reverse_list();
		ASSERT_TRUE(manager3.get_size() == 1);
		ASSERT_TRUE(manager3.first != NULL && manager3.last != NULL && *manager3.first == record && *manager3.last == record);

		return true;
	}

	// PURPOSE: insert_front() keeps moving elements forward
	bool test6()
	{
		DronesManager manager1;
		DronesManager::DroneRecord record(100);
		DronesManager::DroneRecord record2(110);
		DronesManager::DroneRecord record3(120);

		manager1.insert_front(record);
		ASSERT_TRUE(manager1.first != NULL && manager1.last != NULL && *manager1.first == record && *manager1.last == record);

		manager1.insert_front(record2);
		ASSERT_TRUE(manager1.first != NULL && manager1.last != NULL && *manager1.first == record2 && *manager1.last == record);

		manager1.insert_front(record3);
		ASSERT_TRUE(manager1.first != NULL && manager1.last != NULL && *manager1.first == record3 && *manager1.last == record);

		return true;
	}

	// PURPOSE: inserting at different positions in the list
	bool test7()
	{
		// Assume that .select works properly.
		DronesManager manager1;
		DronesManager::DroneRecord record1(123456);
		DronesManager::DroneRecord record2(123457);
		DronesManager::DroneRecord record3(123458);

		// Test inserting a DroneRecord into an empty DronesManager:
		manager1.insert(record1, 0);
		ASSERT_TRUE(manager1.select(0) == record1 && manager1.get_size() == 1);

		// Test inserting a DroneRecord at 0 index into a non-empty DronesManager:
		manager1.insert(record2, 0);
		ASSERT_TRUE(manager1.select(0) == record2 && manager1.get_size() == 2);

		// Test inserting a duplicated DroneRecord:
		manager1.insert(record2, 0);
		ASSERT_TRUE(manager1.get_size() == 2);

		// Test inserting a DroneRecord between two other DroneRecords:
		manager1.insert(record3, 1);
		ASSERT_TRUE(manager1.select(1) == record3 && manager1.get_size() == 3);

		return true;
	}

	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8()
	{
		// Assume that .select and .insert_back work properly.
		DronesManager manager1;
		DronesManager::DroneRecord record1(123456);
		DronesManager::DroneRecord record2(123457);
		DronesManager::DroneRecord record3(123458);
		manager1.insert_back(record1);
		manager1.insert_back(record2);
		manager1.insert_back(record3);

		// Test removing one DroneRecord from index 0:
		ASSERT_TRUE(manager1.remove(0) && manager1.select(0) == record2 && manager1.get_size() == 2);

		// Test removing one DroneRecord from index 0 till the size becomes 0:
		ASSERT_TRUE(manager1.remove(0) && manager1.select(0) == record3 && manager1.get_size() == 1);
		ASSERT_TRUE(manager1.remove(0) && manager1.get_size() == 0);

		// Test removing one DroneRecord from index 0 when there is no DroneRecord at index 0 (empty DronesManager):
		ASSERT_TRUE(!manager1.remove(0) && manager1.get_size() == 0);

		// Add a few elements:
		ASSERT_TRUE(manager1.insert(record1, 0) && manager1.insert(record2, 1));

		return true;
	}

	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9()
	{
		// Insert several elements:
		DronesManager manager1;
		DronesManager::DroneRecord record1(123456);
		ASSERT_TRUE(manager1.insert(record1, 0) && manager1.select(0) == record1 && manager1.get_size() == 1);
		DronesManager::DroneRecord record2(123457);
		ASSERT_TRUE(manager1.insert(record2, 1) && manager1.select(1) == record2 && manager1.get_size() == 2);

		// Test inserting an element to invalid indices:
		DronesManager::DroneRecord record3(123458);
		ASSERT_TRUE(!manager1.insert(record3, -1) || manager1.get_size() == 2);
		ASSERT_TRUE(!manager1.insert(record3, 3) || manager1.get_size() == 2);

		// Remove several elements, some of which are invalid:
		ASSERT_TRUE(manager1.remove(0) && manager1.select(0) == record2 && manager1.get_size() == 1);
		ASSERT_TRUE(!manager1.remove(1) && manager1.get_size() == 1);
		ASSERT_TRUE(!manager1.remove(-1) && manager1.get_size() == 1);

		return true;
	}

	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10()
	{
		// Insert several elements:
		DronesManager manager1;
		DronesManager::DroneRecord record1(123456);
		ASSERT_TRUE(manager1.insert(record1, 0) && manager1.select(0) == record1 && manager1.get_size() == 1);
		DronesManager::DroneRecord record2(123457);
		ASSERT_TRUE(manager1.insert(record2, 1) && manager1.select(1) == record2 && manager1.get_size() == 2);
		DronesManager::DroneRecord record3(123458);
		ASSERT_TRUE(manager1.insert(record3, 2) && manager1.select(2) == record3 && manager1.get_size() == 3);

		ASSERT_TRUE(manager1.select(0) == record1 && manager1.select(1) == record2 && manager1.select(2) == record3);

		// Reverse the list:
		manager1.reverse_list();
		ASSERT_TRUE(manager1.select(0) == record3 && manager1.select(1) == record2 && manager1.select(2) == record1);

		// Remove multiple elements till empty:
		while (manager1.get_size() != 0)
		{
			int size = manager1.get_size();
			manager1.remove(manager1.get_size() - 1);
			ASSERT_TRUE(manager1.get_size() == size - 1);
		}
		ASSERT_TRUE(manager1.get_size() == 0);
		ASSERT_TRUE(manager1.first == manager1.last && manager1.first == NULL);

		return true;
	}

	// PURPOSE: Test the print functionality of DroneRecord
	bool test11()
	{
		DronesManager manager1;
		DronesManager::DroneRecord test(1, 2, 3, "s", "ss", "sss", "ssss");
		manager1.insert_front(test);
		cout << "This belongs to test 11: " << endl
			 << endl;
		manager1.print();
		return true;
	}
};

#endif