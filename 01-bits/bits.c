/*
 * Primeiro laboratório de Computadores e Programação
 *
 * A ideia do laboratório é mostrar ao aluno outras formas de fazer as operações
 * que ele já está acostumado a fazer, mas de formas diferentes.
 * Criamos esse desafio com o objetivo de fazê-lo pensar em diferentes formas de se
 * atingir o mesmo resultado. Num cenário real, saber quais instruções são melhor
 * otimizadas pelo compilador pode ajudar muito a perfomance de um programa.
 *
 * O aluno deverá usar apenas um subset de operações de C para realizar o que
 * for pedido no enunciado.
 *
 * Todas as operações permitidas serão especificadas em cada questão.
 * Não está permitido o uso de if-else, for, while, switch, etc.
 *
 * Forma de avaliação:
 *      - Quantas operações o aluno utlizou para realizar a tarefa (se está dentro da quantidade aceitável)
 *      - Explicação do código -- deverá ser o mais claro possível,
 *          imaginando que qualquer pessoa sem conhecimento prévio da
 *          matéria consiga entender o que foi feito, em detalhes.
 *      - As resoluções com menos operações do que a do monitor terão bonificação.
 *
 * Assinatura:
 *      Aluno: Daniel Lopes de Sousa
 *      DRE: 114143976
 *      Versão do GCC utilizada: 9.3.0
 * 
 *      Aluno: Níkolas Ribeiro curtinhas Pimentel
 *      DRE: 
 *      Versão do GCC utilizada: 
 *
 * Se descobrir algo errado, inesperado ou engraçado com o código,
 * entre em contato com o monitor!
 */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>
#include <stdint.h>

/*
 * Diferente sem !=
 *      Permitido:
 *          Operações bitwise: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 6
 *      Monitor: 3
 *
 *      Retorna 1 se x != y, 0 caso contrário
 *
 *      Exemplo:
 *          ehDiferente(10, 10) -> 0
 *          ehDiferente(16, 8) -> 1
 */
int32_t ehDiferente(int32_t x, int32_t y) {
    /*
     * se x^y = 0, x=y
     */
    return !(!(x^y));
}

/*
 * Número é zero ou não
 *      Permitido:
 *          Operações: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 3
 *      Monitor: 1
 *
 *      Retorna 1 se x é 0, retorna 0 caso contrário
 *
 *      Exemplo:
 *          ehZero(0) -> 1
 *          ehZero(7) -> 0
 */
int32_t ehZero(int32_t x) {
    /* 
     * A operação "ou exclusivo" (representada por ^) retornará um valor falso
     * sempre que as entradas forem iguais e verdadeiro caso sejam diferentes.
     * Por isso, podemos usá-la para verificar se um valor é igual a zero,
     * bastando fazer a operação de "ou exclusivo" com 0.
     * 
     * Como o resultado será 0 caso o número seja igual a 0 e 1 se for diferente,
     * temos que fazer uma operação de negação (representada por !) que muda o 
     * valor de verdadeiro (1) para falso (0) e vice-versa. Assim, teremos a 
     * saída 1 caso o número seja zero e 0 se não for.
     * 
     */
    return !(x^0);
}

/*
 * Número é ímpar ou não
 *      Permitido:
 *          Operações: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 4
 *      Monitor: 1
 *
 *      Retorna 1 se x é ímpar, retorna 0 caso contrário
 *
 *      Exemplo:
 *          ehImpar(0) -> 0
 *          ehImpar(7) -> 1
 */
