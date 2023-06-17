
#include <iostream>
#include <sstream>
#include <numbers>
#include <format>
#include <chrono>
#include <iomanip>
#include <string>
#include <fstream>
#include <string_view>


int getTotale() { return 100; }

std::string f() { return "terzo placeholder"; }

int main()
{
	// metodo per creare una stringa
	std::stringstream ss;
	ss << "prima parte, "
		<< "part2 "
		<< getTotale()
		<< "confronto con "
		<< std::numbers::pi
		<< std::endl;

	std::string s = ss.str();
	std::cout << s << std::endl;

	const std::string s1 = "primo placheholder";
	const std::string s2 = "secondo placheholder";
	const std::string s3 = "primo placheholder";

	std::string s4 = std::format("{} parte fissa {}, {}\n",s1,s2,f());
	std::cout << s4 << std::endl;

	for (int i = 1; i < 21; i++)
	{
		// <10 allignamento a sx
		// >10 allignamento a dx di default
		// ^10 allignamento centrato
		// #10x -> formato esadecimale
		// supporta anche il pedding
		// https://fmt.dev/latest/syntax.html

		std::cout << std::format("{0:^10} {1:^10}\n", i * i, i * i * i);
	}

	auto ora = std::chrono::system_clock::now();
	std::cout << std::format("{:%d-%m-%Y %H:%m}\n", ora);

	/*
	std::ofstream file  {"dati.txt"};
	std::format_to(std::ostream_iterator<char>(file), "prova, {}!", s3);
	file.close();
	*/

	std::string frase = "Oggi c'e' un bel sole e non piove";
	// Nuova specifica che ti permettte di creare una variabile locale dentro al if
	// questo permette di non ingombrare lo spazio globale delle variabili
	if (const auto it = frase.find("sole"); it != std::string::npos)
		std::cout << "Trovato sole \n";

	std::ifstream leggi("catalogo.txt");

	int codice = 0;
	std::string titolo = "";
	double costo = 0;

	if (leggi)
		while (leggi >> codice >> std::quoted(titolo) >> costo)
			std::cout << std::format("Codice: {} - Titolo: {} - Costo: {}\n", codice, titolo, costo);
	else
		std::cout << "Errore apertura file\n";

	leggi.close();
	leggi.clear();




	return 0;
}