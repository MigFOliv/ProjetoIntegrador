#include "imgui.h"
#include <string>
#include <unordered_map>
#include "account.h"

using namespace std;

extern unordered_map<string, Account> accounts;

void criarConta(const string& nome, const string& telemovel, const string& password);
bool autenticarConta(const string& nome, const string& password);
void depositar(const string& nome, double valor);
double obterSaldo(const string& nome);
void transferir(const string& remetente, const string& destinatario, double valor);
bool levantar(const string& nome, double valor);

enum class AppState {
    INICIO,
    CRIAR_CONTA,
    LOGIN,
    MENU_CONTA
};

void BotaoCentralizado(const char* label, ImVec2 tamanho) {
    float x = (ImGui::GetWindowSize().x - tamanho.x) * 0.5f;
    ImGui::SetCursorPosX(x);
    ImGui::Button(label, tamanho);
}

void layout(string& conta_atual, string& mensagem, double& valor,
            char (&nome)[128], char (&telemovel)[128], char (&password)[128],
            char (&destinatario)[128], double& valor_transferencia,
            AppState& estado_atual) {

    ImGui::SetNextWindowSize(ImVec2(600, 550), ImGuiCond_Always);
    ImGui::Begin("ByteBank Interface", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    switch (estado_atual) {
    case AppState::INICIO:
        ImGui::Text("Bem-vindo ao ByteBank");
        BotaoCentralizado("Criar Conta", ImVec2(250, 40));
        if (ImGui::IsItemClicked()) {
            estado_atual = AppState::CRIAR_CONTA;
            mensagem.clear();
        }
        BotaoCentralizado("Iniciar Sessao", ImVec2(250, 40));
        if (ImGui::IsItemClicked()) {
            estado_atual = AppState::LOGIN;
            mensagem.clear();
        }
        BotaoCentralizado("Sair", ImVec2(250, 40));
        if (ImGui::IsItemClicked()) {
            exit(0);
        }
        break;

    case AppState::CRIAR_CONTA:
        ImGui::Text("Criacao de Conta");
        ImGui::InputText("Nome", nome, IM_ARRAYSIZE(nome));
        ImGui::InputText("Telemovel", telemovel, IM_ARRAYSIZE(telemovel));
        ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

        BotaoCentralizado("Confirmar Criacao", ImVec2(250, 40));
        if (ImGui::IsItemClicked()) {
            if (string(nome).empty() || string(telemovel).empty() || string(password).empty()) {
                mensagem = "Preencha todos os campos.";
            } else if (accounts.find(nome) != accounts.end()) {
                mensagem = "Conta ja existe.";
            } else {
                criarConta(nome, telemovel, password);
                conta_atual = nome;
                estado_atual = AppState::MENU_CONTA;
                mensagem = "Conta criada com sucesso!";
            }
        }
        BotaoCentralizado("Voltar", ImVec2(120, 40));
        if (ImGui::IsItemClicked()) {
            estado_atual = AppState::INICIO;
        }
        break;

    case AppState::LOGIN:
        ImGui::Text("Login da Conta");
        ImGui::InputText("Nome", nome, IM_ARRAYSIZE(nome));
        ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

        BotaoCentralizado("Entrar", ImVec2(250, 40));
        if (ImGui::IsItemClicked()) {
            if (autenticarConta(nome, password)) {
                conta_atual = nome;
                estado_atual = AppState::MENU_CONTA;
                mensagem = "Login bem-sucedido!";
            } else {
                mensagem = "Credenciais incorretas.";
            }
        }
        BotaoCentralizado("Voltar", ImVec2(120, 40));
        if (ImGui::IsItemClicked()) {
            estado_atual = AppState::INICIO;
        }
        break;

    case AppState::MENU_CONTA:
        ImGui::Text("Conta Ativa: %s", conta_atual.c_str());
        ImGui::InputDouble("Valor", &valor);

        BotaoCentralizado("Depositar", ImVec2(180, 40));
        if (ImGui::IsItemClicked()) {
            depositar(conta_atual, valor);
            mensagem = "Deposito realizado.";
        }

        BotaoCentralizado("Levantar", ImVec2(180, 40));
        if (ImGui::IsItemClicked()) {
            if (levantar(conta_atual, valor))
                mensagem = "Levantamento realizado.";
            else
                mensagem = "Saldo insuficiente.";
        }

        BotaoCentralizado("Mostrar Saldo", ImVec2(250, 40));
        if (ImGui::IsItemClicked()) {
            double saldo = obterSaldo(conta_atual);
            mensagem = "Saldo atual: " + to_string(saldo) + " bytes.";
        }

        ImGui::InputText("Destinatario", destinatario, IM_ARRAYSIZE(destinatario));
        ImGui::InputDouble("Valor Transferencia", &valor_transferencia);

        BotaoCentralizado("Transferir", ImVec2(250, 40));
        if (ImGui::IsItemClicked()) {
            if (string(destinatario).empty()) {
                mensagem = "Destinatario invalido.";
            } else {
                transferir(conta_atual, destinatario, valor_transferencia);
                mensagem = "Transferencia realizada.";
            }
        }

        BotaoCentralizado("Terminar Sessao", ImVec2(250, 40));
        if (ImGui::IsItemClicked()) {
            conta_atual.clear();
            estado_atual = AppState::INICIO;
            mensagem = "Sessao encerrada.";
        }
        break;
    }

    ImGui::Spacing();
    ImGui::TextWrapped("%s", mensagem.c_str());

    ImGui::End();
}
