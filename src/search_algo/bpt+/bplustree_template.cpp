#ifndef BPLUSTREE_TEMPLATE
#define BPLUSTREE_TEMPLATE 

#include "bplustree.h"



template <class K, class V>
MMap<K,V>& operator +=(MMap<K,V>& lhs, const MMap<K,V>& rhs){
    return lhs;
}

template <class K, class V>
V* BPlusTree<K, V>::find_ptr(const K& entry){
    int i = first_ge(data, data_count, entry);
    bool found = i < data_count && data[i] == entry;

    if(found)
    {
        if(is_leaf())
            return get_subset<V>(i);
        else return get_subset<bpt>(i+1)->find_ptr(entry);
    }
    else
    {
        if(!is_leaf())
            return get_subset<bpt>(i)->find_ptr(entry);
        else return nullptr;
    }
}          

template <class K, class V>
void BPlusTree<K, V>::loose_insert(const K& key, const V& value){
    // if(DEBUG)
    //     std::cout << "\t\t [debug][loose_insert]: called!\n";
    int i = first_ge(data, data_count, key);
    bool found = i < data_count && data[i] == key;

    BPlusTree<K,V>* child;

    if(found){
        if(is_leaf()){
            V* vptr = get_subset<V>(i);
            if(dups_ok){
                // std::cout << "\t[DEBUG] [BPT::looser insert]found and dup is ok, key: " << key << "\n" ;
                *vptr += value;
            }
            else *vptr = value;
        }
        else    
        {   
            child = get_subset<bpt>(i + 1);
            child->loose_insert(key,value);
            if(child->data_count > MAXIMUM)
                fix_excess(i+1);
        }
    }
    else
    {
        if(is_leaf()){
            RPointer* new_v = allocate_token(new V(value));
            insert_item(subset, i, data_count,  new_v);
            --data_count;
            insert_item(data, i, data_count, key);
        }
        else
        {
            child = get_subset<bpt>(i);
            child->loose_insert(key,value);
            if(child->data_count > MAXIMUM)
                fix_excess(i);
        }
    }
}                                           

template <class K, class V>
void BPlusTree<K, V>::fix_excess(int i){
    //New Node
    bpt *new_bpt = new bpt(dups_ok), 
    //representing BPT child at subset[i]
    *subset_i = get_subset<bpt>(i);

    int old_d_count = subset_i->data_count, new_d_count = 0;
    K temp;

    

    // split d, insert d
    split(subset_i->data, 
        subset_i->data_count, 
        new_bpt->data, 
        new_bpt->data_count);

    detach_item(subset_i->data, 
            subset_i->data_count,
            temp);
    insert_item(data, i, data_count, temp);



    RPointer* rptr;
    //insert new child to this.subset
    insert_item(subset, i+1, child_count, (RPointer*)allocate_token(new_bpt));


    if(subset_i->is_leaf()){
        //insert data to the front of new child
        insert_item(new_bpt->data, 0, new_bpt->data_count, temp);
        new_bpt->next = subset_i->next;
        subset_i->next = new_bpt;


        //insert c, split c
            // std::cout << "subset_i is leaf! and subset_i->subset[]= "; 
            //     print_array(subset_i->subset, old_d_count);
            //     std::cout << std::endl;
        split(subset_i->subset, old_d_count, new_bpt->subset, new_d_count);
            // std::cout << "After Split, subset_i->subset[]= "; 
            //     print_array(subset_i->subset, old_d_count);
            //     std::cout << ",  and new_bpt->subset_i[]= ";print_array(subset_i->subset, old_d_count);
            //     std::cout << std::endl;
        detach_item(subset_i->subset, old_d_count, rptr);
        insert_item(new_bpt->subset, 0, new_d_count, rptr);
    }
    else
    {

        split(subset_i->subset, subset_i->child_count, new_bpt->subset, new_bpt->child_count);
    }


}              

