#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<string> tokenize(const string& csvLine, char sep) {
    if (csvLine.empty()) {
        return {};
    }

    vector<string> tokens;
    size_t start = 0;

    while (true) {
        size_t end = csvLine.find(sep, start);
        if (end == string::npos) {
            tokens.push_back(csvLine.substr(start));
            break;
        } else {
            tokens.push_back(csvLine.substr(start, end - start));
            start = end + 1;
        }
    }

    return tokens;
}

bool assertEqualVectors(const vector<string>& actual, const vector<string>& expected, const string& testName) {
    if (actual.size() != expected.size()) {
        cout << "(X)" << testName << " failed: size mismatch\n";
        return false;
    }

    for (size_t i = 0; i < actual.size(); ++i) {
        if (actual[i] != expected[i]) {
            cout << "(X)" << testName << " failed: at index " << i
                 << " expected '" << expected[i] << "', got '" << actual[i] << "'\n";
            return false;
        }
    }

    cout << "(V)" << testName << " passed\n";
    return true;
}

void runTests() {
    assertEqualVectors(tokenize("A,B,C", ','),         {"A", "B", "C"},      " 1. Basic CSV");
    assertEqualVectors(tokenize("A,,C", ','),          {"A", "", "C"},       " 2. Empty middle field");
    assertEqualVectors(tokenize(",,", ','),            {"", "", ""},         " 3. Only separators");
    assertEqualVectors(tokenize("", ','),              {},                  " 4. Empty string");
    assertEqualVectors(tokenize(",A,B,", ','),         {"", "A", "B", ""},       " 5. Leading and trailing sep");
    assertEqualVectors(tokenize("A,B,", ','),          {"A", "B", ""},           " 6. Trailing separator");
    assertEqualVectors(tokenize("A", ','),             {"A"},                " 7. Single token, no sep");
    assertEqualVectors(tokenize(",,,A,,,", ','),       {"", "", "", "A", "", "", ""},    " 8. Multiple leading seps");
}

int main(void) {
    runTests();
    return 0;
}