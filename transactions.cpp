#include <iostream>
#include <unordered_map>
#include "account.h"
using namespace std;

extern unordered_map<string, Account> accounts;
void salvarContas();
void carregarContas();

void transferir(string remetente, string destinatario, double valor) {
    if (accounts.find(remetente) == accounts.end()) {
        cout << "❌ Conta do remetente não encontrada!\n";
        return;
    }

    if (accounts.find(destinatario) == accounts.end()) {
        cout << "❌ Conta do destinatário não encontrada!\n";
        return;
    }

    if (accounts[remetente].gastar(valor)) {
        accounts[destinatario].depositar(valor);
        cout << "✅ Transferência de " << valor << " Byte(s) para " << destinatario << " realizada com sucesso!\n";
        salvarContas();
    }
}

int main() {
    carregarContas();

    int escolha;
    string remetente, destinatario;
    double valor;

    while (true) {
        cout << "\nEscolha uma opção:\n";
        cout << "1. Transferir Bytes\n";
        cout << "2. Sair\n";
        cout << "➡️ Escolha: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                cout << "Digite o nome da conta do remetente: ";
                cin >> remetente;
                cout << "Digite o nome da conta do destinatário: ";
                cin >> destinatario;
                cout << "Digite o valor para transferir: ";
                cin >> valor;
                transferir(remetente, destinatario, valor);
                break;

            case 2:
                cout << "👋 Obrigado por usar o sistema Byte! Até logo.\n";
                return 0;

            default:
                cout << "❗ Opção inválida. Tente novamente.\n";
        }
    }

    return 0;
}
