#ifndef DECBUFF_H_
#define DECBUFF_H_

typedef struct Buff {
  int* buffer;
  int size;
  // Save the first of each decimation_factor elements (this = 1 means no compression)
  int decimation_factor; 
  // Index of the buffer array writable element
  int write_index;
  // Index of the last element of compressed chunk 
  int compression_index;
} Buff;

void init(Buff* buff, int size, int decimation_factor);
void compress(Buff* buff);
void put(Buff* buff, int val);
void print(Buff* buff);

#endif