int32_t ehImpar(int32_t x) {
    /*
     * Todo número par em binário tem como algarismo menos significativa um 0.
     * Só se dispõe de dois números para representação binária, e começamos os 
     * inteiros em zero, que é um número par. Ou seja, quando o algarismo menos 
     * significativo for 0, o incremento resultará na mudança desse algarismo para 1. 
     * Por outro lado, quando o algarismo menos significativo for 1, o incremento 
     * resultará na mudança dele para 0 com o valor de 1 "carregado" para o próximo 
     * algarismo mais significativo.
     * 
     * 0 decimal = 0 binário -> par
     * 1 decimal = 1 binário -> ímpar
     * 2 decimal = 10 binário -> par
     * 3 decimal = 11 binário -> ímpar
     * 
     * Assim, podemos utilizar a operação de "e" para determinar se o número é par 
     * ou ímpar. Quando fazemos 0 & 1 (0 "e" 1) temos como resultado 0, já quando 
     * fazemos 1 & 1 temos como resultado 1. Isso significa que, caso o algarismo menos 
     * significativo seja 0 (ou seja, se o número for par), o resultado da operação 
     * "e" com 1 será 0. Caso contrário, se o número for ímpar, o resultado será 1.
     */
    return 0x1&x;
}

/*
 * Módulo 4
 *      Permitido:
 *          Operações: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 3
 *      Monitor: 1
 *
 *      Retorna x % 4
 *
 *      Exemplo:
 *          mod4(1) -> 1
 *          mod4(7) -> 3
 */
int32_t mod4(int32_t x) {
    return x&3;
}

/*
 * Número positivo ou não
 *      Permitido:
 *          Operações: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 5
 *      Monitor: 2
 *
 *      Retorna 1 se número é positivo, 0 caso contrário
 *
 *      Exemplo:
 *          ehPositivo(878) -> 1
 *          ehPositivo(-343) -> 0
 */
int32_t ehPositivo(int32_t x) {
    /*
     * A representação de números inteiros em ponto flutuante é feita da seguinte
     * forma. O algarismo (ou bit) mais significativo representa o valor do sinal
     * (0 para números positivos, 1 para números negativos), seguido por 8 bits 
     * que representam o expoente e mais 23 bits para a mantissa. O número inteiro
     * é definido por:
     * 
     * (-1)^s * M * 2^e
     * 
     * onde s = sinal, M = mantissa e e = expoente.
     * 
     * Assim, para verificar se um número é positivo ou não, só precisamos saber
     * se o bit de sinal é 0 ou 1. Para fazer isso, podemos executar uma operação
     * de "e" (&) com o menor número inteiro negativo, representado pelo número 
     * que possui o bit mais significativo em 1 e o restante em 0:
     * 
     * 0x80000000 = 1000...000 = -2147483648
     * 
     * A operação "e" retorna 0 caso as entradas sejam ambas 0 e 1 caso elas
     * sejam diferentes. Portanto, se o número que queremos verificar for positivo, 
     * a operação retornará um número com o primeiro bit em 0 (pois 0 & 0 = 0) e 
     * todos os outros bits também em 0, que corresponde ao número 0 em si. Já se 
     * o número for negativo, o valor retornado será uma sequência de bits em que
     * o primeiro algarismo é 1 e o restante é 0, que corresponde ao nosso menor
     * valor negativo (0x80000000).
     * 
     * A operação de negação (!) transforma valores verdadeiros em falsos e vice-versa.
     * Como a linguagem C define 0 como falso e qualquer valor diferente de zero como
     * verdadeiro, só precisamos executar a negação (!) no resultado, pois queremos que
     * o valor retornado seja 1 caso o número seja positivo e 0 caso contrário.
     */
    return !(0x80000000&x);
}

/*
 * Negativo sem -
 *      Permitido:
 *          Operações: ~ & ^ | ! << >> +
 *
 *      Número máximo de operações: 4
 *      Monitor: 2
 *
 *      Retorna -x
 *
 *      Exemplo:
 *          negativo(1) -> -1
 *          negativo(42) -> -42
 */
