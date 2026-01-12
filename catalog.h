#ifndef CATALOG_H
#define CATALOG_H

#include "book.h"
#include <stddef.h>

typedef struct {
    Book* book;
    size_t size;
} Catalog;

void initCatalog(Catalog*);
void freeCatalog(Catalog*);
void printCatalog(const Catalog*);
void addBook(Catalog*);
void deleteBook(Catalog*);
void saveToFile(const Catalog*, const char*);
void loadFromFile(Catalog*, const char*);
void sortCatalog(Catalog*, FieldSort);
void printMenu();
#endif
