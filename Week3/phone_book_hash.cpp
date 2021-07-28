#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; i++) {
        cin >> queries[i].type;
        if (queries[i].type == "add") {
            cin >> queries[i].number >> queries[i].name;
        }     
        else {
            cin >> queries[i].number;
        }          
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << "\n";
    }     
}

int hash_func(const int& s)  {
    int table_size = 1000;
    static const int64_t prime = 1000000007;
    static const uint64_t multiplier = (uint64_t)(rand() % 1000000006) + 1;
    static const uint64_t add = rand() % 1000000006; 
    uint64_t hash = 0;
    hash = (s * multiplier + add) % prime;
    return hash % table_size;
}

void Add(Query query, vector<vector<Query>>& contacts) {
    vector<Query>& array = contacts[hash_func(query.number)];
    if (array.empty()) {
        array.push_back(query);
    }
    else {
        for (size_t i = 0; i < array.size(); i++) {
            if (query.number == array[i].number) {
                array[i].name = query.name;
                break;
            }
        }
    }
}

void Del(Query query, vector<vector<Query>>& contacts) {
    vector<Query>& array = contacts[hash_func(query.number)];
    if (!array.empty()) {
        for (vector<Query>::iterator i = array.begin(); i < array.end(); i++) {
            if (query.number == i -> number){
                array.erase(i);
                break;
            }
        }
    }
}

vector<string> Find(vector<string>& result, Query query, vector<vector<Query>>& contacts) {
    vector<Query>& array = contacts[hash_func(query.number)];
    if (array.empty()) {
        result.push_back("not found");
        return result;
    }
    else {
        for (size_t i = 0; i < array.size(); i++) {
            if (query.number == array[i].number) {
                result.push_back(array[i].name);
                return result;
            }
        }
    }
}



vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    vector<vector<Query>> contacts(1000);
    for (size_t i = 0; i < queries.size(); i++) {
        if (queries[i].type == "add") {
            Add(queries[i], contacts);
        }
        else if (queries[i].type == "del") {
            Del(queries[i], contacts);
        }
        else {
            result = Find(result, queries[i], contacts);
        }             
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