int32_t negativo(int32_t x) {
    /*
     * Na representação de números positivos e negativos, consideram-se os números 
     * com o primeiro algarismo (bit) igual a 0 como positivos e aqueles com o 
     * primeiro algarismo em 1 como negativos. Assim, podemos alterar esse bit para
     * mudar o sinal do número, porém, como nenhum outro bit foi alterado, o número
     * resultante será diferente.
     * 
     * Podemos pensar nessa representação como um círculo ou roda. Se diminuírmos
     * em 1 o menor valor negativo que pode ser representado, -2147483648, também 
     * representado por 0x80000000, teremos o maior valor positivo, que é 2147483647.
     * Da mesma forma, se somarmos em 1 o maior valor positivo, 2147483647, também
     * representado por 0x7FFFFFFF em hexadecimal, teremos como resultado o menor
     * valor negativo, que é -2147483648. Toda vez que a representação chega no seu
     * limite, ela faz uma "volta" e retorna para o que pode ser representado dessa
     * forma. 
     * 
     * Por isso, voltando a analogia do círculo, para converter um número nessa 
     * representação, podemos encontrar o número que é diretamente oposto a ele, ou 
     * seja, cuja distância para o nosso número seja o diâmetro do nosso círculo.
     * Podemos encontrar esse número fazendo uma operação de negação bit a bit, também
     * representada pelo símbolo ~, ou seja, tranformando todos os bits 0 em 1 e 
     * vice-versa. 
     * 
     * Como o número de inteiros que pode ser representado é diferente para positivos 
     * e negativos (podemos representar um número negativo a mais), toda vez que 
     * negarmos cada bit de um número, o valor resultante será menor do que o valor
     * que esperamos encontrar em 1:
     * 
     * ~x = -x-1
     * 
     * Portanto, para corrigir isso, basta somar em 1 o valor encontrado com a 
     * operação de negação.
     */
    return (~x)+1;
}

/*
 * Implementação do | usando bitwise
 *      Permitido:
 *          Operações: ~ & ^ ! << >>
 *
 *      Número máximo de operações: 7
 *      Monitor: 4
 *
 *      Retorna x | y
 *
 *      Exemplo:
 *          bitwiseOr(1, 2) -> 3
 *              1 | 10 -> 11
 *          bitwiseOr(3, 9) -> 11
 *              11 | 1001 -> 1011
 */
int32_t bitwiseOr(int32_t x, int32_t y) {
    /*
     * Cheguei nesse resultado com as tabelas verdade das operações & e ^. 
     * Explicar melhor.
     */
    return ~((~(x&y))&(~x^y));
}

/*
 * Multiplicação por 6
 *      Permitido:
 *          Operações: << >> | ! & +
 *
 *      Número máximo de operações: 3
 *      Monitor: 3
 *
 *      Retorna x multiplicado por 6
 *
 *      Exemplo:
 *          mult6(36) -> 216
 */
int32_t mult6(int32_t x) {
    /*
     * Na operação de deslocamento à esquerda, simbolizada por <<, é feito o 
     * deslocamento de todos os bits n vezes para a esquerda, preenchendo os espaços
     * na direita com zeros. Por exemplo, 0001 << 2 = 0100. Matematicamente falando, 
     * x << n equivale a multiplicar x por 2^n.
     * 
     * Podemos escrever uma multiplicação por 6 da seguinte forma:
     * 
     * 6*x = (4+2)x = 4*x + 2*x
     * 
     * 4 e 2 são potências de 2 (2^2 e 2^1, respectivamente), que estão sendo 
     * multiplicadas por x, o que nos dá a chance de usar a operação de deslocamento 
     * à esquerda. Assim, temos:
     * 
     * 2^2*x + 2^1*x = x<<2 + x<<1
     */
    return (x<<2)+(x<<1);
}

/*
 * Bit na posição p do inteiro x
 *      Permitido:
 *          Operações bitwise: << >> | & + -
 *
 *      Número máximo de operações: 10
 *      Monitor: 6
 *
 *      Retorna o valor do bit na posição p no inteiro x
 *      Valor de retorno pode ser apenas 0 ou 1
 *
 *      p será um valor entre 0 e 31
 *
 *      Exemplo:
 *          23 em binário: 0   0 ... 0 1 0 1 1 1
 *               posições: 31 30 ... 5 4 3 2 1 0
 *
 *          bitEmP(23, 31) -> 0
 *          bitEmP(23, 5) -> 0
 *          bitEmP(23, 4) -> 1
 *          bitEmP(23, 3) -> 0
 *          bitEmP(23, 2) -> 1
 *          bitEmP(23, 1) -> 1
 *          bitEmP(23, 0) -> 1
 *
 */
