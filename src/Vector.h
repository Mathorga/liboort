/*
********************************************************************************
Vector.h

This file implements a wrapper for a standard array (not a linked list),
allowing easy management of insertion, deletion and retrieval of items in the
array.
It's important for the array to be contiguous, in order to optimize parallel of
it. To do so the contained object is a standard C pointer.

Copyright (C) 2019  Luka Micheletti

********************************************************************************
*/

#ifndef __VECTOR__
#define __VECTOR__

#include "utils.h"

#define vector_size_t uint16_t

namespace Oort {
    template <class T>
    class Vector {
    public:
        // Constructors.
        Vector() {
            this->size = 0;
            this->items = nullptr;
        }
        Vector(vector_size_t size) {
            this->size = size;
            this->items = (T*) malloc(size * sizeof(T));
        }
        Vector(vector_size_t size, T* items) {
            this->size = size;
            this->items = items;
        }

        // Destructors.
        ~Vector() {
            delete[] this->items;
        }

        void addFirst(T* item) {}
        void addLast(T item) {
            T* tempItems;

            tempItems = (T*) realloc(this->items, (this->size + 1) * sizeof(T));

            if (tempItems != NULL) {
                this->items = tempItems;
                this->items[this->size] = item;
                this->size++;
            } else {
                printf("\n<Vector::addLast()> Error inserting item\n");
            }
        }
        void addLast(T* item) {
            T* tempItems;

            tempItems = (T*) realloc(this->items, (this->size + 1) * sizeof(T));

            if (tempItems != NULL) {
                this->items = tempItems;
                this->items[this->size] = (*item);
                this->size++;
            } else {
                printf("\nERROR INSERTING ITEM\n");
                //TODO.
            }
        }
        void addAt(T* item, vector_size_t position) {}
        void replaceAt(T item, vector_size_t index) {
            if (index >= 0 && index < this->size) {
                this->items[index] = item;
            } else {
                printf("\nINDEX OUT OF BOUNDS\n");
                //TODO
            }
        }
        void replaceAt(T* item, vector_size_t index) {
            if (index >= 0 && index < this->size) {
                this->items[index] = (*item);
            } else {
                printf("\nINDEX OUT OF BOUNDS\n");
                //TODO
            }
        }
        T removeFirst() {}
        T removeLast() {}
        T removeAt(vector_size_t position) {}
        void empty() {
            this->size = 0;
            // free(this->items);
            this->items = nullptr;
        }

        // Getters.
        vector_size_t getSize() {
            return this->size;
        }
        T* getItems() {
            return this->items;
        }
        T* getItem(vector_size_t index) {
            if (index >= 0 && index < this->size) {
                return &(this->items[index]);
            } else {
                printf("\nINDEX OUT OF BOUNDS\n");
                //TODO
                // return NULL;
            }
        }
        T* getFirst() {
            if (this->size > 0) {
                return &(this->items[0]);
            } else {
                return nullptr;
            }
        }
        T* getLast() {
            T* item = nullptr;
            if (this->size > 0) {
                item = &(this->items[this->size - 1]);
            }
            return item;
        }

        // Setters.
        void setItems(T* items, vector_size_t size) {
            this->size = size;
            this->items = items;
        }

    protected:
        vector_size_t size;
        T* items;

    };
}

#endif
