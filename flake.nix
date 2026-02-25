{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    self = {
      submodules = true;
    };
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
      stdenv = "stdenv";
    in {
      packages.${system}.default =
        pkgs.${stdenv}.mkDerivation {
          pname = "ihopethisworks";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = with pkgs [
            cmake
          ];

          buildInputs = with pkgs [
            glm
            sdl3
            spdlog
          ];

          buildPhase = ''
               cc -o main main.c
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp main $out/bin/
          '';
        };
    };
}
