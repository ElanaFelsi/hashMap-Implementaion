#include "TestHashMap.h"
#include <iostream>

void test()
{
    creatHashMapTest();
}

void creatHashMapTest()
{
    std::cout << "\n *** create HashMap ***\n";
    HashMap<int> hashMap(3);
    std::cout << hashMap;

    insertTest(hashMap);
}

template <typename T>
void insertTest(HashMap<T> &map)
{
    std::cout << "\n *** insert Test ***\n";
    map.insert("Elana Felsenthal", 9);
    map.insert("Shoham", 44);
    map.insert("a", 12);
    map.insert("Leora", 100);

    std::cout << map;

    getOperTest(map);
}

template <typename T>
void getOperTest(HashMap<T> &map)
{
    std::cout << "\n *** operator[] ***\n";
    std::cout << "hashMap[Elana] " << map["Elana Felsenthal"];
    map["Elana Felsenthal"] = 99;
    std::cout << map;

    rehashTest(map);
}

template <typename T>
void rehashTest(HashMap<T> &map)
{
    std::cout << "\n *** rehash ***\n";
    map.rehash(9);
    std::cout << map;
}