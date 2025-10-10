#include <stdio.h>
#include <stdlib.h>
#include "decbuff.h"

int main(){
  int size;
  int decimation_factor;

  printf("Set buffer size: ");
  scanf("%d", &size);
  printf("Set decimation factor: ");
  scanf("%d", &decimation_factor);
  Buff* myBuff = buff_init(size, decimation_factor);

  int inserted_int = 1;
  while (inserted_int!=0) {
    printf("\n\nInsert a number in buffer (0 for terminating): ");
    scanf("%d", &inserted_int);
    buff_put(myBuff, inserted_int);
    buff_print(myBuff);
    printf("\nBuffer is full (1 yes / 0 no)?: %d", buff_is_full(myBuff));
  }
  
  return 0;
}
