/*====================================
 *                 Loja
 *           Desenvolvido por:
 *               Jorge Silva
 * ====================================*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <algorithm>
using namespace std;

/*
 * Temos a class itens a seguir que servira para armazenas os dados que seram lidos do arquivo txr
 */
class Itens
{

  int Numero_identificador;
  string Nome;
  int Tipo;
  float Custo;
  int Unidade;

public:
  void set_Numero_identificador(int num) { Numero_identificador = num; }
  int get_Numero_identificador() { return

                                   Numero_identificador; }
  void set_Nome(string nome) { Nome = nome; }
  string get_Nome() { return Nome; }

  void set_Tipo(int tipo) { Tipo = tipo; }
  int get_Tipo() { return Tipo; }

  void set_Custo(float custo) { Custo = custo; }
  int get_Custo() { return Custo; }

  void set_unidade(int unidade) { Unidade = unidade; }
  int get_unidade() { return Unidade; }
};

/*
 *  as classe abaixo representam os tres tipo de itens que a loja diponiliza
 *  Elas herdam os atributos da classe pai (itens) e cada um tem um atributo especifico
 */
class Armamentos : public Itens // Define um caminhao.
{
  int Dano;

public:
  void set_dano(int dano) { Dano = dano; }
  int get_dano() { return Dano; }
  void calcular_dano();
};

class Armaduras : public Itens // Define um caminhao.
{
  double Durabilidade;

public:
  void set_Durabilidade(int durabilidade) { Durabilidade = durabilidade; }
  double get_Durabilidade()
  {
    return Durabilidade;
  }
  void calcular_Durabilidade();
};

class Consumiveis : public Itens
{
  double Usos;

public:
  void set_carga(int usos) { Usos = usos; }
  double get_carga() { return Usos; }
  void calcular_Usos();
};

/*
 *  EStruturas que seram utelizadas para controle dos itens
 */
struct Armanentos_Jogo
{
  Armamentos *itens = new Armamentos[100];
  int num = 0;
};

struct Armadura_Jogo
{
  Armaduras *itens = new Armaduras[100];
  int num = 0;
};

struct Consumiveis_Jogo
{
  Consumiveis *itens = new Consumiveis[100];
  int num = 0;
};

string replace(string nome)
{
  for (int i = 0; i < nome.length(); i++)
  {
    if (nome[i] == '_')
      nome[i] = ' ';
  }

  return nome;
}

string replace_inv(string nome)
{
  for (int i = 0; i < nome.length(); i++)
  {
    if (nome[i] == ' ')
      nome[i] = '_';
  }

  return nome;
}

