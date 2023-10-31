#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
     vector<list<pair<K, V>>> table; // Table is a vector of lists

    int num_buckets; // Number of buckets
    int elements; // Total number of elements

    void rehash() {
         int new_num_buckets = findNextPrime(2 * num_buckets); // Find a new prime number for the number of buckets
        vector<list<pair<K, V>>> new_table(new_num_buckets); // Create a new table with the updated number of buckets

        for (const auto& chain : table) {
            for (const auto& pair : chain) {
                int hash = this->hash(pair.first); // Calculate new hash for the pair
                new_table[hash].push_back(pair); // Redistribute existing elements to the new buckets
            }
        }

        table = std::move(new_table); // Update the table with the new one
        num_buckets = new_num_buckets; // Update the number of buckets
    }

public:
    ChainingHash(int n = 11) {
        num_buckets = findNextPrime(n);
        table.resize(num_buckets);
        elements = 0;
    }

    ~ChainingHash() {
        this->clear();
    }

    int size() {
        return 0;
    }

    V operator[](const K& key) {
       int hash = this->hash(key); // Calculate the hash of the key

        for (const auto& pair : table[hash]) {
            if (pair.first == key) {
                return pair.second; // If found, return the associated value
            }
        }

        throw std::out_of_range("Key not found"); // If not found, throw an exception
    }
    bool insert(const std::pair<K, V>& pair) {
        int hash = this->hash(pair.first); // Calculate the hash of the key

        for (auto& existing_pair : table[hash]) {
            if (existing_pair.first == pair.first) {
                existing_pair.second = pair.second; // If key already exists, update the value
                return true;
            }
        }

        table[hash].push_back(pair); // If key doesn't exist, insert a new pair
        elements++;

        if (elements >= 0.75 * num_buckets) {
            rehash(); // Rehash if load factor exceeds 0.75
        }

        return true;
    }

    void erase(const K& key) {
         int hash = this->hash(key); // Calculate the hash of the key

        auto& chain = table[hash];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it); // If found, remove the pair and update 'elements' count
                elements--;
                return;
            }
        }
    }

    void clear() {
        table.clear(); // Clear all lists in the 'table'
        table.resize(num_buckets);
        elements = 0; // Reset 'elements' count
    }

    int bucket_count() {
        return 1;
    }

    float load_factor() {
        return static_cast<float>(elements) / num_buckets; // Calculate load factor
    }
  

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }


    int hash(const K& key) override {
    return std::hash<K>{}(key) % num_buckets;
}


};

#endif //__CHAINING_HASH_H