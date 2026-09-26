#include <stdio.h>

int calculator(int a, int b, char ch, int flag) {
  

  if (ch == '+') {
    return a + b;
  } else if (ch == '-') {
    return a - b;
  } else if (ch == '*') {
    return a * b;
  } else if (ch == '/') {
    flag = 1;
    return (float)a / b;
  } else if (ch == '%') {
    return a % b;
  } else {
    printf("This calculator uses only this operations: 'add+', 'div-', 'mul*', 'div/', 'mod%' ");
    return -1;
  }

}

int main() {

  int a = 0;
  int b = 0;
  char ch = 0;
  int flag = 0;
  
  printf("   WELCOME TO BASIC CALCULATOR \n");


  printf("Please enter the first number: \n");
  scanf("%d", &a);

  printf("Please enter the second number:\n");
  scanf("%d", &b);

  printf("Please enter the operation for numbers\n");
  scanf(" %c", &ch);

  float result = calculator(a, b, ch, flag);
  
  if (flag == 1) printf("The result is: %.02f\n", (float)result);
  else printf("The result is: %f\n", result);

  printf("   You are STUPID\n");
  return 0;
}
