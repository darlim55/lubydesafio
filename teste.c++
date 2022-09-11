/*====================================
 *                 Loja
 *           Desenvolvido por:
 *               Jorge Silva
 * ====================================*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include "classes.h"
using namespace std;

/*===========================

** Funcoes usadas em termos gerais

*============================ */

/*Funcao para ajeitar a string que vem dos arquivos*/
string Replace(string nome)
{
  for (int i = 0; i < nome.length(); i++)
  {
    if (nome[i] == '_')
      nome[i] = ' ';
  }

  return nome;
}

/*Funcao para ajeitar a string que vai ser gravada nos arquivos txt*/
string Replace_inv(string nome)
{
  for (int i = 0; i < nome.length(); i++)
  {
    if (nome[i] == ' ')
      nome[i] = '_';
  }

  return nome;
}

/*Funcao que valida o id do item para nao ser cadastrado itens de mesmo id*/
bool Valida_identificador(int numero_identificador)
{
  fstream fout;
  int id, d, custo, unidade, valor;
  string linha;
  string nome;
  fout.open("estoque.txt", ios::in); // abre para escrita (ios::out)

  while (fout >> id >> d >> custo >> unidade >> linha >> valor)
  {

    if (numero_identificador == id)
    {
      fout.close();
      return true;
    }
  }

  fout.close();
  return false;
}

/*Funcao que valida o nome do item para nao ser cadastrado itens de mesmo nome*/
bool Valida_nome(string nome)
{
  fstream fout;
  int id, d, custo, unidade, valor;
  string linha, aux, aux2;
  aux2 = nome;
  fout.open("estoque.txt", ios::in); // abre para escrita (ios::out)

  while (fout >> id >> d >> custo >> unidade >> linha >> valor)
  {
    string aux = Replace(linha);

    transform(aux2.begin(), aux2.end(), aux2.begin(),
              [](unsigned char c)
              { return tolower(c); });

    transform(aux.begin(), aux.end(), aux.begin(),
              [](unsigned char c)
              { return tolower(c); });

    int x = (aux).compare(aux2);
    if (x == 0)
    {
      fout.close();
      return true;
    }
  }

  fout.close();
  return false;
}

/*Funcao que verifica o tipo de item pois esta cadastrado no arquivo os itens com um valor numerico */
int valida_tipo(string tipo)
{

  fstream fout;
  string aux2;
  aux2 = tipo;
  fout.open("estoque.txt", ios::in); // abre para escrita (ios::out)

  std::for_each(tipo.begin(), tipo.end(), [](char &c)
                { c = ::tolower(c); });

  if (aux2.compare("armamento") == 0)
  {
    fout.close();
    return 1;
  }
  else if (aux2.compare("armadura") == 0)
  {
    fout.close();
    return 2;
  }
  else if (aux2.compare("consumivel") == 0)
  {
    fout.close();
    return 3;
  }
  else
  {
    fout.close();
    return 0;
  }
}

/*============================================

* Funções usadas para operacoes com estoque

==============================================
*/