int32_t bitEmP(int32_t x, uint8_t p) {
    return (((0x1<<p)&x)>>p)&0x1;
}

/*
 * Byte na posição p do inteiro x
 *      Permitido:
 *          Operações: << >> | ! &
 *
 *      Número máximo de operações: 6
 *      Monitor: 3
 *
 *      Retorna o valor do bit na posição p no inteiro x
 *      Valor de retorno pode ser entre 0 e 0xFF
 *
 *      p será um valor entre 0 e 3
 *      0 retorna LSB
 *      3 retorna MSB
 *
 *      Exemplo:
 *          byteEmP(0x12345678, 0) -> 0x78
 *          byteEmP(0x12345678, 1) -> 0x56
 *          byteEmP(0x12345678, 2) -> 0x34
 *          byteEmP(0x12345678, 3) -> 0x12
 *
 */
int32_t byteEmP(int32_t x, uint8_t p) {
    return ((0xFF<<(p<<3))&x)>>(p<<3);
}

/*
 * Negação lógica sem !
 *      Permitido:
 *          Operações: << >> | & + ~
 *
 *      Número máximo de operações: 9
 *      Monitor: 5
 *
 *      Retorna 1 se x == 0, retorna 0 caso contrário
 *
 *      Exemplo:
 *          negacaoLogica(0) -> 1
 *          negacaoLogica(37) -> 0
 *
 */
int32_t negacaoLogica(int32_t x) {
    return  ~(x&&1)+2;
}

void teste(int32_t saida, int32_t esperado) {
    static uint8_t count = 0;
    count++;
    if(saida == esperado)
        printf(ANSI_COLOR_GREEN "PASSOU! Saída: %-10d\t Esperado: %-10d\n" ANSI_COLOR_RESET,
            saida, esperado);

    else
        printf(ANSI_COLOR_RED "%d: FALHOU! Saída: %-10d\t Esperado: %-10d\n" ANSI_COLOR_RESET,
            count, saida, esperado);
}

