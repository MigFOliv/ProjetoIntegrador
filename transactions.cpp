#include <iostream>
#include <unordered_map>
#include "account.h"

using namespace std;

extern unordered_map<string, Account> accounts;

void salvarContas();
void carregarContas();

void transferir(const string& remetente, const string& destinatario, double valor) {
    if (accounts.find(remetente) == accounts.end()) {
        cout << "❌ Remetente não encontrado!\n";
        return;
    }

    if (accounts.find(destinatario) == accounts.end()) {
        cout << "❌ Destinatário não encontrado!\n";
        return;
    }

    if (accounts[remetente].gastar(valor)) {
        accounts[destinatario].depositar(valor);
        cout << "✅ Transferência de " << valor << " Byte(s) para " << destinatario << " realizada com sucesso!\n";
        salvarContas();
    } else {
        cout << "❌ Saldo insuficiente para transferência.\n";
    }
}

bool levantar(const string& nome, double valor) {
    if (accounts.find(nome) == accounts.end()) {
        cout << "❌ Conta não encontrada!\n";
        return false;
    }

    if (accounts[nome].gastar(valor)) {
        salvarContas();
        return true;
    }

    return false;
}
