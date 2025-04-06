#include <iostream>
#include "utils.h"
#include "analizador.h"

string sinSaltos(const string &str)
{
    string res = str;
    res.erase(remove(res.begin(), res.end(), '\n'), res.end());
    return res;
}

void verificarYMostrar(const string &transmissionOriginal, const string &mcodeOriginal)
{
    string transmissionLower = toLower(transmissionOriginal);
    string mcodeLower = toLower(mcodeOriginal);

    int pos;
    bool encontrado = buscarCodigo(transmissionLower, mcodeLower, pos);
    if (encontrado)
        std::cout << "true " << (pos + 1) << std::endl;
    else
        std::cout << "false" << std::endl;
}

int main()
{
    // Leer archivos
    string t1 = leerArchivo("transmission1.txt");
    string t2 = leerArchivo("transmission2.txt");
    string m1 = leerArchivo("mcode1.txt");
    string m2 = leerArchivo("mcode2.txt");
    string m3 = leerArchivo("mcode3.txt");

    // Parte 1
    verificarYMostrar(t1, m1);
    verificarYMostrar(t1, m2);
    verificarYMostrar(t1, m3);
    verificarYMostrar(t2, m1);
    verificarYMostrar(t2, m2);
    verificarYMostrar(t2, m3);

    // Parte 2
    int start1, end1, start2, end2;
    string pal1, pal2;
    tie(start1, end1, pal1) = encontrarPalindromoMasLargo(t1);
    tie(start2, end2, pal2) = encontrarPalindromoMasLargo(t2);

    std::cout << start1 << " " << end1 << " " << sinSaltos(pal1) << std::endl;
    std::cout << start2 << " " << end2 << " " << sinSaltos(pal2) << std::endl;

    // Parte 3
    int commonStart, commonEnd;
    string substringComun;
    tie(commonStart, commonEnd, substringComun) = substringComunMasLargo(t1, t2);

    std::cout << commonStart << " " << commonEnd << " " << substringComun;

    return 0;
}
