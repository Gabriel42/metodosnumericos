/*
 * NewtonCotes.cpp
 *
 *  Created on: 1 de abr de 2016
 *      Author: Gabriel
Caro Professor,

Fiz esse programa de maneira bem pragmática. Espero que você não se incomode muito com a
falta de cuidado com os métodos um pouco mal estruturados e com o aninhamento das variáveis.

Para mudar a função integrada tem que mudar a linha escrita no método func().

Deixei também o debug ativado. Caso você queira só ver os resultados você pode marcar como
comentado os printf's que tem o comentário //debug antes deles.

Deixei o debug pois o programa fica mais interessante de se observar com ele =P

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void input();
double calc();
double func(double x, int c);
double funG(int c);

double x, h, XI, XF, E, I, Y[6];
int G;
char buf[100];

int main(){
	printf(" Integrando x^10 pela equacao de substituicao de Newton-Cotes de intervalo fechado \n Eh possivel alterar a funcao que sera integrada na linha de codigo atraves do metodo func()\n\n");

	input();

	I = calc();
	//debug
	printf("\nTP = Total de particoes \nNP = Numero da particao atual \nD = Comparacao para achar o erro \nA = Area atual");

	printf("\nA area da funcao eh %lf \n", I );



	return 0;
}

void input(){

	//debug
	/*XI = 0;
	XF = 200;
	G = 2;
	E = 6;
	E = -pow(10.0,(-E));*/

	printf(" Digite o valor do inicio da integracao\n ");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%lf", &XI);
	//printf("%lf \n", XI);

	printf(" Digite o valor do fim da integracao\n ");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%lf", &XF);
	//printf("%lf \n", XF);

	printf(" Digite quantas casas decimais o erro vai ter\n ");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%lf", &E);
	E = -pow(10.0,(-E));//deixando o erro na forma de potência negativa de 10
	//printf("%lf \n",E);

	printf(" Digite o grau da funcao de substituicao (1-5)\n ");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d", &G);
	//printf("%lf \n",G);

	return;
}

double calc(){
	double teste[2];
	int c1=1;//contador que define o numero das partições
	int c2=0;//contador que varre o numero de partições
	int c3=0;//contador que varre cada partição
	double dif;//calcular o erro
	do{
		c2=0;
		teste[0] = teste[1];
		teste[1]=0;
		do{
			c3 = 0;
			h = (XF - XI)/(c1*G);
			do{
				//h*G*c2 define o intervalo da partição que vai ser usado no calcula da integral de N-C
				//h*c3 define qual ponto de controle será usado para definir o Y[x]
				Y[c3]=func(XI+h*G*c2+h*c3, c3);
				c3++;
			}while(c3<G+1);

			//teste[0] = teste[1];
			teste[1] += funG(c2);
			c2++;
			//TP = Total de partições
			//NP = Numero da partição atual
			//D = Comparação para achar o erro
			//A = Area atual
			//debug
			//printf("TP:%4d NP:%4d h:%4lf D:%7lf A:%7lf \n",c1,c2,h, dif, teste[1]);
		}while(c2<c1);
		if (c1==1)//caso não se tenham dois valores para comparar ainda
			dif = E-1;
		else{
			dif = (teste[1] - teste[0])/teste[0];
			}
		printf("TP:%4d NP:%4d h:%4lf D:%7lf A:%7lf \n",c1,c2, h, dif, teste[1]);//debug
		c1++;
	}while(dif <= E);//Calcular a função da integral de substituição e comparar até ser menor que o erro

	return teste[1];
}
//Método que define qual função será integrada
double func(double x, int c){
	double resultado;
	//resultado = x;
	//resultado = sin(x);
	resultado = pow(x,10);
	//resultado = pow(x,sin(x));
	//resultado = x*sin(x);
	//não funciona para a integral abaixo
	//resultado = 10 - (10/5)*sin(8*x)*exp(pow((-x),(10/4)));//integral que o professor passou na sala
	//printf("f%d tem valor %lf\n", c,resultado);

	return resultado;

}

double funG(int c){
	double integral;
	switch (G){
	case 1://
		integral = (h/2)*(Y[0]+Y[1]);
		break;
	case 2:
		integral = (h/3)*(Y[0]+4*Y[1]+Y[2]);
		break;
	case 3:
		integral = (3*h/8)*(Y[0]+3*Y[1]+3*Y[2]+Y[3]);
		break;
	case 4:
		integral = (2*h/45)*(7*Y[0]+32*Y[1]+12*Y[2]+32*Y[3]+7*Y[4]);
		break;
	case 5:
		integral = (5*h/288)*(19*Y[0]+75*Y[1]+50*Y[2]+50*Y[3]+75*Y[4]+19*Y[5]);
		break;
	}
	//printf("P:%d tem valor %lf\n", c,integral);//debug
	return integral;


}
