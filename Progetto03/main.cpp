#include <iostream>
#include <compare>
#include <format>
#include <concepts>
#include <vector>
#include <algorithm>
#include <ranges>

// Spaceship operator : <=>
// Genera tutti gli operatori di confronto
class Cliente
{
public:
    Cliente(std::string s, double fatt) : ragioneSociale(s), fatturato(fatt) {}

    std::string getRagioneSociale() const { return ragioneSociale; }

    /*
    bool operator> (const Cliente& operandoADestra) const
    {
        return this->fatturato > operandoADestra.fatturato;
    }
    */

    auto operator<=>(const Cliente &operatoreADestra) const
    {
        return this->fatturato <=> operatoreADestra.fatturato;
    }

private:
    std::string ragioneSociale = "";
    double fatturato = 0;
};

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
    requires Number<T>
T somma(T a, T b)
{
    return a + b;
}

// forma abbreviata
auto somma2(Number auto n1, Number auto n2)
{
    return n1 + n2;
}

template <Number T>
class UsaConcept
{
public:
    UsaConcept(T numero) : valore{numero} {}
    T valore;
};

int main()
{
    Cliente cli1{"Zio Paperone", 99999999999};
    Cliente cli2{"Paperino", 0};

    std::cout << somma<int>(5, 3) << std::endl;
    std::cout << somma<double>(5253.56, 18.35) << std::endl;
    // std::cout << somma<std::stirng>("Ciao ", " a tutti") << std::endl;

    // Prima del introduzione dei concetti di range e views
    std::vector<int> numeri = {1, 2, 3, 4, 5, 6};
    std::vector<int> numeriPari;
    std::copy_if(std::begin(numeri), std::end(numeri), std::back_inserter(numeriPari),
                 [](int n)
                 { return n % 2 == 0; });

    std::vector<int> numeriPariRaddoppiati;
    std::transform(std::begin(numeriPari), std::end(numeriPari), std::back_inserter(numeriPariRaddoppiati),
                   [](int n)
                   { return n * 2; });

    for (int n : numeriPariRaddoppiati)
        std::cout << n << ' ';

    std::cout << std::endl;

    // Dopo del introduzione dei concetti di range e views
    // lazy evaluation

    for (int n : numeri |
                     std::ranges::views::filter([](int n)
                                                { return n % 2 == 0; }) |
                     std::ranges::views::transform([](int n)
                                                   { return n * 2; }))
        std::cout << n << ", ";

    return 0;
}