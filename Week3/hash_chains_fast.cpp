#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct Query {
    string type, s;
    size_t index;
};

class QueryProcessor {
    int bucket_num;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; i--)
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

    vector<list<string>> hash_table() {
        list<string> elems;
        vector<list<string>> table(bucket_num, elems);
        return table;
    }
    vector<list<string>> table = hash_table();

    void processQuery(const Query& query, vector<list<string>>& table) {
        if (query.type == "check") {
            if (!table[query.index].empty()) {
                list<string> list_ = table[query.index];
                for (list<string>::iterator it = list_.begin(); it != list_.end(); it++) {
                    cout << *it << " ";
                }
            }
            else {
                cout << "\n";
            }                
            cout << "\n";
        } else {
            list<string>& list_ = table[hash_func(query.s)];
            list<string>::iterator begin = list_.begin();
            list<string>::iterator end = list_.end();
            if (query.type == "find") {
                bool found = false;
                if (!list_.empty()) {
                    while(begin != end) {
                        if (*begin == query.s) {
                            found = true;
                            break;
                        }
                        begin++;
                    }
                }
                writeFindResult(found);
            }             
            else if (query.type == "add") {    
                bool exist = false;
                if (table[hash_func(query.s)].empty()) {
                    table[hash_func(query.s)].push_front(query.s);
                }
                else {               
                    while (begin != end) {
                        if (*begin == query.s) {
                            exist = true;
                            break;
                        }                          
                        begin++;
                    }                                          
                    if (exist == false) {
                        table[hash_func(query.s)].push_front(query.s);
                    }
                }                                       
            } 
            else if (query.type == "del") {
                if (list_.size() == 1 && list_.front() == query.s) {
                    list_.pop_front();
                }
                else if (list_.size() > 1){
                    while (begin != end) {
                        if (*begin == query.s) {
                            list_.erase(begin);
                            break;
                        }
                        begin++;
                    }
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            processQuery(readQuery(), table);
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
