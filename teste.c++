#include <iostream>
using namespace std;

class Itens
{

  int Numero_identificador;
  string Nome;
  string Tipo;
  float Custo;

public:
  void set_Numero_identificador(int num) { Numero_identificador = num; }
  int get_Numero_identificador() { return

                                   Numero_identificador; }
  void set_Nome(string nome) { Nome = nome; }
  string get_Nome() { return Nome; }

  void set_Tipo(string tipo) { Tipo = tipo; }
  string get_Tipo() { return Tipo; }

  void set_Custo(float custo) { Custo = custo; }
  int get_Custo() { return Custo; }
};

class Armamentos : public Itens // Define um caminhao.
{
  double Dano;

public:
  void set_dano(int dano) { Dano = dano; }
  double get_carga() { return Dano; }
  void calcular_dano();
};

class Armaduras : public Itens // Define um caminhao.
{
  double Durabilidade;

public:
  void set_Durabilidade(int durabilidade) { Durabilidade = durabilidade; }
  double get_carga() { return Durabilidade; }
  void calcular_Durabilidade();
};

class Consumiveis : public Itens
{
  double Usos;

public:
  void set_dano(int usos) { Usos = usos; }
  double get_carga() { return Usos; }
  void calcular_Usos();
};

int main()
{

  int Raio;
  cout << "Entre com o valor do raio: ";
  cin >> Raio;
  cout << "O Raio e: " << Raio << endl;
}
