{
  description = "QMK userspace";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          name = "qmk-userspace";

          packages = [
            pkgs.qmk
            pkgs.dos2unix
            pkgs.just
            pkgs.git
            pkgs.clang-tools
          ];

          shellHook = ''
            # Repo root, not $PWD — otherwise entering the shell from a
            # subdirectory points QMK at a path that does not exist.
            root="$(${pkgs.git}/bin/git rev-parse --show-toplevel 2>/dev/null || echo "$PWD")"
            export QMK_USERSPACE="$root"
            export QMK_HOME="$root/.qmk_firmware"
          '';
        };

        formatter = pkgs.nixpkgs-fmt;
      });
}
