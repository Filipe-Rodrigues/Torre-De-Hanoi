#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#define MAX 10
#define TEMPO 125

using namespace std;

//////////////// ESTRUTURA DE DADOS: PILHA ////////////////

struct pilha
{
	pilha(int n);
	int push(int nivel);
	int pop();
	int topo;
	int pecaSuspensa;

  private:
	int pecas[MAX];
};

pilha::pilha(int n)
{
	cout << "Construindo a pilha " << n << endl;
	topo = 0;
	pecaSuspensa = 0;
}

int pilha::push(int nivel)
{
	if (topo == MAX)
	{
		//cout << "Nao vai dar nao, pai" << endl;
		return -1;
	}
	pecas[topo++] = nivel;
	return 0;
}

int pilha::pop()
{
	if (topo == 0)
	{
		//cout << "Que nao vai dar o que rapaz?" << endl;
		return 0;
	}
	return pecas[--topo];
}

///////////////////////////////////////////////////////////
////////////////    FUNÇÕES AUXILIARES     ////////////////

ifstream splash("splash.txt");
ifstream menuPrincipal("menuPrincipal.txt");
ifstream menuPecas("menuPecas.txt");

void reempilhar(pilha **torres, pilha **auxiliar)
{
	for (int i = 0; i < 3; i++)
	{
		int aux = auxiliar[i]->pop();
		while (aux > 0)
		{
			torres[i]->push(aux);
			aux = auxiliar[i]->pop();
		}
	}
}

void empilhar(int pecas, pilha **torres)
{
	for (int i = 1; i <= pecas; i++)
	{
		torres[0]->push(i);
	}
}

void limparPilha(pilha **torres)
{
	int controle;
	for (int i = 0; i < 3; i++)
	{
		do
		{
			controle = torres[i]->pop();
		} while (controle > 0);
	}
}

void iniciarEstados(int *estados, int quantidade)
{
	for (int i = 0; i < 10; i++)
	{
		estados[i] = (i < quantidade) ? (1) : (0);
	}
}

void limpar(int *vetor)
{
	for (int i = 0; i < 10; i++)
	{
		vetor[i] = 0;
	}
}

void dec2bin(int decimal, int *binario, int cont)
{
	if ((decimal / 2) > 0)
	{
		dec2bin((decimal / 2), binario, cont - 1);
	}
	binario[cont] = (decimal % 2);
}

void converter(int decimal, int *binario)
{
	limpar(binario);
	dec2bin(decimal, binario, 9);
}

bool detectaSubida(int atual, int anterior)
{
	if (anterior == 0 and atual == 1)
	{
		return true;
	}
	return false;
}

int proximaOrigem(int quantidade, int *atual, int *anterior, int *estado)
{
	for (int i = 9; i >= 0; i--)
	{
		if (detectaSubida(atual[i], anterior[i]))
		{
			return (9 - i);
		}
	}
	return -1;
}

void avanca(int &posicao, bool praFrente)
{
	if (praFrente)
	{
		if (posicao < 3)
		{
			posicao++;
		}
		else
		{
			posicao = 1;
		}
	}
	else
	{
		if (posicao > 1)
		{
			posicao--;
		}
		else
		{
			posicao = 3;
		}
	}
}

int esperar(int milissegundos)
{
	int *lixo = new int;
	*lixo = 1;
	for (int i = 0; i < milissegundos * 250000; i++)
	{
		*lixo *= 2;
	}
	delete lixo;
}

///////////////////////////////////////////////////////////
////////////////   FUNÇÕES DE IMPRESSÃO    ////////////////

void limparTela()
{
	system("clear");
	cout << endl;
}

void imprimeEspacos(int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << " ";
	}
}

void imprimeFullBlock(int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << "\u2588";
	}
}

void imprimeHeavyFullBlock(int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << "\u2593";
	}
}

void imprimeMediumFullBlock(int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << "\u2592";
	}
}

void imprimeLightFullBlock(int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << "\u2591";
	}
}

void imprimeCampoResposta()
{
	imprimeLightFullBlock(2);
	imprimeMediumFullBlock(2);
	imprimeHeavyFullBlock(2);
	imprimeEspacos(1);
}

