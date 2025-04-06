#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <string>
#include <tuple>
#include <vector>
#include <fstream>

using namespace std;

inline string leerArchivo(const string &nombre)
{
    ifstream archivo(nombre);
    string linea, contenido;
    while (getline(archivo, linea))
    {
        contenido += linea + "\n"; // ✅ conservar saltos de línea
    }
    return contenido;
}

inline bool buscarCodigo(const string &transmission, const string &mcode, int &posicion)
{
    posicion = transmission.find(mcode);
    return posicion != string::npos;
}

inline tuple<int, int, string> encontrarPalindromoMasLargo(const string &texto)
{
    int maxLen = 0, inicio = 0;
    int n = texto.size();

    for (int i = 0; i < n; ++i)
    {
        int l = i, r = i;
        while (l >= 0 && r < n && texto[l] == texto[r])
        {
            if (r - l + 1 > maxLen)
            {
                maxLen = r - l + 1;
                inicio = l;
            }
            --l;
            ++r;
        }

        l = i;
        r = i + 1;
        while (l >= 0 && r < n && texto[l] == texto[r])
        {
            if (r - l + 1 > maxLen)
            {
                maxLen = r - l + 1;
                inicio = l;
            }
            --l;
            ++r;
        }
    }

    return make_tuple(inicio + 1, inicio + maxLen, texto.substr(inicio, maxLen));
}

inline tuple<int, int, string> substringComunMasLargo(const string &a, const string &b)
{
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    int maxLen = 0, endIdx = 0;

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (a[i - 1] == b[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen)
                {
                    maxLen = dp[i][j];
                    endIdx = i;
                }
            }

    return make_tuple(endIdx - maxLen + 1, endIdx, a.substr(endIdx - maxLen, maxLen));
}

#endif
