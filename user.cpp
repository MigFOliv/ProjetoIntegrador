#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>
#include "account.h"
#include "layout.h"

using namespace std;

extern unordered_map<string, Account> accounts;

void salvarContas();
void carregarContas();
void criarConta(const string& nome, const string& telemovel, const string& password);
bool autenticarConta(const string& nome, const string& password);
void depositar(const string& nome, double valor);
double obterSaldo(const string& nome);
void transferir(const string& remetente, const string& destinatario, double valor);
bool levantar(const string& nome, double valor);

int main() {
    carregarContas();

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Sistema Byte", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    
    ImVec4* colors = style.Colors;
    
    // Fundo azul bebê
    colors[ImGuiCol_WindowBg]         = ImVec4(0.70f, 0.85f, 0.95f, 1.00f);
    
    // Texto padrão branco
    colors[ImGuiCol_Text]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    
    // Botões vermelhos com texto branco
    colors[ImGuiCol_Button]           = ImVec4(0.90f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ButtonHovered]    = ImVec4(1.00f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_ButtonActive]     = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
    
    // Outros elementos visuais
    colors[ImGuiCol_FrameBg]          = ImVec4(0.90f, 0.95f, 1.00f, 1.00f); // campos input azul muito claro
    colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.85f, 0.90f, 1.00f, 1.00f);
    colors[ImGuiCol_TitleBg]          = ImVec4(0.40f, 0.60f, 0.80f, 1.00f);
    colors[ImGuiCol_TitleBgActive]    = ImVec4(0.30f, 0.50f, 0.70f, 1.00f);
    colors[ImGuiCol_Header]           = ImVec4(0.90f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_HeaderHovered]    = ImVec4(1.00f, 0.30f, 0.30f, 1.00f);
    


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    char nome[128] = "";
    char telemovel[128] = "";
    char password[128] = "";
    char destinatario[128] = "";
    double valor = 0.0;
    double valor_transferencia = 0.0;
    string mensagem = "";
    string conta_atual = "";
    AppState estado_atual = AppState::INICIO;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        layout(conta_atual, mensagem, valor,
               nome, telemovel, password,
               destinatario, valor_transferencia,
               estado_atual);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}