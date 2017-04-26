#include <stdio.h>
#include <stdlib.h>

#define SLOTS 13
#define hash(x) ((x) % 13)
#define DEBUG(x) do {\
    printf(x);\
    fflush(stdout);\
} while (0)

typedef struct {
    int slots[SLOTS];
} TTable, *Table;


void initTable (Table* T) {
    (*T) = (Table) calloc(1, sizeof(TTable));
}

void destroyTable (Table* T) {
    free(*T);
    *T = NULL;
}

int searchTable (Table T, int value) {
    int key = hash(value), p, cnt = 0;
    for (p = key; T->slots[p] && cnt < SLOTS; p = (p + 1) % SLOTS, cnt++)
        if (T->slots[p] == value) return p;
    return -1;
}

void insertValue (Table T, int value) {
    int key = hash(value), p;
    for (p = key; T->slots[p] > 0; p = (p + 1) % SLOTS)
        if (T->slots[p] == value) return;
    if (T->slots[p] > 0) return;
    T->slots[p] = value;
}

void deleteValue (Table T, int value) {
    int key = hash(value), p;
    for (p = key; T->slots[p]; p = (p + 1) % SLOTS)
        if (T->slots[p] == value) {
            T->slots[p] = -1;
            return;
        }
}

void traverseTable (Table T) {
    int i;

    for (i = 0; i < SLOTS; i++) {
        printf("%d:\t", i);
        if (T->slots[i] > 0) printf("%d\n", T->slots[i]);
        else printf("^\n");
    }
}

void searchLength (Table T) {
    int sum = 0, i, cnt = 0, p;
    for (i = 0; i < SLOTS; i++)
        if (T->slots[i] > 0) {
            p = i - hash(T->slots[i]);
            while (p < 0) p += SLOTS;
            while (p >= SLOTS) p -= SLOTS;
            sum += 1 + p;
            cnt++;
        }
    printf("Success: %g\n", sum * 1.0 / cnt);
}

void digest (void) {
    while (getchar() != 10);
}

int choice (const char* menu, int num) {
    int result = -1;

    do {
        printf("%s\nMake a choice (0 ~ %d) ", menu, num - 1);
        scanf("%d", &result);
        printf("\n");
        digest();
    } while (result < 0 || result >= num);

    return result;
}

const char* menu =
    "======= Hash Table Menu =======\n"
    "0) Exit\n"
    "1) Insert\n"
    "2) Delete\n"
    "3) Search\n"
    "4) Traverse\n"
    "5) Search length\n";

typedef void (*Operation)();

Table table;

void opExit () {
    exit(0);
}

void opInsert () {
    int value = -1;
    do {
        printf("Enter an positive integer (-1 to pass) ");
        scanf("%d", &value);
        if (value == -1) break;
        insertValue(table, value);
    } while (1);
}

void opDelete () {
    int value = -1;
    do {
        printf("Enter an positive integer (-1 to pass) ");
        scanf("%d", &value);
        if (value == -1) break;
        deleteValue(table, value);
    } while (1);
}

void opSearch () {
    int value;
    printf("Input value to be searched: ");
    scanf("%d", &value);
    printf("Result: %d.", searchTable(table, value));
}

void opTraverse () {
    traverseTable(table);
}

void opSearchLength () {
    searchLength(table);
}

Operation operations[] = { opExit, opInsert, opDelete, opSearch, opTraverse, opSearchLength };
const unsigned int nOperations = sizeof (operations) / sizeof (Operation);

int main () {
    initTable(&table);
    while (1) {
        operations[choice(menu, nOperations)]();
        printf("\n");
    }
    destroyTable(&table);
    return 0;
}
