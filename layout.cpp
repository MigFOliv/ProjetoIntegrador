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

void layout(string& conta_atual, string& mensagem, double& valor,
            char (&nome)[128], char (&telemovel)[128], char (&password)[128],
            char (&destinatario)[128], double& valor_transferencia,
            AppState& estado_atual) {

    ImGui::SetNextWindowSize(ImVec2(600, 550), ImGuiCond_Always);
    ImGui::Begin("ByteBank Interface", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    switch (estado_atual) {
    case AppState::INICIO:
        ImGui::Text("Bem-vindo ao ByteBank");
        if (ImGui::Button("Criar Conta", ImVec2(200, 0))) {
            estado_atual = AppState::CRIAR_CONTA;
            mensagem.clear();
        }
        if (ImGui::Button("Iniciar Sessao", ImVec2(200, 0))) {
            estado_atual = AppState::LOGIN;
            mensagem.clear();
        }
        if (ImGui::Button("Sair", ImVec2(200, 0))) {
            exit(0);
        }
        break;

    case AppState::CRIAR_CONTA:
        ImGui::Text("Criacao de Conta");
        ImGui::InputText("Nome", nome, IM_ARRAYSIZE(nome));
        ImGui::InputText("Telemovel", telemovel, IM_ARRAYSIZE(telemovel));
        ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

        if (ImGui::Button("Confirmar Criacao", ImVec2(200, 0))) {
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
        ImGui::SameLine();
        if (ImGui::Button("Voltar", ImVec2(100, 0))) {
            estado_atual = AppState::INICIO;
        }
        break;

    case AppState::LOGIN:
        ImGui::Text("Login da Conta");
        ImGui::InputText("Nome", nome, IM_ARRAYSIZE(nome));
        ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

        if (ImGui::Button("Entrar", ImVec2(200, 0))) {
            if (autenticarConta(nome, password)) {
                conta_atual = nome;
                estado_atual = AppState::MENU_CONTA;
                mensagem = "Login bem-sucedido!";
            } else {
                mensagem = "Credenciais incorretas.";
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Voltar", ImVec2(100, 0))) {
            estado_atual = AppState::INICIO;
        }
        break;

    case AppState::MENU_CONTA:
        ImGui::Text("Conta Ativa: %s", conta_atual.c_str());
        ImGui::InputDouble("Valor", &valor);

        if (ImGui::Button("Depositar", ImVec2(120, 0))) {
            depositar(conta_atual, valor);
            mensagem = "Deposito realizado.";
        }
        ImGui::SameLine();
        if (ImGui::Button("Levantar", ImVec2(120, 0))) {
            if (levantar(conta_atual, valor))
                mensagem = "Levantamento realizado.";
            else
                mensagem = "Saldo insuficiente.";
        }

        if (ImGui::Button("Mostrar Saldo", ImVec2(250, 0))) {
            double saldo = obterSaldo(conta_atual);
            mensagem = "Saldo atual: " + to_string(saldo) + " bytes.";
        }

        ImGui::InputText("Destinatario", destinatario, IM_ARRAYSIZE(destinatario));
        ImGui::InputDouble("Valor Transferencia", &valor_transferencia);

        if (ImGui::Button("Transferir", ImVec2(250, 0))) {
            if (string(destinatario).empty()) {
                mensagem = "Destinatario invalido.";
            } else {
                transferir(conta_atual, destinatario, valor_transferencia);
                mensagem = "Transferencia realizada.";
            }
        }

        if (ImGui::Button("Terminar Sessao", ImVec2(250, 0))) {
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