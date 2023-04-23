#ifndef BPLUSTREE_CPP
#define BPLUSTREE_CPP 

#include "bplustree.h"


template <class K, class V>
const bool BPlusTree<K, V>::DEBUG;

//========================================
//              *** Iterator ***
//========================================
template <class K, class V>
BPlusTree<K, V>::Iterator::Iterator
(BPlusTree<K, V>* _it, int _key_ptr):it(_it), key_ptr(_key_ptr){}

template <class K, class V>
Pair<K,V> BPlusTree<K, V>::Iterator::operator *(){
    assert(it && "[BPlusTree<K, V>::Iterator] [operator*]: dereferncing a NULL Iterator");
    return Pair<K,V>(it->data[key_ptr],*(it->get_subset<V>(key_ptr)) );
}

template <class K, class V>
typename BPlusTree<K, V>::Iterator BPlusTree<K, V>::Iterator::operator++(int un_used){
    assert(it && "[Error] [BPlusTree<K, V>::Iterator::operator++ POSTFIX]: Itor is NULL");
    
    typename BPlusTree<K, V>::Iterator temp(*this);

    if(key_ptr == it->data_count - 1){
        it = it->next;
        key_ptr = 0;
    }
    else ++key_ptr;
    return temp;
}

template <class K, class V>
typename BPlusTree<K, V>::Iterator& BPlusTree<K, V>::Iterator::operator++(){
    assert(it && "[Error] [BPlusTree<K, V>::Iterator::operator++ PREFIX]: Itor is NULL");
    if(key_ptr == it->data_count - 1){
        it = it->next;
        key_ptr = 0;
    }
    else ++key_ptr;
    return *this;
}

template <class K, class V>
void BPlusTree<K, V>::Iterator::print_Iterator(std::ostream& outs) const{
    if(!it) {
        outs << "[NULL]|||";
    }
    else
    {
        outs << "[" << it->data[key_ptr]<< "]-->";
    }

}

template <class K, class V>
bool BPlusTree<K, V>::Iterator::is_null(){return !it;}

template <class K, class V>
void BPlusTree<K, V>::Iterator::info(){
    std::cout << std::endl << "Iterator info:"<< std::endl;
    std::cout << "key_ptr: " << key_ptr << std::endl;
    std::cout << "it: " << *it << std::endl;
}


//========================================
//              *** B+tree ***
//========================================


        //-----------
        //Constructor
template <class K, class V>
BPlusTree<K, V>::BPlusTree(bool dups){
    dups_ok = dups;
    data_count = 0;
    child_count = 0;
    next = nullptr;
}


//-----------
//Big three:
template <class K, class V>
BPlusTree<K, V>::BPlusTree(const BPlusTree<K, V>& other){
    copy_tree(other);
}


template <class K, class V>
BPlusTree<K, V>::~BPlusTree(){
    // std::cout << "[~BPT]";
    clear_tree();
}

template <class K, class V>
BPlusTree<K, V>& BPlusTree<K, V>::operator =(const BPlusTree<K, V>& RHS){
    if(this == &RHS) return *this;

    clear_tree();
    copy_tree(RHS);

    return *this;
}


        //-----------

template <class K, class V>
void BPlusTree<K, V>::copy_tree(const BPlusTree<K, V>& other){
    copy_array(data, other.data, data_count, other.data_count);
    child_count = other.child_count;
    dups_ok = other.dups_ok;

    if(other.is_leaf()){
        for(int i = 0; i < data_count; ++i){
            V* new_v = new V(*other.get_subset<V>(i));
            subset[i] = allocate_token(new_v);
        }
    }
    else
    {
        BPlusTree<K, V>* last_node = nullptr;
        for(int i = 0; i < child_count; ++i){
            bpt* new_sub = new bpt(other.dups_ok);
            subset[i] = allocate_token(new_sub);
            get_subset<bpt>(i)->copy_tree(*other.get_subset<bpt>(i), last_node);
        }
    }
}  

template <class K, class V>
void BPlusTree<K, V>::copy_tree(const BPlusTree<K, V>& other, BPlusTree<K, V>*& last_node){
    copy_array(data, other.data, data_count, other.data_count);
    child_count = other.child_count;
    dups_ok = other.dups_ok;


    if(other.is_leaf()){
        if(last_node)
            last_node->next = this;
        last_node = this;
        for(int i = 0; i < data_count; ++i){
            V* new_v = new V(*other.get_subset<V>(i));
            subset[i] = allocate_token(new_v);
        }
    }
    else
    {
        for(int i = 0; i < child_count; ++i){
            bpt* new_sub = new bpt(other.dups_ok);
            subset[i] = allocate_token(new_sub);
            get_subset<bpt>(i)->copy_tree(*other.get_subset<bpt>(i), last_node);
        }
    }
}