/*FUnção usada para cadastrar itens no estoque*/
void Cadastrar_itens()
{

  int numero_identificador, custo, unidade, escolha;
  string nome, tipo;
  cout << "Identificador (valor inteiro): " << endl;
  cin >> numero_identificador;
  if (numero_identificador == (int)numero_identificador)
    cout << "inteiro" << endl;
  else
    cout << "nao e inteiro" << endl;
  cout << endl;
  while (Valida_identificador(numero_identificador) == 1)
  {
    cout << "Id ja cadsatrado. Digite um novo (valor inteiro): " << endl;
    cin >> numero_identificador;
    cout << endl;
  }

  cout << "Nome do item (digite sem acentos ou ç): " << endl;
  cin.ignore();
  getline(cin, nome);
  cout << endl;

  while (Valida_nome(nome) == 1)
  {
    cout << "Nome do item ja cadastrado (digite sem acentos ou ç)digite novamente: " << endl;
    cin.ignore();
    getline(cin, nome);
    cout << endl;
  }

  cout << "Digite o tipo de item (Armamento, Armadura e Consumivel): " << endl;
  getline(cin, tipo);
  cout << endl;

  escolha = valida_tipo(tipo);
  while (valida_tipo(tipo) == 0)
  {
    cout << "Digite um tipo valido (Armamento, Armadura e Consumivel): " << endl;
    getline(cin, tipo);
    escolha = valida_tipo(tipo);
    cout << endl;
  }

  cout << "Custo em PO (Peças de Ouro -Valor inteiro): " << endl;
  cin >> custo;
  cout << endl;

  cout << "Digite as unidades disponiveis (Valor inteiro): " << endl;
  cin >> unidade;
  cout << endl;

  if (escolha == 1)
  {
    Armamentos item;
    int dano;
    cout << "Digite o dano do item (Valor inteiro): " << endl;
    cin >> dano;
    cout << endl;
    item.set_Numero_identificador(numero_identificador);
    item.set_Tipo(escolha);
    item.set_Custo(custo);
    item.set_Nome(nome);
    fstream fout;
    fout.open("estoque.txt", ios::app); // abre para escrita (ios::out)

    fout << item.get_Numero_identificador()
         << " " << item.get_Tipo() << " " << item.get_Custo() << " " << unidade << " "
         << Replace_inv(item.get_Nome())
         << " " << dano << endl;
    fout.close();
  }
  else if (escolha == 2)
  {
    Armaduras item;
    int armadura;
    cout << "Digite o valor da armadura (Valor inteiro): " << endl;
    cin >> armadura;
    cout << endl;
    item.set_Numero_identificador(numero_identificador);
    item.set_Tipo(escolha);
    item.set_Custo(custo);
    item.set_Nome(nome);
    fstream fout;
    fout.open("estoque.txt", ios::app); // abre para escrita (ios::out)

    fout << item.get_Numero_identificador()
         << " " << item.get_Tipo() << " " << item.get_Custo() << " " << unidade << " "
         << Replace_inv(item.get_Nome())
         << " " << armadura << endl;
    fout.close();
  }
  else
  {
    Consumiveis item;
    int qtd;
    cout << "Digite o valor dos usos (Valor inteiro): " << endl;
    cin >> qtd;
    cout << endl;
    item.set_Numero_identificador(numero_identificador);
    item.set_Tipo(escolha);
    item.set_Custo(custo);
    item.set_Nome(nome);
    fstream fout;
    fout.open("estoque.txt", ios::app); // abre para escrita (ios::out)

    fout << item.get_Numero_identificador()
         << " " << item.get_Tipo() << " " << item.get_Custo() << " " << unidade << " "
         << Replace_inv(item.get_Nome())
         << " " << qtd << endl;
    fout.close();
  }
}

/*Lista todos os itens do estoque*/
void Lista_itens()
{

  fstream fout;
  int id, custo, unidade, escolha, valor;
  string nome, tipo;
  fout.open("estoque.txt", ios::in); // abre para escrita (ios::out)

  while (fout >> id >> escolha >> custo >> unidade >> nome >> valor)
  {
    cout << "Id do item: " << id << endl;
    if (escolha == 1)
    {
      cout << "Tipo item: Armanento" << endl;
      cout << "Dano causado: " << valor << endl;
    }

    else if (escolha == 2)
    {
      cout << "Tipo item: Armadura" << endl;
      cout << "Dano absorvido (Armadura): " << valor << endl;
    }

    else
    {
      cout << "Tipo item: consumivel" << endl;
      cout << "Quantiadde uso (Consumivel): " << valor << endl;
    }

    cout << "Valor em peças de ouro: " << custo << endl;
    cout << "Quantidade disponivel para venda: " << unidade << endl;
    cout << "Nome do item: " << Replace(nome) << endl;
    cout << endl;
  }

  fout.close();
  cout << endl;
}

