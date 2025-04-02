#include "user_utils.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <string>
#include <iostream>

#include "account.h"

using namespace std;

// Variável global (definida em accounts_data.cpp)
extern unordered_map<string, Account> accounts;

// Protótipos das funções auxiliares
void salvarContas();
void carregarContas();
void criarConta(const string& nome);
void depositar(const string& nome, double valor);
double obterSaldo(const string& nome);

int main() {
    carregarContas();

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Sistema Byte 💸", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Variáveis da interface
    char nome[128] = "";
    double valor = 0.0;
    string mensagem = "";
    string conta_atual = "";

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Janela principal
        ImGui::Begin("💸 Sistema Byte", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("🧾 Bem-vindo ao Sistema Byte");
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Janela interna
        ImGui::BeginChild("content", ImVec2(400, 220), true, ImGuiWindowFlags_NoScrollbar);

        if (conta_atual.empty()) {
            ImGui::Text("🔐 Login / Criar Conta");
            ImGui::Spacing();
            ImGui::InputText("👤 Nome da Conta", nome, IM_ARRAYSIZE(nome));

            ImGui::Spacing();

            if (ImGui::Button("🆕 Criar Conta", ImVec2(180, 0))) {
                if (string(nome).empty()) {
                    mensagem = "❌ Nome inválido.";
                } else {
                    criarConta(string(nome));
                    conta_atual = nome;
                    mensagem = "✅ Conta criada e acessada.";
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("➡️ Acessar Conta", ImVec2(180, 0))) {
                if (accounts.find(nome) != accounts.end()) {
                    conta_atual = nome;
                    mensagem = "✅ Conta acessada.";
                } else {
                    mensagem = "❌ Conta não encontrada.";
                }
            }

        } else {
            ImGui::Text("👤 Conta atual: %s", conta_atual.c_str());
            ImGui::Spacing();
            ImGui::InputDouble("💰 Valor (Bytes)", &valor);

            ImGui::Spacing();

            if (ImGui::Button("➕ Depositar", ImVec2(120, 0))) {
                if (valor <= 0.0) {
                    mensagem = "❌ Valor inválido para depósito.";
                } else {
                    depositar(conta_atual, valor);
                    mensagem = "✅ Depósito realizado.";
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("📊 Ver Saldo", ImVec2(120, 0))) {
                double saldo = obterSaldo(conta_atual);
                mensagem = "💰 Saldo: " + to_string(saldo) + " bytes.";
            }

            ImGui::Spacing();

            if (ImGui::Button("↩️ Sair da Conta", ImVec2(250, 0))) {
                conta_atual = "";
                mensagem = "🔁 Conta encerrada.";
            }
        }

        ImGui::EndChild();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::TextWrapped("%s", mensagem.c_str());

        ImGui::Spacing();
        if (ImGui::Button("❌ Fechar Programa", ImVec2(400, 0))) {
            glfwSetWindowShouldClose(window, true);
        }

        ImGui::End();

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
