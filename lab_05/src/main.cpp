#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

/**
 * @brief Основной класс, который является кирпичиком стека вызовов.
 *
 */
class runable
{
public:
    runable()
    {
    }
    runable(string sargs)
    {
    }
    virtual double run()
    {
        return 0;
    }
};
// Указатель на функцию, которая возвращает объект класса runable по названию функции и аргументам
runable *(*get_func)(string, string);

/**
 * @brief Вспомогательное, ожидает ввода любой клавиши
 *
 */
void wait_any_key()
{
    cout << "press any key...";
    cin.ignore();
    cin.get();
}

/**
 * @brief Вспомогательное, пишет об ошибке и завершает процесс
 *
 */
void error_msg(string msg)
{
    cout << msg << endl;
    wait_any_key();
    exit(-1);
}

/**
 * @brief Ищет закрывающую кавычку
 *
 * @param s подстрока для поиска
 * @param close_char закрывающий символ, например )
 * @param open_char открывающий, например (
 * @return int номер закрывающего символа в подстроке
 */
int find_close(string s, char close_char, char open_char)
{
    int index = 0;
    for (string::size_type i = 0; i < s.size(); i++)
    {
        if (s[i] == open_char)
        {
            index += 1;
        }
        else if (s[i] == close_char)
        {
            index -= 1;
        }
        if (index == 0)
        {
            return i;
        }
    }
    string msg = "can't find `";
    msg += close_char;
    msg += "`";
    error_msg(msg);
    return -1;
}

/**
 * @brief Запускает run переданного экземпляра класса runable.
 * Выводит сообщение о старте и сообщение о завершении со временем исполнения.
 *
 * @param f экземпляра класса runable
 * @param n номер потока для сообщения
 */
void fthreadrun(runable *f, int n)
{
    cout << "[" << n << "]"
         << " started" << endl;
    auto begin = std::chrono::high_resolution_clock::now();
    f->run();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "[" << n << "]"
         << " ended in " << elapsed.count() * 1e-9 << "s" << endl;
}

/**
 * @brief Класс стека вызовов
 *
 */
class stack : public runable
{
public:
    vector<runable *> *vec;
    stack(string sstack)
    {
        parse_stack(sstack);
    }
    // поочередный запуск каждого элемента из стека
    double run()
    {
        double res;
        // cout << "runing stack" << endl;
        for (runable *f : *(this->vec))
        {

            res = f->run();
        }
        return res;
    }
    // параллельный запуск каждого элемента из стека
    void runparallel()
    {
        double res;
        vector<thread> threads;

        int n = 0;
        for (runable *f : *(this->vec))
        {
            threads.push_back(thread(fthreadrun, f, n));
            n++;
        }
        for (int t = 0; t < threads.size(); t++)
        {
            threads[t].join();
        }
    }

private:
    // рекурсивно парсит стек {a(ar1)b(ar2){c(ar3)}} -> [a(ar1), b(ar1), [c(ar3)]]
    void parse_stack(string sstack)
    {
        vector<runable *> *newstack = new vector<runable *>;
        string command = "";
        for (string::size_type i = 0; i < sstack.size(); i++)
        {
            if (sstack[i] == '(')
            {
                int cindex = find_close(sstack.substr(i), ')', '(');
                string arg = sstack.substr(i + 1, cindex - 1);

                // cout << command << " " << arg << endl;
                runable *f = get_func(command, arg);
                newstack->push_back(f);

                command = "";
                i += cindex;
            }
            else if (sstack[i] == '{')
            {
                if (command.length() != 0)
                {
                    error_msg("can't parse. invalid `command{}` syntax");
                }

                int cindex = find_close(sstack.substr(i), '}', '{');
                string arg = sstack.substr(i + 1, cindex - 1);

                // cout << "{} " << arg << endl;
                runable *f = new stack(arg);
                newstack->push_back(f);

                i += cindex;
            }
            else if (sstack[i] == ' ')
            {
            }
            else
            {
                command += sstack[i];
            }
        }
        this->vec = newstack;
    }
};

/**
 * @brief  вспомогательная функция. Делит строку на две части по разделителю
 *
 * @param s строка
 * @param delim разделитель
 * @return vector<string>
 */
vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    int i = s.find_first_of(delim);
    elems.push_back(s.substr(0, i));
    elems.push_back(s.substr(i + 1));
    return elems;
}
/**
 * @brief базовый класс функции
 *
 */
class pfunc : public runable
{
public:
    string args;
    stack *_stack;
    string fname = "pfunc";
    pfunc()
    {
    }
    pfunc(string sargs)
    {
        args = sargs;
        parse_args(args);
    }
    pfunc(string sargs, string name)
    {
        args = sargs;
        parse_args(args);
        fname = name;
    }
    virtual double run()
    {
        // cout << "im runnfing " << fname << " of " << args << endl;
        return this->_stack->run();
    }
    virtual void parse_args(string sargs)
    {
        this->_stack = new stack(sargs);
    }
};
/**
 * @brief Класс операции math()
 *
 */
class f_math : public pfunc
{
public:
    f_math(string sargs)
    {
        this->args = sargs;
    }
    // Описан простой калькулятор
    double run()
    {
        string ops = {'+', '-', '*', '/'};
        int index = args.find_first_of(ops);
        if (index == -1)
        {
            return stod(args);
        }
        else
        {
            double a = stod(args.substr(0, index));
            double b = stod(args.substr(index + 1));
            double res;
            char op = args[index];
            switch (op)
            {
            case ('+'):
                res = a + b;
                break;
            case ('-'):
                res = a - b;
                break;
            case ('*'):
                res = a * b;
                break;
            case ('/'):
                res = a / b;
                break;
            }
            return res;
        }
        return 0;
    }
};
/**
 * @brief Класс операции print()
 *
 */
class f_print : public pfunc
{
public:
    f_print(string sargs)
    {
        this->args = sargs;
        parse_args(sargs);
    }
    double run()
    {
        cout << this->_stack->run() << endl;
        return 0;
    }
};
/**
 * @brief Класс операции f_printf() для записи в файл
 *
 */
class f_printf : public pfunc
{
public:
    f_printf(string sargs)
    {
        this->args = sargs;

        vector<string> vargs = split(sargs, ',');
        if (vargs.size() != 2)
        {
            error_msg("invalid amount of args in printf()");
        }
        filename = vargs[0];
        parse_args(vargs[1]);
    }
    double run()
    {
        ofstream myfile;
        myfile.open(filename, ios_base::app);
        myfile << this->_stack->run() << endl;
        myfile.close();
        return 0;
    }

private:
    string filename;
};
/**
 * @brief Класс операции repeat() для повторения
 *
 */
class f_repeat : public pfunc
{
public:
    f_repeat(string sargs)
    {
        this->args = sargs;

        vector<string> vargs = split(sargs, ',');
        if (vargs.size() != 2)
        {
            error_msg("invalid amount of args in repeat()");
        }
        // cout << vargs[0] << " " << vargs[1] << endl;
        times = stoi(vargs[0]);
        parse_args(vargs[1]);
    }
    double run()
    {
        int res;
        for (int i = 0; i < times; i++)
        {
            res = this->_stack->run();
        }
        return res;
    }

private:
    int times;
};
/**
 * @brief Функция, которая по названию операции возвращает класс
 *
 * @param name название операции
 * @param sargs аргументы операции
 * @return runable*
 */
runable *_get_func(string name, string sargs)
{
    pfunc *func;
    if (name == "math")
    {
        func = new f_math(sargs);
    }
    else if (name == "print")
    {
        func = new f_print(sargs);
    }
    else if (name == "printf")
    {
        func = new f_printf(sargs);
    }
    else if (name == "repeat")
    {
        func = new f_repeat(sargs);
    }
    else
    {
        func = new pfunc(sargs);
    }
    return func;
}

int main()
{
    get_func = &_get_func;
    string code = "";
    cout << "Code: " << endl;
    while (true)
    {
        string newCode;
        cin >> newCode;
        if (newCode == "run")
        {
            stack a(code);
            // a.run();
            a.runparallel();
            wait_any_key();
            break;
        }
        else
        {
            code = code + newCode;
        }
    }
    return 0;
}