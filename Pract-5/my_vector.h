#pragma once
#include "IndexOutOfBoubds.h"
template <typename T>
class Vector {
private:
    T* arr;
    int size_reserved = 0;
    int current_end = 0;

public:
    Vector(int size) {
        size_reserved = size;
        arr = new T[size];
        current_end = 0;
    }
    Vector() {

    }

    T* get(int index) throw (IndexOutOfBounds) {

        if (index < size_reserved) {
            return (arr + index);
        }
        else if (index < 0) {
            throw IndexOutOfBounds(current_end, index);
        }
        else {
            throw IndexOutOfBounds(current_end, index);
        }
    }

    void push(T shape) {

        if (isFull()) {
            T* tmp = new T[size_reserved * 2];
            size_reserved *= 2;

            for (int i = 0; i < current_end; i++) {
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = tmp;

        }
        arr[current_end++] = shape;
    }

    T& operator[](int index) {
        if (index < size_reserved)
            return arr[index];
    }

    inline bool isEmpty() {
        return (current_end == 0);
    }
    inline bool isFull() {// also can be pasted to .h file
        return (current_end == size_reserved);
    }
};