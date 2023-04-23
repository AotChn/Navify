#ifndef BPLUSTREE_ARRAY_FUNCTIONS_CPP
#define BPLUSTREE_ARRAY_FUNCTIONS_CPP

#include "btree_array_funcs.h"
#include <cassert>
#include <iostream>

template <class T>
T maximal(const T& a, const T& b){
    if(b < a)
        return a;
    else return b;
}

template <class T>
void Swap(T& a, T& b){
    T  temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[ ], int n){
    int l_index = -1;
    T l_value = *data;
    for(int i = 0; i < n; i ++){
        if(!(data[i] < l_value)){
            l_index = i;
            l_value = data[i];
        }
    }

    return l_index;
}

template <class T>
void ordered_insert(T data[ ], int& n, T entry){
    insert_item(data, first_ge(data, n, entry), n , entry);
}

template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    // for(int i = 0; i < n; i++)
    // {
    //     if(!(data[i] < entry)){
    //         return i;
    //     }
    // }

    if(n == 0 || data[n-1] < entry) return n;
    else{
        int last_index;
        int left = 0, right = n - 1;
        int mid; 
        while(left <= right){
            mid = left + (right - left)/2;
            if(data[mid] < entry){
                left = mid + 1;
            }
            else{
                last_index = mid;
                right = mid - 1;
            }
        }
        // std::cout << "[Debug] [FIRST_GE] last_index: " << last_index << std::endl;
        return last_index;
    }

}


template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    insert_item(data, n, entry);
}

template <class T>
void insert_item(T data[ ], int insert_here, int& n, T entry){
    assert(insert_here >=  0 && "[Insert Item]: Negative Index");
    for(int i = n; i > insert_here; i--){
        Swap(data[i], data[i-1]);
    }
    data[insert_here] = entry;
    n++;
}

template <class T>
void detach_item(T data[ ], int& n, T& entry){
    delete_item(data, n - 1, n, entry);
}

template <class T>
void delete_item(T data[ ], int index, int& n, T& entry){
    assert(index >= 0 && "[delete_item]negative index");
    assert(index < n && "[delete_item]index out of bound");
    entry = data[index];
    n--;
    for(int i = index; i < n; i++){
        Swap(data[i], data[i+1]);
    }
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
    assert(data1 != data2);
    for(int i = 0; i < n2; i++){
        data1[i + n1] = data2[i];
    }
    n1 += n2;
    n2 = 0;
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
    bool debug = false;
    assert(n2 == 0 && "data1 should be containing the data, and data2 should be empty");
    assert(data1 != data2);

    if(n1 == 0) return;
    if(debug){
        std::cout << "[Debug] Before split, data1: "; print_array(data1, n1);
    }

    int temp = n1 /2; //the number of element taken from n1
    n2 = temp;

    //if n1 is odd
    //split starting from mid+1
    if(n1 % 2){
        temp++;
    }
    
    if(debug){
        std::cout << "\n[Debug] data1[temp]: " << data1[temp] <<std::endl;
        // std::cout << "\n\n    temp = " << temp << "\n\n";
    }
    for(int i = 0; i < n2; ++i)
    {
        data2[i] = data1[i + temp];
    }
    
    //decrement n1
    n1 -= n2;

    if(debug){
        std::cout << "\n[Debug] data1: "; print_array(data1, n1);
        std::cout << "\n[Debug] data2: "; print_array(data2, n2); std::cout << "\n";
    }

}

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size)
{
    dest_size = src_size;
    for(int i = 0; i < src_size; i++){
        dest[i] = src[i];
    }
}

template <class T>
void print_array(const T data[], int n, int pos){
    if(pos == -1){
        for(int i = 0; i < n; i++){
            std::cout << data[i] << " ";
        }
    }else std::cout << data[pos];
}

template <class T>
bool is_gt(const T data[], int n, const T& item){
    for(int i = 0; i < n; i++){
        if(item <= data[i]) return false;
    }
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item){
    for(int i = 0; i < n; i++){
        if(item > data[i]) return false;
    }
    return true;
}
//-------------- Vector Extra operators: ---------------------

template <typename T>
std::ostream& operator <<(std::ostream& outs, const std::vector<T>& list){
    for(int i = 0; i < list.size(); i++){
        outs << "[" << list[i] << "] "; 
    }
    return outs;
}


template <class T>
std::vector<T>& operator +=(std::vector<T>& lhs, const T& rhs){
    // std::cout << "\t[Debug][+= (vector& v, const &T)]: called\n";

    lhs.push_back(rhs);
    return lhs;
}


template <class T>
std::vector<T>& operator +=(std::vector<T>& lhs, const std::vector<T>& rhs){
    // std::cout << "\t[Debug][+= (vector& v, const vector& v2)]: called\n";
    for(int i = 0; i < rhs.size(); ++i){
        lhs.push_back(rhs.at(i));
    }
    return lhs;
}

// std::vector<std::string>& operator +=(std::vector<std::string>& lhs, const char* rhs){
//     lhs.push_back(rhs);
//     return lhs;
// }

#endif 