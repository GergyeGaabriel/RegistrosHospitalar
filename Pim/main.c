#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iso646.h>

// MUDAR COR
enum DOS_COLORS {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
    LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
    LIGHT_RED, LIGHT_MAGENTA, LIGHT_YELLOW, WHITE

};

void textcolor (iColor){
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}

struct cadastro_paciente{
    char nome[150];
    char comorbidade[150];
    char cpf[50],tel[50];
    int dia_diag,mes_diag,ano_diag;
    int dia_nas,mes_nas,ano_nas,cep,num,idade;
    char rua[50];
    char bairro[25];
    char cidade[25];
    char uf[3];
    char Email [150];

}cad;

struct central_saude{
    int cep,idade;
}cad_central;

//validar mes
int validar_mes(int c){
    int x=c;
           while(x>=13){
            textcolor(RED);
            printf("\nDIGITE UM VALOR VALIDO:  ");
            textcolor(WHITE);
             scanf("%d", &x);
           }
}

//Validar Números
int validar_num(int numero){

    char digitado[50];
    char c;
    int i=0;

     do
    {
       c=getch();
       if (isdigit(c)!=0)
       {
          digitado[i] = c;
          i++;
          printf ("%c", c);
       }
       else if(c==8&&i)
       {
          digitado[i]='\0';
          i--;
          printf("\b \b");
       }
    }while(c!=13);

    digitado[i]='\0';

    numero = atoi(digitado);
    return numero;
}

//validar letras
int validar_letra(char *dig){

    char c;
    int i=0;

    do
    {
       c=getch();
       if (isalpha(c)!=0 || c==32)
       {
          dig[i] = c;
          i++;
          printf ("%c", c);
       }
       else if(c==8&&i)
       {
          dig[i]='\0';
          i--;
          printf("\b \b");
       }
    }while(c!=13);

    dig[i]='\0';

}

// Buscar cadastro
int buscar(){
     FILE *arq;
    if ((arq = fopen("paciente.txt","rb")) == NULL){
    printf("Erro ao abrir o arquivo. O programa sera fechado.\n");
    system("pause");
    exit(1);
    }

    if(fread(&cad,sizeof(struct cadastro_paciente),1, arq)==1){
     textcolor(RED);
     printf("1:");
     textcolor(WHITE);
     printf("\n\nNome: %s",cad.nome);
     printf("\nTelefone: %s",cad.tel);
     printf("\nidade: %d",cad.idade);
     printf("\nCPF: %s",cad.cpf);
     printf("\nComorbidade: %s",cad.comorbidade);
     printf("\nData de nascimento: %d",cad.dia_nas);
     printf("/%d",cad.mes_nas);
     printf("/%d",cad.ano_nas);
     printf("\nData diagnostico: %d",cad.dia_diag);
     printf("/%d",cad.mes_diag);
     printf("/%d",cad.ano_diag);
     textcolor(LIGHT_YELLOW);
     printf("\n-------- Endereco --------");
     textcolor(WHITE);
     printf("\nRua: %s",cad.rua);
     printf("\nBairro: %s",cad.bairro);
     printf("\nNumero: %d",cad.num);
     printf("\nUF: %s",cad.uf);
     printf("\nCidade: %s",cad.cidade);
     printf("\nCEP: %d",cad.cep);
     printf("\n\n");
    }
    fclose(arq);
    system ("pause");

}

// Comorbidade
comor(){
    char c_esp;
    printf("(Y/N) Possui comorbidade? ");
     scanf("%s",&c_esp);

      if(c_esp=='Y' || c_esp=='y')
        {
         printf("Comorbidade: ");
         scanf("%s",&cad.comorbidade);
        } else {
             printf("Comorbidade: OK!\n");
        }
}

//Transferir valores para a struct central saude
Central_saude(){

    FILE *arq;
    if ((arq = fopen("central_saude.txt","wb")) == NULL){
    printf("Erro ao abrir o arquivo. O programa sera fechado.\n");
    system("pause");
    exit(1);
    }

         cad_central.cep= cad.cep;
         cad_central.idade= cad.idade;

    if(fwrite(&cad_central,sizeof(struct central_saude),1, arq)==1){

    }
    fclose(arq);

}

// Buscar central
int buscar_central(){
     FILE *arq;
    if ((arq = fopen("central_saude.txt","rb")) == NULL){
    printf("Erro ao abrir o arquivo. O programa sera fechado.\n");
    system("pause");
    exit(1);
    }

    if(fread(&cad_central,sizeof(struct central_saude),1, arq)==1){
     textcolor(RED);
     printf("1:");
     textcolor(WHITE);
     printf("\nidade: %d",cad_central.idade);
     printf("\nCEP: %d",cad_central.cep);
     printf("\n\n");
    }
    fclose(arq);
    system ("pause");

}

int validar_num1(char *digitado){
    char c;
    int i=0;

     do
    {
       c=getch();
       if (isdigit(c)!=0)
       {
          digitado[i] = c;
          i++;
          printf ("%c", c);
       }
       else if(c==8&&i)
       {
          digitado[i]='\0';
          i--;
          printf("\b \b");
       }
    }while(c!=13);

    digitado[i]='\0';



}

