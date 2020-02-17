#ifndef DATA_STRUCTURES_HASHMAP_TEMPLATED_ELANAFELSI_HASHEDMAP_H
#define DATA_STRUCTURES_HASHMAP_TEMPLATED_ELANAFELSI_HASHEDMAP_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>

using std::string;
typedef size_t(*HashFunc)(const string &, size_t);
size_t defaultHashFunc(const string &key, size_t hashSize);

template<typename T>
class HashMap {
private:
    struct Pair {
        Pair(const string &key, T value): m_key(key), m_value(value){};
        string m_key;
        T m_value;

        bool operator==(const Pair& pair)
        {
            return m_key == pair.m_key && m_value == pair.m_value;
        }

        bool operator!=(const Pair& pair)
        {
            return !operator==(pair);
        }
    };

    static const size_t HASH_TABLE_SIZE = 73;
    typedef std::list<Pair> PairList;
    typedef typename std::list<Pair>::iterator ListItr;
    typedef typename std::list<Pair>::const_iterator ConstItr;
    typedef std::vector<std::list<Pair> > HashTable;

    size_t m_hashSize;
    HashTable m_table;
    HashFunc m_hashFunc;

    size_t m_bucketsInUse;
    size_t m_numOfPairs;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const HashMap<U> &map);

public:
    explicit HashMap(size_t hashSize = HASH_TABLE_SIZE, HashFunc func = defaultHashFunc);
    void insert(const string&, const T &);
    T &operator[](const string &); //set value
    const T &operator[](const string &) const; //get value


    Pair &addPair(const Pair &, size_t, HashTable &);
    ListItr getPairItr(const string &, size_t *slot = NULL);
    void rehash(size_t newSize = 0);
    bool isPrime(size_t);
    size_t validateSize(size_t);
    size_t getNearestBigEnoughPrimeSize(size_t);
};


/* the index of a key is calculated by the hash function */
template<typename T>
inline void HashMap<T>::insert(const string& key, const T & val) {
    size_t index = m_hashFunc(key, m_hashSize);
    ListItr it = m_table[index].begin();
    for(; it != m_table[index].end(); ++it)
    {
        if(it->m_key == key)
        {
            it->m_value = val;
            return;
        }
    }
    Pair p(key, val);
    m_table[index].push_back(p);
    ++m_numOfPairs;
}

template<typename T>
T &HashMap<T>::operator[](const string &key){
    size_t index = m_hashFunc(key, m_hashSize);
    ListItr it = m_table[index].begin();
    for(; it != m_table[index].end(); ++it)
    {
        if((*it).m_key == key)
            return it->m_value;
    }
    exit(0);
}

template <typename U>
inline std::ostream &operator<<(std::ostream &os, const HashMap<U> &map) {

    os << "\n***** HashMap *****\n";
    os << "HashMap size: " << map.m_hashSize << std::endl;
    os << "HashMap Pairs: " << map.m_numOfPairs << std::endl;

    for(size_t i = 0; i < map.m_hashSize; ++i)
    {
        os << "Bucket #" << i << " : ";
        typename HashMap<U>::ConstItr it;
        for(it = map.m_table[i].begin(); it != map.m_table[i].end(); ++it)
        {
            os << "[" << it->m_key << ", " << it->m_value << "] ->";
        }
        os << std::endl;
    }
    return os;
}

template<typename T>
inline HashMap<T>::HashMap(size_t hashSize, HashFunc func) : m_hashSize(hashSize), m_hashFunc(func),
                                        m_table(HashTable(hashSize)), m_bucketsInUse(0),m_numOfPairs(0) {}

template<typename T>
inline void HashMap<T>::rehash(size_t newSize) {
    HashMap<T> newHashMap(newSize);

    for(size_t i = 0; i < m_hashSize; ++i)
    {
        ConstItr it;
        for(it = m_table[i].begin(); it != m_table[i].end(); ++it)
        {
            Pair p(it->m_key, it->m_value);
            newHashMap.insert(it->m_key, it->m_value);
        }
    }
    m_table = newHashMap.m_table;
    m_hashSize = newSize;
}


#endif //DATA_STRUCTURES_HASHMAP_TEMPLATED_ELANAFELSI_HASHEDMAP_H
