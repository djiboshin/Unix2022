#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

struct Step
{
    int id;
    int from;
    int to;
    Step *next = nullptr;
    Step *prev = nullptr;
    Step(int id, int from, int to)
    {
        this->id = id;
        this->from = from;
        this->to = to;
    }
};

struct ListOfSteps
{
    Step *first = nullptr;
    Step *last = nullptr;
    void add(int id, int from, int to)
    {
        Step *newStep = new Step(id, from, to);
        if (first == nullptr)
        {
            first = newStep;
        }
        if (last != nullptr)
        {
            newStep->prev = last;
            last->next = newStep;
        }
        last = newStep;
    }
    void print()
    {
        Step *cur = this->first;
        while (cur != nullptr)
        {
            cout << "disk " << cur->id << " from " << cur->from << " to " << cur->to << endl;
            cur = cur->next;
        }
    }
    void destroy()
    {
        Step *cur = this->first;
        while (cur != nullptr)
        {
            cur = cur->next;
            delete cur->prev;
            // cout << "deleted " << cur << endl;
        }
    }
};

/**
 * @brief Replace n disks from pin i to pin k
 *
 * @param n is an amount of disks
 * @param i is a pin number
 * @param k is a pin nunber
 */
void replace(int n, int i, int k, ListOfSteps *list)
{
    if (n == 1)
    {
        list->add(n, i, k);
    }
    else
    {
        if (i != k)
        {
            int tmp = 6 - i - k;
            replace(n - 1, i, tmp, list);
            list->add(n, i, k);
            replace(n - 1, tmp, k, list);
        }
    }
}

int main()
{
    int n, to;
    cout << "number of disks: ";
    cin >> n;
    cout << "to: ";
    cin >> to;

    ListOfSteps list;
    replace(n, 1, to, &list);
    list.print();
    list.destroy();

    return 0;
}