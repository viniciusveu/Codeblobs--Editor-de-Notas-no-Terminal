#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "editor.h"
#include "editor.c"

Linha linha = NULL;
Texto fluxo = NULL;
Cursor pfluxo = NULL;


void sair(char* nome_arquivo){
  endwin();
  texto_salvar(fluxo,nome_arquivo);
  texto_apagar(fluxo);
  printf("\nTexto salvo! :D\n");
}

int main(int argc, char *argv[]){
  if(argc == 2) {
    switch(*argv[1]) {
      case '?': 
        como_usar();
        break;
    }
  }
  char op; char nome_arquivo[200]; char palavra[16];
  
  printf("Deseja criar novo arquivo de texto, abrir existente ou cancelar? [a,n,c]: ");
  scanf("%c", &op);
  if(op == 'a') {
    printf("Qual o nome do arquivo? [sem espaços]\n");
    scanf("%s", nome_arquivo);
  } else if(op == 'n') {
    printf("Qual será o nome do seu arquivo? [sem espaços]\n");
	  scanf("%s", nome_arquivo); 
    FILE* f;	
	  if( (f=fopen(nome_arquivo, "w+r")) == NULL) {
      printf("ERRO na criação do arquivo %s!!! \n", nome_arquivo);
      exit(1);
    }
	  fputs("Escreva aqui  ", f);
    fclose(f);
 	} else if(op == 'c') exit(EXIT_SUCCESS);
    else printf("Entrada inválida!\n");
  
  fluxo = texto_abrir(nome_arquivo, linha);
  pfluxo = fluxo;

  initscr();
  keypad(stdscr,TRUE);
  erase();
  printw("%s",texto_parastring(fluxo,pfluxo));
  refresh();
 
  int ch;
 
  while(1){
    switch(ch = getch()){
   
      case KEY_BACKSPACE:
        texto_movercursor(fluxo,&pfluxo,-1);
        texto_deletarchar(&fluxo,&pfluxo);	
        break;

      case KEY_LEFT:
        texto_movercursor(fluxo,&pfluxo,-1);
        break;
   
      case KEY_RIGHT:
        texto_movercursor(fluxo,&pfluxo,1);
        break;
   
      case KEY_UP:
        texto_movercursor(fluxo,&pfluxo,-100);
        break;
   
      case KEY_DOWN:
        texto_movercursor(fluxo,&pfluxo,64);
        break;
   
      case KEY_HOME:
        texto_movercursor(fluxo,&pfluxo,-1000);
        break;
   
      case KEY_END:
        texto_movercursor(fluxo,&pfluxo,32);
        break;
   
      case KEY_DC:
        texto_deletarchar(&fluxo,&pfluxo);
        break;
   
      case KEY_IC:
        erase();
   	    printw ("Digite a palavra a ser procurada:\n");
   	    scanw("%19s", palavra);
   	    procurar(palavra,texto_parastring(fluxo,pfluxo));
   	    break;
   	
      case '\n':
        printw("\n");
        //mostre o menu
        sair(nome_arquivo);
        exit(EXIT_SUCCESS);
      break;
   
      default:
        if(ch < 256){
          texto_inserirchar(fluxo,pfluxo,ch,linha);
        }
    
        else{
          printw("\a");
        }
    }
  
    erase();
    printw("%s",texto_parastring(fluxo,pfluxo));
    refresh();
    texto_limpar();
  }
  sair(nome_arquivo);
  exit(EXIT_SUCCESS);
}
