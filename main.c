#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int randgen() {
  int fd = open("/dev/urandom", O_RDONLY); //don't need error handling, not the program's fault /dev/urandom isn't accessible
  int * buff = malloc(sizeof(int));
  read(fd, buff, sizeof(int)); //same reasoning here
  close(fd);

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

  //==========================================================

  printf("\n");
  printf("Writing numbers to file... \n");
  int fd = open("random.txt", O_CREAT | O_WRONLY, 0640);
  if (fd < 0) {
    printf("Error %d: %s \n", errno, strerror(errno));
    return 0;
  }

  int bytesWritten = write(fd, randArr, sizeof(randArr));
  if (bytesWritten < 0) {
    printf("Error %d: %s \n", errno, strerror(errno));
    return 0;
  }

  //==========================================================

  printf("\n");
  printf("Reading numbers from file... \n");
  fd = open("random.txt", O_RDONLY); //start from beginning of file again
  int randArr2[10];
  int bytesRead = read(fd, randArr2, sizeof(randArr2));
  if (bytesRead == -1) {
    printf("Error %d: %s \n", errno, strerror(errno));
    return 0;
  }

  close(fd);

  //==========================================================

  printf("\n");
  printf("Verification that written values were the same: \n");
  for (i = 0; i < 10; i++) {
    printf("  Random %d: %d \n", i, randArr2[i]);
  }

  return 0;
}