template <class K, class V>
void BPlusTree<K, V>::loose_remove(const K& entry){
    int i = first_ge(data, data_count,entry);
    bool found = i < data_count && data[i] == entry;
    if(is_leaf()){
        if(found){
            K temp;
            RPointer* subset_ptr;
            delete_item(data, i, data_count, temp);
            // std::cout << "\t[Debug][loose_remove] data_count = " << data_count << std::endl;
            delete_item(subset, i, ++data_count, subset_ptr);

            // assert(subset_ptr && "[DEBUG] [Remove error]: deleting value ptr which should not be NULL, but is NULL");
            // std::cout << "\t[Debug][loose_remove] *subset_ptr = " << *static_cast<vToken*>(subset_ptr)->recover_pointer() << std::endl;
                // std::cout << "\t[Debug][loose_remove] *subset = ";
                // for(int i = 0; i < data_count + 1; ++i){
                //     std::cout << *get_subset<V>(i) << " ";
                // }
                // std::cout << std::endl;
            delete (vToken*) subset_ptr;
        }
    }
    else
    {   //Not Leaf:

        if(found){
            get_subset<bpt>(i+1)->loose_remove(entry);
            // if(DEBUG)
            //     std::cout << "\n[debug] [loose_remove]: get_smallest will be called\n";
            if(get_subset<bpt>(i+1)->data_count < MINIMUM){
                bpt* subset_i = fix_shortage(i + 1);
                i = first_ge(data, data_count,entry);
                found = i < data_count && data[i] == entry;
                if(found){ 
                    get_subset<bpt>(i+1)->get_smallest(data[i]);
                }
                else{
                    // if(i+1 < child_count){
                        // bpt* subset_i = get_subset<bpt>(i + 1);
                    int i = first_ge(subset_i->data, subset_i->data_count, entry);
                    found = i < subset_i->data_count && subset_i->data[i] == entry;
                    if(found){
                        // std::cout << "\n[debug] [loose_remove]: found in subset_i\n";
                        subset_i->get_subset<bpt>(i + 1)->get_smallest(subset_i->data[i]);
                    }
                    // }
                    // ptr->get_smallest(data);
                }
            }
            else{
                get_subset<bpt>(i+1)->get_smallest(data[i]);
            }
        }
        else
        {
            get_subset<bpt>(i)->loose_remove(entry);
            if(get_subset<bpt>(i)->data_count < MINIMUM)
                fix_shortage(i);    
        }
            
    }
}   

template <class K, class V> 
BPlusTree<K, V>* BPlusTree<K, V>::fix_shortage(int i){
    bool debug = false;

    //if there is a left sibling and if there is extra elements in the sibling
    if(i != 0 && get_subset<bpt>(i - 1)->data_count > MINIMUM){
        //do a rotate right at subset[i - 1] to transfer the extra element
        transfer_right(i - 1);
    }

    //if there is a righ sibling transfer and if there is extra elements in the sibling
    else  if(i!= child_count - 1 && get_subset<bpt>(i + 1)->data_count > MINIMUM){ 
        //do a rotate left at subset[i + 1] to transfer element
        transfer_left(i + 1);
    }
    //else if there is a right sibling then combin two subset
    else if(i < child_count - 1){         

        merge_with_next_subset(i);
    }
    else  //else it must have left sibling, combine left sibling
    { 

        merge_with_next_subset(i-1);
        return get_subset<bpt>(i-1);
    
    }
        return get_subset<bpt>(i);

}  


template <class K, class V>
void BPlusTree<K, V>::get_smallest(K& entry){
    // bool debug = false;
    // if(debug && DEBUG)
    //     std::cout << "\t[debug] [get_mallest]: called \n";
    if(is_leaf()){
        entry = data[0];
    }
    else{
        get_subset<bpt>(0)->get_smallest(entry);
    }
}   


template <class K, class V>
void BPlusTree<K, V>::transfer_left(int i){
    assert(i < child_count && "[ROTATE_LEFT]: index out of bound!");
    assert(i > 0 && "[ROTATE_LEFT]: cannot rotate left at 0 OR negative index!");
    bpt* subset_i = get_subset<bpt>(i);
    bpt* subset_i_1 = get_subset<bpt>(i-1);
    int data_count_0 = subset_i->data_count;
    int data_count_1 = subset_i_1->data_count;
    RPointer* rptr;
    assert(subset_i->data_count > MINIMUM && "[ROTATE_LEFT]: there are no extra element to transfer!");

    if(subset_i->is_leaf())
    {
        K entry;
        delete_item(subset_i->data, 0, subset_i->data_count, entry);
        insert_item(subset_i_1->data, subset_i_1->data_count, subset_i_1->data_count, entry);

        data[i-1] = subset_i->data[0];

        delete_item(subset_i->subset, 0, data_count_0, rptr);
        insert_item(subset_i_1->subset, data_count_1, data_count_1, rptr);

    }
    else
    {
        K entry = data[i - 1];
        delete_item(subset_i->data, 0, subset_i->data_count, data[i - 1]);
        insert_item(subset_i_1->data, subset_i_1->data_count, subset_i_1->data_count, entry);

        delete_item(subset_i->subset, 0, subset_i->child_count, rptr);
        insert_item(subset_i_1->subset, subset_i_1->child_count, subset_i_1->child_count, rptr);

    }

}         

