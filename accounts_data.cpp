#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "account.h"

using namespace std;

// definição correta da variável global
unordered_map<string, Account> accounts;

void salvarContas() {
    ofstream file("accounts_data.txt");
    if (!file) {
        cerr << "❌ Erro ao salvar ficheiro das contas!\n";
        return;
    }

    for (const auto& [nome, conta] : accounts) {
        file << nome << " " << conta.getSaldo() << endl;
    }

    file.close();
}

void carregarContas() {
    ifstream file("accounts_data.txt");
    if (!file) {
        cerr << "⚠️ Ficheiro de contas não encontrado. Começando sem dados anteriores.\n";
        return;
    }

    string nome;
    double saldo;

    while (file >> nome >> saldo) {
        Account conta(nome);
        conta.setSaldo(saldo);
        accounts[nome] = conta;
    }

    file.close();
}
