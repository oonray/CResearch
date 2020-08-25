#include <iostream>

template <typename T>
T max_of(T a, T b)
{
    return a > b ? a : b;
}

template <typename T>
T min_of(T a, T b)
{
    return a < b ? a : b;
}

int main()
{
    int a = 5;
    int b = 6;

    std::cout << max_of(a, b) << " Is greater than "
              << min_of(float(a), float(b)) << '\n';
};
