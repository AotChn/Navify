#ifndef BPLUSTREE_ARRAY_FUNCTIONS_H
#define BPLUSTREE_ARRAY_FUNCTIONS_H

#include <vector>
#include <iostream>
#include <string>

template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void Swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data



//Pre: n is the number of entry in data
//Post: n will be incremented and
//      entry is insert in ascending order
//Note: if there are duplicate values in data[] as same as entry (determined by <=),
//      entry will be inserted at the position of the first met <= entry.
template <class T>
void ordered_insert(T data[ ], int& n, T entry);        

//return the first element in data that is
//not less than entry
template <class T>
int first_ge(const T data[ ], int n, const T& entry);   

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry


//Precondition: data1 have enough space for n1 + n2;
//Poscondition: All the entries in data2 are appended to the right of data1
//              n1 = n1 + n2;
//              n2 = 0;
template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   


//Pre:  data2 is empty
//Post: move n/2 elements from the right of data1
//      and move to data2
template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   


template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
std::ostream& operator <<(std::ostream& outs, const std::vector<T>& list); //print vector list

template <typename T>
std::vector<T>& operator +=(std::vector<T>& list, const T& addme); //list.push_back addme

template <typename T>
std::vector<T>& operator +=(std::vector<T>& lhs, const std::vector<T>& rhs);


// std::vector<std::string>& operator +=(std::vector<std::string>& lhs, const char* rhs);

#include "btree_array_funcs.cpp"
#endif 