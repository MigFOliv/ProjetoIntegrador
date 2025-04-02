#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "account.h"

using namespace std;

// Definição da variável global
unordered_map<string, Account> accounts;

void salvarContas() {
    ofstream file("accounts_data.txt");
    if (!file) {
        cerr << "❌ Erro ao salvar ficheiro das contas!\n";
        return;
    }

    for (const auto& [nome, conta] : accounts) {
        file << nome << " "
             << conta.getSaldo() << " "
             << conta.getTelemovel() << " "
             << conta.getPassword() << "\n";
    }

    file.close();
}

void carregarContas() {
    ifstream file("accounts_data.txt");
    if (!file) {
        cerr << "⚠️ Ficheiro de contas não encontrado. Começando sem dados anteriores.\n";
        return;
    }

    string nome, tel, pass;
    double saldo;

    while (file >> nome >> saldo >> tel >> pass) {
        Account conta(nome, tel, pass);
        conta.setSaldo(saldo);
        accounts[nome] = conta;
    }

    file.close();
}
