#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
  char *buff = (char *)malloc(1234567);
  bzero(buff, 1234567);
  
  int fd = open("jin.bmp", O_RDONLY);
  int ret = read(fd, buff, 1234567);
  
  buff = &buff[54];
  int size = ret - 54;

  for (int i = 16; i + 16 < size; i += 16)
    {
      write(1, &buff[size - i], 16);
    }
}
