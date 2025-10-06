#include <stdio.h>
#include <stdlib.h>

int buffer_size;
// Save the first of each decimation_factor elements (this = 1 means no compression)
int decimation_factor;
// Index of the buffer array writable element
int write_index = 0;
// Index of the last element of compressed chunk 
int compression_index = -1;

void compress(int* buffer, int bufferSize){
  // If you've compressed the whole buffer, then start again from first element
  if (compression_index+1>=bufferSize) compression_index = -1;

  // This is the index of the current element that is going to be conserved
  // during compression, others are going to be deleted from buffer
  int saved_element_index = compression_index+1;

  // For each element starting from the last compressed one, save the first
  // for each decimation_factor elements if it's inside the buffer, 
  // otherwise set it NULL
  for (int i=saved_element_index; i<bufferSize; i++) {
    if (saved_element_index<bufferSize) {
      buffer[i] = buffer[saved_element_index];
      saved_element_index += decimation_factor;
      compression_index++;
    } else {
      buffer[i] = NULL;
    }
  }

  // After compression, you can write in buffer starting from last compressed element
  write_index = compression_index+1;
}

void put(int* buffer, int bufferSize, int val) {
  if (write_index >= bufferSize) compress(buffer, bufferSize);

  buffer[write_index] = val;
  write_index++;
}

void printbff(int* buffer, int bufferSize){
  for (int i=0; i<bufferSize; i++) {
    printf("%d ", buffer[i]);
  }
}


int main(){
  printf("Set buffer size: ");
  scanf("%d", &buffer_size);
  printf("Set decimation factor: ");
  scanf("%d", &decimation_factor);
  int* buffer = (int*)malloc(sizeof(int)*buffer_size);

  int inserted_int = 1;
  while (inserted_int!=0) {
    printf("\n\nInsert a number in buffer (0 for terminating): ");
    scanf("%d", &inserted_int);
    put(buffer, buffer_size, inserted_int);
    printf("New buffer (write_index: %d, compression_index: %d): \n", write_index, compression_index);
    printbff(buffer, buffer_size);
  }
  
  return 0;
}