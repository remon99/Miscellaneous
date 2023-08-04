#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <fstream>

using namespace std;

set<string> standardKeywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break",
    "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept",
    "const", "consteval", "constexpr", "const_cast", "continue", "co_await", "co_return",
    "co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
    "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline",
    "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
    "operator", "or", "or_eq", "private", "protected", "public", "reflexpr", "register",
    "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static",
    "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this",
    "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned",
    "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"};

bool isUrl(string &input)
{
    int state = 1;
    int i = 0;
    int n = input.length();
    while (i < n)
    {
        char ch = input[i];
        switch (state)
        {
        case 1:
            if (ch == 'h')
                state = 2;
            else if (ch == 'w')
                state = 14;
            else
                state = 13;
            break;
        case 2:
            if (ch == 't')
                state = 3;
            else
                state = 13;
            break;
        case 3:
            if (ch == 't')
                state = 4;
            else
                state = 13;
            break;
        case 4:
            if (ch == 'p')
                state = 5;
            else
                state = 13;
            break;
        case 5:
            if (ch == ':')
                state = 7;
            else if (ch == 's')
                state = 6;
            else
                state = 13;
            break;
        case 6:
            if (ch == ':')
                state = 7;
            else
                state = 13;
            break;
        case 7:
            if (ch == '/')
                state = 8;
            else
                state = 13;
            break;
        case 8:
            if (ch == '/')
                state = 9;
            else
                state = 13;
            break;
        case 9:
            if (isalnum(ch))
                state = 10;
            else
                state = 13;
            break;
        case 10:
            if (isalnum(ch))
                state = 10;
            else if (ch == '.')
                state = 11;
            else
                state = 13;
            break;
        case 11:
            if (isalnum(ch))
                state = 12;
            else
                state = 13;
            break;
        case 12:
            if (isalnum(ch))
                state = 12;
            else
                state = 13;
            break;
        case 13:
            return false;
        case 14:
            if (ch == 'w')
                state = 15;
            else
                state = 13;
            break;
        case 15:
            if (ch == 'w')
                state = 16;
            else
                state = 13;
            break;
        case 16:
            if (ch == '.')
                state = 10;
            else
                state = 13;
            break;
        }
        i++;
    }
}
void checks(const string &input)
{
    auto it = standardKeywords.find(input);
    if (it != standardKeywords.end())
    {
        cout << "keyword";
        return;
    }
    int state = 1;
    int i = 0;
    const int n = input.length();

    while (i < n)
    {
        char ch = input[i];
        switch (state)
        {
        case 1:
            if (isalpha(ch) || ch == '_')
                state = 2;
            else if (isdigit(ch) || ch == '-' || ch == '+')
                state = 9;
            else
            {
                state = 20;
                i = n;
            }
            break;
        case 2:
            if (isalnum(ch) || ch == '_')
            {
                state = 2;
            }
            else if (ch == '@')
                state = 3;
            else
            {
                state = 20;
                i = n;
            }
            break;
        case 3:
            if (isalpha(ch))
                state = 4;
            else
            {
                state = 21;
                i = n;
            }
            break;
        case 4:
            if (isalpha(ch))
                state = 4;
            else if (ch == '.')
                state = 5;
            else
            {
                state = 21;
                i = n;
            }
            break;
        case 5:
            if (isalpha(ch))
                state = 6;
            else
            {
                state = 21;
                i = n;
            }
            break;
        case 6:
            if (isalpha(ch))
                state = 6;
            else if (ch == '.')
                state = 7;
            else
            {
                state = 21;
                i = n;
            }
            break;
        case 7:
            if (isalpha(ch))
                state = 8;
            else
            {
                state = 21;
                i = n;
            }
            break;
        case 8:
            if (isalpha(ch))
                state = 8;
            else
            {
                state = 21;
                i = n;
            }
            break;
        case 9:
            if (isdigit(ch))
                state = 9;
            else if (ch == 'E')
                state = 10;
            else if (ch == '.')
                state = 12;
            else
            {
                state = 22;
                i = n;
            }
            break;
        case 10:
            if (isdigit(ch))
                state = 11;
            else
            {
                state = 22;
                i = n;
            }
            break;
        case 11:
            if (isdigit(ch))
                state = 11;
            else
            {
                state = 22;
                i = n;
            }
            break;
        case 12:
            if (isdigit(ch))
                state = 12;
            else
            {
                state = 22;
                i = n;
            }
            break;
        }
        i++;
    }
    if (state == 20)
        cout << "invalid identifier";
    if (state == 2)
        cout << "valid identifier";
    if (state == 6 || state == 8)
        cout << "valid email";
    if (state == 21)
        cout << "invalid email";
    if (state == 22)
        cout << "invalid number";
    if (state == 11 || state == 9 || state == 12)
        cout << "valid number";
    cout << endl;
}

int main()
{
    ifstream inputFile("C:\\Users\\USER\\Desktop\\New Text Document.txt");
    string input;
    if (inputFile)
    {
        while (inputFile >> input)
        {
            if (isUrl(input))
                cout << "url" << endl;
            else
                checks(input);
        }
    }

    return 0;
}
