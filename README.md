# Buku Game 🎮

Implementação em C do jogo de tabuleiro **Buku**, criado por Jorge Gómez Arrausi (2001).

## 🎯 Sobre o Jogo

Jogo de semeadura bidimensional em tabuleiro 8x8. Dois jogadores competem:
- **Branco** controla linhas (casas claras)
- **Preto** controla colunas (casas escuras)

### Regras
1. Colete todas as peças de uma linha/coluna
2. Distribua uma por uma em casas adjacentes
3. Capture automaticamente suas casas com 3 ou 4 peças
4. Jogo termina quando todas as casas têm ≤1 peça
5. Quem capturou mais peças vence!

## 🚀 Jogar Agora

### NixOS
```bash
cd Game
nix-shell
make
./buku
```

### Outras Distros
```bash
# Instalar Raylib primeiro
sudo apt install libraylib-dev  # Ubuntu/Debian
sudo pacman -S raylib           # Arch

# Compilar e jogar
cd Game
make
./buku
```

## 🎮 Controles

- **Mouse**: Selecionar e semear
- **ESC**: Sair

## 📚 Documentação

- [ESTRATEGIAS.md](ESTRATEGIAS.md) - Dicas de jogo
- [NIXOS_SETUP.md](NIXOS_SETUP.md) - Guia NixOS completo
- [CHANGELOG.md](CHANGELOG.md) - Histórico
- [docs/](docs/) - Documentação técnica detalhada

## 🛠️ Tecnologias

- C (C99) + Raylib
- Estrutura de dados: Pilhas

## ✨ Status

**✅ Completo e jogável!** Todas as regras oficiais implementadas.

## 📝 Licença

Software livre - veja [LICENSE](LICENSE)

---

**Jogo original**: Jorge Gómez Arrausi | **Implementação**: Arthur (2026)
