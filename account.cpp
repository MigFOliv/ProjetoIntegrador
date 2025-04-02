#include <iostream>
#include "account.h"
using namespace std;

Account::Account() : nome(""), saldo(0), telemovel(""), password("") {}

Account::Account(const string& nome, const string& tel, const string& pass)
    : nome(nome), saldo(0), telemovel(tel), password(pass) {}

void Account::depositar(double valor) {
    saldo += valor;
    cout << "✅ " << valor << " Byte(s) depositados com sucesso! Saldo atual: " << saldo << " Byte(s)\n";
}

bool Account::gastar(double valor) {
    if (valor > saldo) {
        cout << "❌ Saldo insuficiente. Seu saldo é de " << saldo << " Byte(s).\n";
        return false;
    }
    saldo -= valor;
    cout << "✅ " << valor << " Byte(s) gastos com sucesso! Saldo atual: " << saldo << " Byte(s)\n";
    return true;
}

void Account::exibirSaldo() const {
    cout << "💰 Saldo de " << nome << ": " << saldo << " Byte(s)\n";
}

double Account::getSaldo() const {
    return saldo;
}

string Account::getNome() const {
    return nome;
}

string Account::getTelemovel() const {
    return telemovel;
}

string Account::getPassword() const {
    return password;
}

void Account::setSaldo(double valor) {
    saldo = valor;
}

void Account::setTelemovel(const string& tel) {
    telemovel = tel;
}

void Account::setPassword(const string& pass) {
    password = pass;
}
