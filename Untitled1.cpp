#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

void searchText(const string& filename, const string& pattern) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
        return;
    }

    regex reg(pattern);
    string line;
    while (getline(file, line)) {
        if (regex_search(line, reg)) {
            cout << "Matched line: " << line << endl;  // Output the matched line
        }
    }
    file.close();
}

int main() {
    string filename = "sample.txt";  // Change this to your file's name or full path
    string pattern = R"(^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$)";  // Example pattern (email matching)
    searchText(filename, pattern);
    return 0;
}