void imprimeBase()
{
	imprimeFullBlock(2);
	for (int i = 0; i < 3; i++)
	{
		imprimeEspacos(4);
		imprimeFullBlock(24);
	}
	imprimeEspacos(4);
	imprimeFullBlock(2);
	cout << endl;
}

void imprimeBloco(int nivel)
{
	imprimeEspacos(nivel);
	imprimeMediumFullBlock(2 * (12 - nivel));
	imprimeEspacos(nivel);
}

void imprimeVazio()
{
	imprimeEspacos(11);
	imprimeFullBlock(2);
	imprimeEspacos(11);
}

void imprimeMargemCompleta()
{
	imprimeFullBlock(92);
	cout << endl;
}

void imprimeMargemLateral()
{
	imprimeFullBlock(2);
	imprimeEspacos(88);
	imprimeFullBlock(2);
	cout << endl;
}

void imprimeLinhaDeIdentificacao()
{
	imprimeFullBlock(2);
	for (int i = 1; i <= 3; i++)
	{
		imprimeEspacos(15);
		cout << i;
		imprimeEspacos(12);
	}
	imprimeEspacos(4);
	imprimeFullBlock(2);
	cout << endl;
}

void imprimeMensagemDeErro()
{
	imprimeFullBlock(2);
	imprimeEspacos(35);
	cout << "Para de fazer merda";
	imprimeEspacos(34);
	imprimeFullBlock(2);
	cout << endl;
}

///////////////////////////////////////////////////////////
////////////////  IMPRESSÕES DE INTERFACE  ////////////////

void imprimirSplash()
{
	limparTela();
	string linha;
	while (getline(splash, linha))
	{
		cout << linha << endl;
	}
}

void imprimirMenuPrincipal(bool ta_suave)
{
	limparTela();
	string linha;
	while (getline(menuPrincipal, linha))
	{
		cout << linha << endl;
	}
	if (ta_suave)
	{
		cout << endl;
	}
	else
	{
		imprimeEspacos(40);
		cout << "Deixa de ser idiota" << endl;
	}
	imprimeEspacos(32);
	imprimeCampoResposta();
	menuPrincipal.clear();
	menuPrincipal.seekg(0, ios::beg);
}

void imprimirMenuPecas(bool ta_suave)
{
	limparTela();
	string linha;
	while (getline(menuPecas, linha))
	{
		cout << linha << endl;
	}
	if (ta_suave)
	{
		cout << endl;
	}
	else
	{
		imprimeEspacos(41);
		cout << "Não finge de égua" << endl;
	}
	imprimeEspacos(27);
	imprimeCampoResposta();
	menuPecas.clear();
	menuPecas.seekg(0, ios::beg);
}

void imprimirLinhaDeMoverPeca(pilha **torres)
{
	imprimeFullBlock(2);
	for (int i = 0; i < 3; i++)
	{
		imprimeEspacos(4);
		if (torres[i]->pecaSuspensa == 0)
		{
			imprimeEspacos(24);
		}
		else
		{
			imprimeBloco(torres[i]->pecaSuspensa);
		}
	}
	imprimeEspacos(4);
	imprimeFullBlock(2);
	cout << endl;
}

void imprimirLinhaDeErro(bool ta_suave)
{
	if (ta_suave)
	{
		imprimeMargemLateral();
	}
	else
	{
		imprimeMensagemDeErro();
	}
}

void imprimirMovimentos(int movimentos)
{
	imprimeEspacos(76);
	cout << "Movimentos:";
	imprimeEspacos(4 - (int)(floor(log10(movimentos))));
	cout << movimentos << endl;
}

void imprimirParteSuperior(pilha **torres, bool ta_suave)
{
	imprimeMargemCompleta();
	imprimeMargemLateral();
	imprimirLinhaDeErro(ta_suave);
	imprimeMargemLateral();
	imprimirLinhaDeMoverPeca(torres);
	imprimeMargemLateral();
}

