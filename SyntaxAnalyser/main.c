#include <stdio.h>
#include <stdlib.h>

#define TKId 1
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKVirgula 5
#define TKDoisPontos 6
#define TKAbreParenteses 7
#define TKFechaParenteses 8
#define TKAtrib 9
#define TKPontoEVirgula 10
#define TKAbreChaves 11
#define TKFechaChaves 12
#define TKSoma 13
#define TKDuploMais 14
#define TKProd 15
#define TKChar 16
#define TKSub 17
#define TKVolatile 18
#define TKDouble 19
#define TKFimArquivo 20
#define TKAndBit 21
#define TKAndLogico 22
#define TKCteInt 23
#define TKMaior 24

#define false 0
#define true 1

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

char nomes[][20] = {"",
    "TKId",
    "TKVoid",
    "TKInt",
    "TKFloat",
    "TKVirgula",
    "TKDoisPontos",
    "TKAbreParenteses",
    "TKFechaParenteses",
    "TKAtrib",
    "TKPontoEVirgula",
    "TKAbreChaves",
    "TKFechaChaves",
    "TKSoma",
    "TKDuploMais",
    "TKProd",
    "TKChar",
    "TKSub",
    "TKVolatile",
    "TKDouble",
    "TKFimArquivo",
    "TKAndBit",
    "TKAndLogico",
    "TKCteInt",
    "TKMaior"
};

int pos = 0;

int tk;
char lex[20];
FILE *arqin;
char c;

struct pal_res{char palavra[20]; int tk;};
struct pal_res lista_pal[]={{"void",TKVoid},
                  {"int",TKInt},
                  {"float",TKFloat},
                  {"char",TKChar},
                  {"volatile",TKVolatile},
                  {"double",TKDouble},
                  {"fimtabela",TKId}};

int palavra_reservada(char lex[]){

    int postab=0;

    while (strcmp("fimtabela",lista_pal[postab].palavra)!=0){
        if (strcmp(lex,lista_pal[postab].palavra)==0){
            return lista_pal[postab].tk;
        }

        postab++;
    }

    return TKId;
}

void getToken();
void proxC();

long int posglobal;

void proxC(){
    if (feof(arqin)) {
        c=-1;
        return;
    }

    fread(&c,1,1,arqin);
}

void getToken(){

    printf("%s - %s\n", nomes[tk], lex);
    int estado=0,
    fim=0,
    posl=0;

    while (!fim){
        printf("char=%c pos=%d\n",c,pos);
        lex[posl++]=c;

        switch(estado){
            case 0:if ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='_'))
                {proxC();estado=1;break;}
            if (c>='0' && c<='9')
                {while (c>='0' && c<='9') proxC(); tk=TKCteInt;return;}
            if (c=='='){lex[posl]='\0';proxC();tk=TKAtrib;return;}
            if (c=='+'){
                proxC();
				if (c=='+'){
				   lex[posl++]='+';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKDuploMais;return;
                }else{
	               lex[posl]='\0';
				   tk=TKSoma;return;
                }
             }

                if (c=='&'){
                    proxC();
                    if (c=='&'){
                        lex[posl++]='+';
                        lex[posl]='\0';
                        proxC();
                        tk=TKAndLogico;return;
                    }else{
                        lex[posl]='\0';
                        tk=TKAndBit;return;
                    }
                }

                if (c=='*'){lex[posl]='\0';proxC();tk=TKProd;return;}
                if (c=='>'){lex[posl]='\0';proxC();tk=TKMaior;return;}
                if (c=='('){lex[posl]='\0';proxC();tk=TKAbreParenteses;return;}
                if (c==')'){lex[posl]='\0';proxC();tk=TKFechaParenteses;return;}
                if (c=='&'){lex[posl]='\0';proxC();tk=TKAndBit;return;}
                if (c=='{'){lex[posl]='\0';proxC();tk=TKAbreChaves;return;}
                if (c=='}'){lex[posl]='\0';proxC();tk=TKFechaChaves;return;}
                if (c==','){lex[posl]='\0';proxC();tk=TKVirgula;return;}
                if (c==';'){lex[posl]='\0';proxC();tk=TKPontoEVirgula;return;}
                if (c==':'){lex[posl]='\0';proxC();tk=TKDoisPontos;return;}
                if (c=='-'){lex[posl]='\0';proxC();tk=TKSub;return;}
                if (c==-1){lex[posl]='\0';proxC();tk=TKFimArquivo;return;}
                if (c==' ' || c=='\n' || c=='\t' || c=='\r') {proxC();posl--;break;}
                if (c=='\0') {tk=-1;return;}
                printf("Erro l�xico: encontrou o caracter %c (%d)",c,c);
                getch();
                break;

            case 1:if ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='_') || (c>='0' && c<='9')) {proxC();break;}
                lex[--posl]='\0';
                tk=palavra_reservada(lex);
                return;
      }
   }
}

//--------------------------------- IF COMMAND ---------------------------------
/*
//S -> if ( C ) { S }
int S(){
	if(tk == TK1){// if
		getToken();
		if(tk == TK2){// (
			getToken();
			if (C()){
				if(tk == TK3){// )
					getToken();
					if(tk == TK4){// {
						getToken();
						if (S()){
							if(tk == TK5){// }
								getToken();
								return 1;
							}//fecha24
							else{return 0;}
						}//fecha24
						else{return 0;}
					}//fecha24
					else{return 0;}
				}//fecha24
				else{return 0;}
			}//fecha24
			else{return 0;}
		}//fecha24
		else{return 0;}
	}//fecha24
	else{return 0;}
}//fecha25

//C -> E R E
int C(){
	if (E()){
		if (R()){
			if (E()){
				return 1;
			}//fecha22
			else{return 0;}
		}//fecha22
		else{return 0;}
	}//fecha22
	else{return 0;}
}//fecha25

//E -> ID | NUM | E OP E | ( E )
int E(){
	if (ID()){
		return 1;
	}//fecha21
	else if (NUM()){
		return 1;
	}//fecha21
	else 	if (E()){
		if (OP()){
			if (E()){
				return 1;
			}//fecha22
			else{return 0;}
		}//fecha22
		else{return 0;}
	}//fecha22
	else if(tk == TK2){// (
		getToken();
		if (E()){
			if(tk == TK3){// )
				getToken();
				return 1;
			}//fecha24
			else{return 0;}
		}//fecha24
		else{return 0;}
	}//fecha24
	else{return 0;}
}//fecha25

//R -> == | != | < | > | <= | >=
int R(){
	if(tk == TK6){// ==
		getToken();
		return 1;
	}//fecha23
	else if(tk == TK7){// !=
		getToken();
		return 1;
	}//fecha23
	else if(tk == TK8){// <
		getToken();
		return 1;
	}//fecha23
	else if(tk == TK9){// >
		getToken();
		return 1;
	}//fecha23
	else if(tk == TK10){// <=
		getToken();
		return 1;
	}//fecha23
	else if(tk == TK11){// >=
		getToken();
		return 1;
	}//fecha23
	else{return 0;}
}//fecha25

//OP -> + | - | * | /
int OP(){
	if(tk == TK12){// +
		getToken();
		return 1;
	}//fecha23
	else if(tk == TK13){// -
		getToken();
		return 1;
	}//fecha23
	else if(tk == TK14){// *
		getToken();
		return 1;
	}//fecha23
	else if(tk == TK15){// /
		getToken();
		return 1;
	}//fecha23
	else{return 0;}
}
*/
int TLinha();
int ELinha();

int main()
{
    printf("Hello world!\n");
    return 0;
}
