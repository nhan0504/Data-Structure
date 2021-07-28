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
void Add(int number, string name, vector<Query>& contacts) {
    bool was_founded = false;
    for (size_t j = 0; j < contacts.size(); j++) {
        if (contacts[j].number == number) {
            contacts[j].name = name;
            was_founded = true;
            break;
        }
    }
    if (!was_founded) {
        Query contact;
        contact.name = name;
        contact.number = number;
        contacts.push_back(contact);
    }
}

void Del(int number, vector<Query>& contacts) {
    for (size_t j = 0; j < contacts.size(); j++) {
        if (contacts[j].number == number) {
            contacts.erase(contacts.begin() + j);
            break;
        }
    }
}

vector<string> Find(vector<string>& result, int number, vector<Query>& contacts) {
    string response = "not found";
    for (size_t j = 0; j < contacts.size(); j++) {
        if (contacts[j].number == number) {
            response = contacts[j].name;
            break;
        }
    }
    result.push_back(response);
    return result;
}
vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); i++) {
        if (queries[i].type == "add") {
            Add(queries[i].number, queries[i].name, contacts);
        }
        else if (queries[i].type == "del") {
            Del(queries[i].number, contacts);
        }
        else {
            result = Find(result, queries[i].number, contacts);
        }             
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
