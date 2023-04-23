#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "pair.h"
#include "raw_pointer.h"
#include "btree_array_funcs.h"

/*-------------------------------------------
            [Genral Genral purpose]
        *******BPlusTree<Key,Value>*********
    A Better version of BPlusTree comapres to 
    Barkeshly's one;        

    This BPT is using Minimum number of key of each node to be its order,
    for all non-leaf: number of child would always be data_count + 1;
    the Maximum therefore would be 2* the Minimum.
    
    Search:
        if(is_leaf)
            1.if found: return data[i]
            2.else: not found
        else
            1.if found: subtree[i+1]->search(entry);
            2.else: subtree[i]->search(entry);

    BPT except the root, all subtree and values are dynamic allocated;
    To increase its capacity, simply change the static const MINIMUM to a higher value.
-------------------------------------------*/
template <class K, class V>
class BPlusTree
{
public:
    friend class Iterator;
    class Iterator{
        public:
        friend class BPlusTree;
        Iterator(BPlusTree<K,V>* _it=NULL, int _key_ptr = 0);

        Pair<K,V> operator *();

        Iterator operator++(int un_used);
        Iterator& operator++();
        
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return !(lhs == rhs);
        }

        friend std::ostream& operator <<(std::ostream& outs, const Iterator& print_me){
            print_me.print_Iterator(outs);
            return outs;
        }

        void print_Iterator(std::ostream& outs = std::cout) const;
        bool is_null();
        void info();

    private:
        BPlusTree* it;
        int key_ptr;
    };
    
    BPlusTree(bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<K,V>& other);
    ~BPlusTree();
    BPlusTree<K,V>& operator =(const BPlusTree<K,V>& RHS);

    //copyfunciton
    void copy_tree(const BPlusTree<K,V>& other);  //copy other into this object
    void copy_tree(const BPlusTree<K,V>& other, BPlusTree<K,V>*& last_node);
    
    //Modifer
    void insert(const K& key, const V& value = V());   //insert entry into the tree
    void insert(const Pair<K,V>& entry);   //insert entry into the tree

    void remove(const K& key);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    //Element Acessor
    bool contains(const K& entry) const; //true if entry can be found
    V& get(const K& entry);              //return a reference to entry
    const V& get(const K& entry)const;   //return a reference to entry
    V& get_existing(const K& entry) const;     //return a reference to entry
    Iterator find(const K& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const K& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const K& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    std::ostream &outs = std::cout) const;

    friend std::ostream& operator<<(std::ostream& outs,
                               const BPlusTree<K,V>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    std::string in_order();
    std::string pre_order();
    std::string post_order();

    Iterator begin();
    Iterator end();
    std::ostream& list_keys(Iterator from = NULL, Iterator to = NULL);

private:
    //my typedef/ helper functions
    typedef BPlusTree<K,V> bpt;
    typedef RPointerToken<V> vToken;
    typedef RPointerToken<bpt> bptToken;

    template<class T>
    T* get_subset(int i) const;

    template <class T>
    RPointerToken<T>* allocate_token(T* ptr = nullptr);

    //------------
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;
    static const bool DEBUG = false;
    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    K data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    RPointer* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    V* find_ptr(const K& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const K& key, const V& value);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const K& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<K, V>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    void get_smallest(K& entry);      //entry := leftmost leaf

    // void get_biggest(K& entry);       //entry := rightmost leaf
    // void remove_biggest(K& entry);    //remove the biggest child of tree->entry

    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    void merge_with_next_subset(int i); //merge subset i with  i+1
};  

template<class K, class V>
class MMap;

template<class K, class V>
class Map;

#include "bplustree.cpp"
#include "bplustree_template.cpp"

#endif