/*Registra as mudanças no estoque seja exclusão ou modificação das unidades de um item*/
void Registra_mudanca(Armadura_Jogo vtr, Armanentos_Jogo vta, Consumiveis_Jogo vtc, int opcao, int num)
{
  fstream fout;
  int i;
  int maior = (vta.num > vtr.num) ? (vta.num > vtc.num ? vta.num : vtc.num) : (vtr.num > vtc.num ? vtr.num : vtc.num);
  fout.open("estoque.txt", ios::out);

  if (opcao == 3)
  {
    int unidade;
    cout << "Digite as unidade disponiveis para o item" << endl;
    cin >> unidade;

    for (i = 0; i < maior; i++)
    {
      if (vta.num > i)
      {
        if (num == vta.itens[i].get_Numero_identificador())
        {
          fout << vta.itens[i].get_Numero_identificador()
               << " " << vta.itens[i].get_Tipo() << " " << vta.itens[i].get_Custo() << " " << unidade << " "
               << vta.itens[i].get_Nome()
               << " " << vta.itens[i].get_dano() << endl;
        }
        else
        {
          fout << vta.itens[i].get_Numero_identificador()
               << " " << vta.itens[i].get_Tipo() << " " << vta.itens[i].get_Custo() << " " << vta.itens[i].get_unidade() << " "
               << vta.itens[i].get_Nome()
               << " " << vta.itens[i].get_dano() << endl;
        }
      }

      if (vtr.num > i)
      {

        if (num == vtr.itens[i].get_Numero_identificador())
        {
          fout << vtr.itens[i].get_Numero_identificador()
               << " " << vtr.itens[i].get_Tipo() << " " << vtr.itens[i].get_Custo() << " " << unidade << " "
               << vtr.itens[i].get_Nome()
               << " " << vtr.itens[i].get_Durabilidade() << endl;
        }
        else
        {
          fout << vtr.itens[i].get_Numero_identificador()
               << " " << vtr.itens[i].get_Tipo() << " " << vtr.itens[i].get_Custo() << " " << vtr.itens[i].get_unidade() << " "
               << vtr.itens[i].get_Nome()
               << " " << vtr.itens[i].get_Durabilidade() << endl;
        }
      }

      if (vtc.num > i)
      {

        if (num == vtc.itens[i].get_Numero_identificador())
        {
          fout << vtc.itens[i].get_Numero_identificador()
               << " " << vtc.itens[i].get_Tipo() << " " << vtc.itens[i].get_Custo() << " " << unidade << " "
               << vtc.itens[i].get_Nome()
               << " " << vtc.itens[i].get_carga() << endl;
        }
        else
        {
          fout << vtc.itens[i].get_Numero_identificador()
               << " " << vtc.itens[i].get_Tipo() << " " << vtc.itens[i].get_Custo() << " " << vtc.itens[i].get_unidade() << " "
               << vtc.itens[i].get_Nome()
               << " " << vtc.itens[i].get_carga() << endl;
        }
      }
    }
  }

  if (opcao == 2)
  {
    for (i = 0; i < maior; i++)
    {
      if (vta.num > i)
      {
        if (num != vta.itens[i].get_Numero_identificador())
        {
          fout << vta.itens[i].get_Numero_identificador()
               << " " << vta.itens[i].get_Tipo() << " " << vta.itens[i].get_Custo() << " " << vta.itens[i].get_unidade() << " "
               << vta.itens[i].get_Nome()
               << " " << vta.itens[i].get_dano() << endl;
        }
      }

      if (vtr.num > i)
      {

        if (num != vtr.itens[i].get_Numero_identificador())
        {
          fout << vtr.itens[i].get_Numero_identificador()
               << " " << vtr.itens[i].get_Tipo() << " " << vtr.itens[i].get_Custo() << " " << vtr.itens[i].get_unidade() << " "
               << vtr.itens[i].get_Nome()
               << " " << vtr.itens[i].get_Durabilidade() << endl;
        }
      }

      if (vtc.num > i)
      {

        if (num != vtc.itens[i].get_Numero_identificador())
        {
          fout << vtc.itens[i].get_Numero_identificador()
               << " " << vtc.itens[i].get_Tipo() << " " << vtc.itens[i].get_Custo() << " " << vtc.itens[i].get_unidade() << " "
               << vtc.itens[i].get_Nome()
               << " " << vtc.itens[i].get_carga() << endl;
        }
      }
    }
  }

  fout.close();
}

