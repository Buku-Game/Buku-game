#include <raylib.h>
#include "arquivo.h"

#define CEL 100

int main() {
    InitWindow(600, 600, "DUKU");

    Pilha tabuleiro[tam][tam];
    iniciartabuleiro(tabuleiro);

    push(&tabuleiro[0][0], 1);
    push(&tabuleiro[0][0], 2);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                DrawRectangleLines(
                    j * CEL + 50,
                    i * CEL + 50,
                    CEL,
                    CEL,
                    BLACK
                );

                if (!pilhavazia(&tabuleiro[i][j])) {
                    DrawText(
                        TextFormat("%d", tabuleiro[i][j].topo->valor),
                        j * CEL + 90,
                        i * CEL + 90,
                        20,
                        RED
                    );
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
