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
                 ? ((E->salary - finalSalary) / E->salary) * 100
                 : (((finalSalary - E->salary) / E->salary * 100 > 30)
                        ? 20
                        : ((finalSalary - E->salary) / E->salary * 100) + 10);
  printf("Bonus : %f\n", (E->bonus > 0) ? E->bonus : 0.0f);
  finalSalary = E->salary * (1 + E->bonus / 100);
  printf("Final salary : %f\n", finalSalary);
}

int main() {
  system("clear");
  // Deduction Logic
  struct Employee E[100];
  int Running = 1;
  int totalemp = 0;
  char buffer, option;
  printf("==========================================================\n");
  printf("                Employee Payroll Management               \n");
  printf("==========================================================\n");
  while (Running) {
    printf("==========================================================\n");
    printf("                           Menu                           \n");
    printf("==========================================================\n");
    printf("  1. n -> New Employee\n  2. l -> List "
           "Employee\n  3. s -> Enter Salaries\n  4. c -> Clear whole screen"
           "\n  5. q -> quit application\nEnter an Option : ");
    scanf("%c%c", &option, &buffer);
    if (option == 'q') {
      Running = 0;
    } else if (option == 'n') {
      printf("==========================================================\n");
      printf("                      New Employee                        \n");
      printf("==========================================================\n");
    ReEnter:
      initEmployee(&E[totalemp]);
      for (int i = 0; i < totalemp; i++) {
        if (E[i].id[6] == E[totalemp].id[6] &&
            E[i].id[7] == E[totalemp].id[7] &&
            E[i].id[8] == E[totalemp].id[8]) {
          printf("Employee Already Exists! Please Recheck and Reenter the "
                 "name!\n");
          goto ReEnter;
        }
      }
      totalemp++;
    } else if (option == 'l') {
      printf("==========================================================\n");
      printf("                      Employee List                       \n");
      printf("==========================================================\n");
      for (int i = 0; i < totalemp; i++) {
        printf("Name : ");
        printvar(E[i].name);
        printf("Id : ");
        printvar(E[i].id);
        printf("Salary : %.2f\n", E[i].salary);
      }
    } else if (option == 's') {
      printf("==========================================================\n");
      printf("                    Employee Salaries                     \n");
      printf("==========================================================\n");
      for (int i = 0; i < totalemp; i++) {
        printf("For ID : %s", E[i].id);
        salaryDay(&E[i]);
      }
    } else if (option == 'c') {
      system("clear");
      printf("==========================================================\n");
      printf("                Employee Payroll Management               \n");
      printf("==========================================================\n");
    } else {
      printf("Enter a Valid Option!\n");
    }
  }
}
