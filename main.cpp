#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

/* ---------- STRUCTURES ---------- */
struct Employee {
    int id;
    char name[30];
    int salary;
};

struct Payroll {
    int empID;
    int allowance;
    int deduction;
    int netSalary;
};

/* ---------- GLOBAL VARIABLES ---------- */
struct Employee emp[MAX];
struct Payroll pay[MAX];

int empCount = 0;
int payCount = 0;

/* ---------- FUNCTION PROTOTYPES ---------- */
void employeeMenu();
void payrollMenu();

void addEmployee();
void viewEmployees();
void searchEmployee();
void updateEmployee();
void deleteEmployee();

void addPayroll();
void viewPayroll();
void updatePayroll();
void deletePayroll();

char getChoice();
void clearScreen() { system("cls"); }

/* ---------- MAIN ---------- */
int main() {
    int choice;
    do {
        clearScreen();
        printf("\n===== OFFICE MANAGEMENT SYSTEM =====\n");
        printf("1. Employee Management\n");
        printf("2. Payroll Management\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: employeeMenu(); break;
            case 2: payrollMenu(); break;
            case 0: printf("\nExiting Program...\n"); break;
            default: 
                printf("Invalid Choice!\n");
                system("pause");
        }
    } while(choice != 0);

    return 0;
}

/* ---------- COMMON ---------- */
char getChoice() {
    char ch;
    scanf(" %c", &ch);
    getchar();
    return ch;
}

/* ---------- EMPLOYEE MENU ---------- */
void employeeMenu() {
    int ch;
    do {
        clearScreen();
        printf("\n--- Employee Menu ---\n");
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        getchar();

        switch(ch) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: deleteEmployee(); break;
        }
    } while(ch != 0);
}

/* ---------- EMPLOYEE FUNCTIONS ---------- */
void addEmployee() {
    char choice;
    do {
        clearScreen();
        if(empCount >= MAX) {
            printf("Employee limit reached!\n");
            system("pause");
            return;
        }

        printf("\n--- Add Employee ---\n");
        printf("Enter ID: ");
        scanf("%d", &emp[empCount].id);
        getchar();

        printf("Enter Name: ");
        fgets(emp[empCount].name, sizeof(emp[empCount].name), stdin);
        emp[empCount].name[strcspn(emp[empCount].name, "\n")] = 0;

        printf("Enter Salary: ");
        scanf("%d", &emp[empCount].salary);
        getchar();

        empCount++;
        printf("\nEmployee Added Successfully!\n");

        printf("Add more? (y/n): ");
        choice = getChoice();

    } while(choice == 'y' || choice == 'Y');
}

void viewEmployees() {
    clearScreen();
    int i;
    
    printf("\n--- View Employees ---\n");
    if(empCount == 0) {
        printf("No employee record found!\n");
        system("pause");
        return;
    }

    for(i = 0; i < empCount; i++) {
    	printf("\nEmployee %d", i + 1);
        printf("\nEmployee ID	: %d", emp[i].id);
        printf("\nEmployee Name	: %s", emp[i].name);
        printf("\nSalary		: %d\n", emp[i].salary);
    }
    system("pause");
}

