#ifndef MPAIR_PAIR_H
#define MPAIR_PAIR_H

#include <iostream>
#include <vector>

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()): key(k), value(v){}
    friend std::ostream& operator <<(std::ostream& outs, const Pair<K, V>& print_me){
        outs << print_me.key << ": " <<print_me.value;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key == rhs.key;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key < rhs.key;

    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        
        return lhs.key > rhs.key;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key <= rhs.key;
        
    }
    friend Pair<K, V>  operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return Pair(lhs.key, lhs.value + rhs.value);
    }
};

template <typename K, typename V>
struct MPair{
    K key;
    std::vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k = K()): key(k){}
    MPair(const K& k, const V& v):  key(k), value_list(v){}
    MPair(const K& k, const std::vector<V>& vlist): key(k), value_list(vlist){}
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend std::ostream& operator <<(std::ostream& outs, const MPair<K, V>& print_me){
        int size = print_me.value_list.size();
        outs << print_me.key << " (" << size << "): " ;
        if(size > 5){
            for(int i = 0; i < 5; ++i)
                outs << print_me.value_list[i] << " | ";
            outs << "...";
        }
        else{
            for(int i = 0; i < size; ++i)
                outs << print_me.value_list[i] << " | ";
        }

        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key == rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key <= rhs.key;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key > rhs.key;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        MPair<K,V> temp1(lhs);
        for(int i = 0; i < rhs.value_list.size(); ++i){
            temp1.value_list.push_back(rhs.value_list[i]);
        }
        return temp1;
    }
};


#endif