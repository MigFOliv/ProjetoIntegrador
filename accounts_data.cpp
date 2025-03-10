#include <unordered_map>
#include <fstream>
#include <sstream>
#include "account.h"
using namespace std;

unordered_map<string, Account> accounts;

void salvarContas() {
    ofstream file("accounts_data.txt");
    for (const auto& [nome, conta] : accounts) {
        file << nome << " " << conta.getSaldo() << endl;
    }
    file.close();
}

void carregarContas() {
    ifstream file("accounts_data.txt");
    string nome;
    double saldo;

    while (file >> nome >> saldo) {
        accounts[nome] = Account(nome);
        accounts[nome].setSaldo(saldo);
    }
    file.close();
}
