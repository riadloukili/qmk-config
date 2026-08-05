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

        build = [ pkgs.qmk pkgs.dos2unix pkgs.just pkgs.git ];

        env = ''
          # WARN: repo root, not $PWD. Entering the shell from a
          # subdirectory would point QMK at a path that does not exist.
          root="$(${pkgs.git}/bin/git rev-parse --show-toplevel 2>/dev/null || echo "$PWD")"
          export QMK_USERSPACE="$root"
          export QMK_HOME="$root/.qmk_firmware"
        '';
      in
      {
        devShells.default = pkgs.mkShell {
          name = "qmk-userspace";
          packages = build ++ [ pkgs.clang-tools pkgs.uv ];
          shellHook = env + ''
            (cd "$root" && uv sync --quiet)
            export PATH="$root/.venv/bin:$PATH"
          '';
        };

        # NOTE: what CI needs to run `just build`, without the editor tooling
        # and python environment that only matter interactively.
        devShells.ci = pkgs.mkShell {
          name = "qmk-userspace-ci";
          packages = build;
          shellHook = env;
        };

        formatter = pkgs.nixpkgs-fmt;
      });
}
