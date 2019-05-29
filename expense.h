//
// Created by Victor on 5/25/2019.
//

#ifndef UNTITLED_EXPENSE_H
#define UNTITLED_EXPENSE_H

enum ExpenseType {
    car, electricity, water, heating, phone, food, shopping
};

char *EXPENSE_TYPE_STRING[7] = {"car", "electricity", "water", "heating", "phone", "food", "shopping"};

struct Date {
    int day;
    int month;
    int year;
};

struct ExpenseEntry {
    enum ExpenseType type;
    struct Date date;
    double amount;
};

struct Node {
    struct ExpenseEntry *value;
    struct Node *next;
};

struct LinkedList {
    struct Node *root;
    struct Node *head;
};

// Returns chosen option from menu
int getInputFromMenu();

// adds new entry of type ExpenseEntry to the given list
void addNewExpense(struct LinkedList *expenses);

// returns the biggest expense entry from the given list for month chosen by the user
struct ExpenseEntry *getMaxExpenseForMonth(struct LinkedList *expenses);

// lists the sum of expenses for the given list by type
void listExpensesForMonth(struct LinkedList *expenses);

// Helper functions:
// Adds the given entry to the given list
void add(struct LinkedList *expenses, struct ExpenseEntry *newEntry);

// Checks if the given day month and year are valid
int isValidDate(int day, int month, int year);

// gets month from user input
int getMonth();

// gets month from user input
int getYear();

// releases the taken resources
void cleanUp(struct LinkedList *expenses);

#endif //UNTITLED_EXPENSE_H
