#include <iostream>
#include <format>
#include <span>
#include <vector>

int sommatoria(const int v[], size_t dimensione)
{
    long long risultato = 0LL;
    for (size_t i = 0; i < dimensione; i++)
        risultato += v[i];

    return risultato;
}

// le performance sono ugali
// le linee guida suggeriscono di passare gli array tradizionali in questo modo
int sommatoriaConSpan(std::span<const int> v)
{
    long long risultato = 0LL;
    for (int n : v)
        risultato += n;

    return risultato;
}

struct Nemico
{
    int codice;
    std::string classe;
    int potenza {0};
};


int main()
{

    int valori[]{15, 5464, 634, 16, 442, 665};
    std::cout << std::format("La sommatoria vale: {}\n", sommatoria(valori, 3));
    std::cout << std::format("La sommatoria vale: {}\n", sommatoriaConSpan(valori));

    std::span<const int> v = valori;
    std::cout << std::format("Primo elemento span: {}, ultimo elemento: {}\n", v.front(), v.back());

    std::vector<int> vect{4, 435, 657, 89, 54};

    enum class Status
    {
        On,
        Off,
        Standby
    };
    using enum Status;
    Status stato = Off;

    // puoi inzializzare variabili nella dichiarazione del range for
    for (int parziale = 0; int ele : valori)
    {
        parziale += ele;
        std::cout << parziale << std::endl;
    }

    // to_array -> crea oggetti di classe array
    auto arr{std::to_array({10, 20, 30, 40})};
    
    Nemico numberOne  {.codice{666}, .potenza{99999}};

    return 0;
}