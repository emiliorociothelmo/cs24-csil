#include "movies.h"

// Sort by rating descending, then name ascending for ties
bool movieComparator(const Movie& a, const Movie& b) {
    if (a.rating != b.rating)
        return a.rating > b.rating;
    return a.name < b.name;
}