/*Função que exporta o estoque*/
void Export_estoque(Armadura_Jogo vtr, Armanentos_Jogo vta, Consumiveis_Jogo vtc)
{
  fstream fout;
  int i;
  int maior = (vta.num > vtr.num) ? (vta.num > vtc.num ? vta.num : vtc.num) : (vtr.num > vtc.num ? vtr.num : vtc.num);
  fout.open("export/estoque.txt", ios::out);
  for (i = 0; i < maior; i++)
  {
    if (vta.num > i)
    {
      fout << "Identificador item: " << vta.itens[i].get_Numero_identificador() << endl;
      fout << "Nome do item: " << vta.itens[i].get_Nome() << endl;
      fout << "Tipo de item: Armanento" << endl;
      fout << "Custo em peças de ouro: " << vta.itens[i].get_Custo() << endl;
      fout << "Quantidade disponivel: " << vta.itens[i].get_unidade() << endl;
      fout << "Dano causado pelo item: " << vta.itens[i].get_dano() << endl;
      fout << endl;
    }

    if (vtr.num > i)
    {
      fout << "Identificador item: " << vtr.itens[i].get_Numero_identificador() << endl;
      fout << "Nome do item: " << vtr.itens[i].get_Nome() << endl;
      fout << "Tipo de item: Armadura" << endl;
      fout << "Custo em peças de ouro: " << vtr.itens[i].get_Custo() << endl;
      fout << "Quantidade disponivel: " << vtr.itens[i].get_unidade() << endl;
      fout << "Armdura a mais: " << vtr.itens[i].get_Durabilidade() << endl;
      fout << endl;
    }

    if (vtc.num > i)
    {
      fout << "Identificador item: " << vtc.itens[i].get_Numero_identificador() << endl;
      fout << "Nome do item: " << vtc.itens[i].get_Nome() << endl;
      fout << "Tipo de item: Consumivel" << endl;
      fout << "Custo em peças de ouro: " << vtc.itens[i].get_Custo() << endl;
      fout << "Quantidade disponivel: " << vtc.itens[i].get_unidade() << endl;
      fout << "Quantas vezes o item pode ser usado: " << vtc.itens[i].get_carga() << endl;
      fout << endl;
    }
  }

  fout.close();
}

/*Função que e usada para modificar usadas*/
void Modifica_unidades(int selecionado)
{

  fstream fout;
  Armadura_Jogo vtr;
  Armanentos_Jogo vta;
  Consumiveis_Jogo vtc;

  int id, custo, unidade, escolha, valor, maior, num;
  string nome, tipo;
  fout.open("estoque.txt", ios::in); // abre para escrita (ios::out)

  while (fout >> id >> escolha >> custo >> unidade >> nome >> valor)
  {
    if (escolha == 1)
    {
      vta.itens[vta.num].set_Numero_identificador(id);
      vta.itens[vta.num].set_Tipo(escolha);
      vta.itens[vta.num].set_Custo(custo);
      vta.itens[vta.num].set_Nome(nome);
      vta.itens[vta.num].set_unidade(unidade);
      vta.itens[vta.num].set_dano(valor);
      vta.num = vta.num + 1;
    }
    else if (escolha == 2)
    {
      vtr.itens[vtr.num].set_Numero_identificador(id);
      vtr.itens[vtr.num].set_Tipo(escolha);
      vtr.itens[vtr.num].set_Custo(custo);
      vtr.itens[vtr.num].set_Nome(nome);
      vtr.itens[vtr.num].set_unidade(unidade);
      vtr.itens[vtr.num].set_Durabilidade(valor);
      vtr.num = vtr.num + 1;
    }
    else
    {
      vtc.itens[vtc.num].set_Numero_identificador(id);
      vtc.itens[vtc.num].set_Tipo(escolha);
      vtc.itens[vtc.num].set_Custo(custo);
      vtc.itens[vtc.num].set_Nome(nome);
      vtc.itens[vtc.num].set_unidade(unidade);
      vtc.itens[vtc.num].set_carga(valor);
      vtc.num = vtc.num + 1;
    }
  }
  fout.close();

  if (selecionado == 3)
  {
    cout << "Digite o identificador do item" << endl;
    cin >> num;
    if (Valida_identificador(num) == 1)
    {
      Registra_mudanca(vtr, vta, vtc, selecionado, num);
      cout << "Item modificado com sucesso" << endl;
      cout << endl;
    }
    else
    {
      cout << "Item nao identificado" << endl;
      cout << endl;
    }
  }

  if (selecionado == 2)
  {
    cout << "Digite o identificador do item" << endl;
    cin >> num;
    if (Valida_identificador(num) == 1)
    {
      Registra_mudanca(vtr, vta, vtc, selecionado, num);
      cout << "Item excluido com sucesso" << endl;
      cout << endl;
    }
    else
    {
      cout << "Item nao identificado" << endl;
      cout << endl;
    }
  }

  if (selecionado == 5)
  {
    Export_estoque(vtr, vta, vtc);
    cout << "Estoque exportado com sucesso (verifique pasta export)" << endl;
  }
}

