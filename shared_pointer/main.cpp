#include <iostream>
#include "shared_pointer.hpp"

int main()
{
    shared_ptr<int> ptr = new int(10);
    std::cout << "value ptr is: " << *ptr << std::endl;

    shared_ptr<int> ptr1;
    ptr1 = ptr;
    std::cout << "value ptr is: " << *ptr << std::endl;
    std::cout << "value ptr1 is: " << *ptr1 << std::endl;

    std::cout << "ref count = " << ptr.get_count() << std::endl;

    {
        shared_ptr<int> ptr3;
        ptr3 = ptr1;
        std::cout << "ref count = " << ptr1.get_count() << std::endl;
    }

    shared_ptr<int> ptr4 = new int(20);
    ptr4.swap(ptr1);
    std::cout << "ptr4: " << *ptr4 << std::endl;
    std::cout << "ptr1: " << *ptr1 << std::endl;

    //std::cout << "ref count = " << ptr4.get_count() << std::endl;

    size_t size = 5;
    int* arr = new int[size]{1, 3, 5, 7, 9};
    shared_ptr<int> ptr_arr = arr;

    for (size_t i = 0; i < size; ++i) {
        std::cout << "ptr_arr[" << i << "] = " <<ptr_arr[i] << std::endl;
    }

}
