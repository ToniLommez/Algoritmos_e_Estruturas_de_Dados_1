/*
Guia0212 - v0.0. - 27 / 03 / 2022
Author: Marcos Antonio Lommez Candido Ribeiro - 77157
Para compilar em uma janela de comandos (terminal):
No Linux : g++ -o Guia0212 ./Guia0212.cpp
No Windows: g++ -o Guia0212.exe Guia0212.cpp
Para executar em uma janela de comandos (terminal):
No Linux : ./Guia0212
No Windows: Guia0212
*/
// lista de dependencias
#include "karel.hpp"
#include "io.hpp" // para entradas e saídas
// --------------------------- definicoes de metodos
/**
decorateWorld - Metodo para preparar o cenario.
@param fileName - nome do arquivo para guardar a descricao.
*/
void decorateWorld(const char *fileName)
{
    // colocar paredes no mundo
    world->set(2, 2, VWALL);
    world->set(2, 3, VWALL);
    world->set(2, 4, VWALL);
    world->set(2, 6, VWALL);
    world->set(2, 7, VWALL);
    world->set(2, 8, VWALL);

    world->set(4, 2, VWALL);
    world->set(4, 3, VWALL);
    world->set(4, 5, VWALL);
    world->set(4, 7, VWALL);
    world->set(4, 8, VWALL);

    world->set(5, 2, VWALL);
    world->set(5, 3, VWALL);
    world->set(5, 5, VWALL);
    world->set(5, 7, VWALL);
    world->set(5, 8, VWALL);

    world->set(7, 2, VWALL);
    world->set(7, 3, VWALL);
    world->set(7, 4, VWALL);
    world->set(7, 6, VWALL);
    world->set(7, 7, VWALL);
    world->set(7, 8, VWALL);

    world->set(3, 1, HWALL);
    world->set(4, 1, HWALL);
    world->set(6, 1, HWALL);
    world->set(7, 1, HWALL);

    world->set(5, 3, HWALL);

    world->set(3, 4, HWALL);
    world->set(4, 4, HWALL);
    world->set(6, 4, HWALL);
    world->set(7, 4, HWALL);

    world->set(3, 5, HWALL);
    world->set(4, 5, HWALL);
    world->set(6, 5, HWALL);
    world->set(7, 5, HWALL);

    world->set(5, 6, HWALL);

    world->set(3, 8, HWALL);
    world->set(4, 8, HWALL);
    world->set(6, 8, HWALL);
    world->set(7, 8, HWALL);

    // colocar um marcador no mundo
    world->set(5, 3, BEEPER);
    world->set(4, 5, BEEPER);
    world->set(6, 5, BEEPER);
    world->set(5, 7, BEEPER);
    // salvar a configuracao atual do mundo
    world->save(fileName);
} // decorateWorld ( )
/**
Classe para definir robo particular (MyRobot),
a partir do modelo generico (Robot)
Nota: Todas as definicoes irao valer para qualquer outro robo
criado a partir dessa nova descricao de modelo.
*/
class MyRobot : public Robot
{
public:
    /**
     * moveI - Metodo para mover o robot interativamente.
     * Lista de comandos disponiveis:
     * 0 - turnOff
     * 1 - turnLeft 2 - to South
     * 3 - turnRight 4 - to West
     * 5 - move 6 - to East
     * 7 - pickBeeper 8 - to North
     * 9 - putBeeper
     */
    /*
    up/down + left/right
    */
    void stepUpRight()
    {
        execute(8);
        execute(5);
        execute(6);
        execute(5);
    } // fim stepUpRight( )

    void stepDownRight()
    {
        execute(6);
        execute(5);
        execute(2);
        execute(5);
    } // fim stepDownRight( )

    void stepUpLeft()
    {
        execute(8);
        execute(5);
        execute(4);
        execute(5);
    } // fim stepUpleft( )

    void stepDownLeft()
    {
        execute(4);
        execute(5);
        execute(2);
        execute(5);
    } // fim stepDownLeft( )

