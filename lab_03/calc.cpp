#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 4) {
        float a = stod(argv[1]);
        float b = stod(argv[3]);
        char op = *argv[2];

        switch (op)
        {
        case('+'):
            cout << a + b;
            break;
        case('-'):
            cout << a - b;
            break;
        case('*'):
            cout << a * b;
                break;    
        case('^'):
            cout << pow(a, b);
                break;
        default:
            cout << "operator error: " << op;
            break;
        }
    } else {
        cout << "wrong arguments number";
    }
    return 0;
}