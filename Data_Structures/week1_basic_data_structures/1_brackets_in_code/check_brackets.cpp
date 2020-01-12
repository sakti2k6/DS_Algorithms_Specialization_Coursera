#include <iostream>
#include <stack>
#include <string>

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

void match_brackets(const std::string& text) {

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket
            opening_brackets_stack.emplace(Bracket(next,position));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket
            if (opening_brackets_stack.empty()) {
                std::cout << position+1 << std::endl;
                return;
            } else {
                Bracket obracket = opening_brackets_stack.top();
                if (!obracket.Matchc(next)) {
                    std::cout << position+1 << std::endl;
                    return;
                } else {
                    opening_brackets_stack.pop();
                }
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.empty())
        std::cout << "Success" << std::endl;
    else
        std::cout << opening_brackets_stack.top().position + 1 << std::endl;
    
    return;
}

int main() {
    std::string text;
    getline(std::cin, text);
    match_brackets(text);
    return 0;
}
