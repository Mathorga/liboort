#include "Vector.h"

// template <class T>
// Vector<T>::Vector() {
//     this->items = NULL;
// }
//
// template <class T>
// Vector<T>::Vector(T* items) {
//     this->items = items;
// }

template <class T>
T* Vector<T>::getItems() {
    return this->items;
}

template <class T>
void Vector<T>::setItems(T* items) {
    this->items = items;
}
