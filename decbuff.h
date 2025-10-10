#ifndef DECBUFF_H_
#define DECBUFF_H_

typedef uint64_t buff_data_type;
#define PRINT_BUFF_DATA(x) printf("%llu ", (unsigned long long)(x))

typedef struct Buff {
  buff_data_type* buffer;
  int size;
  // Save the first of each decimation_factor elements (this = 1 means no compression)
  int decimation_factor; 
  // Index of the buffer array writable element
  int write_index;
  // Index of the last element of compressed chunk 
  int compression_index;
} Buff;

Buff* buff_init(int size, int decimation_factor);
void buff_compress(Buff* buff);
void buff_put(Buff* buff, buff_data_type val);
void buff_clear(Buff* buff);
void buff_delete(Buff* buff);
int buff_is_full(Buff* buff);
void buff_print(Buff* buff);

#endif
