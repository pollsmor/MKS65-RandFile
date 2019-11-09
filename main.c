#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int randgen() {
  int fd = open("/dev/urandom", O_RDONLY);
  int * buff = malloc(sizeof(int));
  read(fd, buff, sizeof(int));

  int output = *buff;
  free(buff);

  return output;
}

int main() {
  printf("Generating random numbers: \n");
  int randArr[10];
  int i;
  for (i = 0; i < 10; i++) {
    randArr[i] = randgen();
    printf("  Random %d: %d \n", i, randArr[i]);
  }

  printf("\n");

  return 0;
}