template <class K, class V>
void BPlusTree<K, V>::insert(const K& key, const V& value){
    loose_insert(key, value);
    if(data_count > MAXIMUM){
        // if(DEBUG)
        //     std::cout << "\t[debug] [insert()]: data_count > MAXIMUM\n";
        bpt* new_bpt = new bpt(dups_ok);
        
        copy_array(new_bpt->data, data, new_bpt->data_count, data_count);
        if(!is_leaf())
            copy_array(new_bpt->subset, subset, new_bpt->child_count, child_count);
        else{
            int temp = 0;
            copy_array(new_bpt->subset, subset, temp, data_count);
        }
        
            data_count = 0;
            child_count = 1;
            subset[0] = allocate_token<bpt>(new_bpt);
    
        fix_excess(0);
    }
}    

template <class K, class V>
void BPlusTree<K, V>::remove(const K& key){
    loose_remove(key);
    if(child_count == 1){
        // std::cout << "\n[debug] [remove]: shrinking\n";
        bpt* child = get_subset<bpt>(0);
        bptToken* deleted_child = static_cast<bptToken*>(subset[0]);
        copy_array(data, child->data, data_count, child->data_count);
        if(child->is_leaf()){
            copy_array(subset, child->subset, data_count, child->data_count);
            child_count = 0;
        }
        else
            copy_array(subset, child->subset, child_count, child->child_count);

    
        child->child_count = 0;
        child->data_count = 0;
        delete deleted_child;
    }

}    

template <class K, class V>
void BPlusTree<K, V>::clear_tree(){
    if(is_leaf()){
        for(int i = 0; i < data_count; ++i){
            delete (vToken*) subset[i];
        }
    }
    else{
        for(int i = 0; i < child_count; ++i){
            delete (bptToken*) subset[i];
        }
    }

    data_count = 0;
    child_count = 0;
}             


template <class K, class V>
bool BPlusTree<K, V>::contains(const K& entry) const{
    int i = first_ge(data, data_count,entry);
    bool found = i < data_count && data[i] == entry;

    if(found){
        return true;
    }
    else
    {
        if(is_leaf()){
            return false;
        }
        else
        {
            return get_subset<bpt>(i)->contains(entry);
        }
    }
}  

template <class K, class V>
V& BPlusTree<K, V>::get(const K& entry){
    if(!contains(entry)){
        insert(entry, V());
    }
    return get_existing(entry);
}               

template <class K, class V>
const V& BPlusTree<K, V>::get(const K& entry)const{
    V* ptr = find_ptr(entry);
    assert(ptr && "[Error] [BPlusTree<K, V>::get() const]: entry does NOT EXIST");
    return *ptr;
}    

template <class K, class V>
V& BPlusTree<K, V>::get_existing(const K& entry) const{

    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);

    if (is_leaf()){
        if (found)
            return *get_subset<V>(i);
        else
            assert(found && "[BPlusTree<K, V>]: get_existing was called with nonexistent entry");        
    }
    else
    {
        if (found) //inner node
            return get_subset<bpt>(i+1)->get_existing(entry);
            //or just return true?
        else //not found yet...
            return get_subset<bpt>(i)->get_existing(entry);
    }

}      

template <class K, class V>
typename BPlusTree<K, V>::Iterator BPlusTree<K, V>::find(const K& key){
    int i = first_ge(data, data_count, key);
    bool found = i < data_count && data[i] == key;
    if(is_leaf())
    {   
        if(found)
            return Iterator(this, i);
        else return Iterator();
    }
    else
    {
        if(found)
            ++i;
        return get_subset<bpt>(i)->find(key);  
    }
}         
                                       

template <class K, class V>
typename BPlusTree<K, V>::Iterator BPlusTree<K, V>::lower_bound(const K& key){
    int i = first_ge(data, data_count, key);
    if(is_leaf())
    {   
        if(i < data_count)
            return Iterator(this, i);
        else 
            return Iterator(next, 0);
    }
    else
    {
        bool found = i < data_count && data[i] == key;
        if(found)
            ++i;
        return get_subset<bpt>(i)->lower_bound(key);  
    }
}  
                                        
                                         

template <class K, class V>
typename BPlusTree<K, V>::Iterator BPlusTree<K, V>::upper_bound(const K& key){
    int i = first_ge(data, data_count, key);
    bool found = i < data_count && data[i] == key;
    if(is_leaf())
    {   
        if(found) ++i;
        
        if(i < data_count)
            return Iterator(this, i);
        else 
            return Iterator(next, 0);
    }
    else
    {
        if(found)
            ++i;
        return get_subset<bpt>(i)->upper_bound(key);  
    }
}   
                                        


template <class K, class V>
int BPlusTree<K, V>::size() const{
    int total = 0;
    if(is_leaf()) total = data_count;
    for(int i = 0; i < child_count; ++i)
        total += get_subset<bpt>(i)->size();
    return total;
}                     


