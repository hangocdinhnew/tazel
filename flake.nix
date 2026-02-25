{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
      stdenv = "stdenv";
    in {
      packages.${system}.default =
        pkgs.${stdenv}.mkDerivation {
          pname = "tazel";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = with pkgs; [
            cmake
            pkg-config
          ];

          buildInputs = with pkgs; [
            glm
            alsa-lib
            sdl3
            spdlog
            jack2
            pipewire
            pulseaudio
            libX11
            libxcb
            libxau
            libxdmcp
            libxext
            libxcursor
            libxrender
            libxfixes
            libxi
            libxrandr
            libxscrnsaver
            libxtst
            libdrm
            libgbm
            wayland
            libffi
            libGL
            libxkbcommon
            libdecor
            libusb1
          ];
        };
    };
}
