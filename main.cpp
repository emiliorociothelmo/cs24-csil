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

string cleanName(const string& name) {
    string result;
    for (char c : name) {
        if (c != ':' && c != ',' && c != '!' && c != '.' && c != '-' && c != '&' && c != '(' && c != ')') {
            result += c;
        }
    }
    // collapse multiple spaces
    string final;
    bool lastSpace = false;
    for (char c : result) {
        if (c == ' ') {
            if (!lastSpace) final += c;
            lastSpace = true;
        } else {
            final += c;
            lastSpace = false;
        }
    }
    // trim trailing space
    while (!final.empty() && final.back() == ' ') final.pop_back();
    return final;
}

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

    map<string, double> movieMap;
    string line, movieName;
    double movieRating;

    while (getline(movieFile, line) && parseLine(line, movieName, movieRating)){
        string clean = movieName;
        movieMap[clean] = movieRating;
    }
    movieFile.close();

    if (argc == 2){
        for (auto& p : movieMap){
            cout << p.first << ", " << fixed << setprecision(1) << p.second << "\n";
        }
        return 0;
    }

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

    vector<pair<string, Movie>> bestMovies;

    for (const string& prefix : prefixes){
        vector<Movie> matches;
        auto it = movieMap.lower_bound(prefix);
        while (it != movieMap.end()){
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
            sort(matches.begin(), matches.end(), movieComparator);
            for (auto& m : matches){
                cout << m.name << ", " << fixed << setprecision(1) << m.rating << "\n";
            }
            cout << "\n";
            bestMovies.push_back({prefix, matches[0]});
        }
    }

    for (auto& p : bestMovies){
        if (p.second.rating >= 0){
            cout << "Best movie with prefix " << p.first << " is: "
                 << p.second.name << " with rating "
                 << fixed << setprecision(1) << p.second.rating << "\n";
        }
    }

    return 0;
}

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
