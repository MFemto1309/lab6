#include "book.h"
#include <string.h>

int cmpByAuthor(const void* a, const void* b) {
    return strcmp(((Book*)a)->author, ((Book*)b)->author);
}

int cmpByTitle(const void* a, const void* b) {
    return strcmp(((Book*)a)->title, ((Book*)b)->title);
}

int cmpByCategory(const void* a, const void* b) {
    return strcmp(((Book*)a)->category, ((Book*)b)->category);
}

int cmpByYear(const void* a, const void* b) {
    return ((Book*)a)->year - ((Book*)b)->year;
}

int cmpByPrice(const void* a, const void* b) {
    double diff = ((Book*)a)->price - ((Book*)b)->price;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}
