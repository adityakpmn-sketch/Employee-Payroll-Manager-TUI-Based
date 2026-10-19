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

struct Employee initemployee() {
  struct Employee E;
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
  while (ch != '\n' && pos < 9) {
    scanf("%c", &ch);
    E.id[pos] = ch;
    pos++;
  }
  if (pos != 9) {
    printf("Please Enter a ValidID!\n");
    goto ID;
  }
  printf("Enter Inital salary : ");
  scanf("%f", &E.salary);
  E.sickleaves = 0;
  E.paidleaves = 0;
  E.workingdays = 0;
  return E;
}

int main() {
  system("clear");
  // Deduction Logic
  struct Employee E[100];
  int Running = 1;
  int totalemp = 0;
  char buffer;
  while (Running) {
    printf("Choose An Option :\n 0.Quit -> 'q'\n 1. Add a User -> 'n'\n 2. View Employees -> 'v' : \n");
    char option;
    int temp;
    scanf("%c%c", &option, &buffer);
    switch (option) {
      case 'v':
        temp=totalemp-1;
        if(totalemp==0){
          printf("There are no employees stored.\n");
          break;
        }
        while(temp>=0){
            printf("Employee Name: %s",E[temp].name);
            printf("Employee ID: %s\n",E[temp].id);
            printf("employee Salary: %.2f\n",E[temp].salary);
            printf("-----------------------------------------\n");
            temp--;
            }
        break;
    case 'q':
      Running = 0;
      break;
    case 'n':
      E[totalemp]=initemployee();
      totalemp++;
      break;
    default:
      printf("Please Enter Valid Option!\n");
    }
  }
}