/* Menu estoque */
void menu_estoque()
{

  int opcao, id;
  cout << "Estoque: " << endl;
  cout << "1 - Cadastro de Itens" << endl;
  cout << "2 - Remover um item" << endl;
  cout << "3 - Adicionar unidades" << endl;
  cout << "4 - Listar Itens" << endl;
  cout << "5 - Exportar estoque" << endl;
  cout << "Digite outro valor inteiro para voltar ao menu anterior" << endl;
  cin >> opcao;
  while (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5)
  {
    switch (opcao)
    {
    case 1:
      system("clear||cls");
      Cadastrar_itens();
      break;
    case 2:
      system("clear||cls");
      Modifica_unidades(2);
      break;
    case 3:
      system("clear||cls");
      cout << "Digite o identificador do item" << endl;
      cin >> id;
      Modifica_unidades(3);

      break;
    case 4:
      system("clear||cls");
      Lista_itens();

      break;
    case 5:
      system("clear||cls");
      Modifica_unidades(5);

      break;
    default:
      cout << "1 - Estoque" << endl;
      ;
    }

    cout << "Estoque: " << endl;
    cout << "1 - Cadastro de Itens" << endl;
    cout << "2 - Remover um item" << endl;
    cout << "3 - Adicionar unidades" << endl;
    cout << "4 - Listar Itens" << endl;
    cout << "5 - Exportar estoque" << endl;
    cout << "Digite outro valor inteiro para voltar ao menu anterior" << endl;
    cin >> opcao;
  }
  system("clear||cls");
}

/* ===================

    * Funções usadas para operacoes com vendas

   ====================*/

/*Busca a quantidade de unidades de um item */

Itens busca_unidade(int idi)
{
  fstream fout;
  Itens aux;
  int id, d, custo, unidade, valor;
  string linha;
  fout.open("estoque.txt", ios::in); // abre para escrita (ios::out)

  while (fout >> id >> d >> custo >> unidade >> linha >> valor)
  {
    if (idi == id)
    {
      fout.close();
      aux.set_unidade(unidade);
      aux.set_Custo(custo);
      aux.set_Nome(Replace(linha));
      return aux;
    }
  }

  fout.close();
  return aux;
}

