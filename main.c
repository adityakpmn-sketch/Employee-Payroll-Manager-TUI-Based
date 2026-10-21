
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
    char name[100];
    char id[10];
    float salary;
    float bonus;
    int workingdays;
    int paidleaves;
    int sickleaves;
};

void header(void) {
    printf("\n");
    printf("===============================================================\n");
    printf("                 EMPLOYEE MANAGEMENT SYSTEM                   \n");
    printf("===============================================================\n");
}

/* Display main menu */
void displayMenu(void) {
    header();
    printf("  1. Add Employee\n");
    printf("  2. View All Employees\n");
    printf("  3. Calculate Salary\n");
    printf("  4. Search Employee\n");
    printf("  5. Exit\n");
    printf("---------------------------------------------------------------\n");
}

/* Add an employee */
void addEmployee(void) {
    if (totalemp >= MAX_EMPLOYEES) {
        printf("Employee list is full!\n");
        return;
    }

    struct Employee E = {0};

    header();
    printf("                         ADD EMPLOYEE\n");

    do {
        readLine("Enter employee name: ", E.name, sizeof(E.name));

        if (strlen(E.name) == 0) {
            printf("Name cannot be empty.\n");
        }
    } while (strlen(E.name) == 0);

    while (1) {
        readLine("Enter employee ID (9 characters): ",
                 E.id, sizeof(E.id));

        if (strlen(E.id) != 9) {
            printf("ID must contain exactly 9 characters.\n");
            continue;
        }

        if (findEmployee(E.id) != -1) {
            printf("This ID already exists!\n");
            continue;
        }

        break;
    }

    char line[100];
    char *end;
    float salary;

    while (1) {
        readLine("Enter monthly base salary: ", line, sizeof(line));

        errno = 0;
        salary = strtof(line, &end);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (line[0] != '\0' && *end == '\0' &&
            errno == 0 && salary > 0.0f) {
            break;
        }

        printf("Enter a valid positive salary.\n");
    }

    E.salary = salary;
    E.bonus = 0;
    E.finalSalary = 0;
    E.workingdays = 0;
    E.totalWorkingDays = 0;
    E.paidleaves = 0;
    E.sickleaves = 0;

    employees[totalemp++] = E;

    printf("\nEmployee added successfully!\n");
}

/* Display all employees in a table */
void viewEmployees(void) {
    header();

    if (totalemp == 0) {
        printf("No employees found. Add an employee first.\n");
        return;
    }

    printf("%-9s %-20s %12s %7s %9s %12s\n",
           "ID", "NAME", "BASE SALARY", "DAYS",
           "BONUS %", "FINAL SALARY");

    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < totalemp; i++) {
        printf("%-9s %-20.20s %12.2f %7d %9.2f %12.2f\n",
               employees[i].id,
               employees[i].name,
               employees[i].salary,
               employees[i].workingdays,
               employees[i].bonus,
               employees[i].finalSalary);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Total employees: %d\n", totalemp);
}

/* Calculate salary */
void calculateSalary(void) {
    char id[10];

    header();

    if (totalemp == 0) {
        printf("No employees available.\n");
        return;
    }

    readLine("Enter employee ID: ", id, sizeof(id));

    if (strlen(id) != 9) {
        printf("Invalid ID format.\n");
        return;
    }

    int index = findEmployee(id);

    if (index == -1) {
        printf("Employee not found!\n");
        return;
    }

    struct Employee *E = &employees[index];

    E->totalWorkingDays =
        readInt("Enter total working days (1-31): ", 1, 31);

    E->workingdays =
        readInt("Enter days actually worked: ", 0,
                E->totalWorkingDays);

    E->paidleaves =
        readInt("Enter paid leave days: ", 0,
                E->totalWorkingDays);

    E->sickleaves =
        readInt("Enter sick leave days: ", 0,
                E->totalWorkingDays);

    if (E->workingdays + E->paidleaves + E->sickleaves >
        E->totalWorkingDays) {
        printf("Invalid attendance: days and leaves exceed total days.\n");
        return;
    }

    float payableDays =
        (float)(E->workingdays + E->paidleaves);

    float earnedSalary =
        E->salary * payableDays / E->totalWorkingDays;

    char line[100];
    char *end;
    float bonusPercent;

    while (1) {
        readLine("Enter bonus percentage (0-100): ",
                 line, sizeof(line));

        errno = 0;
        bonusPercent = strtof(line, &end);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (line[0] != '\0' && *end == '\0' &&
            errno == 0 && bonusPercent >= 0 &&
            bonusPercent <= 100) {
            break;
        }

        printf("Enter a valid bonus percentage from 0 to 100.\n");
    }

    E->bonus = bonusPercent;
    float bonusAmount = earnedSalary * E->bonus / 100.0f;
    E->finalSalary = earnedSalary + bonusAmount;

    printf("\n=================== SALARY SLIP ===================\n");
    printf("Employee Name       : %s\n", E->name);
    printf("Employee ID         : %s\n", E->id);
    printf("Base Salary         : %.2f\n", E->salary);
    printf("Days Worked         : %d\n", E->workingdays);
    printf("Paid Leaves         : %d\n", E->paidleaves);
    printf("Sick Leaves         : %d\n", E->sickleaves);
    printf("Earned Salary       : %.2f\n", earnedSalary);
    printf("Bonus Percentage    : %.2f%%\n", E->bonus);
    printf("Bonus Amount        : %.2f\n", bonusAmount);
    printf("----------------------------------------------------\n");
    printf("FINAL SALARY        : %.2f\n", E->finalSalary);
    printf("====================================================\n");
}

/* Search for an employee */
void searchEmployee(void) {
    char id[10];

    header();

    if (totalemp == 0) {
        printf("No employees available.\n");
        return;
    }

    readLine("Enter employee ID: ", id, sizeof(id));

    if (strlen(id) != 9) {
        printf("Invalid ID format.\n");
        return;
    }

    int index = findEmployee(id);

    if (index == -1) {
        printf("Employee not found!\n");
        return;
    }

    struct Employee E = employees[index];

    printf("\nEmployee Details\n");
    printf("----------------------------------------------------\n");
    printf("Name          : %s\n", E.name);
    printf("ID            : %s\n", E.id);
    printf("Base Salary   : %.2f\n", E.salary);
    printf("Days Worked   : %d\n", E.workingdays);
    printf("Bonus         : %.2f%%\n", E.bonus);
    printf("Final Salary  : %.2f\n", E.finalSalary);
}

/* Main program */
int main(void) {
    while (1) {
        displayMenu();

        int choice = readInt("Select an option (1-5): ", 1, 5);

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
                printf("\nThank you for using the system!\n");
                return 0;
        }

        char temp[8];
        readLine("\nPress ENTER to return to the menu...", temp,
                 sizeof(temp));
    }
}
