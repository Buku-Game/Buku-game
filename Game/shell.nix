# Shell de desenvolvimento para o jogo Buku
{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    # Compilador
    gcc
    gnumake
    
    # Raylib e suas dependências
    raylib
    
    # Ferramentas de desenvolvimento (opcionais)
    valgrind
    gdb
    
    # Dependências do Raylib no NixOS
    xorg.libX11
    xorg.libXrandr
    xorg.libXi
    xorg.libXcursor
    xorg.libXinerama
    libGL
    mesa
  ];

  # Variáveis de ambiente
  shellHook = ''
    echo "====================================="
    echo "  Ambiente Buku Game carregado!"
    echo "====================================="
    echo ""
    echo "Comandos disponíveis:"
    echo "  make       - Compilar o jogo"
    echo "  make run   - Compilar e executar"
    echo "  make clean - Limpar arquivos compilados"
    echo ""
    echo "Raylib: $(pkg-config --modversion raylib 2>/dev/null || echo 'instalado')"
    echo ""
  '';
  
  # Configurar paths para o compilador encontrar o Raylib
  NIX_CFLAGS_COMPILE = "-I${pkgs.raylib}/include";
  NIX_LDFLAGS = "-L${pkgs.raylib}/lib";
}
