#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"


void ctor(Vector* this){    
    this->capacity = 10;
    this->size = 0;
    this->ptr = malloc(this->capacity * sizeof(int));
}

void dtor(Vector* this){
    this->size = 0;
    this->capacity = 0;
    free(this->ptr);
    this->ptr==NULL;
}

void push_back(Vector* this, int val){
    if(this->size == this->capacity){
        this->capacity *= 1.2;
        this->ptr = realloc(this->ptr, this->capacity * sizeof(int));
        if(!(this->ptr)){
            perror("Malloc Error\n");
            exit(EXIT_FAILURE);
        }
    }
    this->ptr[this->size++] = val;
}

void clear(Vector* this){
    this->size = 0;
}

void pop_back(Vector* this){
    if (this->size == 0){
        printf("Seg fault");
    }
    --this->size;
}

size_t size(Vector* this){
    return this->size;
}

size_t capacity(Vector* this){
    return this->capacity;
}

void insert(Vector* this, size_t index, int val){  
    if(this->size == this->capacity){ 
        this->capacity *= 2;
        this->ptr = realloc(this->ptr, this->capacity * sizeof(int));
        if(!(this->ptr)){
            perror("Malloc Error\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = this->size++; i >= index; i--){   
        this->ptr[i] = this->ptr[i-1];
    }

    this->ptr[index] = val;

}

void erase(Vector* this, size_t index){
    if(index > this->size){
        printf("Index not found");
    }
    int tmp = 0;
    for (int i = index; i < this->size; i++)
    {
        tmp = this->ptr[i];
        this->ptr[i] = this->ptr[i + 1];
        this->ptr[i + 1] = tmp;
    }

    --this->size;
}

void print(Vector* this){
    if (this->size > this->capacity)
    {
        perror("Malloc Error");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < this->size; i++)
    {
        printf("%d ", this->ptr[i]);
    }
    
}


void insert_range(Vector* this, size_t start, size_t end, int val){
    int count = end - start + 1;

    if(this->size + count == this->capacity){
        this->capacity *= 2;
        this->ptr = realloc(this->ptr, this->capacity * sizeof(int));
        if(!(this->ptr)){
            perror("Malloc Error\n");
            exit(EXIT_FAILURE);
        }
    }

   
    for(int i = this->size + count - 1; i > start; i--){
        this->ptr[i] = this->ptr[this->size--];
    }

    for(int i = start; i <= end; i++){
        this->ptr[i] = val;
    }
}
