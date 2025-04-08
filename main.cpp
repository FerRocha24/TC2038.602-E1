#include <iostream>
#include <chrono>
#include "utils.h"
#include "analizador.h"

std::string sinSaltos(const std::string &str)
{
    std::string res = str;
    res.erase(std::remove(res.begin(), res.end(), '\n'), res.end());
    return res;
}

void verificarYMostrar(const std::string &transmissionOriginal, const std::string &mcodeOriginal)
{
    std::string transmissionLower = toLower(transmissionOriginal);
    std::string mcodeLower = toLower(mcodeOriginal);

    int pos;
    bool encontrado = buscarCodigo(transmissionLower, mcodeLower, pos);
    if (encontrado)
        std::cout << "\033[1;32mtrue\033[0m " << (pos + 1) << std::endl;
    else
        std::cout << "\033[1;31mfalse\033[0m" << std::endl;
}

void medirTiempo(const std::string &nombre, const std::function<void()> &func)
{
    auto inicio = std::chrono::high_resolution_clock::now();
    func();
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    std::cout << "\n\033[1;34m[Tiempo de ejecución - " << nombre << "]: " 
              << duracion.count() << " segundos\033[0m\n" << std::endl;
}

int main()
{
    std::cout << "== CARGANDO ARCHIVOS ==" << std::endl;

    std::string t1 = leerArchivo("transmission1.txt");
    std::string t2 = leerArchivo("transmission2.txt");
    std::string m1 = leerArchivo("mcode1.txt");
    std::string m2 = leerArchivo("mcode2.txt");
    std::string m3 = leerArchivo("mcode3.txt");

    if (t1.empty() || t2.empty() || m1.empty() || m2.empty() || m3.empty()) {
        std::cerr << "Error al leer uno o más archivos." << std::endl;
        return 1;
    }

    std::cout << "\n== PARTE 1: Verificar códigos ==" << std::endl;
    medirTiempo("Parte 1", [&]() {
        verificarYMostrar(t1, m1);
        verificarYMostrar(t1, m2);
        verificarYMostrar(t1, m3);
        verificarYMostrar(t2, m1);
        verificarYMostrar(t2, m2);
        verificarYMostrar(t2, m3);
    });

    std::cout << "== PARTE 2: Palíndromos más largos ==" << std::endl;
    medirTiempo("Parte 2", [&]() {
        int start1, end1, start2, end2;
        std::string pal1, pal2;

        std::tie(start1, end1, pal1) = encontrarPalindromoMasLargo(t1);
        std::tie(start2, end2, pal2) = encontrarPalindromoMasLargo(t2);

        std::cout << "Archivo 1: " << start1 << " " << end1 << " " << sinSaltos(pal1) << std::endl;
        std::cout << "Archivo 2: " << start2 << " " << end2 << " " << sinSaltos(pal2) << std::endl;
    });

    std::cout << "== PARTE 3: Substring común más largo ==" << std::endl;
    medirTiempo("Parte 3", [&]() {
        int commonStart, commonEnd;
        std::string substringComun;
        std::tie(commonStart, commonEnd, substringComun) = substringComunMasLargo(t1, t2);

        std::cout << commonStart << " " << commonEnd << " " << sinSaltos(substringComun) << std::endl;
    });

    std::cout << "\n== FIN DEL PROGRAMA ==" << std::endl;
    return 0;
}
