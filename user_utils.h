#ifndef USER_UTILS_H
#define USER_UTILS_H

#include <string>
using namespace std;

void criarConta(const string& nome, const string& telemovel, const string& password);
bool autenticarConta(const string& nome, const string& password);
void depositar(const string& nome, double valor);
double obterSaldo(const string& nome);

#endif
