#ifndef RAW_POINTER_H 
#define RAW_POINTER_H
#include <iostream>

class RPointer{
public:
    void recover_pointer()
    { 
        bool debug = false;
        if(debug)std::cout << "[debug] [RPointer]: called recover_pointer()\n";
    }
};

template <typename T>
class RPointerToken:  public RPointer{
    T* _ptr;
public:
    RPointerToken(T* ptr = nullptr): _ptr(ptr){}
    RPointerToken(T value){_ptr = new T(value);}

    RPointerToken& operator = (T* ptr){_ptr = ptr; return this;}
    ~RPointerToken(){
        if(_ptr) {
            // std::cout << "[debug] [RPointerToken: Destructor]: deleting _ptr\n";
            delete _ptr;
        }
    }
    T* recover_pointer(){
        bool debug = false;
        if(debug)
            std::cout << "[debug] [RPointerToken]: called recover_pointer()\n";
        
        return _ptr;
    }

};
#endif
