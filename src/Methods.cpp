#include "Methods.h"

using namespace std;

/* 1. Alphanumeric/Space/Lowercase:
 * https://cplusplus.com/reference/cctype/
 */

void formatString (string &format) {
    stack<int> remove;
    int index = 0;
    for (char &currChar : format) {
        if (isalnum(currChar) || isspace(currChar))  // 1
            currChar = tolower(currChar);               // 1
        else
            remove.push(index);
        index++;
    }

    while (!remove.empty()){
        format.erase(remove.top());
        remove.pop();
    }

    if (format.substr(0,4) == "the ")
        format = format.substr(4, format.size() - 4);
}