    /**
    turnRight - Procedimento para virar 'a direita.
    */
    void turnRight()
    {
        // definir dado local
        int step = 0;
        // testar se o robo esta' ativo
        if (checkStatus())
        {
            // o agente que executar esse metodo
            // devera' virar tres vezes 'a esquerda
            for (step = 1; step <= 3; step = step + 1)
            {
                turnLeft();
            } // end for
        }     // end if
    }         // end turnRight ( )
    /**
    moveN - Metodo para mover certa quantidade de passos.
    @param steps - passos a serem dados.
    */
    void moveN(int steps)
    {
        // definir dado local
        int step = 0;
        // testar se a quantidade de passos e' maior que zero
        for (step = steps; step > 0; step = step - 1)
        {
            // dar um passo
            move();
        } // end if
    }     // end moveN( )
    /**
    doPartialTask - Metodo para especificar parte de uma tarefa.
    */
    void doPartialTask()
    {
        // especificar acoes dessa parte da tarefa
        moveN(3);
        turnLeft();
    } // end doPartialTask( )
    /**
    doTask - Relacao de acoes para o robo executar.
    */
    void doTask()
    {
        // definir dado local
        int step = 4;
        // especificar acoes da tarefa
        while (step > 0)
        {
            // realizar uma parte da tarefa
            doPartialTask();
            // tentar passar 'a proxima
            step = step - 1;
        } // end while
        // encerrar
        turnOff();
    } // end doTask( )
    /**
     * pickBeepers - Funcao para coletar marcadores.
     * @return quantidade de marcadores coletados
     */
    int pickBeepers()
    {
        // definir dado local
        int n = 0;
        // repetir (com teste no inicio)
        // enquanto houver marcador proximo
        while (nextToABeeper())
        {
            // coletar um marcador
            pickBeeper();
            // contar mais um marcador coletado
            n = n + 1;
        } // end while
        // retornar a quantidade de marcadores coletados
        return (n);
    } // end pickBeepers( )
    /**
     * doSquare - Metodo para especificar outro percurso.
     */
    void doSquare()
    {
        // definir dado local
        int step = 1;
        int n = 0;
        char msg[80];
        // especificar acoes da tarefa
        while (step <= 4)
        {
            // realizar uma parte da tarefa
            moveN(3);
            n = pickBeepers();
            // testar se quantidade maior que zero
            if (n > 0)
            {
                // montar a mensagem para a saida
                sprintf(msg, "Recolhidos = %d", n);
                // solicitar a exibicao da mensagem
                show_Text(msg);
            } // end if
            turnRight();
            // tentar passar 'a proxima
            step = step + 1;
        } // end while
        turnOff();
    } // end doSquare( )
    /**
     * execute - Metodo para executar um comando.
     * @param action - comando a ser executado
     */
    void execute(int option)
    {
        // executar a opcao de comando
        switch (option)
        {
        case 0: // terminar
            // nao fazer nada
            break;
        case 1: // virar para a esquerda
            if (leftIsClear())
            {
                turnLeft();
            } // end if
            break;
        case 2: // virar para o sul
            while (!facingSouth())
            {
                turnLeft();
            } // end while
            break;
        case 3: // virar para a direita
            if (rightIsClear())
            {
                turnRight();
            } // end if
            break;
        case 4: // virar para o oeste
            while (!facingWest())
            {
                turnLeft();
            } // end while
            break;
        case 5: // mover
            if (frontIsClear())
            {
                move();
            } // end if
            break;
        case 6: // virar para o leste
            while (!facingEast())
            {
                turnLeft();
            } // end while
            break;
        case 7: // pegar marcador
            if (nextToABeeper())
            {
                pickBeeper();
            } // end if
            break;
        case 8: // virar para o norte
            while (!facingNorth())
            {
                turnLeft();
            } // end while
            break;
        case 9: // colocar marcador
            if (beepersInBag())
            {
                putBeeper();
            } // end if
            break;
        default: // nenhuma das alternativas anteriores
            // comando invalido
            show_Error("ERROR: Invalid command.");
        } // end switch
    }     // end execute( )
    /**
     * moveI - Metodo para mover o robot interativamente.
     * Lista de comandos disponiveis:
     * 0 - turnOff
     * 1 - turnLeft 2 - to South
     * 3 - turnRight 4 - to West
     * 5 - move 6 - to East
     * 7 - pickBeeper 8 - to North
     * 9 - putBeeper
     */
    void moveI()
    {
        // definir dados
        int action;
        // repetir (com testes no fim)
        // enquanto opcao diferente de zero
        do
        {
            // ler opcao
            action = IO_readint("Command? ");
            // executar acao dependente da opcao
            execute(action);
        } while (action != 0);
    } // end moveI( )
    /**
     * recordActions - Metodo para mover o robot interativamente
     * e guardar a descricao da tarefa em arquivo.
     * @param fileName - nome do arquivo
     */
    void recordActions(const char *fileName)
    {
        // definir dados
        int action;
        // definir arquivo onde gravar comandos
        std::ofstream archive(fileName);
        // ler acao
        action = IO_readint("Command? ");
        // repetir enquanto acao maior ou igual a zero
        while (action >= 1)
        {
            // testar se opcao valida
            if (0 <= action && action <= 9)
            {
                // executar comando
                execute(action);
                // guardar o comando em arquivo
                archive << action << "\n";
            } // end if
            // ler acao
            action = IO_readint("Command? ");
        } // end while
        // fechar o arquivo
        // INDISPENSAVEL para a gravacao
        archive.close();
    } // end recordActions ( )
    /**
appendActions - Metodo para acrescentar comandos ao arquivo e traduzi-los.
@param filename - nome do arquivo
*/
    void appendActions(const char *fileName)
    {
        // definir dados
        int action;
        // definir arquivo para receber acrescimos ao final
        std::fstream archive(fileName, std::ios::app);
        // repetir enquanto acao diferente de zero
        do
        {
            // ler acao
            action = IO_readint("Command? ");
            // testar se opcao valida
            if (0 <= action && action <= 9)
            {
                // executar comando
                execute(action);
                // guardar o comando em arquivo
                archive << action << std::endl;
            } // end if
        } while (action != 0);
        // fechar o arquivo
        // INDISPENSAVEL para a gravacao
        archive.close();
    } // end appendActions ( )
    /**
playActions - metodo para receber comandos de arquivo.
@param fileName - nome do arquivo
*/
    void playActions(const char *fileName)
    {
        // definir dados
        int action;
        // definir arquivos de onde ler dados
        std::ifstream archive(fileName);
        // repetir enquanto houver dados
        archive >> action;     // tentar ler a primeira linha
        while (!archive.eof()) // testar se nao encontrado o fim
        {
            // mostrar mais um comando
            IO_print(IO_toString(action));
            delay(stepDelay);
            // executar mais um comando
            execute(action);
            // tentar ler a proxima linha
            archive >> action; // tentar ler a próxima linha
        }                      // end for
        // fechar o arquivo
        // RECOMENDAVEL para a leitura
        archive.close();
    } // end playActions ( )
    /**
     * dictionary - Metodo para traduzir um comando.
     * @param action - comando a ser traduzido
     */
    chars dictionary(int action)
    {
        // definir dado
        static char word[80];
        strcpy(word, ""); // palavra vazia
        // identificar comando
        switch (action)
        {
        case 1: // virar para a esquerda
            strcpy(word, "turnLeft( ); ");
            break;
        case 2: // virar para o sul
            strcpy(word, "faceSouth( ); ");
            break;
        case 3: // virar para a direita
            strcpy(word, "turnRight( ); ");
            break;
        case 4: // virar para o oeste
            strcpy(word, "faceWest( ); ");
            break;
        case 5: // mover
            strcpy(word, "move( ); ");
            break;
        case 6: // virar para o leste
            strcpy(word, "faceEast( ); ");
            break;
        case 7: // pegar marcador
            strcpy(word, "pickBeeper( );");
            break;
        case 8: // virar para o norte
            strcpy(word, "faceNorth( ); ");
            break;
        case 9: // colocar marcador
            strcpy(word, "putBeeper( ); ");
            break;
        } // end switch
        // retornar palavra equivalente
        return (&(word[0]));
    } // end dictionary( )
    /**
translateActions - Metodo para receber comandos de arquivo e traduzi-los.
@param fileName - nome do arquivo
*/
    void translateActions(const char *fileName)
    {
        // definir dados
        int action;
        // definir arquivo de onde ler dados
        std::ifstream archive(fileName);
        // repetir enquanto houver dados
        archive >> action;     // tentar ler a primeira linha
        while (!archive.eof()) // testar se nao encontrado o fim
        {
            // tentar traduzir um comando
            IO_print(dictionary(action));
            getchar();
            // guardar mais um comando
            execute(action);
            // tentar ler a proxima linha
            archive >> action; // tentar ler a proxima linha
        }                      // end for
        // fechar o arquivo
        // RECOMENDAVEL para a leitura
        archive.close();
    } // end translateActions ( )

