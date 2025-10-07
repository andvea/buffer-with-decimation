#include <stdio.h>
#include <stdlib.h>
#include "decbuff.h"

int main(){
  Buff* myBuff;
  int size;
  int decimation_factor;

  printf("Set buffer size: ");
  scanf("%d", &size);
  printf("Set decimation factor: ");
  scanf("%d", &decimation_factor);
  init(myBuff, size, decimation_factor);

  int inserted_int = 1;
  while (inserted_int!=0) {
    printf("\n\nInsert a number in buffer (0 for terminating): ");
    scanf("%d", &inserted_int);
    put(myBuff, inserted_int);
    print(myBuff);
  }
  
  return 0;
}