void searchEmployee() {
    clearScreen();
    int id, i, found = 0;
    
    printf("\n--- Search Employee ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &id);

    for(i = 0; i < empCount; i++) {
        if(emp[i].id == id) {
            printf("\nEmployee ID	: %d", emp[i].id);
            printf("\nEmployee Name	: %s", emp[i].name);
            printf("\nSalary		: %d\n", emp[i].salary);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Employee not found!\n");

    system("pause");
}

void updateEmployee() {
    clearScreen();
    int id, i, option;
    
    printf("\n--- Update Employee ---\n");
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);
    getchar();

    for(i = 0; i < empCount; i++) {
        if(emp[i].id == id) {
        	printf("\nEmployee Details:\n");
            printf("Employee ID   : %d\n", emp[i].id);
            printf("Employee Name : %s\n", emp[i].name);
            printf("Salary        : %d\n", emp[i].salary);
            printf("\n1. Update Name\n2. Update Salary\n3. Update All\n");
            printf("Enter choice: ");
            scanf("%d", &option);
            getchar();

            if(option == 1 || option == 3) {
                printf("Enter New Name: ");
                fgets(emp[i].name, sizeof(emp[i].name), stdin);
                emp[i].name[strcspn(emp[i].name, "\n")] = 0;
            }
            if(option == 2 || option == 3) {
                printf("Enter New Salary: ");
                scanf("%d", &emp[i].salary);
                getchar();
            }

            printf("\nEmployee Updated!\n");
            system("pause");
            return;
        }
    }
    printf("Employee not found!\n");
    system("pause");
}

void deleteEmployee() {
    clearScreen();
    int id, i, j;
    char choice;

    printf("\n--- Delete Employee ---\n");
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    getchar();

    for(i = 0; i < empCount; i++) {
        if(emp[i].id == id) {

            printf("\nEmployee Details:\n");
            printf("Employee ID   : %d\n", emp[i].id);
            printf("Employee Name : %s\n", emp[i].name);
            printf("Salary        : %d\n", emp[i].salary);

            printf("\nDelete this employee record? (y/n): ");
            choice = getChoice();

            if(choice == 'y' || choice == 'Y') {

                /* delete employee */
                for(j = i; j < empCount - 1; j++) {
                    emp[j] = emp[j + 1];
                }
                empCount--;

                /* delete related payroll also (important) */
                for(j = 0; j < payCount; j++) {
                    if(pay[j].empID == id) {
                        int k;
                        for(k = j; k < payCount - 1; k++) {
                            pay[k] = pay[k + 1];
                        }
                        payCount--;
                        break;
                    }
                }

                printf("\nEmployee record deleted successfully!\n");
            }
            else {
                printf("\nEmployee record not deleted!\n");
            }

            system("pause");
            return;
        }
    }

    printf("\nEmployee record not found!\n");
    system("pause");
}


/* ---------- PAYROLL MENU ---------- */
void payrollMenu() {
    int ch;
    do {
        clearScreen();
        printf("\n--- Payroll Menu ---\n");
        printf("1. Add Payroll\n");
        printf("2. View Payroll\n");
        printf("3. Update Payroll\n");
        printf("4. Delete Payroll\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        getchar();

        switch(ch) {
            case 1: addPayroll(); break;
            case 2: viewPayroll(); break;
            case 3: updatePayroll(); break;
            case 4: deletePayroll(); break;
        }
    } while(ch != 0);
}

/* ---------- PAYROLL FUNCTIONS ---------- */
void addPayroll() {
    clearScreen();
    int id, i;
    if(payCount >= MAX) {
        printf("Payroll limit reached!\n");
        system("pause");
        return;
    }
	
	printf("\n--- Add Payroll ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &id);

    for(i = 0; i < empCount; i++) {
        if(emp[i].id == id) {
            pay[payCount].empID = id;

			printf("\nEmployee Details:\n");
            printf("Employee ID   : %d\n", emp[i].id);
            printf("Employee Name : %s\n", emp[i].name);
            printf("Salary        : %d\n", emp[i].salary);
            printf("Enter Allowance: ");
            scanf("%d", &pay[payCount].allowance);

            printf("Enter Deduction: ");
            scanf("%d", &pay[payCount].deduction);

            pay[payCount].netSalary =
                emp[i].salary + pay[payCount].allowance - pay[payCount].deduction;

            printf("Net Salary: %d\n", pay[payCount].netSalary);
            payCount++;
            system("pause");
            return;
        }
    }
    printf("Employee not found!\n");
    system("pause");
}

void viewPayroll() {
    clearScreen();
    int i, j;
    
    printf("\n--- View Payroll ---\n");
    if(payCount == 0) {
        printf("No payroll record found!\n");
        system("pause");
        return;
    }

    for(i = 0; i < payCount; i++) {
        for(j = 0; j < empCount; j++)
            if(emp[j].id == pay[i].empID)
                break;

        printf("\nEmployee ID	: %d", pay[i].empID);
        printf("\nEmployee Name	: %s", emp[j].name);
        printf("\nNet Salary	: %d\n", pay[i].netSalary);
    }
    system("pause");
}

void updatePayroll() {
    clearScreen();
    int id, i, j;
    
    printf("\n--- Update Payroll ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &id);
	
	
    for(i = 0; i < payCount; i++) {
        if(pay[i].empID == id) {
            for(j = 0; j < empCount; j++)
                if(emp[j].id == id)
                    break;
			printf("\nEmployee Details:\n");
    		printf("Employee ID   : %d\n", pay[i].empID);
    		printf("Employee Name : %s\n", emp[i].name);
			printf("Net Salary    : %d\n", pay[i].netSalary);
            printf("Enter New Allowance: ");
            scanf("%d", &pay[i].allowance);

            printf("Enter New Deduction: ");
            scanf("%d", &pay[i].deduction);

            pay[i].netSalary =
                emp[j].salary + pay[i].allowance - pay[i].deduction;

            printf("Payroll Updated!\n");
            system("pause");
            return;
        }
    }
    printf("Payroll not found!\n");
    system("pause");
}

void deletePayroll() {
    clearScreen();
    int id, i, j;
    char choice;

    printf("\n--- Delete Payroll ---\n");
    printf("Enter Employee ID to delete payroll: ");
    scanf("%d", &id);
    getchar();

    for(i = 0; i < payCount; i++) {
        if(pay[i].empID == id) {

            printf("\nPayroll Details:\n");
            printf("Employee ID	: %d\n", pay[i].empID);

            for(j = 0; j < empCount; j++)
                if(emp[j].id == id)
                    break;

            printf("Employee Name	: %s\n", emp[j].name);
            printf("Allowance	: %d\n", pay[i].allowance);
            printf("Deduction	: %d\n", pay[i].deduction);
            printf("Net Salary	: %d\n", pay[i].netSalary);

            printf("\nDelete this payroll record? (y/n): ");
            choice = getChoice();

            if(choice == 'y' || choice == 'Y') {

                for(j = i; j < payCount - 1; j++) {
                    pay[j] = pay[j + 1];
                }
                payCount--;

                printf("\nPayroll record deleted successfully!\n");
            }
            else {
                printf("\nPayroll record not deleted!\n");
            }

            system("pause");
            return;
        }
    }

    printf("\nPayroll record not found!\n");
    system("pause");
}


