
#include <stdio.h>
#include <string.h>
#define MAX_EMPLOYEES 100
struct Employee {
  char name[100];  // 1
  char id[10];     // 2
  float salary;    // 3
  float bonus;     // 4
  int workingdays; // 5
  int paidleaves;  // 6
  int sickleaves;  // 7
};
void initEmployee(struct Employee *E);
void salaryDay(struct Employee *E);
/* UI owns the employee list */
struct Employee employees[MAX_EMPLOYEES];
int totalemp = 0;
void header(void) {
    printf("\n");
    printf("====================================================\n");
    printf("             EMPLOYEE MANAGEMENT SYSTEM             \n");
    printf("====================================================\n");
}
void displayMenu(void) {
    header();
    printf("  1. Add Employee\n");
    printf("  2. View All Employees\n");
    printf("  3. Calculate Salary\n");
    printf("  4. Search Employee\n");
    printf("  5. Exit\n");
    printf("----------------------------------------------------\n");
}
void addEmployee(void) {
    if (totalemp >= MAX_EMPLOYEES) {
        printf("Employee storage is full!\n");
        return;
    }
    initEmployee(&employees[totalemp]);
    totalemp++;
     printf("\nEmployee added successfully!\n");
}
void viewEmployees(void) {
    header();
    if (totalemp == 0) {
        printf("No employees available.\n");
        return;
    }
    printf("%-10s %-20s %12s %8s\n",
           "ID", "NAME", "SALARY", "DAYS");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < totalemp; i++) {
        printf("%-10s %-20.20s %12.2f %8d\n",
               employees[i].id,
               employees[i].name,
               employees[i].salary,
               employees[i].workingdays);
    }
    printf("----------------------------------------------------\n");
    printf("Total employees: %d\n", totalemp);
}
int findEmployee(const char *id) {
    for (int i = 0; i < totalemp; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}
void calculateSalary(void) {
    char id[100];
    if (totalemp == 0) {
        printf("No employees available.\n");
        return;
    }
    printf("Enter employee ID: ");
    if (fgets(id, sizeof(id), stdin) == NULL) {
        return;
    }
    id[strcspn(id, "\n")] = '\0';
    int index = findEmployee(id);
    if (index == -1) {
        printf("Employee not found.\n");
        return;
    }
    salaryDay(&employees[index]);
}
void searchEmployee(void) {
    char id[100];
    if (totalemp == 0) {
        printf("No employees available.\n");
        return;
    }
     printf("Enter employee ID: ");

    if (fgets(id, sizeof(id), stdin) == NULL) {
        return;
    }

    id[strcspn(id, "\n")] = '\0';

    int index = findEmployee(id);

    if (index == -1) {
        printf("Employee not found.\n");
        return;
    }

    struct Employee *E = &employees[index];

    header();
    printf("Name          : %s\n", E->name);
    printf("ID            : %s\n", E->id);
    printf("Base Salary   : %.2f\n", E->salary);
    printf("Working Days  : %d\n", E->workingdays);
    printf("Paid Leaves   : %d\n", E->paidleaves);
    printf("Sick Leaves   : %d\n", E->sickleaves);
    printf("Bonus         : %.2f%%\n", E->bonus);
}

int main(void) {
    while (1) {
        displayMenu();

        printf("Select option (1-5): ");

        char input[30];

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        int choice;

        if (sscanf(input, "%d", &choice) != 1) {
            printf("Please enter a valid menu number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                viewEmployees();
                break;
            case 3:
                calculateSalary();
                break;
            case 4:
                searchEmployee();
                break;
            case 5:
                printf("Exiting Employee Management System.\n");
                return 0;
            default:
                printf("Choose an option from 1 to 5.\n");
        }

        printf("\nPress ENTER to continue...");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    return 0;
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
