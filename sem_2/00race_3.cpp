#include <thread>
#include <iostream>
#include <mutex>
using std::cout, std::endl;

int a;
std::mutex mutex;

void func()
{
    for (int i = 0; i < 1000000; ++i)
    {
        {
            std::lock_guard<std::mutex> lock(mutex);
            a++;
        }
    }
}

int main()
{
    cout << a << endl;

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    cout << a << endl;
}

/*
    Задача:

        0)  Будет ли равно значение переменной a числу 2000000, после того как потоки отработают? 
        Да, значение переменной a также будет равно 2000000 после того, как потоки отработают, если использовать std::lock_guard для автоматического освобождения мьютекса.
        
        2)  Исправьте программу, используя std::lock_guard из библиотеки mutex.
*/