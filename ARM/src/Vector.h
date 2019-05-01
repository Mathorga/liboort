#ifndef __VECTOR__
#define __VECTOR__

#include "utils.h"

template <class T>
class Vector {
public:
    // Getters.
    T* getItems();

    // Setters.
    void setItems(T* items);

protected:
    T* items;
};

#endif
