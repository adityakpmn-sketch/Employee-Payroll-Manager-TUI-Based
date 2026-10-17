#include <stdio.h>
#include <stdlib.h>

struct Employee {
  char name[100];  // 1
  char id[10];     // 2
  float salary;    // 3
  float bonus;     // 4
  int workingdays; // 5
  int paidleaves;  // 6
  int sickleaves;  // 7
};

void initEmployee(struct Employee E) {
  char ch = ' ';
  printf("Enter Name : ");
  int pos = 0;
  while (ch != '\n') {
    scanf("%c", &ch);
    E.name[pos] = ch;
    pos++;
  }
ID:
  printf("Enter ID : ");
  ch = ' ';
  pos = 0;
  while (ch != '\n' && pos < 10) {
    scanf("%c", &ch);
    E.id[pos] = ch;
    pos++;
  }
  if (pos >= 10) {
    printf("Please Enter a ValidID!\n");
    goto ID;
  }
  scanf("%s", E.id);
  printf("Enter Inital salary : ");
  scanf("%f", &E.salary);
  E.sickleaves = 0;
  E.paidleaves = 0;
  E.workingdays = 0;
}

int main() {
  system("clear");
  // Deduction Logic
  struct Employee E[100];
  initEmployee(E[0]);
}
