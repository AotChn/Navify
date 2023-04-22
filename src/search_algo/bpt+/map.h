#ifndef BTREE_MAP_H
#define BTREE_MAP_H 
#include <iostream>
#include "bplustree.h"
#include <vector>

#include "pair.h"

template<class K, class V>
class Map
{
public:
    typedef BPlusTree<K, V> map_base;
    class Iterator{
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it = typename map_base::Iterator()):_it(it){}
        Iterator operator ++(int unused){return _it++;}
        Iterator operator ++(){return ++_it;}
        Pair<K, V> operator *(){return *_it;}

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return lhs._it == rhs._it;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return lhs._it != rhs._it;
        }
        
        private:
        typename map_base::Iterator _it;

    };

    Map():map(false){}

//  Iterators
    Iterator begin(){return map.begin();}
    Iterator end(){return map.end();}

//  Capacity
    int size() const{return map.size();}
    bool empty() const{ return map.empty();}

//  Element Access
    const std::vector<V>& operator[](const K& key) const{return map.get_existing(key);}
    V& operator[](const K& key){return get(key);}

    const std::vector<V>& at(const K& key) const{return map.get_existing(key);}
    V& at(const K& key){return get(key);}

//  Modifiers
    void insert(const K& k, const V& v){
        map.insert(k,v);
    }

    void erase(const K& key){map.remove(key);}
    void clear(){map.clear_tree();}

//  Operations:
    bool contains(const K& key) const {return map.contains(key);}
    V &get(const K& key){return map.get(key);}

    Iterator find(const K& key){return map.find(key);}

    Iterator lower_bound(const K& key){return map.lower_bound(key);}
    Iterator upper_bound(const K& key){return map.upper_bound(key);}

    //    equal_range:



    bool is_valid(){return map.is_valid();}

    friend std::ostream& operator<<(std::ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<std::endl;
        return outs;
    }
private:
    map_base map;
};


#endif