    /**
     * moveI - Metodo para mover o robot interativamente.
     * Lista de comandos disponiveis:
     * 0 - turnOff
     * 1 - turnLeft 2 - to South
     * 3 - turnRight 4 - to West
     * 5 - move 6 - to East
     * 7 - pickBeeper 8 - to North
     * 9 - putBeeper
     */
    void exercicio2()
    {
        execute(6);
        execute(5);
        execute(8);
        execute(5);
        execute(5);
        execute(5);
        execute(5);
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        if (nextToABeeper())
        {
            pickBeeper();
        } // fim se
        execute(4);
        execute(5);
        execute(5);
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        execute(5);
        execute(5);

        // parte 2

        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        execute(5);
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        if (nextToABeeper())
        {
            pickBeeper();
        } // fim se
        execute(8);
        execute(5);
        execute(5);
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        execute(5);

        // parte 3
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        execute(5);
        execute(5);
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        if (nextToABeeper())
        {
            pickBeeper();
        } // fim se
        execute(6);
        execute(5);
        execute(5);
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        execute(5);
        execute(5);

        //parte 4
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        execute(5);
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        if (nextToABeeper())
        {
            pickBeeper();
        } // fim se
        execute(2);
        execute(5);
        execute(5);
        if (rightIsClear())
        {
            turnRight();
            move();
        } // fim se
        execute(5);
        execute(5);
        execute(5);
        execute(8);
    }
}; // end class MyRobot

