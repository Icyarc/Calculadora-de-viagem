#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include <sstream>
#include <algorithm>

using namespace std;

double ler_double(const string& prompt) {
    double valor;
    cout << prompt;
    while (!(cin >> valor)) {
        cout << "Entrada invalida. Por favor, digite um numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return valor;
}

void salvar_relatorio(const string& relatorio) {
    ofstream arquivo("historico_viagens.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << relatorio << "\n";
        arquivo.close();
        cout << "\nRelatorio da viagem foi salvo em historico_viagens.txt" << endl;
    } else {
        cout << "Erro ao tentar salvar o relatorio." << endl;
    }
}

void pausar_console() {
    cout << "\nPressione ENTER para fechar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    double distancia_viagem, consumo_carro, preco_gasolina, velocidade_media, orcamento, tempo_limite, tanque_litros;

    cout << fixed << setprecision(2);

    cout << "\n--- Calculadora de Viagem ---\n";
    cout << "Digite os dados do seu carro e da viagem:\n\n";

    distancia_viagem = ler_double("Qual a distancia da viagem (km)? ");
    consumo_carro = ler_double("Qual o consumo do carro (km/l)? ");
    tanque_litros = ler_double("Quantos litros cabem no tanque? ");
    preco_gasolina = ler_double("Qual o preco da gasolina (R$/litro)? ");
    velocidade_media = ler_double("Qual sera a velocidade media (km/h)? ");
    orcamento = ler_double("Qual o orcamento para a viagem (R$)? ");
    tempo_limite = ler_double("Qual o tempo maximo para a viagem (em horas)? ");


    double total_litros = distancia_viagem / consumo_carro;
    double custo_final = total_litros * preco_gasolina;
    double tempo_final = distancia_viagem / velocidade_media;

    double autonomia_total = consumo_carro * tanque_litros;
    int paradas_combustivel = 0;
    if (autonomia_total > 0) {
        paradas_combustivel = ceil(distancia_viagem / autonomia_total) - 1;
    }
    if (paradas_combustivel < 0) paradas_combustivel = 0;

    int paradas_descanso = floor(tempo_final / 2);

    bool orcamento_ok = orcamento >= custo_final;
    bool tempo_ok = tempo_final <= tempo_limite;

    double vel_eco = max(40.0, velocidade_media - 20);
    double consumo_eco = consumo_carro * 1.10;
    double custo_eco = (distancia_viagem / consumo_eco) * preco_gasolina;
    double tempo_eco = distancia_viagem / vel_eco;

    double vel_rap = velocidade_media + 20;
    double consumo_rap = consumo_carro * 0.90;
    double custo_rap = (distancia_viagem / consumo_rap) * preco_gasolina;
    double tempo_rap = distancia_viagem / vel_rap;

    cout << "\n===== Resumo do seu Plano de Viagem =====\n";
    cout << "Tempo total de viagem: " << tempo_final << " horas\n";
    cout << "Total de combustivel: " << total_litros << " L\n";
    cout << "Custo total da viagem: R$ " << custo_final << "\n";
    cout << "Paradas para abastecer: " << paradas_combustivel << "\n";
    cout << "Paradas para descanso: " << paradas_descanso << "\n";

    cout << "\n--- Checagem de Recursos ---\n";
    if (!orcamento_ok)
        cout << "-> ATENCAO: Vai faltar dinheiro! (Falta R$ " << (custo_final - orcamento) << ")\n";
    else
        cout << "-> Seu orcamento e suficiente para a viagem!\n";

    if (!tempo_ok)
        cout << "-> ATENCAO: Voce nao tem tempo suficiente! (Vai passar " << (tempo_final - tempo_limite) << " h do limite)\n";
    else
        cout << "-> O tempo e suficiente para a viagem!\n";

    cout << "\n--- Simulacao de Rotas Alternativas ---\n";
    cout << "1. Rota Economica: Vel " << vel_eco << " km/h | Custo R$ " << custo_eco << " | Tempo " << tempo_eco << " h\n";
    cout << "2. Rota Rapida   : Vel " << vel_rap << " km/h | Custo R$ " << custo_rap << " | Tempo " << tempo_rap << " h\n";

    cout << "\n>>> Minha Sugestao: ";
    if (orcamento_ok && tempo_ok) {
        cout << "Seu plano original funciona. Se quiser, a ROTA ECONOMICA pode te poupar R$ " << (custo_final - custo_eco) << ".\n";
    } else if (custo_eco <= orcamento && tempo_eco <= tempo_limite) {
        cout << "Seu plano nao funciona, mas a ROTA ECONOMICA e uma boa opcao!\n";
    } else if (custo_rap <= orcamento && tempo_rap <= tempo_limite) {
        cout << "Seu plano nao funciona, mas a ROTA RAPIDA pode ser uma alternativa!\n";
    } else {
        cout << "Nenhuma das rotas parece funcionar com seu orcamento e tempo. E melhor rever o plano.\n";
    }

    stringstream ss;
    ss << fixed << setprecision(2);
    ss << "Distancia: " << distancia_viagem << " km"
       << " | Custo: R$ " << custo_final
       << " | Tempo: " << tempo_final << " h"
       << " | Paradas Abastecer: " << paradas_combustivel
       << " | Paradas Descanso: " << paradas_descanso
       << " | Orcamento OK: " << (orcamento_ok ? "Sim" : "Nao")
       << " | Tempo OK: " << (tempo_ok ? "Sim" : "Nao");

    string relatorio_final = ss.str();

    salvar_relatorio(relatorio_final);

    pausar_console();
    return 0;
}

