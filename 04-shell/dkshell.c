/*
 * Laboratório 4 de Computadores e Programação
 * Alunos:  Daniel Lopes de Sousa 
 *          Níkolas Ribeiro Curtinhas Pimentel
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// Numero maximo de argumentos aceitos na linha de comando
#define MAXARGS 10
// Tamanho maximo da linha de comando
#define MAXLINE 1000

// Variavel definida por libc
extern char **environ;

// Prototipos de funcao
void dkInit();
void eval (char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void dkhelp();
void dkcd(char **argv);
int dkfg(pid_t pid);
int dkbg(pid_t pid);
void sigIntHandler();
void sigTstpHandler();

int main(int argc, char **argv, char **envp) {

    char cmdline[MAXARGS];  // linha de comando

    // boas vindas e inicialização de sinais, etc...
    dkInit();

    // loop principal
    while(1) {
        // leitura da linha de comando
        printf("dk> ");
        fgets(cmdline, MAXLINE, stdin);

        if(feof(stdin))
            exit(0);

        // analise da linha
        eval(cmdline);
    }
}

void dkInit() {
    // imprime instruções
    dkhelp();

    // define os handlers para SIGINT e SIGSTP
    signal(SIGINT, sigIntHandler);
    signal(SIGTSTP, sigTstpHandler);
}

// Analisa a linha de comando para executar comandos
void eval (char *cmdline) {
    char *argv[MAXARGS];    // lista de argumentos para execve()
    char buf[MAXLINE];      // para a linha de comando modificada
    int bg;                 // identifica processo em background
    pid_t pid;              // pid do processo

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    if(argv[0] == NULL)
        return;             // ignora linha vazia

    if(!builtin_command(argv)) {
        if((pid = fork()) == 0) {       // filho executa o trabalho
            if (execve(argv[0], argv, environ) < 0) {
                printf("Erro: Comando '%s' não encontrado.\n", argv[0]);
                exit(0);
            }
        }

        // pai espera pelo trabalho no foreground terminar
        if(!bg) {
            int status;
            if(waitpid(pid, &status, 0) < 0)
                printf("Erro: Waitpid error.\n");
        } else {
            printf("%d %s", pid, cmdline);
        }
    }

    return;
}

// Gera o vetor argv
int parseline(char *buf, char **argv) {
    char *delim;            // aponta para primeiro delimitador de espaço
    int argc;               // numero de argumentos
    int bg;                 // identifica processo em background

    buf[strlen(buf)-1] = ' ';       // substitui '\n' com espaço
    while(*buf && (*buf == ' '))    // ignora espaços
        buf++;
    
    // constroi lista argv
    argc = 0;
    while((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while(*buf && (*buf == ' '))    // ignora espaços
            buf++;
    }

    argv[argc] = NULL;

    if(argc == 0)       // ignora linha vazia
        return 1;

    // processo executa em background?
    if((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}

// Se primeiro argumento é um comando, executa e retorna 1
int builtin_command(char **argv) {
    if(!strcmp(argv[0], "quit"))    // comando quit
        exit(0);
    if(!strcmp(argv[0], "&"))       // ignora & sozinho
        return 1;
    if(!strcmp(argv[0], "help")) {  // comando help
        dkhelp(); 
        return 1;
    }
    if(!strcmp(argv[0], "cd")) {    // comando cd
        dkcd(argv);
        return 1;
    }    
    if(!strcmp(argv[0], "fg")) {    // comando fg
        return dkfg(atoi(argv[1]));
    }    
    if(!strcmp(argv[0], "bg")) {    // comando bg
        return dkfg(atoi(argv[1]));
    }    

    return 0;       // nao e um comando
}

// Imprime pequena explicacao e lista de comandos validoos
void dkhelp() {
    printf("\n");
    printf("DK Shell - Versão 1.0\n");
    printf("Escreva um comando e aperte enter.\n");
    printf("\n");
    printf("Os comandos a seguir são válidos:\n");
    printf("- quit\n");
    printf("- help\n");
    printf("- quit\n");
    printf("- cd\n");
    printf("- fg\n");
    printf("- bg\n");
    printf("\n");
    printf("Por: Daniel Lopes e Nikolas Pimentel\n");
    printf("\n");
}

// Altera o diretorio corrente
void dkcd(char **argv) {
    if (argv[1] == NULL) {
        printf("Erro: use cd <diretorio>\n");
    } else {
        if (chdir(argv[1]) != 0) {
            printf("Erro: diretório inexistente.\n");
        }
    }
}

// Coloca processo no foreground
int dkfg(pid_t pid) {
    if(kill(pid, SIGCONT) < 0) {
        printf("Erro: Processo não encontrado.\n");
        return 0;
    }

    return 1;
}

// Coloca processo no background
int dkbg(pid_t pid) {
    if(kill(pid, SIGSTOP) < 0) {
        printf("Erro: Processo não encontrado.\n");
        return 0;
    }

    return 1;
}

// Handler de sinal
void sigIntHandler() {
    //if(kill(-getpid(), SIGINT) < 0) 
    //    printf("Erro: Kill error.\n");
    return;
}

void sigTstpHandler() {
    // if(kill(-getpid(), SIGTSTP) < 0) 
    //    printf("Erro: Kill error.\n");
    return;
}
