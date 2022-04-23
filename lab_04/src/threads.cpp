#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

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

void threadFunction(int n, float x)
{
    for (int i = 0; i < n; i++)
    {
        f3(x);
    }
}

void solve(int n, float x, int n_threads)
{
    cout << "============================================" << endl;
    cout << "x=" << x << "; n=" << n << "; solving..." << endl;

    std::vector<std::thread> threads;
    auto begin = std::chrono::high_resolution_clock::now();

    for (int t = 0; t < n_threads; t++)
    {
        threads.push_back(std::thread(threadFunction, n / n_threads, x));
    }
    for (int t = 0; t < n_threads; t++)
    {
        threads[t].join();
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
        int n = 10000000;
        int n_threads = (argc == 3) ? stod(argv[2]) : 1;
        solve(n, x, n_threads);

        n = 100000000;
        solve(n, x, n_threads);
    }
    else
    {
        cout << "wrong arguments number";
    }
    return 0;
}