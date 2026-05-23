// Winter'24
// Instructor: Diba Mirza
// Student name: Emilio Rocio Thelmo
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;
#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[0] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile(argv[1]);
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    // Use a map to store movies: name -> rating (auto-sorted alphabetically)
    map<string, double> movieMap;
    string line, movieName;
    double movieRating;

    while (getline(movieFile, line) && parseLine(line, movieName, movieRating)){
        movieMap[movieName] = movieRating;
    }
    movieFile.close();

    // Part 1: print all movies in alphabetical order
    if (argc == 2){
        for (auto& pair : movieMap){
            cout << pair.first << ", " << fixed << setprecision(1) << pair.second << "\n";
        }
        return 0;
    }

    // Part 2: prefix search
    ifstream prefixFile(argv[2]);
    if (prefixFile.fail()){
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline(prefixFile, line)){
        if (!line.empty())
            prefixes.push_back(line);
    }
    prefixFile.close();

    // For each prefix, find matching movies and track the best
    vector<pair<string, Movie>> bestMovies; // prefix -> best movie

    for (const string& prefix : prefixes){
        vector<Movie> matches;

        // map is sorted, so we can find the range that starts with prefix
        auto it = movieMap.lower_bound(prefix);
        while (it != movieMap.end()){
            // check if this movie starts with the prefix
            if (it->first.substr(0, prefix.size()) == prefix){
                matches.push_back({it->first, it->second});
                it++;
            } else {
                break;
            }
        }

        if (matches.empty()){
            cout << "No movies found with prefix " << prefix << "\n";
            bestMovies.push_back({prefix, {"", -1}});
        } else {
            // sort by rating desc, then name asc
            sort(matches.begin(), matches.end(), movieComparator);
            for (auto& m : matches){
                cout << m.name << ", " << fixed << setprecision(1) << m.rating << "\n";
            }
            bestMovies.push_back({prefix, matches[0]});
        }
    }

    // Print best movies at the end
    for (auto& p : bestMovies){
        if (p.second.rating >= 0){
            cout << "Best movie with prefix " << p.first << " is: "
                 << p.second.name << " with rating "
                 << fixed << setprecision(1) << p.second.rating << "\n";
        }
    }

    return 0;
}

/* Part 3: Time and Space Complexity Analysis
 * Time complexity: O(n log n + m * (k log k + l))
 * - n log n to build the map
 * - For each of m prefixes: O(l) for lower_bound, O(k log k) to sort k matches
 * Space complexity: O(n) for the map
 */

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
