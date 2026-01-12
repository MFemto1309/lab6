#include "catalog.h"
#include <stdio.h>

int main(void) {
    Catalog catalog;
    initCatalog(&catalog);

    int choice;
    char filename[100];

    while (1) {
        printMenu();
        printf("Enter: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printCatalog(&catalog);
                break;

            case 2:
                addBook(&catalog);
                break;

            case 3:
                deleteBook(&catalog);
                break;

            case 4:
                printf("File's name: ");
                scanf(" %99s", filename);
                saveToFile(&catalog, filename);
                break;

            case 5:
                printf("File's name: ");
                scanf(" %99s", filename);
                loadFromFile(&catalog, filename);
                break;

            case 6: {
                int f;
                printf("Sort by:\n");
                printf("1 - author\n2 - title\n3 - category\n4 - year\n5 - price\n");
                scanf("%d", &f);
                sortCatalog(&catalog, (FieldSort)(f - 1));
                break;
            }

            case 0:
                freeCatalog(&catalog);
                return 0;

            default:
                printf("Wrong choice\n");
        }
    }
}
