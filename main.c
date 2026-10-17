#include <stdio.h>
#include <stdlib.h>

struct Employee {
  char *name;
  char *id;
  float salary;
  float bonus;
  int workingdays;
  int paidleaves;
  int sickleaves;
};

void initEmployee(struct Employee *E) {
  printf("Enter Name : ");
  scanf("%s", E->name);
  printf("Enter ID : ");
  scanf("%s", E->id);
  printf("Enter Inital salary : ");
  scanf("%f", &E->salary);
}

int main() {
  system("clear");
  // Deduction Logic
  struct Employee Employee[100];
  Employee[0].name = "Sharma";
  Employee[0].id = "STR26001";
  Employee[0].salary = 10000.0f;
  Employee[0].workingdays = 100;
  Employee[0].paidleaves = 8;
  Employee[0].sickleaves = 2;
}
