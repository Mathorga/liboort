#ifndef __VECTOR__
#define __VECTOR__

#include "utils.h"

#define vector_size_t uint16_t

template <class T>
class Vector {
public:
    // Constructors.
    Vector() {
        this->size = 0;
        this->items = NULL;
    }

    Vector(vector_size_t size) {
        this->size = size;
        this->items = (T*) malloc(size * sizeof(T));
    }

    Vector(vector_size_t size, T* items) {
        this->size = size;
        this->items = items;
    }

    void addFirst(T* item) {}
    void addLast(T* item) {}
    void addAt(T* item, vector_size_t posigion) {}
    T* removeFirst() {}
    T* removeLast() {}
    T* removeAt(vector_size_t position) {}

    // Getters.
    vector_size_t getSize() {
        return this->size;
    }

    T* getItems() {
        return this->items;
    }

    // Setters.
    void setItems(T* items);

protected:
    vector_size_t size;
    T* items;

};

#endif
