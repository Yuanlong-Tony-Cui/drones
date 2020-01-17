#include "drones_manager.hpp"
#include <iostream>

DronesManager::DronesManager()
{
	first = NULL;
	last = NULL;
	size = 0;
}

DronesManager::~DronesManager()
{
	first = NULL;
	last = NULL;
	size = 0;
}

bool operator==(const DronesManager::DroneRecord &lhs, const DronesManager::DroneRecord &rhs)
{

	if (lhs.droneID == rhs.droneID && lhs.range == rhs.range && lhs.yearBought == rhs.yearBought)
	{
		if (lhs.droneType == rhs.droneType && lhs.manufacturer == rhs.manufacturer && lhs.description == rhs.description && lhs.batteryType == rhs.batteryType)
			return true;
	}

	return false;
}

unsigned int DronesManager::get_size() const
{
	return size;
}

bool DronesManager::empty() const
{
	return first == NULL;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const
{
	if (index < 0 || index >= size)
	{
		if (size == 0)
			return DroneRecord(0);
		else
			return *last;
	}
	else if (empty())
		return DroneRecord(0);
	else
	{
		DroneRecord *curr = first;

		for (int i = 0; i < size; i++)
		{
			if (i == index)
				return *curr;
			curr = curr->next;
		}
	}
}

unsigned int DronesManager::search(DroneRecord value) const
{
	if (empty())
		return 0;

	DroneRecord *curr = first;
	for (int i = 0; i < size; i++)
	{
		if (*curr == value)
			return i;
		curr = curr->next;
	}

	return size;
}

void DronesManager::print() const
{
	DroneRecord *curr = first;

	for (int i = 0; i < size; i++)
	{
		cout << "Drone: " << i + 1 << endl;

		cout << "ID: " << curr->droneID << endl;
		cout << "Range: " << curr->range << endl;
		cout << "Year Bought: " << curr->yearBought << endl;

		cout << "Type: " << curr->droneType << endl;
		cout << "Manufacturer: " << curr->manufacturer << endl;
		cout << "Description: " << curr->description << endl;
		cout << "Battery Type: " << curr->batteryType << endl
			 << endl;

		curr = curr->next;
	}
}

bool DronesManager::remove(unsigned int index)
{
	if (index > size - 1 || index < 0)
		return false;
	if (size == 1)
	{
		delete first;
		first = last = NULL;
		size = 0;
		return true;
	}
	else if (index == 0)
	{
		return remove_front();
	}
	else if (index == size - 1)
	{
		return remove_back();
	}
	int i = 0;
	DroneRecord *curr = first;
	while (curr)
	{
		if (i == index)
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			delete curr;
			curr = NULL;
			size--;
			return true;
		}
		i++;
		curr = curr->next;
	}
}

bool DronesManager::remove_front()
{
	if (size == 0)
	{
		return false;
	}
	else if (size == 1)
	{
		delete first;
		first = last = NULL;
		size = 0;
		return true;
	}
	size--;
	first = first->next;
	delete first->prev;
	first->prev = NULL;
	return true;
}

bool DronesManager::remove_back()
{
	if (size == 0)
	{
		return false;
	}
	else if (size == 1)
	{
		delete last;
		first = last = NULL;
		size--;
		return true;
	}
	size--;
	last = last->prev;
	delete last->next;
	last->next = NULL;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value)
{
	if (size == 0 || index > size - 1)
		return false;
	int i = 0;
	DroneRecord *curr = first;
	while (curr)
	{
		if (i == index)
		{
			DroneRecord *position = curr;
			*position = value;
			return true;
		}
		i++;
		curr = curr->next;
	}
	return false;
}

bool DronesManager::any_duplicates(DroneRecord value) const
{
	if (size == 0)
		return false;
	else
	{
		DroneRecord *curr = first;
		while (curr)
		{
			if (curr->droneID == value.droneID)
				return true;
			curr = curr->next;
		}
		return false;
	}
}

bool DronesManager::insert(DroneRecord value, unsigned int index)
{
	if (any_duplicates(value))
		return false;
	DroneRecord *newRecord = new DroneRecord(value);
	if (size == 0)
	{
		first = newRecord;
		last = newRecord;
		size++;
		return true;
	}
	else if (index > size || index < 0)
	{
		return false;
	}
	else if (index == 0)
	{
		return insert_front(value);
	}
	else if (index == size)
	{
		return insert_back(value);
	}
	int i = 0;
	DroneRecord *curr = first;
	while (curr)
	{
		if (i == index)
		{
			DroneRecord *originalPrev = curr->prev;
			originalPrev->next = newRecord;
			curr->prev = newRecord;
			newRecord->prev = originalPrev;
			newRecord->next = curr;
			size++;
			return true;
		}
		curr = curr->next;
		i++;
	}
}

bool DronesManager::insert_front(DroneRecord value)
{
	if (any_duplicates(value))
		return false;
	DroneRecord *newRecord = new DroneRecord(value);
	if (size == 0)
	{
		first = newRecord;
		last = newRecord;
		size++;
		return true;
	}
	else
	{
		newRecord->next = first;
		first->prev = newRecord;
		first = newRecord;
		size++;
		return true;
	}
}

bool DronesManager::insert_back(DroneRecord value)
{
	if (any_duplicates(value))
		return false;
	DroneRecord *newRecord = new DroneRecord(value);
	if (size == 0)
	{
		first = newRecord;
		last = newRecord;
		size++;
		return true;
	}
	else
	{
		newRecord->prev = last;
		last->next = newRecord;
		last = newRecord;
		size++;
		return true;
	}
}

bool DronesManager::reverse_list()
{
	if (size <= 1)
		return true;
	DroneRecord *curr = first;
	first = last;
	last = curr;
	DroneRecord *originalPrev = NULL;
	DroneRecord *originalNext = NULL;
	while (curr)
	{
		originalPrev = curr->prev;
		originalNext = curr->next;
		curr->prev = originalNext;
		curr->next = originalPrev;
		curr = originalNext;
	}
	return true;
}
