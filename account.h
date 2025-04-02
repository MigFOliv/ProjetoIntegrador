#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
private:
    string nome;
    double saldo;

public:
    Account();
    explicit Account(const string& nome);

    void depositar(double valor);
    bool gastar(double valor);
    void exibirSaldo() const;
    double getSaldo() const;
    string getNome() const;
    void setSaldo(double valor);
};

#endif
