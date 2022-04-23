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

### 1. [С++ CLI CALC] Создать программу CALC с интерфейсом CLI

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

Пример работы:

```text
Int: 999999
n=999999; solving...
time per step (us): 0.334021
Int:
```

### 2. [PYTHON EXPRESSION] Создать и скомпилировать программу на Python 3

```python
import time
x = 1
def step():
    x**2 - x**2 + x**4-x**5+x+x


if __name__ == '__main__':
    while True:
        try:
            n = int(input("Int: "))
            print(f"n={n}; solving...")
            begin = time.process_time()
            for _ in range(int(n)):
                step()
            end = time.process_time()
            elapsed = end - begin
            print(f'time per step (us): {elapsed/n * 1e6}')
        except ValueError:
            print("exit")
            break
```

Пример работы:

```text
Int: 999999
n=999999; solving...
time per step (us): 0.8437508437508437
Int:
```

### 3. [SAVE] Результат всех вышеперечисленных шагов сохранить в репозиторий (+ отчет по данной ЛР в папку doc)

Скрипт, который возвращает к виду текущей ревизии

```shell
#!/bin/bash
git reset --hard
git clean -f
```