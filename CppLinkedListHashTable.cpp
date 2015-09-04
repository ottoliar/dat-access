#include <iostream>

const int tableSize = 128;

class HashNode {
protected:
	int key;
	int value;
	HashNode *next;
public:
	HashNode(int key, int value) {
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
	friend class HashMap;
};

class HashMap {
private:
	HashNode **htable;
public:
	HashMap() {
		htable = new HashNode*[tableSize];
		for (int i = 0; i < tableSize; i++) {
			htable[i] = NULL;
		}
	}
	~HashMap() {
		for (int i = 0; i < tableSize; i++) {
			HashNode *entry = htable[i];
			while (entry != NULL) {
				HashNode *prev = entry;
				entry = entry->next;
				delete prev;
			}
			delete[] htable;
		}
	}
	int hashFunction(int key) {
		return key % tableSize;
	}
	void insert(int key, int value) {
		int hashVal = hashFunction(key);
		HashNode *prev = NULL;
		HashNode *entry = htable[hashVal];
		while (entry != NULL) {
			prev = entry;
			entry = entry->next;
		}
		entry = new HashNode(key, value);
		if (prev == NULL) {
			htable[hashVal] = entry;
		} else {
			prev->next = entry;
		}
	}
	void remove(int key) {
		int hashVal = hashFunction(key);
		HashNode *prev = NULL;
		HashNode *entry = htable[hashVal];
		if (entry == NULL || entry->key != key) {
			std::cout << "No element at key\n";
			return;
		}
		while (entry->next != NULL) {
			prev = entry;
			entry = entry->next;
		}
		if (prev != NULL) {
			prev->next = entry->next;
		}
		delete entry;
	}
	bool search(int key) {
		bool flag = false;
		int hashVal = hashFunction(key);
		HashNode *entry = htable[hashVal];
		while (entry != NULL) {
			if (entry->key == key)
				flag = true;
			entry = entry->next;
		}
		return flag;
	}
	void print(int key) {
		int hashVal = hashFunction(key);
		HashNode *entry = htable[hashVal];
		std::cout << "At key: " << key << std::endl;
		while (entry != NULL) {
			std::cout << entry->value << "-> ";
			entry = entry->next;
		}
		std::cout << "\n";
	}
};

int main() {
	HashMap hash;
	hash.insert(3, 12);
	hash.insert(3, 15);
	hash.insert(3, 60);
	hash.print(3);
	hash.insert(1, 5);
	hash.insert(1, 77);
	hash.print(1);
	hash.remove(1);
	std::cout << "Removing from 1...\n";
	hash.print(1);
	if (hash.search(1)) {
		std::cout << "Something still at one!\n";
	}
	return 0;
}