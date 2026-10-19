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

void initEmployee(struct Employee *E) {
  char ch = ' ';
  printf("Enter Name : ");
  int pos = 0;
  while (ch != '\n') {
    scanf("%c", &ch);
    E->name[pos] = ch;
    pos++;
  }
ID:
  printf("Enter ID : ");
  ch = ' ';
  pos = 0;
  while (ch != '\n' && pos < 10) {
    scanf("%c", &ch);
    E->id[pos] = ch;
    pos++;
  }
  if (pos >= 10 && E->id[0] == 'S' && E->id[1] == 'T' && E->id[2] == 'R') {
    printf("Please Enter a ValidID!\n");
    goto ID;
  }
  if (E->id[3] == '0' && E->id[4] == '0') {
    E->paidleaves = 25;
    E->salary = 100000;
  } else if (E->id[3] == '0' && E->id[4] == '1') {
    E->paidleaves = 20;
    E->salary = 10000;
  } else if (E->id[3] == '0' && E->id[4] == '2') {
    E->paidleaves = 12;
    E->salary = 1000;
  } else {
    goto ID;
  }
  E->sickleaves = 12;
  E->workingdays = 0;
}

void printvar(char *str) {
  int pos = 0;
  char ch = str[0];
  while (ch != '\n') {
    pos++;
    printf("%c", ch);
    ch = str[pos];
  }
  printf("\n");
}

void salaryDay(struct Employee *E) {
  int totalWorkingdays;
  printf("Enter No.of Total Working Days : ");
  scanf("%d", &totalWorkingdays);
  printf("Enter No.of Working Days : ");
  scanf("%d", &E->workingdays);
  float finalSalary = ((float)E->workingdays /
                       (totalWorkingdays - E->paidleaves - E->sickleaves)) *
                      E->salary;
  E->bonus = (finalSalary <= E->salary)
                 ? 10
                 : (((finalSalary - E->salary) / E->salary * 100 > 30)
                        ? 20
                        : ((finalSalary - E->salary) / E->salary * 100) + 10);
  printf("Bonus : %f\n", E->bonus);
  finalSalary = E->salary * (1 + E->bonus / 100);
  printf("Final salary : %f\n", finalSalary);
}

int main() {
  system("clear");
  // Deduction Logic
  struct Employee E[100];
  int Running = 1;
  int totalemp = 0;
  char buffer;
  initEmployee(&E[0]);
  printvar(E[0].name);
  printvar(E[0].id);
  printf("%.2f\n", E[0].salary);
  printf("%d\n", E[0].sickleaves);
  printf("%d\n", E[0].paidleaves);
  salaryDay(&E[0]);
}
