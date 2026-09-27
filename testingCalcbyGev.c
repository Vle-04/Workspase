#include <stdio.h>

int main () {
  printf("Hi!!");

  int i = 0;
  while(i < 10) {
    int l = 10 - i;
    printf("you have %d calculations\n", l);
    char ch;
    scanf(" %c", &ch);

    if (ch == 'q') {
      printf("Quit!!!\n");
      return 0;
    }

    double a, b, c;
    printf("type the first num!\n ");
    scanf("%lf", &a);
    printf("type the second num!\n");
    scanf("%lf", &b);

    if (ch == '+') {
      c = a + b;
      printf("result is : %f\n", c);
    } else if (ch == '-') {
      c = a - b;
      printf("result is : %f\n", c);
    } else if (ch == '*') {
      c = a * b;
      printf("result is : %f\n", c);
    } else if (ch == '/')  {
      c = a / b;
      printf("result is : %f\n", c);
    } else {
      printf("something went wrong");
      return 0;
    }
  }
    return 0;
}
