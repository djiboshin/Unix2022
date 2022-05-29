# Реквизиты

Игошин Владимир Дмитриевич, 3 курс, z33434, 2022

# Наименование

[C++ & UNIX]: C++ OOP / PARALLEL

# Цель

Познакомить студента с принципами объектно-ориентированного программирования на примере создания сложной синтаксической структуры. Придумать синтаксис своего персонального мини-языка параллельного программирования, а также реализовать его разбор и вычисление.

# Задача

1. [С++ PARALLEL LANG] Создать параллельный язык программирования
   Требуется создать язык программирования, в котором будет доступна установка следующих команд:

   - Установка счетного цикла
   - Вывод в консоль
   - Вывод в файл в режиме добавления
   - Арифметические операции +, -, \*, /

   Счетный цикл должен поддерживать дальнейшую установку всех остальных поддерживаемых команд.

   Для реализации задачи использовать технологию объектно-ориентированного программирования в части реализации поддерживаемых команд языка.

   В программе должны быть отражены следующие шаги:

   1. 1. Текстовый ввод команд. Каждая новая строка – это новый набор команд.
      2. Ожидание команды на окончание ввода
      3. Параллельное исполнение введенных строк (наборов команд). Наборы команд должны исполняться параллельно. В консоли фиксировать время запуска / завершения каждого потока. При выводе информации о времени указывать принадлежность потока к строке (набору команд)

2. [LOG] Результат всех вышеперечисленных шагов сохранить в репозиторий (+ отчет по данной ЛР в папку doc)
   Фиксацию ревизий производить строго через ветку dev. С помощью скриптов накатить ревизии на stg и на prd. Скрипты разместить в корне репозитория. Также создать скрипты по возврату к виду текущей ревизии (даже если в папке имеются несохраненные изменения + новые файлы).

# Решение

### 1. [С++ PARALLEL LANG] Создать параллельный язык программирования

Краткая документация дана в коде. Здесь приведу примеры работы. Чтобы скомпилировать, необходимо использовать `g++ main.cpp -o build/main -pthread`.

Запуск:

```bash
    ./build/main
```

Результат:

```bash
   Code:

```

После этого вводится код. `run` на новой строке является указателем к запуску.

#### Пример 1

Самая простая команда

```bash
print(math(4))
run
```

Результат:

```bash
[0] started
4
[0] ended in 4.22e-05s
press any key...
```

#### Пример 1.1

Запись в файл

```bash
printf(1.txt,math(4))
run
```

Результат:

```bash
[0] started
[0] ended in 0.0021829s
press any key...
```

#### Пример 2

`math` поддерживает `+`, `-`, `*`, `/`

```bash
print(math(2.2*321.1))
run
```

Результат:

```bash
[0] started
706.42
[0] ended in 0.0001489s
press any key..
```

#### Пример 3

Внутри команды можно писать целый стак команд. Будет использован результат выполнения последней

```bash
print(math(2)math(3))
run
```

Результат:

```bash
[0] started
3
[0] ended in 4.5e-05s
press any key...
```

Аналогично можно использовать

```bash
print({math(2)math(3)})
run
```

#### Пример 4

Результат выполнения `print`, `printf` -- ноль.

```bash
print(print(math(1)))
run
```

Результат:

```bash
[0] started
1
0
[0] ended in 4.98e-05s
press any key...
```

#### Пример 5

Чтобы запустить программу параллельно, основной стек нужно подробить на мелкие, используя фигурные скобки

```bash
{printf(1.txt,math(1))}
{printf(2.txt,math(2))}
{printf(3.txt,math(2))print(math(3))}
run
```

Результат:

```bash
[0] started
[1] started
[2] started
[0] ended in 0.0026476s
[1] ended in 0.0037143s
3
[2] ended in 0.0066036s
press any key...
```

#### Пример 6

`repeat` требует два аргумента, первый из них -- число повторений. `repeat` возвращает результат последней выполненной функции

```bash
{repeat(4,print(math(2/3)))print(repeat(4,{math(2)print(math(2+5))}))}
run
```

Результат:

```bash
[0] started
0.666667
0.666667
0.666667
0.666667
7
7
7
7
0
[0] ended in 0.0001034s
press any key...
```

#### Пример 7

Пробелы игнорируются

```bash
{
    printf(1.txt,math(4+1))
    print(math(4+2))
    print(math(4+3))
    repeat(5, {
        {math(2+2)}
        print(math(34.324))
    })
}
run
```

Результат:

```bash
[0] started
6
7
34.324
34.324
34.324
34.324
34.324
[0] ended in 0.0021984s
press any key...
```

### 2. [LOG] Результат всех вышеперечисленных шагов сохранить в репозиторий (+ отчет по данной ЛР в папку doc)

Использовались скрипты с прошлых лаб