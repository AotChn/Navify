#ifndef BTREE_MULTIMAP_H
#define BTREE_MULTIMAP_H 
#include <iostream>
#include <vector>
#include <set>

#include "bplustree.h"
#include "btree_array_funcs.h"
#include "pair.h"

template<class K, class V>
class MMap
{
public:
    typedef BPlusTree<K, std::vector<V>> map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it = typename map_base::Iterator()):_it(it){}
        Iterator operator ++(int unused){return _it++;}
        Iterator operator ++(){return ++_it;}
        Pair<K, std::vector<V>> operator *(){return *_it;}

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return lhs._it == rhs._it;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return lhs._it != rhs._it;
        }
        
        private:
        typename map_base::Iterator _it;

    };

    MMap():mmap(true){}

//  Iterators
    Iterator begin(){return mmap.begin();}
    Iterator end(){return mmap.end();}

//  Capacity
    int size() const{return mmap.size();}
    bool empty() const{ return mmap.empty();}

//  Element Access
    const std::vector<V>& operator[](const K& key) const{return mmap.get_existing(key);}
    std::vector<V>& operator[](const K& key){return get(key);}

    const std::vector<V>& at(const K& key) const{return mmap.get_existing(key);}
    std::vector<V>& at(const K& key){return get(key);}

//  Modifiers


    void insert(const K& k, const V& v){

        get(k) += v;
    }
    void insert(const K&k, const std::vector<V>&v){
        get(k) += v;
    }
    void erase(const K& key){mmap.remove(key);}
    void clear(){mmap.clear_tree();}

//  Operations:
    bool contains(const K& key) const {return mmap.contains(key);}
    std::vector<V> &get(const K& key){return mmap.get(key);}

    Iterator find(const K& key){return mmap.find(key);}
    int count(const K& key){
        if(!contains(key)) return 0;
        return mmap.get_existing(key).size();
    }
    Iterator lower_bound(const K& key){return mmap.lower_bound(key);}
    Iterator upper_bound(const K& key){return mmap.upper_bound(key);}

    //    equal_range:



    bool is_valid(){return mmap.is_valid();}

    friend std::ostream& operator<<(std::ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<std::endl;
        return outs;
    }
private:
    map_base mmap;
};


#endif