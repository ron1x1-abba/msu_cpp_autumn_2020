#include "ThreadPool.hpp"
#include <cassert>

struct A {};

void foo(const A&) {}

int main(){
    ThreadPool pool(8);

    for(size_t i = 0; i < 16; ++i)
        pool.exec(foo, A());
    auto task1 = pool.exec(foo, A());
    task1.get();
    std::vector<int> results;
    for(size_t i = 0; i < 24; ++i) {
        auto task2 = pool.exec([](int b) { return b; }, i);
        results.push_back(task2.get());
    }
    for(int i = 0; i < 24; ++i)
        assert(results[i] == i);
    std::cout << "Done!" << std::endl;
    return 0;
}