void imprimirParteInferior(int movimentos)
{
	imprimeMargemLateral();
	imprimeLinhaDeIdentificacao();
	imprimeMargemLateral();
	imprimeMargemCompleta();
	imprimirMovimentos(movimentos);
}

void imprimirSecaoDeEntrada()
{
	imprimeCampoResposta();
}

void imprimirTorresDeHanoi(pilha **torres, pilha **auxiliar)
{
	for (int i = 11; i >= 1; i--)
	{
		imprimeFullBlock(2);
		for (int j = 0; j < 3; j++)
		{
			imprimeEspacos(4);
			if (i > (torres[j]->topo))
			{
				imprimeVazio();
			}
			else
			{
				int peca = torres[j]->pop();
				auxiliar[j]->push(peca);
				imprimeBloco(peca);
			}
		}
		imprimeEspacos(4);
		imprimeFullBlock(2);
		cout << endl;
	}
	imprimeBase();
}

void imprimirJogo(bool manual, pilha **torres, pilha **auxiliar, bool ta_suave, int movimentos)
{
	limparTela();
	imprimirParteSuperior(torres, ta_suave);
	imprimirTorresDeHanoi(torres, auxiliar);
	reempilhar(torres, auxiliar);
	imprimirParteInferior(movimentos);
	if (manual)
	{
		imprimirSecaoDeEntrada();
	}
	else
	{
		cout << endl
			 << endl
			 << endl;
	}
}

///////////////////////////////////////////////////////////
////////////////      LÓGICA DO JOGO       ////////////////

bool suspendePeca(pilha **torres, int origem)
{
	if (origem < 1 or origem > 3 or torres[origem - 1]->topo == 0)
	{
		return false;
	}
	torres[origem - 1]->pecaSuspensa = torres[origem - 1]->pop();
	return true;
}

bool colocaPeca(pilha **torres, int origem, int destino)
{
	if (destino < 1 or destino > 3)
	{
		return false;
	}
	int aux = torres[destino - 1]->pop();
	if (aux > 0)
	{
		torres[destino - 1]->push(aux);
	}
	if (aux < torres[origem - 1]->pecaSuspensa)
	{
		torres[destino - 1]->push(torres[origem - 1]->pecaSuspensa);
		torres[origem - 1]->pecaSuspensa = 0;
		return true;
	}
	return false;
}

void jogar(pilha **torres, pilha **auxiliar, int quantidade)
{
	int origem;
	int destino;
	int movimentos = 0;
	bool ganhou = false, ta_suave = true;
	do
	{
		do
		{
			imprimirJogo(true, torres, auxiliar, ta_suave, movimentos);
			cin >> origem;
			ta_suave = suspendePeca(torres, origem);
		} while (!ta_suave);
		do
		{
			imprimirJogo(true, torres, auxiliar, ta_suave, movimentos);
			cin >> destino;
			ta_suave = colocaPeca(torres, origem, destino);
		} while (!ta_suave);
		movimentos++;
		ganhou = (torres[2]->topo == quantidade);
	} while (!ganhou);
	imprimirJogo(true, torres, auxiliar, true, movimentos);
	if (movimentos == (int)(pow(2, quantidade)) - 1)
	{
		if (quantidade < 10)
		{
			cout << "    Aah, então agora tu é o \"PICA DAS GALÁXIAS\" né..." << endl;
			imprimeEspacos(7);
			cout << "    Só porque conseguiu resolver com o menor nº de movimentos, fica aí se achando o rei da cocada preta." << endl;
			imprimeEspacos(7);
			cout << "    Se quer se mostrar, por que não tenta fazer essa porra com " << quantidade + 1 << " peças?" << endl
				 << endl;
		}
		else
		{
			cout << "    CA-RA-LE-O, tu é doente, só pode. Você não deve ter vida social." << endl;
			imprimeEspacos(7);
			cout << "    O cara é tão sem vida social que conseguiu zerar a porra de um jogo de torre de hanoi." << endl;
			imprimeEspacos(7);
			cout << "    Não, sério, vai te fuder, agora você mostrou que é de fato o \"PICA DAS GALÁXIAS\"..." << endl
				 << endl;
			imprimeEspacos(7);
			cout << "    ... em torres de hanoi." << endl
				 << endl
				 << endl;
		}
	}
	else
	{
		cout << "    Não seja ridículo. Faz essa merda direito." << endl;
		imprimeEspacos(7);
		cout << "    Com esse tanto de movimento dava pra resolver até duas torres de hanoi." << endl
			 << endl;
	}
	cout << "    Pressione [ENTER] para continuar";
	string lixo;
	cin.ignore();
	getline(cin, lixo);
	limparPilha(torres);
}

