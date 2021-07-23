#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    string type, s;
    size_t index;
};

class QueryProcessor {
    int bucket_num;
    vector<string> elems;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_num;
    }

public:
    explicit QueryProcessor(int bucket_num): bucket_num(bucket_num) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check") {
            cin >> query.s;
        }       
        else {
            cin >> query.index;
        }           
        return query;
    }

    void writeFindResult(bool found) const {
        cout << (found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            for (int i = elems.size() - 1; i >= 0; i--)
                if (hash_func(elems[i]) == query.index) {
                    cout << elems[i] << " ";
                }                  
            cout << "\n";
        } else {
            vector<string>::iterator it = find(elems.begin(), elems.end(), query.s);
            if (query.type == "find") {
                writeFindResult(it != elems.end());
            }             
            else if (query.type == "add") {
                if (it == elems.end()) {
                    elems.push_back(query.s);
                }                  
            } 
            else if (query.type == "del") {
                if (it != elems.end()) {
                    elems.erase(it);
                }                  
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            processQuery(readQuery());
        }         
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int bucket_num;
    cin >> bucket_num;
    QueryProcessor proc(bucket_num);
    proc.processQueries();
    return 0;
}
