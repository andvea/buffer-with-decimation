#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decbuff.h"

Buff* buff_init(int size, int decimation_factor){
  Buff* buff = (Buff*)malloc(sizeof(Buff));
  buff->size = size;
  buff->decimation_factor = decimation_factor;
  buff->write_index = 0;
  buff->compression_index = -1;
  buff->buffer = (buff_data_type*)malloc(sizeof(buff_data_type)*buff->size);
  return buff;
}

void buff_compress(Buff* buff){
  // If you've compressed the whole buffer, then start again from first element
  if (buff->compression_index+1>=buff->size) buff->compression_index = -1;

  int start = buff->compression_index+1;
  int write_index = start;

  // Move compressed elements at the beginning of the buffer
  for (int i=start; i<buff->size; i+=buff->decimation_factor) {
    buff->buffer[write_index++] = buff->buffer[i];
  }

  // Set remaining slots with zeros
  if (write_index < buff->size) {
    memset(&buff->buffer[write_index], 0, (buff->size - write_index) * sizeof(buff->buffer[0]));
  }

  // Update indexes
  buff->write_index = write_index;
  buff->compression_index = write_index - 1;
}

void buff_put(Buff* buff, buff_data_type val){
  if (buff->write_index >= buff->size) buff_compress(buff);

  buff->buffer[buff->write_index] = val;
  buff->write_index++;
}

void buff_clear(Buff* buff){
  memset(buff->buffer, 0, buff->size * sizeof(buff->buffer[0]));
  buff->write_index = 0;
  buff->compression_index = -1;
}

void buff_delete(Buff* buff){
  free(buff->buffer);
  buff->buffer = NULL;
}

int buff_is_full(Buff* buff){
  return (buff->write_index==buff->size);
}

void buff_print(Buff* buff){
  printf("[write_index: %d, compression_index: %d]\n", buff->write_index, buff->compression_index);
  for (int i=0; i<buff->size; i++) {
    PRINT_BUFF_DATA(buff->buffer[i]);
  }
}