#!/usr/bin/env zsh

# Script de execução rápida para NixOS
cd "$(dirname "$0")"

echo "🎮 Iniciando Buku Game..."
echo ""

# Executa dentro do nix-shell
nix-shell --run "./buku"