int main() {
    puts(ANSI_COLOR_BLUE "Primeiro lab - bits" ANSI_COLOR_RESET);
    puts("");

    puts("Teste: ehDiferente");
    teste(ehDiferente(1, 1), 0);                    // 1 NÃO É diferente de 1, deve retornar 0
    teste(ehDiferente(7, 13), 1);                   // 7 É diferente de 13, deve retornar 1
    teste(ehDiferente(1, -2147483648), 1);
    teste(ehDiferente(2147483647, -1), 1);
    teste(ehDiferente(1, -1), 1);
    teste(ehDiferente(2147483647, 2147483647), 0);
    teste(ehDiferente(0,0), 0);
    teste(ehDiferente(123, 124), 1);
    teste(ehDiferente(1073741823, 1073741823), 0);
    teste(ehDiferente(1073741823, 1073741822), 1);
    teste(ehDiferente(1073741823, -1073741824), 1);
    teste(ehDiferente(-1073741824, -1073741824), 0);
    teste(ehDiferente(-1073741824, -2147483648), 1);
    teste(ehDiferente(1024, 1000), 1);
    teste(ehDiferente(2048, -2048), 1);
    teste(ehDiferente(0xFF, -0xFF), 1);
    puts("");

    puts("Teste: ehImpar");
    teste(ehImpar(2), 0);       // 2 NÃO É impar, deve retornar 0
    teste(ehImpar(1), 1);       // 1 É impar, deve retornar 1
    teste(ehImpar(3), 1);
    teste(ehImpar(13), 1);
    teste(ehImpar(100), 0);
    teste(ehImpar(125), 1);
    teste(ehImpar(1024), 0);
    teste(ehImpar(2019), 1);
    teste(ehImpar(2020), 0);
    teste(ehImpar(-1), 1);
    teste(ehImpar(-27), 1);
    teste(ehImpar(-1073741825), 1);
    teste(ehImpar(1073741824), 0);
    teste(ehImpar(2147483647), 1);
    teste(ehImpar(-2147483648), 0);
    teste(ehImpar(0), 0);
    puts("");

    puts("Teste: mod4");
    teste(mod4(4), 0);       // 4 % 4 = 0
    teste(mod4(7), 3);       // 7 % 4 = 3
    teste(mod4(16), 0);
    teste(mod4(2049), 1);
    teste(mod4(404), 0);
    teste(mod4(8197), 1);
    puts("");

    puts("Teste: ehZero");
    teste(ehZero(1), 0);
    teste(ehZero(10000), 0);
    teste(ehZero(0), 1);
    teste(ehZero(2147483647), 0);
    teste(ehZero(0), 1);
    teste(ehZero(-0), 1);
    teste(ehZero(0x0), 1);
    teste(ehZero(0xFF), 0);
    puts("");

    puts("Teste: ehPositivo");
    teste(ehPositivo(-1), 0);
    teste(ehPositivo(1), 1);
    teste(ehPositivo(2037), 1);
    teste(ehPositivo(-2037), 0);
    teste(ehPositivo(-2147483648), 0);
    teste(ehPositivo(-2147483648/2), 0);
    teste(ehPositivo(2147483647), 1);
    teste(ehPositivo(2147483648), 0);
    puts("");

    puts("Teste: negativo");
    teste(negativo(0), 0);
    teste(negativo(-12), 12);
    teste(negativo(-20), 20);
    teste(negativo(1109563935), -1109563935);
    puts("");

    puts("Teste: bitwiseOr");
    teste(bitwiseOr(48, 80), 112);
    teste(bitwiseOr(448, 24), 472);
    teste(bitwiseOr(106, 42), 106);
    teste(bitwiseOr(832, 625), 881);
    puts("");

    puts("Teste: bitEmP");
    teste(bitEmP(1, 0), 1);   //    b01 => retorna 1
    teste(bitEmP(1, 1), 0);   //    b01 => retorna 0
    teste(bitEmP(2, 0), 0);   //    b10 => retorna 0
    teste(bitEmP(2, 1), 1);   //    b10 => retorna 1
    teste(bitEmP(9, 2), 0);   //  b1001 => retorna 0
    teste(bitEmP(-4194305, 22), 0);
    teste(bitEmP(9, 3), 1);
    teste(bitEmP(16, 3), 0);
    teste(bitEmP(24, 2), 0);
    teste(bitEmP(0x1 << 31, 31), 1);
    teste(bitEmP(-1073741825, 30), 0);
    teste(bitEmP(-1073741825, 31), 1);
    puts("");

    puts("Teste: byteEmP");
    teste(byteEmP(0x766B, 1), 0x76);
    teste(byteEmP(0x766B, 0), 0x6B);
    teste(byteEmP(0x8420, 0), 0x20);
    teste(byteEmP(0x12345678, 3), 0x12);   // retorna 0x12
    teste(byteEmP(0x12345678, 2), 0x34);   // retorna 0x34
    teste(byteEmP(0x12345678, 1), 0x56);   // retorna 0x56
    teste(byteEmP(0x12345678, 0), 0x78);   // retorna 0x78
    teste(byteEmP(0x321, 1), 0x03);        // retorna 0x03
    teste(byteEmP(0x321, 0), 0x21);        // retorna 0x21
    puts("");

    puts("Teste: mult6");
    teste(mult6(1), 6);
    teste(mult6(6), 36);
    teste(mult6(3), 18);
    teste(mult6(-1), -6);
    teste(mult6(-357913391), -2147480346);
    teste(mult6(357913941), 2147483646);
    puts("");

    puts("Teste: negacaoLogica");
    teste(negacaoLogica(0), 1);
    teste(negacaoLogica(1), 0);
    teste(negacaoLogica(-1), 0);
    teste(negacaoLogica(64), 0);
    teste(negacaoLogica(-64), 0);
    teste(negacaoLogica(2147483647), 0);
    teste(negacaoLogica(-2147483648), 0);
    puts("");
}
