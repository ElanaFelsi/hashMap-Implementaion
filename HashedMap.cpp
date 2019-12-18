#include "HashedMap.h"

size_t defaultHashFunc(const string& key, size_t hashSize) {
    size_t size = key.size(), sumAll = 0, evenMult = 1, oddMult = 1;
    for (size_t i = 0; i < size; ++i) {
        sumAll += key[i];
        if (i % 2 == 0)
            evenMult *= key[i];
        else
            oddMult *= key[i];
    }
    return (size * sumAll * (evenMult + oddMult)) % hashSize;
}