void jogarAutomaticamente(pilha **torres, pilha **auxiliar, int quantidade)
{
	int origem, destino;
	int movimentos = 0, pos_estado;
	int *estado = new int[10];
	int *atual = new int[10];
	int *anterior = new int[10];
	iniciarEstados(estado, quantidade);
	bool ganhou = false, ta_suave = true;
	do
	{
		converter(movimentos + 1, atual);
		converter(movimentos, anterior);
		pos_estado = proximaOrigem(quantidade, atual, anterior, estado);
		origem = estado[pos_estado];
		imprimirJogo(false, torres, auxiliar, ta_suave, movimentos);
		esperar(TEMPO * (11 - quantidade));
		ta_suave = suspendePeca(torres, origem);
		avanca(estado[pos_estado], (torres[origem - 1]->pecaSuspensa) % 2 == 0);
		destino = estado[pos_estado];
		imprimirJogo(false, torres, auxiliar, ta_suave, movimentos);
		esperar(TEMPO * (11 - quantidade));
		ta_suave = colocaPeca(torres, origem, destino);
		movimentos++;
		ganhou = (torres[2]->topo == quantidade);
	} while (!ganhou);
	imprimirJogo(true, torres, auxiliar, true, movimentos);
	cout << "    Tá vendo como é que faz, bonachão? Tenta ser menos inútil e joga você mesmo." << endl
		 << endl;
	cout << "    Pressione [ENTER] para continuar";
	string lixo;
	cin.ignore();
	getline(cin, lixo);
	limparPilha(torres);
}

///////////////////////////////////////////////////////////
////////////////       PREPARAR JOGO       ////////////////

void iniciarJogo(pilha **torres, pilha **auxiliar)
{
	imprimirSplash();
	string lixo;
	getline(cin, lixo);
	int opcao;
	bool ta_suave = true;
	int quantidade;
	do
	{
		imprimirMenuPrincipal(ta_suave);
		cin >> opcao;
		switch (opcao)
		{
		case 1:
			ta_suave = true;
			do
			{
				imprimirMenuPecas(ta_suave);
				cin >> quantidade;
				ta_suave = false;
			} while (quantidade < 1 or quantidade > 10);
			empilhar(quantidade, torres);
			jogar(torres, auxiliar, quantidade);
			ta_suave = true;
			break;

		case 2:
			ta_suave = true;
			do
			{
				imprimirMenuPecas(ta_suave);
				cin >> quantidade;
				ta_suave = false;
			} while (quantidade < 1 or quantidade > 10);
			empilhar(quantidade, torres);
			jogarAutomaticamente(torres, auxiliar, quantidade);
			ta_suave = true;
			break;

		default:
			ta_suave = false;
			break;
		}
	} while (opcao > 0);
}

void hanoi()
{
	pilha **torres = new pilha *[3];
	pilha **auxiliar = new pilha *[3];
	for (int i = 0; i < 3; i++)
	{
		torres[i] = new pilha(i + 1);
		auxiliar[i] = new pilha(i + 1);
	}
	esperar(1000);
	string lixo;
	cout << "Pressione [ENTER] para continuar..." << endl;
	getline(cin, lixo);

	iniciarJogo(torres, auxiliar);

	cout << endl
		 << endl
		 << endl;
	for (int i = 0; i < 3; i++)
	{
		delete torres[i];
		delete auxiliar[i];
	}
	delete[] torres;
	delete[] auxiliar;
}

///////////////////////////////////////////////////////////
////////////////          INICIAR          ////////////////

int main()
{
	system("clear");
	hanoi();
	return 0;
}

///////////////////////////////////////////////////////////