/*retira a unidade anterior e adicona a nova unidade de um item modificada */
void retira_unidade(int idi, int unidade_nova)
{
  fstream fout;
  Armadura_Jogo vtr;
  Armanentos_Jogo vta;
  Consumiveis_Jogo vtc;

  int id, custo, unidade, escolha, valor, maior, num, i;
  string nome, tipo;
  maior = (vta.num > vtr.num) ? (vta.num > vtc.num ? vta.num : vtc.num) : (vtr.num > vtc.num ? vtr.num : vtc.num);
  fout.open("estoque.txt", ios::in); // abre para escrita (ios::out)

  while (fout >> id >> escolha >> custo >> unidade >> nome >> valor)
  {
    if (escolha == 1)
    {
      vta.itens[vta.num].set_Numero_identificador(id);
      vta.itens[vta.num].set_Tipo(escolha);
      vta.itens[vta.num].set_Custo(custo);
      vta.itens[vta.num].set_Nome(nome);
      vta.itens[vta.num].set_unidade(unidade);
      vta.itens[vta.num].set_dano(valor);
      vta.num = vta.num + 1;
    }
    else if (escolha == 2)
    {
      vtr.itens[vtr.num].set_Numero_identificador(id);
      vtr.itens[vtr.num].set_Tipo(escolha);
      vtr.itens[vtr.num].set_Custo(custo);
      vtr.itens[vtr.num].set_Nome(nome);
      vtr.itens[vtr.num].set_unidade(unidade);
      vtr.itens[vtr.num].set_Durabilidade(valor);
      vtr.num = vtr.num + 1;
    }
    else
    {
      vtc.itens[vtc.num].set_Numero_identificador(id);
      vtc.itens[vtc.num].set_Tipo(escolha);
      vtc.itens[vtc.num].set_Custo(custo);
      vtc.itens[vtc.num].set_Nome(nome);
      vtc.itens[vtc.num].set_unidade(unidade);
      vtc.itens[vtc.num].set_carga(valor);
      vtc.num = vtc.num + 1;
    }
  }
  fout.close();

  fout.open("estoque.txt", ios::out);
  maior = (vta.num > vtr.num) ? (vta.num > vtc.num ? vta.num : vtc.num) : (vtr.num > vtc.num ? vtr.num : vtc.num);
  for (i = 0; i < maior; i++)
  {
    if (vta.num > i)
    {
      if (idi == vta.itens[i].get_Numero_identificador())
      {
        fout << vta.itens[i].get_Numero_identificador()
             << " " << vta.itens[i].get_Tipo() << " " << vta.itens[i].get_Custo() << " " << unidade_nova << " "
             << vta.itens[i].get_Nome()
             << " " << vta.itens[i].get_dano() << endl;
      }
      else
      {
        fout << vta.itens[i].get_Numero_identificador()
             << " " << vta.itens[i].get_Tipo() << " " << vta.itens[i].get_Custo() << " " << vta.itens[i].get_unidade() << " "
             << vta.itens[i].get_Nome()
             << " " << vta.itens[i].get_dano() << endl;
      }
    }

    if (vtr.num > i)
    {

      if (idi == vtr.itens[i].get_Numero_identificador())
      {
        fout << vtr.itens[i].get_Numero_identificador()
             << " " << vtr.itens[i].get_Tipo() << " " << vtr.itens[i].get_Custo() << " " << unidade_nova << " "
             << vtr.itens[i].get_Nome()
             << " " << vtr.itens[i].get_Durabilidade() << endl;
      }
      else
      {
        fout << vtr.itens[i].get_Numero_identificador()
             << " " << vtr.itens[i].get_Tipo() << " " << vtr.itens[i].get_Custo() << " " << vtr.itens[i].get_unidade() << " "
             << vtr.itens[i].get_Nome()
             << " " << vtr.itens[i].get_Durabilidade() << endl;
      }
    }

    if (vtc.num > i)
    {

      if (idi == vtc.itens[i].get_Numero_identificador())
      {
        fout << vtc.itens[i].get_Numero_identificador()
             << " " << vtc.itens[i].get_Tipo() << " " << vtc.itens[i].get_Custo() << " " << unidade_nova << " "
             << vtc.itens[i].get_Nome()
             << " " << vtc.itens[i].get_carga() << endl;
      }
      else
      {
        fout << vtc.itens[i].get_Numero_identificador()
             << " " << vtc.itens[i].get_Tipo() << " " << vtc.itens[i].get_Custo() << " " << vtc.itens[i].get_unidade() << " "
             << vtc.itens[i].get_Nome()
             << " " << vtc.itens[i].get_carga() << endl;
      }
    }
  }
  fout.close();
}

