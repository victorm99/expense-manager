//
// Created by Victor on 5/25/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "expense.h"

int getInputFromMenu() {
    int input;

    printf("Choose an option:\n");
    printf("1. Add new expense\n");
    printf("2. Check expenses for month\n");
    printf("3. Check max expense for month\n");
    printf("4. Quit\n");

    do {
        printf("\nOption: ");
        fflush(stdin);
        scanf("%d", &input);
    } while ((input < 0) || (input > 4));

    printf("\n");
    return input;
}

void addNewExpense(struct LinkedList *expenses) {
    // 'electricity' is the longest valid possible type
    // so 11 is the maximum size
    char type[11];
    double amount;
    int year, month, day;

    printf("Add new expense entry in the following format:\n"
           "<expense type> <amount> <day>.<month>.<year>\n");
    fflush(stdin);
    scanf("%s %lf %d.%d.%d", type, &amount, &day, &month, &year);

    if (!isValidDate(day, month, year)) {
        printf("Invalid date.\n");
        return;
    }

    struct Date date = {day, month, year};
    enum ExpenseType exType;

    // Type check
    if (strcmp(type, EXPENSE_TYPE_STRING[car]) == 0) {
        exType = car;
    } else if (strcmp(type, EXPENSE_TYPE_STRING[electricity]) == 0) {
        exType = electricity;
    } else if (strcmp(type, EXPENSE_TYPE_STRING[water]) == 0) {
        exType = water;
    } else if (strcmp(type, EXPENSE_TYPE_STRING[heating]) == 0) {
        exType = heating;
    } else if (strcmp(type, EXPENSE_TYPE_STRING[phone]) == 0) {
        exType = phone;
    } else if (strcmp(type, EXPENSE_TYPE_STRING[food]) == 0) {
        exType = food;
    } else if (strcmp(type, EXPENSE_TYPE_STRING[shopping]) == 0) {
        exType = shopping;
    } else {
        printf("Invalid expense type. Valid expense types are:\n"
               "'car', 'electricity', 'water', 'heating', 'phone', 'food', 'shopping'\n");
        return;
    }

    struct ExpenseEntry *e = (struct ExpenseEntry *) malloc(sizeof(struct ExpenseEntry));
    e->type = exType;
    e->date = date;
    e->amount = amount;

    add(expenses, e);
    printf("Successfully added new entry.\n");
}

struct ExpenseEntry *getMaxExpenseForMonth(struct LinkedList *expenses) {
    if (expenses->root == NULL) {
        printf("\nNo expenses are present.\n");
        return NULL;
    }

    int month = getMonth();
    int year = getYear();

    struct Node *current = expenses->root;
    struct ExpenseEntry *maxExpense = expenses->root->value;

    while (current != NULL) {
        if (current->value->date.month != month || current->value->date.year != year) {
            current = current->next;
            continue;
        }
        if (current->value->amount > maxExpense->amount) {
            maxExpense = current->value;
        }
        current = current->next;
    }

    return maxExpense;
}

void listExpensesForMonth(struct LinkedList *expenses) {
    if (expenses->root == NULL) {
        printf("\nNo expenses are present.\n");
        return;
    }

    int month = getMonth();
    int year = getYear();

    struct Node *current = expenses->root;

    double carExp = 0, electricityExp = 0, waterExp = 0, heatingExp = 0, phoneExp = 0, foodExp = 0, shoppingExp = 0;

    while (current != NULL) {
        if (current->value->date.month != month || current->value->date.year != year) {
            current = current->next;
            continue;
        }

        switch (current->value->type) {
            case car:
                carExp += current->value->amount;
                break;
            case electricity:
                electricityExp += current->value->amount;
                break;
            case water:
                waterExp += current->value->amount;
                break;
            case heating:
                heatingExp += current->value->amount;
                break;
            case phone:
                phoneExp += current->value->amount;
                break;
            case food:
                foodExp += current->value->amount;
                break;
            case shopping:
                shoppingExp += current->value->amount;
                break;
        }
        current = current->next;
    }

    double total = carExp + electricityExp + waterExp + heatingExp + phoneExp + foodExp + shoppingExp;
    printf("Expenses for month %d:\n"
           "Car: %.2f\n"
           "Electricity bills: %.2f\n"
           "Water bills: %.2f\n"
           "Heating bills: %.2f\n"
           "Phone bills: %.2f\n"
           "Food: %.2f\n"
           "Other shopping expenses: %.2f\n"
           "----------\nTOTAL: %.2f\n\n",
           month, carExp, electricityExp, waterExp, heatingExp, phoneExp, foodExp, shoppingExp, total);
}

void add(struct LinkedList *expenses, struct ExpenseEntry *newEntry) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->value = newEntry;
    newNode->next = NULL;

    if (expenses->root == NULL) {
        expenses->root = newNode;
        expenses->head = expenses->root;
        return;
    }

    expenses->head->next = newNode;
    expenses->head = expenses->head->next;
}

int isValidDate(int day, int month, int year) {
    if (day < 1 || month < 1 || month > 12 || year < 1970 || year > 9999) {
        return 0;
    }

    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: {
            if (day > 31) {
                return 0;
            }
        }
            break;
        case 2:
            if (day > 28) {
                return 0;
            }
            break;
        default:
            if (day > 30) {
                return 0;
            }
    }
    return 1;
}

int getMonth() {
    int month;
    do {
        printf("\nMonth: ");
        fflush(stdin);
        scanf("%d", &month);
    } while ((month < 1) || (month > 12));

    printf("\n");
    return month;
}

int getYear() {
    printf("\nPlease choose an year. Valid years are in the range 1970 - 9999.\n");
    int year;
    do {
        printf("\nYear: ");
        fflush(stdin);
        scanf("%d", &year);
    } while ((year < 1970) || (year > 9999));

    printf("\n");
    return year;
}

void cleanUp(struct LinkedList *expenses) {
    struct Node *current = expenses->root;

    while (current != NULL) {
        free(current->value);
        free(current);
        current = current->next;
    }
    free(expenses);
}
