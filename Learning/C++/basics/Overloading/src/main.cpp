#include <iostream>

class Fraction {
private:
    int _n;
    int _d;

public:
    Fraction(const Fraction& f) : _n(f._n), _d(f._d) {}
    Fraction(int numerator = 0, int denominator = 1)
        : _n(numerator), _d(denominator)
    {
    }
    ~Fraction();
    int numerator() const { return _n; }
    int denominator() const { return _d; }

    Fraction& operator=(const Fraction&);
    //    Fraction operator+(const Fraction&) const;
    Fraction operator-(const Fraction&) const;
    Fraction operator/(const Fraction&) const;
    Fraction operator*(const Fraction&)const;
    int operator[](const int&);
};

Fraction::~Fraction()
{
    _n = 0;
    _d = 0;
}

Fraction& Fraction::operator=(const Fraction& frac)
{
    if (&frac != this) {
        _n = frac.numerator();
        _d = frac.denominator();
    }
    return *this;
}

/* Moved outside class to work with both lhs and rhs
Fraction Fraction::operator+(const Fraction& frac) const
{
    return Fraction((_n * frac._d) + (_d * frac._n), _d * frac._d);
}
*/

Fraction Fraction::operator-(const Fraction& frac) const
{
    return Fraction((_n * frac._n) - (_d * frac._n), _d * frac._d);
}

Fraction Fraction::operator*(const Fraction& frac) const
{
    return Fraction(_n * frac._n, _d * frac._d);
}

Fraction Fraction::operator/(const Fraction& frac) const
{
    return Fraction(_n * frac._d, _d * frac._d);
}

Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
    return Fraction((lhs.numerator() * rhs.denominator()) +
                        (lhs.denominator() * rhs.numerator()),
                    lhs.denominator() * rhs.denominator());
}

int Fraction::operator[](const int& n) { return n; };
/*
 * __str__
 */
std::ostream& operator<<(std::ostream& o, const Fraction& frac)
{
    if (frac.denominator() == 1) return o << frac.numerator();
    return o << frac.numerator() << '/' << frac.denominator();
}

int main()
{
    Fraction a = 7;
    Fraction b(2, 3);

    std::cout << a << "+" << b << "=" << a + b << '\n';
    std::cout << a << "+" << 14 << "=" << a + 14 << '\n';

    std::cout << a[5] << '\n';
}