template <class K, class V>
void BPlusTree<K, V>::transfer_right(int i){
    // assert(i < child_count - 1 && "[ROTATE_RIGHT]: cannot rotate right at the last index OR, index is out of bound!");
    // assert(i >= 0 && "[ROTATE_RIGHT]:  negative index!");
    bpt* subset_i = get_subset<bpt>(i);
    bpt* subset_i_1 = get_subset<bpt>(i+1);
    int data_count_0 = subset_i->data_count;
    int data_count_1 = subset_i_1->data_count;
    RPointer* rptr;
    // assert(subset_i->data_count > MINIMUM && "[ROTATE_RIGHT]: there are no extra element to transfer!");

    if(subset_i->is_leaf())
    {
        K entry;
        delete_item(subset_i->data, data_count_0 - 1, subset_i->data_count, entry);
        insert_item(subset_i_1->data, 0, subset_i_1->data_count, entry);

        data[i] = subset_i_1->data[0];

        delete_item(subset_i->subset, data_count_0 - 1, data_count_0, rptr);
        insert_item(subset_i_1->subset, 0, data_count_1, rptr);

    }
    else
    {
        K entry = data[i];
        delete_item(subset_i->data, subset_i->data_count -1, subset_i->data_count, data[i]);
        insert_item(subset_i_1->data, 0, subset_i_1->data_count, entry);

        delete_item(subset_i->subset, subset_i->child_count -1, subset_i->child_count, rptr);
        insert_item(subset_i_1->subset, 0, subset_i_1->child_count, rptr);

    }

}        

template <class K, class V>
void BPlusTree<K, V>::merge_with_next_subset(int i){
    assert(i < child_count - 1 && "[Merage with next subset] Index out of bound || No next subset for last subset");
    assert(i >= 0 && "[Merage with next subset] merging negative index subset");
    bpt* subset_i = get_subset<bpt>(i);
    bpt* subset_i_1 = get_subset<bpt>(i+1);
    int data_count_0 = subset_i->data_count;
    int data_count_1 = subset_i_1->data_count;
    K key;
    //---------------------------------

    delete_item(data, i, data_count, key);
    if(!subset_i->is_leaf()){
        insert_item(subset_i->data, subset_i->data_count, subset_i->data_count, key);    
    }


    merge(subset_i->data, subset_i->data_count,
    subset_i_1->data, subset_i_1->data_count);

    if(subset_i->is_leaf()){
                // std::cout << "\t[Debug][merge_w_next_subset] before merge sub1 = ";
                // for(int i = 0; i < subset_i->data_count; ++i){
                //     std::cout << *subset_i->get_subset<V>(i) << " ";
                // }
                // std::cout << std::endl;

                // std::cout << "\t[Debug][merge_w_next_subset] sub2 = ";
                // for(int i = 0; i < subset_i_1->data_count; ++i){
                //     std::cout << *subset_i_1->get_subset<V>(i) << " ";
                // }
                // std::cout << std::endl;
                // std::cout << "[Debug][merge_w_next_subset] Also data_count0 = " << data_count_0 <<", data_count1 = " << data_count_1 << std::endl;
                

        merge(subset_i->subset, data_count_0,
        subset_i_1->subset, data_count_1);

        
    }
    else
    {
        // std::cout << "\t[Debug][merge_w_next_subset] merging non leaf nodes" << std::endl;
        merge(subset_i->subset, subset_i->child_count,
        subset_i_1->subset, subset_i_1->child_count);
    }



    RPointer* child;
    delete_item(subset, i + 1, child_count, child);
    subset_i->next = subset_i_1->next;
                // std::cout << "\t[Debug][merge_w_next_subset] subset_i_1 -> child_count = " << subset_i_1->child_count << std::endl;
                // std::cout << "\t[Debug][merge_w_next_subset] subset_i_1 -> data_count = " << subset_i_1->data_count << std::endl;
    delete (bptToken*) child;
} 



// template <class K, class V>
// int& BPlusTree<K,V>::get_subset_data_count(int i){

// }

template<class K, class V>
template<class T>
T* BPlusTree<K,V>::get_subset(int i) const{
    if(is_leaf())
        assert(i < data_count);
    else assert(i < child_count);
    // std::cout << "\tget_subset called!  d_c = " << data_count << "\n" ;
    return static_cast<RPointerToken<T>*>(subset[i])->recover_pointer();
}

template <class K, class V>
template <class T>
RPointerToken<T>* BPlusTree<K,V>::allocate_token(T* ptr){
    return new RPointerToken<T>(ptr);
}
  

#endif