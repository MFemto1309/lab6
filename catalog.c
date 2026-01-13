#include "catalog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initCatalog(Catalog* catalog) {
    catalog->book = NULL;
    catalog->size = 0;
}

void freeCatalog(Catalog* catalog) {
    free(catalog->book);
    catalog->book = NULL;
    catalog->size = 0;
}

void printCatalog(const Catalog* catalog) {
    if (catalog->size == 0) {
        printf("Catalog is empty\n");
        return;
    }

    for (size_t i = 0; i < catalog->size; i++) {
        printf("%zu) %s | %s | %s | %d | %.2f\n",
               i + 1,
               catalog->book[i].author,
               catalog->book[i].title,
               catalog->book[i].category,
               catalog->book[i].year,
               catalog->book[i].price);
    }
}

void addBook(Catalog* catalog) {
    Book book;

    printf("Author: ");
    scanf(" %99[^\n]", book.author);

    printf("Title: ");
    scanf(" %99[^\n]", book.title);

    printf("Category: ");
    scanf(" %49[^\n]", book.category);

    printf("Year: ");
    scanf("%d", &book.year);

    printf("Price: ");
    scanf("%lf", &book.price);

    Book* tmp = realloc(catalog->book, (catalog->size + 1) * sizeof(Book));
    if (!tmp) {
        printf("Memory error\n");
        return;
    }

    catalog->book = tmp;
    catalog->book[catalog->size] = book;
    catalog->size++;
}

void deleteBook(Catalog* catalog) {
    if (catalog->size == 0) {
        printf("Catalog is empty\n");
        return;
    }

    char title[MAX_TITLE_LEN];
    printf("Enter book title to delete: ");
    scanf(" %99[^\n]", title);

    size_t index = catalog->size;

    for (size_t i = 0; i < catalog->size; i++) {
        if (strcmp(catalog->book[i].title, title) == 0) {
            index = i;
            break;
        }
    }

    if (index == catalog->size) {
        printf("Book not found\n");
        return;
    }

    for (size_t i = index; i < catalog->size - 1; i++) {
        catalog->book[i] = catalog->book[i + 1];
    }

    catalog->size--;
    catalog->book = realloc(catalog->book, catalog->size * sizeof(Book));

    printf("Book deleted successfully\n");
}


void saveToFile(const Catalog* catalog, const char* filename) {
    if (catalog->size == 0) {
        printf("Catalog is empty, nothing to save.\n");
        return;
    }

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "../%s", filename);

    FILE* f = fopen(filepath, "w");
    if (!f) {
        perror("Error creating file in parent directory");
        return;
    }

    for (size_t i = 0; i < catalog->size; i++) {
        fprintf(f, "%s;%s;%s;%d;%.6f\n",
                catalog->book[i].author,
                catalog->book[i].title,
                catalog->book[i].category,
                catalog->book[i].year,
                catalog->book[i].price);
    }

    fclose(f);
    printf("File '%s' saved successfully in parent directory. %zu books written.\n", filename, catalog->size);
}

void loadFromFile(Catalog* catalog, const char* filename) {
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "../%s", filename);

    FILE* f = fopen(filepath, "r");
    if (!f) {
        perror("Error opening file in parent directory");
        return;
    }

    free(catalog->book);
    catalog->book = NULL;
    catalog->size = 0;

    Book temp;
    while (fscanf(f, " %99[^;]; %99[^;]; %49[^;]; %d; %lf\n",
                  temp.author, temp.title, temp.category,
                  &temp.year, &temp.price) == 5) {
        catalog->size++;
        catalog->book = realloc(catalog->book, catalog->size * sizeof(Book));
        if (!catalog->book) {
            printf("Memory allocation error\n");
            fclose(f);
            exit(1);
        }
        catalog->book[catalog->size - 1] = temp;
    }

    fclose(f);
    printf("File '%s' loaded successfully from parent directory. %zu books loaded.\n", filename, catalog->size);
}

void sort(
    void* base,
    size_t len,
    size_t size,
    void (*swap)(void*, void*),
    int (*cmp)(const void*, const void*)
) {
    if (!base || len < 2 || !swap || !cmp) return;

    char* arr = (char*)base;

    for (size_t i = 0; i < len - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < len; ++j) {
            void* elem_j = arr + j * size;
            void* elem_min = arr + min_idx * size;
            if (cmp(elem_j, elem_min) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            void* elem_i = arr + i * size;
            void* elem_min = arr + min_idx * size;
            swap(elem_i, elem_min);
        }
    }
}

void swapBook(void* a, void* b) {
    Book tmp = *(Book*)a;
    *(Book*)a = *(Book*)b;
    *(Book*)b = tmp;
}

void sortCatalog(Catalog* catalog, FieldSort field) {
    if (catalog->size < 2) return;

    int (*cmp)(const void*, const void*) = NULL;

    switch (field) {
        case AUTHOR_SORT:   cmp = cmpByAuthor; break;
        case TITLE_SORT:    cmp = cmpByTitle; break;
        case CATEGORY_SORT: cmp = cmpByCategory; break;
        case YEAR_SORT:     cmp = cmpByYear; break;
        case PRICE_SORT:    cmp = cmpByPrice; break;
    }

    if (cmp) {
        sort(catalog->book, catalog->size, sizeof(Book), swapBook, cmp);
    }
}

void printMenu() {
    printf("=== Catalog ===\n");
    printf("1. Show Books\n");
    printf("2. Add the book\n");
    printf("3. Delete the book\n");
    printf("4. Save to a file\n");
    printf("5. Load from the file\n");
    printf("6. Sort by:\n");
    printf("0. Exit\n");
}