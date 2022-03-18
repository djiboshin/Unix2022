#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

double x = 1;

void step()
{
    pow(x,2)-pow(x,2)+pow(x,4)-pow(x,5)+x+x;
}

int main()
{
    int n;
    cout << "Int: ";
    while (true) {
        if(cin >> n){
            cout << "n=" << n << "; solving..." << endl;
            auto begin = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++)
            {
                step();
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

            cout << "time per step (us): " << elapsed.count()* 1e-3 / n << endl;
            cout << "Int: ";
        } else {
            cout << "exit";
            break;
        }
    } 
    return 0;
}