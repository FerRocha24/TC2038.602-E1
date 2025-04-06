#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>

using namespace std;

inline string toLower(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

#endif
