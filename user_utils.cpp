
#include "user_utils.h"  
#include "account.h"
#include <unordered_map>
#include <string>
using namespace std;

extern unordered_map<string, Account> accounts;

void salvarContas();

void criarConta(const string& nome) {
    if (accounts.find(nome) != accounts.end()) return;
    accounts[nome] = Account(nome);
    salvarContas();
}

void depositar(const string& nome, double valor) {
    if (accounts.find(nome) == accounts.end()) return;
    accounts[nome].depositar(valor);
    salvarContas();
}

double obterSaldo(const string& nome) {
    if (accounts.find(nome) == accounts.end()) return 0.0;
    return accounts[nome].getSaldo();
}
