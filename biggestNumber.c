#include <stdio.h>

int main() {
  printf("Please enter the 3 numbers\n");

  int a = 0, b = 0, c = 0;
  scanf("%d %d %d", &a, &b, &c);

  if (a > b && a > c) { 
    printf("The biggest number is: %d\n", a);
  } else if (b > a && b > c) {
    printf("The biggest number is: %d\n", b);
  } else {
    printf("The biggest number is: %d\n", c);
  }

  return 0;

};
