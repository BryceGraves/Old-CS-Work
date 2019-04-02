// R. Jesse Chaney

// What do you include to get the standard i/o functions?
// -We have to include stdio.h to get the standard i/o functions
// What do you include to get the new type account_t into your code?
// -We include lab1.h which contains the account_t struct

#include <stdio.h>
#include "lab1.h"

int main(int argc, char *argv[]) {
  account_t act;
  account_t *act_ptr = &act;
  
  act.account_number = 12345;
  act_ptr->balance = 678.9f;
  
  printf("%d\n", act.account_number);
  printf("%f\n", act_ptr->balance);
  printf("%s\n", YOUR_NAME);

  return(0);
}
