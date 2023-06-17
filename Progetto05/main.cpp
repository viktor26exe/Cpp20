/*
#include <iostream>
#include <thread>
 
using namespace std;
 
void ordina_partizione_array(int *v, int quanti)
{
  for (int i=0; i<quanti-1; i++)
    for (int j=i+1; j<quanti; j++)
      if (v[j]<v[i]) swap(v[i], v[j]);
}
 
void setup(int v[], int quanti)
{
  for (int i=0; i<quanti; i++)
    v[i] = rand();
}
 
void stampa(int v[], int quanti)
{
  for (int i=0; i<quanti; i++)
    cout << v[i] << " ";
}
 
const int MAX=30;
int v[MAX];
 
int main()
{
  setup(v, MAX);
 
 
  thread t1 = thread(ordina_partizione_array,v, MAX/2);
  thread t2 = thread(ordina_partizione_array,v+MAX/2, MAX/2);
 
  t1.join();
  t2.join();
 
 
  stampa(v, MAX);
 
 
    return 0;
}
*/ 
 
//VERSIONE CON COROUTINE
#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>
#include <thread>
#include <algorithm>
#include <format>
 
using namespace std;
 
//static int ctr{ 0 };
 
struct ReturnObject {
    struct promise_type {
        ReturnObject get_return_object() {
            
            return { std::coroutine_handle<promise_type>::from_promise(*this) };
        }
 
        void return_void() noexcept {}
 
 
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
 
        auto getHandle() {
            return std::coroutine_handle<promise_type>::from_promise(*this);
        }
    };
 
    std::coroutine_handle<> h_; 
 
    ReturnObject(std::coroutine_handle<> h) :h_{ h } { } 
 
    //implicit conversion operator
    operator std::coroutine_handle<>() const { return h_; } 
};
 
 
//coroutine 
ReturnObject ordina_partizione_array(int* v, int quanti, bool& terminato, string corID) {
    int progresso = 0;
    cout << "inizio coroutine " + corID << endl;
 
    for (int i = 0; i < quanti - 1; i++)
        for (int j = i + 1; j < quanti; j++)
        {
            if (v[j] < v[i]) std::swap(v[i], v[j]);
            
            progresso++;
            cout << progresso << endl;
 
            if (progresso % 3 == 0)
            {
                cout << format("{} Restituisce controllo al main ... i:{} j:{}\n",corID, i,j);
                co_await std::suspend_always{};
                cout << format("Rientro nella {} con i:{} j:{}\n", corID, i, j);
            }
        }
 
    terminato = true;
}
 
 
void setup(int v[], int quanti) { for (int i = 0; i < quanti; i++) v[i] = rand(); }
 
void stampa(int v[], int quanti)
{
    for (int i = 0; i < quanti; i++)    cout << v[i] << " ";
    cout << endl;
}
 
 
const int MAX = 1000000;
int v[MAX];
 
void elaborazione_main()
{
    for (int i = 0; i < 5; i++) cout << "Progresso workload del main ...\n";
}
 
int main() {
    setup(v, MAX);
    stampa(v, MAX);
 
 
    bool terminata_cor1 = false, terminata_cor2 = false;
 
    //il main lavora un po' ...
    elaborazione_main();
 
    std::coroutine_handle<> h1 = 
        ordina_partizione_array(v, MAX / 2, terminata_cor1, "cor1");
    
    //il main lavora un po' ...
    elaborazione_main();
 
    std::coroutine_handle<> h2 
        = ordina_partizione_array(v + MAX / 2, MAX / 2, terminata_cor2, "cor2");
 
 
 
    while (!terminata_cor1 && !terminata_cor2)
    {
        //il main lavora un po' ...
        elaborazione_main();
 
        //passo il controllo alla coroutine che fa avanzare 
        //l'ordinamento per la prima metà dell'array
        h1();
 
        //la coroutine ha restituito il controllo al chiamante che 
        //può avanzare un poco a sua volta
        elaborazione_main();
 
        //passo il controllo alla coroutine che fa avanzare 
        //l'ordinamento per la seconda metà dell'array
        h2();
    }
 
    stampa(v, MAX);
    
}
 