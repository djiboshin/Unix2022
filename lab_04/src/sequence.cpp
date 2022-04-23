#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

float f1(float x)
{
    return pow(x, 2) - pow(x, 2) + pow(x, 4) - pow(x, 5) + x + x;
}

float f2(float x)
{
    return x + x;
}

float f3(float x)
{
    return f1(x) + f2(x) - f1(x);
}

void solve(int n, float x)
{
    cout << "============================================" << endl;
    cout << "x=" << x << "; n=" << n << "; solving..." << endl;
    auto begin = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        f3(x);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    cout << "   time elapsed (s): " << elapsed.count() * 1e-9 << endl;
    cout << "   time per step (us): " << elapsed.count() * 1e-3 / n << endl;
    cout << "============================================" << endl;
}
int main(int argc, char *argv[])
{
    if (argc == 2 || argc == 3)
    {
        float x = stod(argv[1]);
        if (argc == 2)
        {
            int n = 10000000;
            solve(n, x);

            n = 100000000;
            solve(n, x);
        }
        else
        {
            int n = stod(argv[2]);
            solve(n, x);
        }
    }
    else
    {
        cout << "wrong arguments number";
    }
    return 0;
}
