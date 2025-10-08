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

void buff_init(Buff* buff, int size, int decimation_factor);
void buff_compress(Buff* buff);
void buff_put(Buff* buff, int val);
void buff_print(Buff* buff);

#endif
