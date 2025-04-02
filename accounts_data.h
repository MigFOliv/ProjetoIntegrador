#pragma once
#include <unordered_map>
#include <string>
#include "account.h"

extern std::unordered_map<std::string, Account> accounts;

void salvarContas();
void carregarContas();
