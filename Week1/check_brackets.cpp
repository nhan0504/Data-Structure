#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    string text;
    getline(cin, text);
    stack <Bracket> opening_brackets_stack;
    int count = 1;
    for (int position = 0; position < text.length(); position++) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            if (!opening_brackets_stack.empty()) {
                if (opening_brackets_stack.top().Matchc(next)) {
                    opening_brackets_stack.pop();
                    count = position + 1;
                }
                else {
                    cout << position + 1 << endl;                   
                    return 0;
                }
            }
            else {
                cout << position + 1 << endl;
                return 0;
            }
              
        }
    }

    if (opening_brackets_stack.empty()) {
        cout << "Success" << endl;
    }
    else {
        cout << opening_brackets_stack.top().position + 1 << endl;
    }
    

    return 0;
}