// --------------------------- acao principal
/**
Acao principal: executar a tarefa descrita acima.
*/
int main()
{
    // definir o contexto
    // criar o ambiente e decorar com objetos
    // OBS.: executar pelo menos uma vez,
    // antes de qualquer outra coisa
    // (depois de criado, podera' ser comentado)
    world->create(""); // criar o mundo
    decorateWorld("Guia0212.txt");
    world->show();
    // preparar o ambiente para uso
    world->reset();              // limpar configuracoes
    world->read("Guia0212.txt"); // ler configuracao atual para o ambiente
    world->show();               // mostrar a configuracao atual
    set_Speed(1);                // definir velocidade padrao
    // criar robo
    MyRobot *robot = new MyRobot();
    // posicionar robo no ambiente (situacao inicial):
    // posicao(x=1,y=1), voltado para direita, com zero marcadores, nome escolhido )
    robot->create(1, 1, NORTH, 0, "Karel");
    // // executar tarefa
    robot->exercicio2();
    world->close();
    // encerrar programa
    getchar();
    return (0);
} // end main ( )
// ---------------------------------------------- testes
//
// Versao Teste
// 0.1 01. ( OK ) teste inicial
// 0.2 01. ( OK ) teste da repeticao para virar 'a direita
// 0.3 01. ( OK ) teste da repeticao para percorrer um quadrado
//