bool valida_identificador(int numero_identificador)
{
  fstream fout;
  int id, d, custo, unidade, valor;
  string linha;
  string nome;
  fout.open("teste.txt", ios::in); // abre para escrita (ios::out)

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

bool valida_nome(string nome)
{
  fstream fout;
  int id, d, custo, unidade, valor;
  string linha, aux, aux2;
  aux2 = nome;
  fout.open("teste.txt", ios::in); // abre para escrita (ios::out)

  while (fout >> id >> d >> custo >> unidade >> linha >> valor)
  {
    string aux = replace(linha);

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

int valida_tipo(string tipo)
{

  fstream fout;
  string aux2;
  aux2 = tipo;
  fout.open("teste.txt", ios::in); // abre para escrita (ios::out)

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

void cadastrar_itens()
{

  int numero_identificador, custo, unidade, escolha;
  string nome, tipo;
  cout << "Identificador (valor inteiro): " << endl;
  cin >> numero_identificador;
  cout << endl;
  while (valida_identificador(numero_identificador) == 1)
  {
    cout << "Id ja cadsatrado. Digite um novo (valor inteiro): " << endl;
    cin >> numero_identificador;
    cout << endl;
  }

  cout << "Nome do item (digite sem acentos ou ç): " << endl;
  cin.ignore();
  getline(cin, nome);
  cout << endl;

  while (valida_nome(nome) == 1)
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
    fout.open("teste.txt", ios::ate | ios::out | ios::in); // abre para escrita (ios::out)

    fout << item.get_Numero_identificador()
         << " " << item.get_Tipo() << " " << item.get_Custo() << " " << unidade << " "
         << replace_inv(item.get_Nome())
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
    fout.open("teste.txt", ios::ate | ios::out | ios::in); // abre para escrita (ios::out)

    fout << item.get_Numero_identificador()
         << " " << item.get_Tipo() << " " << item.get_Custo() << " " << unidade << " "
         << replace_inv(item.get_Nome())
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
    fout.open("teste.txt", ios::ate | ios::out | ios::in); // abre para escrita (ios::out)

    fout << item.get_Numero_identificador()
         << " " << item.get_Tipo() << " " << item.get_Custo() << " " << unidade << " "
         << replace_inv(item.get_Nome())
         << " " << qtd << endl;
    fout.close();
  }
}

void Lista_itens()
{

  fstream fout;
  int id, custo, unidade, escolha, valor;
  string nome, tipo;
  fout.open("teste.txt", ios::in); // abre para escrita (ios::out)

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
    cout << "Nome do item: " << replace(nome) << endl;
    cout << endl;
  }

  fout.close();
  cout << endl;
}

void imprimi_itens(Armadura_Jogo vtr, Armanentos_Jogo vta, Consumiveis_Jogo vtc, int opcao, int num)
{
  fstream fout;
  int i;
  int maior = (vta.num > vtr.num) ? (vta.num > vtc.num ? vta.num : vtc.num) : (vtr.num > vtc.num ? vtr.num : vtc.num);
  fout.open("teste.txt", ios::out);

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

void Modifica_unidades(int selecionado)
{

  fstream fout;
  Armadura_Jogo vtr;
  Armanentos_Jogo vta;
  Consumiveis_Jogo vtc;

  int id, custo, unidade, escolha, valor, maior, num;
  string nome, tipo;
  fout.open("teste.txt", ios::in); // abre para escrita (ios::out)

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
    if (valida_identificador(num) == 1)
    {
      imprimi_itens(vtr, vta, vtc, selecionado, num);
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
    if (valida_identificador(num) == 1)
    {
      imprimi_itens(vtr, vta, vtc, selecionado, num);
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

void menu_estoque()
{

  int opcao, id;
  cout << "Estoque: " << endl;
  cout << "1 - Cadastro de Itens" << endl;
  cout << "2 - Remover um item" << endl;
  cout << "3 - Adicionar unidades" << endl;
  cout << "4 - Listar Itens" << endl;
  cout << "5 - Exportar estoque" << endl;
  cin >> opcao;
  while (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5)
  {
    switch (opcao)
    {
    case 1:
      system("clear||cls");
      cadastrar_itens();
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
    cin >> opcao;
  }
  system("clear||cls");
}

void retira_unidade()
{
}

int primo(int num)
{
  int aux, div = 0;

  if (div == 0)
    return 0;
  for (aux = 2; aux <= num; aux++)
    if (num % aux == 0)
      div++;

  return div;
}
void registra_compra()
{
  fstream fout;
  fout.open("export/estoque.txt", ios::out);

  fout.close();
}

bool valida_unidade(int num, int unidaded)
{
  fstream fout;
  int id, d, custo, unidade, valor;
  string linha;
  string nome;
  fout.open("teste.txt", ios::in); // abre para escrita (ios::out)

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

void Venda_item()
{
  int num;
  cout << "Digite o identificador do item" << endl;
  cin >> num;

  if (valida_identificador(num) == 1)
  {
    int unidade;
    cout << "Digite a quantidade de itens para compra: " << endl;
    cin >> unidade;
    if (valida_unidade(num, unidade) == 1)
    {
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

void menu_vendas()
{
  int opcao, id;
  cout << "Venda: " << endl;
  cout << "1 - Vender um item " << endl;
  cout << "2 - Remover um item" << endl;
  cout << "3 - Adicionar unidades" << endl;
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
      Modifica_unidades(2);
      break;
    case 3:
      system("clear||cls");
      cout << "Digite o identificador do item" << endl;
      cin >> id;
      Modifica_unidades(3);

      break;
    default:
      cout << "1 - Estoque" << endl;
      ;
    }

    cout << "Venda: " << endl;
    cout << "1 - Vender um item " << endl;
    cout << "2 - Remover um item" << endl;
    cout << "3 - Adicionar unidades" << endl;
    cin >> opcao;
  }
  system("clear||cls");
}
/*FUncao mains */

int main()
{

  int opcao;

  cout << "Selecione uma Opção" << endl;
  cout << "1 - Estoque" << endl;
  cout << "2 - Venda" << endl;
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
      cout << "1 - Estoque" << endl;
      ;
    }

    cout << "Selecione uma Opção" << endl;
    cout << "1 - Estoque" << endl;
    cout << "2 - Venda" << endl;
    cin >> opcao;
  }
}
