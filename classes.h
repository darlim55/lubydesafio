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
 *  As classe a baixo representam os tres tipo de itens que a loja diponiliza
 *  Elas herdam os atributos da classe pai (itens) e cada um tem atributos especificos
 */
class Armamentos : public Itens
{
  int Dano;

public:
  void set_dano(int dano) { Dano = dano; }
  int get_dano() { return Dano; }
  void calcular_dano();
};

class Armaduras : public Itens
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
 *  EStruturas que seram utilizadas para controle dos itens
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
