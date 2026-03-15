#include <raylib.h>
#include "arquivo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CEL 75  // tamanho da célula do tabuleiro (ajustei no olho)
#define OFFSET_X 50
#define OFFSET_Y 150

// Receber a variavel input_Num para definir o tamnho do tabuleiro !!! FEITO
// Corrijir as chamadas das funções (passar a variavel "tam_input" nas chamadas)
//Adicionar a tela de inicio para adicionar o tamanho do tabuleiro 
// Verificar se precisa mudar os valores do RAYLIB 

typedef enum {
    TELA_INICIAL,
    SELECIONANDO,
    SEMEANDO,
    FIM_JOGO
} Estado;

int main() {
    // janela meio grande pra caber tudo

    InitWindow(800, 900, "BUKU GAME");
    SetTargetFPS(60);
    Estado estado = TELA_INICIAL;
    char inputTam[4] = "";
    int inputLen = 0;
    int tam_input = 0;


    Pilha **tabuleiro = NULL;   

    bool turno_branco = true;
    int turno_numero = 0;

    Pilha *pontos_preto_pilha = malloc(sizeof(Pilha));
    iniciar(pontos_preto_pilha);

    Pilha *pontos_branco_pilha = malloc(sizeof(Pilha));
    iniciar(pontos_branco_pilha);

    int linha_sel = -1;
    int coluna_sel = -1;
    int pecas_mao_int = 0;
    Pilha *mao = malloc(sizeof(Pilha)); 
    iniciar(mao);
    bool **visitadas = NULL;

    int ultima_i = -1;
    int ultima_j = -1;
    char msg[100];
    strcpy(msg, "Selecione uma linha (Branco) ou coluna (Preto)");

    while (!WindowShouldClose()) {
        if (estado == TELA_INICIAL){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Digite o tamanho do tabuleiro NxN", 200, 300, 30, BLACK);
            DrawRectangle(300, 350, 200, 40, LIGHTGRAY);
            DrawRectangleLines(300, 350, 200, 40, BLACK);
            DrawText(inputTam, 310, 355, 30, BLACK);
            int key = GetCharPressed();
            DrawText("N deve ser par!", 280, 400, 30, BLACK);
            while(key > 0){
                if (key >= '0' && key <= '9' && inputLen < 3 ){
                    inputTam[inputLen] = key;
                    inputLen++;
                    inputTam[inputLen] = '\0';
                }
                key = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE) && inputLen >0){
                inputLen--;
                inputTam[inputLen] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && inputLen > 0){
                tam_input = atoi(inputTam);
                if(tam_input % 2 !=0){
                    inputLen = 0;
                    inputTam[0] = '\0';
                }
                else if(tam_input > 0){
                    iniciartabuleiro(&tabuleiro, tam_input);
                    for (int i = 0; i<tam_input ; i++){
                        for(int j = 0 ; j<tam_input; j++){
                            iniciar(&tabuleiro[i][j]);
                            push(&tabuleiro[i][j], 0);
                        }
                    }
                visitadas = criar_matriz_visitadas(tam_input);
                estado = SELECIONANDO;
                }
            }
            
            EndDrawing();
            continue;
        }
        limpar_visitadas(visitadas, tam_input);

        // posição do mouse convertida pra célula
        Vector2 mouse = GetMousePosition();
        int mx = (mouse.x - OFFSET_X) / CEL;
        int my = (mouse.y - OFFSET_Y) / CEL;


        if (estado == SELECIONANDO) {

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

                // turno do branco (escolhe a linha)
                if (turno_branco) {
                    if (my >= 0 && my < tam_input) {
                        linha_sel = my;
                        pecas_mao_int = coletar_linha(tabuleiro, linha_sel, tam_input);
                        push_pecas(mao, pecas_mao_int);

                        //verificar se houve desistencia ou vitoria
                        if(mao->size == 0 && pontos_branco_pilha->size <= tam_input/2  ){ //verificar depois se ta correto esse tam_input/2 (se realmente é oq precisa pra vencer ou nao)
                            sprintf(msg, "Branco Encerrou o jogo! O numero de pontos do branco é <= %d, assim, ele perdeu e o preto ganhou!", tam_input/2);
                            estado = FIM_JOGO;
                        }
                        else if(mao->size == 0 && pontos_branco_pilha->size > tam_input/2 ){
                            sprintf(msg, "Branco encerrou o jogo! O numero de peças na mao do branco é > %d, logo, ele ganhou e o preto perdeu!", tam_input/2 );
                            estado = FIM_JOGO;
                        }
                        else{
                            // primeira jogada do branco ganha 1 peça extra
                            if (turno_numero == 0) {
                                push(mao, 0);
                            }

                            estado = SEMEANDO;
                            ultima_i = -1;
                            ultima_j = -1;
                            limpar_visitadas(visitadas, tam_input);

                            sprintf(msg, "Coletou %d pecas. Clique para semear", pecas_mao_int);
                        }
                    }
                }
                // turno do preto (selecianr a coluna)
                else {
                    if (mx >= 0 && mx < tam_input) {
                        coluna_sel = mx;
                        pecas_mao_int = coletar_coluna(tabuleiro, coluna_sel, tam_input);
                        push_pecas(mao, pecas_mao_int);

                        if(mao->size == 0 && pontos_branco_pilha->size <= tam_input/2  ){ //verificar depois se ta correto esse tam_input/2 (se realmente é oq precisa pra vencer ou nao)
                            sprintf(msg, "Preto Encerrou o jogo! O numero de pontos do preto é <= %d, assim, ele perdeu e o branco ganhou!", tam_input/2);
                            estado = FIM_JOGO;
                        }
                        else if(mao->size == 0 && pontos_branco_pilha->size > tam_input/2 ){
                            sprintf(msg, "Preto encerrou o jogo! O numero de peças na mao do preto é > %d, logo, ele ganhou e o branco perdeu!", tam_input/2 );
                            estado = FIM_JOGO;
                        }
                        else{

                            estado = SEMEANDO;
                            ultima_i = -1;
                            ultima_j = -1;
                            limpar_visitadas(visitadas, tam_input);
                            sprintf(msg, "Coletou %d pecas. Clique para semear", pecas_mao_int);
                        }
                    }
                }
            }
        }
        else if (estado == SEMEANDO) {

            if (pecas_mao_int > 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

                if (mx >= 0 && mx < tam_input && my >= 0 && my < tam_input) {

                    bool pode = false;

                    // movimento livcre da primeira peca

                    if (ultima_i == -1) {
                        pode = true;
                    } else {
                        int dx = abs(mx - ultima_j);
                        int dy = abs(my - ultima_i);

                        if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) {
                            if (!visitadas[my][mx]) {
                                pode = true;
                            }
                        }
                    }

                    if (pode) {
                        push(&tabuleiro[my][mx], 1);
                        visitadas[my][mx] = true;

                        ultima_i = my;
                        ultima_j = mx;
                        mao->size--;

                        sprintf(msg, "%d pecas restantes", mao->size);

                        if (mao->size == 0) {
                            int capturadas = realizar_captura(tabuleiro, turno_branco, tam_input);

                            if (turno_branco)
                                push_pecas(pontos_branco_pilha, capturadas);
                            else
                                push_pecas(pontos_preto_pilha, capturadas);

                            // verificae se teve um fim de jogo

                            if (verificar_fim_jogo(tabuleiro, tam_input)) {

                                int rb, rp;
                                contar_pecas_restantes(tabuleiro, &rb, &rp, tam_input);

                                push_pecas(pontos_branco_pilha, rb);
                                push_pecas(pontos_preto_pilha, rp);

                                estado = FIM_JOGO;

                                if (pontos_branco_pilha->size > pontos_preto_pilha->size) {
                                    sprintf(msg, "BRANCO VENCEU! %d x %d", pontos_branco_pilha->size, pontos_preto_pilha->size);
                                } else if (pontos_preto_pilha->size > pontos_branco_pilha->size) {
                                    sprintf(msg, "PRETO VENCEU! %d x %d", pontos_preto_pilha->size, pontos_branco_pilha->size);
                                } else {
                                    sprintf(msg, "EMPATE! %d x %d", pontos_branco_pilha->size, pontos_preto_pilha->size);
                                }
                            } else {
                                turno_branco = !turno_branco;
                                turno_numero++;
                                estado = SELECIONANDO;

                                sprintf(msg, "Turno do %s", turno_branco ? "BRANCO" : "PRETO");
                            }
                        }
                    } else {
                        strcpy(msg, "Movimento invalido!");
                    }
                }
            }
        }
        //comeca o desenho

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("BUKU GAME", 10, 10, 30, BLACK);

        DrawText(
            TextFormat("Turno: %s", turno_branco ? "BRANCO (Linhas)" : "PRETO (Colunas)"),
            10, 50, 20,
            turno_branco ? BLUE : RED
        );

        DrawText(
            TextFormat("Pontos - Branco: %d | Preto: %d", pontos_branco_pilha->size, pontos_preto_pilha->size),
            10, 80, 20, DARKGRAY
        );

        DrawText(msg, 10, 110, 18, DARKGREEN);

        // destaque de linha ou coluna
        if (estado == SELECIONANDO) {
            if (turno_branco && my >= 0 && my < tam_input) {
                for (int j = 0; j < tam_input; j++) {
                    DrawRectangle(j * CEL + OFFSET_X, my * CEL + OFFSET_Y, CEL, CEL,
                                  ColorAlpha(YELLOW, 0.3f));
                }
            }
            if (!turno_branco && mx >= 0 && mx < tam_input) {
                for (int i = 0; i < tam_input; i++) {
                    DrawRectangle(mx * CEL + OFFSET_X, i * CEL + OFFSET_Y, CEL, CEL,
                                  ColorAlpha(YELLOW, 0.3f));
                }
            }
        }

        // tabuleiro
        for (int i = 0; i < tam_input; i++) {
            for (int j = 0; j < tam_input; j++) {

                int x = j * CEL + OFFSET_X;
                int y = i * CEL + OFFSET_Y;

                Color base = eh_casa_branca(i, j) ? LIGHTGRAY : DARKGRAY;

                DrawRectangle(x, y, CEL, CEL, base);
                DrawRectangleLines(x, y, CEL, CEL, BLACK);

                int qtd = contar_pecas(&tabuleiro[i][j]);
                if (qtd > 0) {
                    DrawText(
                        TextFormat("%d", qtd),
                        x + CEL / 2 - 10,
                        y + CEL / 2 - 10,
                        30,
                        eh_casa_branca(i, j) ? BLACK : WHITE
                    );
                }

                if (visitadas[i][j] && estado == SEMEANDO) {
                    DrawCircle(x + CEL / 2, y + CEL / 2, 8, RED);
                }

                // debug de coordenadas
                DrawText(TextFormat("%d,%d", i, j), x + 5, y + 5, 10, GRAY);
            }
        }

        DrawText("Casa CLARA = Branco | Casa ESCURA = Preto", 50, 870, 16, DARKGRAY);

        EndDrawing();
    }
    for (int i = 0; i < tam_input; i++){
        free(visitadas[i]);
    }
    free(visitadas);

    liberar_tabuleiro(tabuleiro, tam_input); 
    free(mao);
    free(pontos_branco_pilha);
    free(pontos_preto_pilha);
    CloseWindow();
    
    return 0;
}
