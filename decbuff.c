#include <stdio.h>
#include <stdlib.h>
#include "decbuff.h"

void init(Buff* buff, int size, int decimation_factor){
  buff->size = size;
  buff->decimation_factor = decimation_factor;
  buff->write_index = 0;
  buff->compression_index = -1;
  buff->buffer = (int*)malloc(sizeof(int)*buff->size);
}

void compress(Buff* buff){
  // If you've compressed the whole buffer, then start again from first element
  if (buff->compression_index+1>=buff->size) buff->compression_index = -1;

  // This is the index of the current element that is going to be conserved
  // during compression, others are going to be deleted from buffer
  int saved_element_index = buff->compression_index+1;

  // For each element starting from the last compressed one, save the first
  // for each decimation_factor elements if it's inside the buffer, 
  // otherwise set it NULL
  for (int i=saved_element_index; i<buff->size; i++) {
    if (saved_element_index<buff->size) {
      buff->buffer[i] = buff->buffer[saved_element_index];
      saved_element_index += buff->decimation_factor;
      buff->compression_index++;
    } else {
      buff->buffer[i] = NULL;
    }
  }

  // After compression, you can write in buffer starting from last compressed element
  buff->write_index = buff->compression_index+1;
}

void put(Buff* buff, int val) {
  if (buff->write_index >= buff->size) compress(buff);

  buff->buffer[buff->write_index] = val;
  buff->write_index++;
}

void clear(Buff* buff) {
  free(buff->buffer);
  buff->buffer = NULL;
  init(buff, buff->size, buff->decimation_factor);
}

void print(Buff* buff){
  printf("[write_index: %d, compression_index: %d]\n", buff->write_index, buff->compression_index);
  for (int i=0; i<buff->size; i++) {
    printf("%d ", buff->buffer[i]);
  }
}