/*Calcula os numeros primos */
int primo(int num)
{
  int x, numDiv = 0,
         contPrimo = 0,
         repetidor;
  for (repetidor = 2; repetidor <= num; repetidor++)
  {
    numDiv = 0;
    for (x = 1; x <= repetidor; x++)
    {
      if (repetidor % x == 0)
      {
        numDiv++;
      }
    }
    if (numDiv == 2)
      contPrimo++;
  }
  return contPrimo;
}

/*Gera numeros aleatorios */
int numeroAleatorio(int menor, int maior)
{
  return rand() % (maior - menor + 1) + menor;
}

/*Imprimi vendas */
void Imprime_vendas()
{

  int idv, idi, qtd;
  string nome;
  float totalc, totald;
  fstream fout;
  fout.open("Logvendas.txt", ios::in);
  if (!fout.is_open())
  {
    cout << "Nao existe vendas registradas";
    return;
  }

  while (fout >> idv >> idi >> nome >> qtd >> totalc >> totald)
  {
    cout << "Id da venda: " << idv << endl;
    cout << "Id do item: " << idi << endl;
    cout << "Nome do item: " << Replace(nome) << endl;
    cout << "Quantidades de itens vendidos: " << qtd << endl;
    cout << "Total sem desconto: " << totalc << endl;
    cout << "Total com desconto: " << totald << endl;
    cout << endl;
  }
  fout.close();
}

/*Gera export*/
void Gravar_export(int idv, int idi, string nome, int qtd, float totalc, float totald)
{

  fstream fout;
  fout.open("export/Logvendas.txt", ios::out);
  if (!fout.is_open())
  {
    fout.open("export/Logvendas.txt");
  }

  fout << "Id da venda: " << idv << endl;
  fout << "Id do item: " << idi << endl;
  fout << "Nome do item: " << Replace_inv(nome) << endl;
  fout << "Quantidades de itens vendidos: " << qtd << endl;
  fout << "Total sem desconto: " << totalc << endl;
  fout << "Total com desconto: " << totald << endl;
  fout << endl;

  fout.close();
}

/*chama a funcao para export*/
void Exportar_vendas()
{

  int idv, idi, qtd;
  string nome;
  float totalc, totald;
  fstream fout;
  fstream fout2;
  fout2.open("export/Logvendas.txt", ios::out);
  fout.open("Logvendas.txt", ios::in);
  if (!fout.is_open())
  {
    cout << "Nao existe vendas registradas";
    return;
  }

  while (fout >> idv >> idi >> nome >> qtd >> totalc >> totald)
  {

    if (!fout2.is_open())
    {
      fout2.open("export/Logvendas.txt");
    }

    fout2 << "Id da venda: " << idv << endl;
    fout2 << "Id do item: " << idi << endl;
    fout2 << "Nome do item: " << Replace_inv(nome) << endl;
    fout2 << "Quantidades de itens vendidos: " << qtd << endl;
    fout2 << "Total sem desconto: " << totalc << endl;
    fout2 << "Total com desconto: " << totald << endl;
    fout2 << endl;
  }
  fout.close();
  fout2.close();
  cout << "Arquivo gerado com sucesso verique a pasta export" << endl;
  cout << endl;
}

/*Registra uma venda*/
void Regista_venda(int id, string nome, int qtd, float totalc, float totald)
{
  fstream fout;
  fout.open("Logvendas.txt", ios::app);
  srand((unsigned)time(0));
  if (!fout.is_open())
  {
    fout.open("Logvendas.txt");
  }

  fout << numeroAleatorio(1000, 4000) << " " << id << " " << Replace_inv(nome) << " " << qtd << " " << totalc << " " << totald << endl;

  fout.close();
}

