# Реквизиты

Игошин Владимир Дмитриевич, 3 курс, z33434, 2022

# Наименование

[C++ & UNIX]: C++ CLI / FUNCTION / LOOP / RECURSION

# Цель

Познакомить студента с основными алгоритмическими конструкциями, которые будут использоваться для создания CLI программы. Далее продемонстрировать эффективность использования механизма рекурсии.
С++ алгоритмы: CLI Калькулятор вещественных чисел +, -, ^, . Реализация с использованием только функций, условий, циклов, + и -. Вид команд в консоли: calc plus / minus / power; Ханойская башня, результат корректной последовательности

# Задача

1. [С++ CLI CALC] Создать программу CALC с интерфейсом CLI
   Создать программу под названием CALC, которая будет принимать на вход 3 аргумента (2 операнда и 1 оператор). Оператор может быть: +, -, ^. Реализация операторов только с использованием функций, условий, циклов, +, - и \*.
2. [C++ RECURSION] Решить задачу ханойской башни с использованием рекурсии
   Описание: Ханойская башня является одной из популярных головоломок XIX века. Даны три стержня, на один из которых нанизаны восемь колец, причём кольца отличаются размером и лежат меньшее на большем. Задача состоит в том, чтобы перенести пирамиду из восьми колец за наименьшее число ходов на другой стержень. За один раз разрешается переносить только одно кольцо, причём нельзя класть большее кольцо на меньшее.
   Описание: Ханойская башня является одной из популярных головоломок XIX века. Даны три стержня, на один из которых нанизаны восемь колец, причём кольца отличаются размером и лежат меньшее на большем. Задача состоит в том, чтобы перенести пирамиду из восьми колец за наименьшее число ходов на другой стержень. За один раз разрешается переносить только одно кольцо, причём нельзя класть большее кольцо на меньшее.
3. [SAVE] Результат всех вышеперечисленных шагов сохранить в репозиторий (+ отчет по данной ЛР в папку doc)
   Фиксацию ревизий производить строго через ветку dev. С помощью скриптов накатить ревизии на stg и на prd. Скрипты разместить в корне репозитория. Также создать скрипты по возврату к виду текущей ревизии (даже если в папке имеются несохраненные изменения + новые файлы).

# Решение

### 1. 1. [С++ CLI CALC] Создать программу CALC с интерфейсом CLI

Код целиком

```c++
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
```

### 2. [C++ RECURSION] Решить задачу ханойской башни с использованием рекурсии

Структура элемента двусвязного списка, содержащего намер шайбы, номер столбика, откуда шайба переставляется, и номер столбика, куда шайба переставляется:

```c++
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
```

Структура списка, содержащего шаги, который позволяет создавать элементы списка.

```c++
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
        }
    }
};
```

Итерируемая функция `replace`, которая переставляет `n` шайб с `i`-ого столика на `k`

```c++
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
```

Весь код целиком

```c++
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
        }
    }
};

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
```

Пример работы:

```text
number of disks: 3
to: 2
disk 1 from 1 to 2
disk 2 from 1 to 3
disk 1 from 2 to 3
disk 3 from 1 to 2
disk 1 from 3 to 1
disk 2 from 3 to 2
disk 1 from 1 to 2
```

### 3. [SAVE] Результат всех вышеперечисленных шагов сохранить в репозиторий (+ отчет по данной ЛР в папку doc)

Использовались скрипты с прошлых лаб
