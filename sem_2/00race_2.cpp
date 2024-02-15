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
        std::lock_guard<std::mutex> lock(mutex);
        a++;
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
        Да, значение переменной a будет равно 2000000 после того, как потоки отработают, если добавить мьютекс для синхронизации доступа к переменной a.

        1)  Исправьте программу, используя объект std::mutex из библиотеки mutex.
*/