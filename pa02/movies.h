#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>
#include <map>

struct Movie {
    std::string name;
    double rating;
};

// comparator for sorting movies: by rating desc, then name asc
bool movieComparator(const Movie& a, const Movie& b);

#endif
