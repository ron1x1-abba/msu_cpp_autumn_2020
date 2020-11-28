#include "my_vector.hpp"
#include <cassert>
#include <vector>

struct President
{
    std::string name;
    std::string country;
    int year;
 
    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    President(President&& other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being moved.\n";
    }
    President& operator=(const President& other) = default;
};

int main() {
    //iterator assertion
    int* ptr1 = new int[20];
    int* ptr2 = ptr1;
    for(int i = 0; i < 20; ++i)
        ptr1[i] = i;
    Iterator<int> it1(ptr1);
    assert(*(it1) == 0);
    assert(*(it1++) == 0);
    assert(*(it1) == 1);
    assert(*(it1 += 2) == 3);
    assert(*(it1 -= 2) == 1);
    assert(*(it1--) == 1);
    assert(*(it1) == 0);
    assert(*(++it1) == 1);
    assert(*(--it1) == 0);
    assert(it1[10] == 10);
    assert(*(it1 + 2) == 2);
    assert(*(it1) == 0);
    assert(*(2 + it1) == 2);
    Iterator<int> it2(ptr1);
    assert(((it2 += 10) - (it1 += 2)) == 8);
    delete[] ptr2;
    //end of iterator assertion
    //vector assertion
    Vector<int> a;
    assert(a.size() == 0);
    for(size_t i = 0; i < 6; ++i) {
        a.push_back(i);
        assert(a[i] == static_cast<int>(i));
    }
    assert(a.size() == 6);
    a.resize(4);
    assert(a.size() == 4);
    a.pop_back();
    assert(a.size() == 3);
    assert(a.empty() == false);
    assert(*(++a.begin()) == 1);
    assert(*(--a.end()) == 2);
    assert(*(--a.rend()) == 0);
    assert(*(a.rbegin()) == 2);
    a.clear();
    assert(a.size() == 0);

    Vector<President> elections;
    std::cout << "emplace_back:\n";
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);
 
    Vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));
    Vector<int> b;
    b = std::move(a);
    assert(b[1] == 1);
    assert(a.empty() == true);
    //end of vector assertion
    std::cout << "Done" << std::endl;
    return 0;
}