#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "expense.h"


int main() {
    struct LinkedList *expenses = (struct LinkedList *) malloc(sizeof(struct LinkedList));
    expenses->root = NULL;
    expenses->head = NULL;
    int option;
    do {
        option = getInputFromMenu();
        switch (option) {
            case 1:
                addNewExpense(expenses);
                break;
            case 2:
                listExpensesForMonth(expenses);
                break;
            case 3: {
                struct ExpenseEntry *entry = getMaxExpenseForMonth(expenses);
                if (entry != NULL) {
                    printf("Max expenses for %d %d are spent for the following entry:\n"
                           "%s: %.2f %d.%d.%d\n", entry->date.month, entry->date.year, EXPENSE_TYPE_STRING[entry->type], entry->amount,
                           entry->date.day, entry->date.month, entry->date.year);
                }
            }
        }
    } while (option != 4);

    printf("Exiting...");
    cleanUp(expenses);
    return 0;
}
