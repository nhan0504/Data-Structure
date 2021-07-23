#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const vector<int>& output) {
    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }      
    cout << "\n";
}

bool AreEqual(string a, string b) {
    bool equal = true;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            equal = false;
        }
    }      
    return equal;
}

size_t hash_func(const string& s) {
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; i--)
        hash = (hash * multiplier + s[i]) % prime;
    return hash % 10;
}

vector<int> RabinKarp(const Data& input) {
    vector<int> result;
    const string& p = input.pattern, t = input.text;
    int pHash = hash_func(p);
    for (size_t i = 0; i + p.size() <= t.size(); i++) {
        string str = t.substr(i, p.size());
        int tHash = hash_func(str);
        if (tHash == pHash) {
            if (AreEqual(p, str) == true) {
                result.push_back(i);
            }
        }
    }
    return result;
}


int main() {
    ios_base::sync_with_stdio(false);
    print_occurrences(RabinKarp(read_input()));
    return 0;
}
