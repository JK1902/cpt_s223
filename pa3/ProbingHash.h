#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>
#include <cmath>
#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> {
private:
    std::vector<std::pair<K, V>> table;
    std::vector<EntryState> status;
    int num_buckets;
    int elements;

    void rehash() {
        int new_buckets = findNextPrime(2 * num_buckets); // Double the number of buckets
        vector<pair<K, V>> new_table(new_buckets);
        vector<EntryState> new_status(new_buckets, EMPTY);

        for (int i = 0; i < num_buckets; i++) {
            if (status[i] == VALID) {
                int hash = this->hash(table[i].first);

                int j = 0;
                while (j < new_buckets) {
                    int index = (hash + j) % new_buckets;

                    if (new_status[index] != VALID) {
                        new_table[index] = table[i];
                        new_status[index] = VALID;
                        break;
                    }

                    j++;
                }
            }
        }

        table = std::move(new_table);
        status = std::move(new_status);
        num_buckets = new_buckets;
    }

public:
    ProbingHash(int n = 11) {
        num_buckets = findNextPrime(n);
        table.resize(num_buckets);
        status.resize(num_buckets, EMPTY);
        elements = 0;
    }
    
    ~ProbingHash() {
        this->clear();
    }

    int size() {
        return 0;
    }

  
    V operator[](const K& key) {
        int hash = this->hash(key);
        int i = 0;

        while (i < num_buckets) {
            int index = (hash + i) % num_buckets;

            if (status[index] == VALID && table[index].first == key) {
                return table[index].second; // Return value if key is found
            } else if (status[index] != VALID) {
                return V(); // Key not found, return default-constructed value
            }

            i++;
        }

        return V(); // Key not found, return default-constructed value
    }


    bool insert(const std::pair<K, V>& pair) {
       int hash = this->hash(pair.first);
        int i = 0;

        while (i < num_buckets) {
            int index = (hash + i) % num_buckets;

            if (status[index] != VALID || table[index].first == pair.first) {
                table[index] = pair;
                status[index] = VALID;
                elements++;

                if (elements >= 0.75 * num_buckets) {
                    rehash(); // Rehash if load factor exceeds 0.75
                }
                return true;
            }

            i++;
        }

        return false; // Unable to insert
    }

    void erase(const K& key) override {
        int hash = this->hash(key);
        int i = 0;

        while (i < num_buckets) {
            int index = (hash + i) % num_buckets;

            if (status[index] == VALID && table[index].first == key) {
                status[index] = DELETED;
                elements--;
                return;
            }

            i++;
        }
    }

    void clear() {
        table.clear();
        table.resize(num_buckets);
        status.clear();
        status.resize(num_buckets, EMPTY);
        elements = 0;
    }
    
    int bucket_count() {
         return num_buckets;
    }

    float load_factor() {
       return static_cast<float>(elements) / num_buckets;
    }

private:
    int findNextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(int n) {
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    int hash(const K& key) override {
    return std::hash<K>{}(key) % num_buckets;
}


};

#endif //__PROBING_HASH_H