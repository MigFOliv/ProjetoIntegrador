#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
private:
    string nome;
    double saldo;
    string telemovel;
    string password;

public:
    Account();
    Account(const string& nome, const string& tel, const string& pass);

    void depositar(double valor);
    bool gastar(double valor);
    void exibirSaldo() const;
    double getSaldo() const;

    string getNome() const;
    string getTelemovel() const;
    string getPassword() const;

    void setSaldo(double valor);
    void setTelemovel(const string& tel);
    void setPassword(const string& pass);
};

#endif
