#include <iostream>
#include <unordered_map>
#include "account.h"
using namespace std;

extern unordered_map<string, Account> accounts;
void salvarContas();
void carregarContas();

void criarConta(const string& nome) {
    if (accounts.find(nome) != accounts.end()) {
        cout << "❌ Essa conta já existe!\n";
        return;
    }
    accounts[nome] = Account(nome);
    cout << "✅ Conta criada para " << nome << " com sucesso!\n";
    salvarContas();
}

void depositar(const string& nome, double valor) {
    if (accounts.find(nome) == accounts.end()) {
        cout << "❌ Conta não encontrada!\n";
        return;
    }
    accounts[nome].depositar(valor);
    salvarContas();
}

void exibirSaldo(const string& nome) {
    if (accounts.find(nome) == accounts.end()) {
        cout << "❌ Conta não encontrada!\n";
        return;
    }
    accounts[nome].exibirSaldo();
}

int main() {
    carregarContas();

    int escolha;
    string nome;
    double valor;

    cout << "💸 Bem-vindo ao sistema Byte! 💸\n";

    while (true) {
        cout << "\nEscolha uma opção:\n";
        cout << "1. Criar Conta\n";
        cout << "2. Depositar Bytes\n";
        cout << "3. Exibir Saldo\n";
        cout << "4. Sair\n";
        cout << "➡️ Escolha: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                cout << "Digite o nome da conta: ";
                cin >> nome;
                criarConta(nome);
                break;

            case 2:
                cout << "Digite o nome da conta: ";
                cin >> nome;
                cout << "Digite o valor para depositar: ";
                cin >> valor;
                depositar(nome, valor);
                break;

            case 3:
                cout << "Digite o nome da conta: ";
                cin >> nome;
                exibirSaldo(nome);
                break;

            case 4:
                cout << "👋 Obrigado por usar o sistema Byte! Até logo.\n";
                return 0;

            default:
                cout << "❗ Opção inválida. Tente novamente.\n";
        }
    }

    return 0;
}
