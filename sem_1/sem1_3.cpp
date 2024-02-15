#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <iterator>

template <typename RandIt, typename Comparator>
void parallelSort(int n, RandIt start, RandIt finish, Comparator comp) {
    int length = std::distance(start, finish);
    std::vector<std::thread> threads;
    for (int i = 0; i < n; ++i) {
        threads.emplace_back([&, i](){
            RandIt thread_start = start + i * length / n;
            RandIt thread_finish = i == n - 1 ? finish : start + (i + 1) * length / n;
            std::sort(thread_start, thread_finish, comp);
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    std::inplace_merge(start, start + length / 2, finish, comp);
}

int main() {
    std::vector<int> v = {5, 2, 9, 1, 5, 6, 0, 3, 8};
    parallelSort(3, v.begin(), v.end(), [](int a, int b) {return a > b;});
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
  
    return 0;
}