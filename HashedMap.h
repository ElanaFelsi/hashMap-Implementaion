#ifndef DATA_STRUCTURES_HASHMAP_TEMPLATED_ELANAFELSI_HASHEDMAP_H
#define DATA_STRUCTURES_HASHMAP_TEMPLATED_ELANAFELSI_HASHEDMAP_H

#include <stdlib.h>
#include <string>
#include <vector>
#include "linkedList.h"

using std::string;
typedef size_t(*HashFunc)(const string &, size_t);
size_t defaultHashFunc(const string &, size_t);

template<typename T>
class HashMap {
public:
    explicit HashMap(size_t hashSize = HASH_TABLE_SIZE, HashFunc func = defaultHashFunc) : m_hashSize(hashSize),
                                                                                           m_hashFunc(func),m_bucketsInUse(0),m_numOfPairs(0){};
    void insert(const string&, const T &);
    T &operator[](const string &);
    const T &operator[](const string &) const;
private:
    struct Pair {
        Pair(const string &, T);
        string m_key;
        T m_value;
    };
    static const size_t HASH_TABLE_SIZE = 73;
    typedef List<Pair> PairList;
    typedef typename List<Pair>::Iterator ListItr;
    typedef std::vector<List<Pair> > HashTable;

    size_t m_hashSize;
    HashTable m_table;
    HashFunc m_hashFunc;

    size_t m_bucketsInUse;
    size_t m_numOfPairs;

    Pair &addPair(const Pair &, size_t, HashTable &);
    ListItr getPairItr(const string &, size_t *slot = NULL);
    void rehash(size_t newSize = 0);
    bool isPrime(size_t);
    size_t validateSize(size_t);
    size_t getNearestBigEnoughPrimeSize(size_t);
    friend std::ostream &operator<<(std::ostream &os, const HashMap<T> &map);
};

template<typename T>
inline void HashMap<T>::insert(const string& key, const T & val) {
    Pair p(key, val);
    size_t index = m_hashFunc(key, m_hashSize);
    PairList list = m_table[index];
    for(ListItr it = list.begin(); it != list.end(); ++it)
    {
        if(it->m_data.m_key == key)
        {
            it->m_data.m_value = val;
            return;
        }
    }
    list.insert(p);


}

template<typename T>
inline T &HashMap<T>::operator[](const string &) {

}

inline std::ostream &operator<<(std::ostream &os, const HashMap<T> &map) {

}


#endif //DATA_STRUCTURES_HASHMAP_TEMPLATED_ELANAFELSI_HASHEDMAP_H
