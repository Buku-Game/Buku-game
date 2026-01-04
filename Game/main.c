#include <raylib.h>
#include "arquivo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CEL 75  // tamanho da celula

// estados do jogo
typedef enum {
    SELECIONANDO,
    SEMEANDO,
    FIM_JOGO
} Estado;

int main() {
    InitWindow(800, 900, "BUKU GAME");
    SetTargetFPS(60);

    Pilha tabuleiro[tam][tam];
    iniciartabuleiro(tabuleiro);

    // colocar 1 peça em cada casa
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            push(&tabuleiro[i][j], 1);
        }
    }

    Estado estado = SELECIONANDO;
    bool turno_branco = true;
    int pontos_branco = 0, pontos_preto = 0;
    int turno_numero = 0;
    
    int linha_sel = -1;
    int coluna_sel = -1;
    int pecas_mao = 0;
    
    int ultima_i = -1, ultima_j = -1;
    bool visitadas[tam][tam] = {false};
    
    char msg[100] = "Selecione uma linha (Branco) ou coluna (Preto)";

    while (!WindowShouldClose()) {
        Vector2 pos_mouse = GetMousePosition();
        int mx = (pos_mouse.x - 50) / CEL;
        int my = (pos_mouse.y - 150) / CEL;
        
        if (estado == SELECIONANDO) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // turno branco escolhe linha
                if (turno_branco && my >= 0 && my < tam) {
                    linha_sel = my;
                    pecas_mao = coletar_linha(tabuleiro, linha_sel);
                    
                    // primeira jogada do branco ganha peça extra
                    if(turno_numero == 0) {
                        pecas_mao++;
                    }
                    
                    estado = SEMEANDO;
                    ultima_i = -1;
                    ultima_j = -1;
                    memset(visitadas, false, sizeof(visitadas));
                    sprintf(msg, "Coletou %d pecas. Clique para semear", pecas_mao);
                } 
                // turno preto escolhe coluna
                else if (!turno_branco && mx >= 0 && mx < tam) {
                    coluna_sel = mx;
                    pecas_mao = coletar_coluna(tabuleiro, coluna_sel);
                    estado = SEMEANDO;
                    ultima_i = -1;
                    ultima_j = -1;
                    memset(visitadas, false, sizeof(visitadas));
                    sprintf(msg, "Coletou %d pecas. Clique para semear", pecas_mao);
                }
            }
        } 
        else if (estado == SEMEANDO && pecas_mao > 0) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (mx >= 0 && mx < tam && my >= 0 && my < tam) {
                    bool eh_valido = false;
                    
                    if (ultima_i == -1) {
                        eh_valido = true;
                    } else {
                        int dx = abs(mx - ultima_j);
                        int dy = abs(my - ultima_i);
                        bool adj = (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
                        
                        if (adj && !visitadas[my][mx]) {
                            eh_valido = true;
                        }
                    }
                    
                    if (eh_valido) {
                        push(&tabuleiro[my][mx], 1);
                        visitadas[my][mx] = true;
                        ultima_i = my;
                        ultima_j = mx;
                        pecas_mao--;
                        
                        sprintf(msg, "%d pecas restantes", pecas_mao);
                        
                        if (pecas_mao == 0) {
                            // fazer captura
                            int cap = realizar_captura(tabuleiro, turno_branco);
                            if(turno_branco) {
                                pontos_branco += cap;
                            } else {
                                pontos_preto += cap;
                            }
                            
                            // ver se acabou o jogo
                            if (verificar_fim_jogo(tabuleiro)) {
                                int rb, rp;
                                contar_pecas_restantes(tabuleiro, &rb, &rp);
                                pontos_branco += rb;
                                pontos_preto += rp;
                                estado = FIM_JOGO;
                                
                                if(pontos_branco > pontos_preto) {
                                    sprintf(msg, "BRANCO VENCEU! %d x %d", pontos_branco, pontos_preto);
                                } else if(pontos_preto > pontos_branco) {
                                    sprintf(msg, "PRETO VENCEU! %d x %d", pontos_preto, pontos_branco);
                                } else {
                                    sprintf(msg, "EMPATE! %d x %d", pontos_branco, pontos_preto);
                                }
                            } else {
                                turno_branco = !turno_branco;
                                turno_numero++;
                                estado = SELECIONANDO;
                                sprintf(msg, "Turno do %s", turno_branco ? "BRANCO" : "PRETO");
                            }
                        }
                    } else {
                        sprintf(msg, "Movimento invalido! Casa adjacente nao visitada");
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // titulo
        DrawText("BUKU GAME", 10, 10, 30, BLACK);
        DrawText(TextFormat("Turno: %s", turno_branco ? "BRANCO (Linhas)" : "PRETO (Colunas)"), 
                 10, 50, 20, turno_branco ? BLUE : RED);
        DrawText(TextFormat("Pontos - Branco: %d | Preto: %d", pontos_branco, pontos_preto), 
                 10, 80, 20, DARKGRAY);
        DrawText(msg, 10, 110, 18, DARKGREEN);
        
        // destacar linha ou coluna que pode ser escolhida
        if (estado == SELECIONANDO) {
            if (turno_branco && my >= 0 && my < tam) {
                for (int j = 0; j < tam; j++) {
                    DrawRectangle(j * CEL + 50, my * CEL + 150, CEL, CEL, 
                                  ColorAlpha(YELLOW, 0.3f));
                }
            } else if (!turno_branco && mx >= 0 && mx < tam) {
                for (int i = 0; i < tam; i++) {
                    DrawRectangle(mx * CEL + 50, i * CEL + 150, CEL, CEL, 
                                  ColorAlpha(YELLOW, 0.3f));
                }
            }
        }
        
        // mostrar casas validas pra semear
        if (estado == SEMEANDO && pecas_mao > 0) {
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    if (!visitadas[i][j]) {
                        bool ok = false;
                        if (ultima_i == -1) {
                            ok = true;
                        } else {
                            int dx = abs(j - ultima_j);
                            int dy = abs(i - ultima_i);
                            bool adj = (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
                            if (adj) ok = true;
                        }
                        
                        if (ok) {
                            DrawRectangle(j * CEL + 50, i * CEL + 150, CEL, CEL, 
                                          ColorAlpha(GREEN, 0.3f));
                        }
                    }
                }
            }
        }

        // desenhar tabuleiro
        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                int x = j * CEL + 50;
                int y = i * CEL + 150;

                // cor da casa tipo xadrez
                Color cor = eh_casa_branca(i, j) ? LIGHTGRAY : DARKGRAY;
                DrawRectangle(x, y, CEL, CEL, cor);
                DrawRectangleLines(x, y, CEL, CEL, BLACK);

                // numero de pecas
                int n = contar_pecas(&tabuleiro[i][j]);
                if (n > 0) {
                    Color txt = eh_casa_branca(i, j) ? BLACK : WHITE;
                    DrawText(TextFormat("%d", n), x + CEL/2 - 10, y + CEL/2 - 10, 30, txt);
                }
                
                // marcar casas ja visitadas
                if (visitadas[i][j] && estado == SEMEANDO) {
                    DrawCircle(x + CEL/2, y + CEL/2, 8, RED);
                }

                // coordenadas (pra debug)
                DrawText(TextFormat("%d,%d", i, j), x + 5, y + 5, 10, 
                         eh_casa_branca(i, j) ? DARKGRAY : LIGHTGRAY);
            }
        }

        DrawText("Casa CLARA = Branco | Casa ESCURA = Preto", 50, 870, 16, DARKGRAY);

        EndDrawing();
    }

    liberar_tabuleiro(tabuleiro);
    CloseWindow();
    return 0;
}