/*chama a funcao para registrar venda*/
void registra_compra(int num, int id)
{

  fstream fout;
  float desconto, total;
  Itens aux = busca_unidade(id);

  if (aux.get_unidade() > 0)
  {
    cout << endl;
    desconto = primo(aux.get_unidade()) * 0.02;
    total = num * (aux.get_Custo() - (aux.get_Custo() * desconto));

    cout << "Quantidade de unidades compradas: " << num << endl;
    cout << "Custo da unidade em peças de ouro: " << aux.get_Custo() << endl;
    cout << "Valor sem custo: " << aux.get_Custo() * num << endl;
    cout << "Desconto em peças de ouro: " << desconto << endl;
    cout << "Valor total com Desconto: " << total << endl;
    retira_unidade(id, aux.get_unidade() - num);
    Regista_venda(id, aux.get_Nome(), num, aux.get_Custo() * num, total);
  }

  cout << endl;
}

/*verifica se o valor digitado para compra da unidade e menor do que esta diposnivel*/
bool valida_unidade(int num, int unidaded)
{
  fstream fout;
  int id, d, custo, unidade, valor;
  string linha;
  string nome;
  fout.open("estoque.txt", ios::in); // abre para escrita (ios::out)

  while (fout >> id >> d >> custo >> unidade >> linha >> valor)
  {

    if (num == id && unidaded <= unidade)
    {
      fout.close();
      return true;
    }
  }

  fout.close();
  return false;
}

/*chama todas as funcoes anteriores relacionada a venda*/
void Venda_item()
{
  int num;
  cout << "Digite o identificador do item" << endl;
  cin >> num;

  if (Valida_identificador(num) == 1)
  {
    int unidade;
    cout << "Digite a quantidade de itens para compra: " << endl;
    cin >> unidade;
    if (valida_unidade(num, unidade) == 1)
    {
      registra_compra(unidade, num);
    }
    else
    {
      cout << "O item nao possui unidades disponiveis" << endl;
    }
  }
  else
  {
    cout << "Identificador invalido" << endl;
  }
}

/*Menu estoque*/
void menu_vendas()
{
  int opcao, id;
  cout << "Venda: " << endl;
  cout << "1 - Vender um item " << endl;
  cout << "2 - Mostrar logs de venda" << endl;
  cout << "3 - Exportar log de venda" << endl;
  cout << "Digite outro valor inteiro para voltar ao menu anterior" << endl;
  cin >> opcao;
  while (opcao == 1 || opcao == 2 || opcao == 3)
  {
    switch (opcao)
    {
    case 1:
      system("clear||cls");
      Venda_item();
      break;
    case 2:
      system("clear||cls");
      Imprime_vendas();
      break;
    case 3:
      system("clear||cls");
      Exportar_vendas();

      break;
    default:
      cout << "1 - Estoque" << endl;
      ;
    }

    cout << "Venda: " << endl;
    cout << "1 - Vender um item " << endl;
    cout << "2 - Mostrar logs de venda" << endl;
    cout << "3 - Exportar log de venda" << endl;
    cout << "Digite outro valor inteiro para voltar ao menu anterior" << endl;
    cin >> opcao;
  }
  system("clear||cls");
}

/*Função Main */
int main()
{

  int opcao;

  cout << "Selecione uma Opção" << endl;
  cout << "1 - Estoque" << endl;
  cout << "2 - Venda" << endl;
  cout << "Digite outro valor inteiro para sair" << endl;
  cin >> opcao;
  while (opcao == 1 || opcao == 2)
  {
    switch (opcao)
    {
    case 1:
      system("clear||cls");
      menu_estoque();
      break;
    case 2:
      system("clear||cls");
      menu_vendas();
      break;
    default:
      cout << "Obrigado por utilizar nosso sistema" << endl;
      ;
    }

    cout << "Selecione uma Opção" << endl;
    cout << "1 - Estoque" << endl;
    cout << "2 - Venda" << endl;
    cout << "Digite outro valor inteiro para sair" << endl;
    cin >> opcao;
  }
}