template <class K, class V>
bool BPlusTree<K, V>::empty() const{
    return data_count == 0;
}                   


template <class K, class V>
void BPlusTree<K, V>::print_tree(int level,
                std::ostream &outs) const{
    int indent = 6;
    if(!is_leaf()){
        // outs << std::setw(indent * level) << "" << "cc =  " << child_count << ", dc = " << data_count << "\n";
        outs << std::setw(indent * level) << ""  << "^\n";
        bpt* child = get_subset<bpt>(child_count-1);
        child->print_tree(level+1,outs);

        for(int i = data_count-1; i >= 0; --i){
            outs << std::setw(indent * level) << "" << data[i] << std::endl;

            child = get_subset<bpt>(i);
            child->print_tree(level+1,outs);
        }
        outs << std::setw(indent * level) << ""  << "v\n";

    }
    else
    {
        V* vptr;
        // outs << std::setw(indent * level) << "" << "cc = " << child_count << ", dc = " << data_count << "\n";
        outs << std::setw(indent * level) << ""  << "^\n";
        for(int i = data_count - 1 ; i >= 0; --i){
            vptr = get_subset<V>(i);
            outs << std::setw(indent * level) << "" ;
            // outs << "vptr = " << vptr << "|";
            outs << data[i] << ": ";
            outs << *vptr << std::endl;
        }
        outs << std::setw(indent * level) << ""  << "v\n";
    }
}
                


template <class K, class V>
bool BPlusTree<K, V>::is_valid(){
/* is_valid():
 *  check to see if all B+ tree conditions are met with the current (sub)tree:
 * if is_leaf: return true;
 * if (data[last item] is NOT <= all subset[last subtree]->data
 *      return false;
 * for every data[i]
 *      if data[i] is NOT > all subset[i]->data
 *          return false;
 * //now, this is lame:
 * for every data[i]
 *      if data[i] is not in the leaves
 *          return false;
 *
 * for every subtree subset[i]
 *      if !subset[i]->is_valid()
 *          return false;
 */
    if(is_leaf())
        return true;
    if(!is_le(get_subset<bpt>(child_count -1)->data, get_subset<bpt>(child_count -1)->data_count, data[data_count - 1]))
        return false;
    
    for(int i = 0; i < data_count; ++i){
        if(!is_gt(get_subset<bpt>(i)->data, get_subset<bpt>(i)->data_count, data[i]))
            return false;
       
    }


    for(int i = 0; i < child_count; ++i){
        if(!get_subset<bpt>(i)->is_valid())
            return false;
    }

    return true;
}

template <class K, class V>
std::string BPlusTree<K, V>::in_order(){
    std::stringstream ss;
    if(child_count > 0){
        int i = 0;
        for(; i < data_count; ++i){
            ss << get_subset<bpt>(i)->in_order() << data[i] << "|";
        }
        ss << get_subset<bpt>(i)->in_order();
    }
    else
        for(int i = 0; i < data_count; ++ i){
            ss << data[i] << "|";
        }
    return ss.str();
}

template <class K, class V>
std::string BPlusTree<K, V>::post_order(){
    std::stringstream ss;
    if(child_count > 0){
        int i = 0;
        ss << get_subset<bpt>(0)->post_order();
        for(; i < data_count;++i){
            ss << get_subset<bpt>(i + 1)->post_order() << data[i] << "|";
        }
    }
    else
        for(int i = 0; i < data_count; ++i){
            ss << data[i] << "|";
        }

    return ss.str();
}

template <class K, class V>
std::string BPlusTree<K, V>::pre_order(){
    std::stringstream ss;
    if(child_count > 0){
        int i = 0;
        for(; i < data_count; ++i){
            ss << data[i] << "|" << get_subset<bpt>(i)->pre_order();
        }
        ss << get_subset<bpt>(i)->pre_order();
    }
    else
        for(int i = 0; i < data_count; ++ i){
            ss << data[i] << "|";
        }
    return ss.str();
}

template <class K, class V>
typename BPlusTree<K, V>::Iterator BPlusTree<K, V>::begin(){
    // return Iterator();
    if(is_leaf())
        return Iterator(this);
    else return get_subset<bpt>(0)->begin();
}

template <class K, class V>
typename BPlusTree<K, V>::Iterator BPlusTree<K, V>::end(){
    return Iterator(nullptr);
}

template <class K, class V>
std::ostream& BPlusTree<K, V>::list_keys(typename BPlusTree<K, V>::Iterator from, typename BPlusTree<K, V>::Iterator to){
    if (from.is_null()) return std::cout;
    int indent = 3;

    for (Iterator w = from; w != to; w++){
        std::cout << *w << '|';
    }
    return std::cout;

}


#endif