// Cadastar pacientes
int cadastrar(){
    FILE *arq;
    if ((arq = fopen("paciente.txt","wb")) == NULL){
    printf("Erro ao abrir o arquivo. O programa sera fechado.\n");
    system("pause");
    exit(1);
    }
    printf("+====================================+\n");
    textcolor(LIGHT_YELLOW);
    printf("         CADASTRO - PACIENTE        \n");
    textcolor(WHITE);
    printf("+====================================+\n\n");

     char c_esp;
     textcolor(RED);
     printf("1:");
     textcolor(WHITE);
     printf("\nNome: ");
     validar_letra(cad.nome);

     printf("\nCpf: ");
     validar_num1(cad.cpf);


     printf("\nTelefone: ");
     validar_num1(cad.tel);

     printf("\nE-mail: ");
     scanf("%s",cad.Email);
     comor();


     printf("Data diagnostico: ");
     cad.dia_diag= validar_num(cad.dia_diag);
     printf("/");
     cad.mes_diag= validar_num(cad.mes_diag);
     validar_mes(cad.mes_diag);
     printf("/");
     cad.ano_diag= validar_num(cad.ano_diag);

     printf("\nData Nascimento: ");
     cad.dia_nas= validar_num(cad.dia_nas);
     printf("/");
     cad.mes_nas= validar_num(cad.mes_nas);
     validar_mes(cad.mes_nas);
     printf("/");
     cad.ano_nas= validar_num(cad.ano_nas);
     printf("\n");



     cad.idade=2022-cad.ano_nas;
     printf("Idade: %d",cad.idade);

     if(cad.idade>65){
         printf("\nGrupo de Risco: Pertence");
         Central_saude();
     }

                   textcolor(LIGHT_YELLOW);
                   printf("\n\n +==============Endereco==================+\n");
                   textcolor(WHITE);


                       printf("| Numero:");
                       cad.num=validar_num(cad.num);
                       printf(" ");
                       printf("| Rua:");
                       validar_letra(cad.rua);
                       printf(" ");
                       printf("| Cidade:");
                       validar_letra(cad.cidade);
                       printf(" ");
                       printf("\n| Bairro:");
                       validar_letra(cad.bairro);
                       printf(" ");
                       printf("| Uf:");
                       validar_letra(cad.uf);
                       printf(" ");
                       printf("| Cep:");
                       cad.cep= validar_num(cad.cep);

                    printf("\n\n +========================================+\n");

    if(fwrite(&cad,sizeof(struct cadastro_paciente),1, arq)==1){
     textcolor(LIGHT_YELLOW);
     printf("\n\n Dados gravados com sucesso....\n\n");
     textcolor(WHITE);
    }
    fclose(arq);
    system ("pause");
}

// menu
int menu (int A){
            printf("\n (1) CADASTRAR PACIENTE");
            printf("\n (2) BUSCAR PACIENTES");
            printf("\n (3) CENTRAL DA SECRETARIA DA SAUDE");
            printf("\n (4) SAIR \n");
            printf("  :");
            scanf("%d",&A);
            return(A);
            system ("pause");
}

//Logar
int logar(){
    // var
    char Coflogin[]="Unip1";
    char Cofsenha[]="1234";
    int Confr = 0;
    char login[10], senha[10];

    //inicio

     printf("+====================================+\n");
     textcolor(LIGHT_YELLOW);
     printf("      SISTEMA DE CONTROLE - COVID       ");
     textcolor(WHITE);
     printf("\n+====================================+");
     textcolor(LIGHT_YELLOW);
     printf("\n\n Autenticacao Usuario:\n\n");
     textcolor(WHITE);


     printf("- Login: ");
     scanf("%s",&login);
     printf("- Senha: ");
     scanf("%s",&senha);

    int Con_l= strcmp(login, Coflogin);
    int Con_s= strcmp(senha, Cofsenha);

    if( Con_l==0 && Con_s==0)
    {

        textcolor(LIGHT_YELLOW);
        printf("\n Logado com sucesso...\n\n");
        textcolor(WHITE);


        return(Confr= 1);

    } else {
        system("cls");
        int a;
        textcolor(RED);
        printf("                  ---- SENHA OU LOGIN INCORRETOS ----              \n");
        printf("---- (4) SAIR OU DIGITE QUALQUER NUMERO PARA TENTAR NOVAMENTE ---- \n\n");
        textcolor(WHITE);
        printf(" :");
        a=validar_num(a);

        if(a==4){
        exit(1);
                }


             return(Confr);
           }

}





int main()
{
SetConsoleTitle("Hospital3.0");
int aux;
int confirmar_LS;
int a;

do{
    system("cls");
    confirmar_LS = logar();

  }while(confirmar_LS==0);

system ("pause");


if(confirmar_LS==1)
    {

           do{
                 system("cls");
                 aux= menu(aux);

                  switch(aux)
                    {

                    case 1:
                     system("cls");
                     cadastrar();
                    break;

                    case 2:
                     system("cls");
                     buscar();
                    break;

                    case 3:
                    system("cls");
                    printf("+====================================+\n");
                    textcolor(LIGHT_YELLOW);
                    printf("      RELATORIO CENTRAL DE SAUDE        \n");
                    textcolor(WHITE);
                    printf("+====================================+\n\n");
                    buscar_central();
                    break;

                    case 4:
                    system("cls");

                    printf("Ate a proxima!\n");
                    textcolor(WHITE);
                    system ("pause");
                    break;

                    default:
                    system("cls");
                    textcolor(RED);
                    printf("DIGITE UM VALOR VALIDO\n");
                    system ("pause");
                    textcolor(WHITE);
                    break;

                     }

                } while(aux!=4);


    }





}
