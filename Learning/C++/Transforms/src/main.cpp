#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
class Add_one {
public:
    T operator()(T val) { return val += 1; }  // A Fucntor overrides ()
};

template <typename T>
class p_vec {
public:
    std::string operator()(std::vector<T> v)
    {
        std::stringstream ss;
        for (auto i : v) {
            ss << i << ' ';
        }
        return ss.str();
    }
};

int main()
{
    std::vector<int> v = {1, 2, 3, 4};
    std::vector<int> v2 = {2, 4, 6, 8};
    std::vector<int> add_one(v.size(), 0);
    std::vector<int> multiply(v.size(), 0);

    Add_one<int> ao;
    p_vec<int> print;

    std::cout << "v1: " << print(v) << '\n';
    std::cout << "v2: " << print(v2) << '\n';

    std::transform(v.begin(), v.end(), add_one.begin(), ao);
    std::cout << "add_one: " << print(add_one) << '\n';

    std::multiplies<int> mul;
    std::transform(v.begin(), v.end(), v2.begin(), multiply.begin(), mul);
    std::cout << "multiply: " << print(multiply) << '\n';
}
