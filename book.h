#ifndef BOOK_H
#define BOOK_H

#define MAX_AUTHOR_LEN   100
#define MAX_TITLE_LEN    100
#define MAX_CATEGORY_LEN 50

typedef struct 
{
    char author[MAX_AUTHOR_LEN];
    char title[MAX_TITLE_LEN];
    char category[MAX_CATEGORY_LEN];
    int year;
    double price;
} Book;

typedef enum {
    AUTHOR_SORT,
    TITLE_SORT,
    CATEGORY_SORT,
    YEAR_SORT,
    PRICE_SORT
} FieldSort;

int cmpByAuthor(const void*, const void*);

int cmpByTitle(const void*, const void*);

int cmpByCategory(const void*, const void*);

int cmpByYear(const void*, const void*);

int cmpByPrice(const void*, const void*);

#endif