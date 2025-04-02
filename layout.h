#pragma once
#include <string>

enum class AppState {
    INICIO,
    CRIAR_CONTA,
    LOGIN,
    MENU_CONTA
};

void layout(std::string& conta_atual, std::string& mensagem, double& valor,
            char (&nome)[128], char (&telemovel)[128], char (&password)[128],
            char (&destinatario)[128], double& valor_transferencia,
            AppState& estado_atual);
