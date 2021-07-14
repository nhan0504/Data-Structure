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
    int count = 0;
    stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); position++) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            if (opening_brackets_stack.empty() || !opening_brackets_stack.top().Matchc(next)) {
                count = position + 1;
                cout << "position = " << position << endl;
                cout << "count = " << count << endl;
            }
            opening_brackets_stack.pop();
        }
    }

    if (count == 0 && opening_brackets_stack.empty()) {
        cout << "Success" << endl;
    }
    else {
        cout << count << endl;
    }

    return 0;
}
