//
// Created by nizzel on 04/08/20.
//

#ifndef SEARCHALGORITHMS_UNORDEREDMAP_H
#define SEARCHALGORITHMS_UNORDEREDMAP_H

#include <unordered_map>

template <class K,class V>
class UnorderedMap{

public:
    virtual V& at(K key ) = 0;
    virtual void insert(K key, V value) = 0;
    virtual void erase(K key) = 0;



};



#endif //SEARCHALGORITHMS_UNORDEREDMAP_H
