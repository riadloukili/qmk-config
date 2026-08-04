set shell := ["bash", "-euo", "pipefail", "-c"]

out := "build"

_default:
    @just --list --unsorted

# Clone qmk_firmware into ./.qmk_firmware and check the toolchain.
init:
    qmk setup -y

#   just build                     every target
#   just build charybdis           every keymap for matching keyboards
#   just build charybdis riad      that combination
#   just build "" riad             every keyboard using the riad keymap
# Build targets from qmk.json, narrowed by optional substring filters.
build kb="" km="": && _collect
    #!/usr/bin/env bash
    set -euo pipefail
    mapfile -t targets < <(qmk userspace-list 2>&1 \
        | sed -n 's/.*Keyboard: \(.*\), keymap: \(.*\)/\1 \2/p')
    if [ ${#targets[@]} -eq 0 ]; then
        echo "no build targets in qmk.json, add one with 'qmk userspace-add'" >&2
        exit 1
    fi
    matched=0
    for t in "${targets[@]}"; do
        read -r k m <<<"$t"
        if [ -n '{{ kb }}' ]; then case "$k" in *'{{ kb }}'*) ;; *) continue ;; esac; fi
        if [ -n '{{ km }}' ]; then case "$m" in *'{{ km }}'*) ;; *) continue ;; esac; fi
        echo "==> $k:$m"
        qmk compile -kb "$k" -km "$m"
        matched=$((matched + 1))
    done
    if [ "$matched" -eq 0 ]; then
        echo "no target matches kb='{{ kb }}' km='{{ km }}'" >&2
        exit 1
    fi

# List the build targets defined in qmk.json.
targets:
    @qmk userspace-list

# NOTE: QMK hardcodes its artifact copy to the userspace root
# (builddefs/common_rules.mk), so move them afterwards.
_collect:
    @mkdir -p {{ out }}
    @find . -maxdepth 1 -type f \( -name '*.uf2' -o -name '*.hex' -o -name '*.bin' \) \
        -exec mv -f {} {{ out }}/ \;
    @ls -1 {{ out }}

# NOTE: put the half into bootloader first (tap reset twice, or QK_BOOT).
# Build and flash. Same filter args as `build`, but must resolve to one target.
flash kb="" km="":
    #!/usr/bin/env bash
    set -euo pipefail
    mapfile -t targets < <(qmk userspace-list 2>&1 \
        | sed -n 's/.*Keyboard: \(.*\), keymap: \(.*\)/\1 \2/p')
    sel=()
    for t in "${targets[@]}"; do
        read -r k m <<<"$t"
        if [ -n '{{ kb }}' ]; then case "$k" in *'{{ kb }}'*) ;; *) continue ;; esac; fi
        if [ -n '{{ km }}' ]; then case "$m" in *'{{ km }}'*) ;; *) continue ;; esac; fi
        sel+=("$k $m")
    done
    if [ ${#sel[@]} -ne 1 ]; then
        printf 'flash needs exactly one target, matched %d:\n' "${#sel[@]}" >&2
        printf '  %s\n' "${sel[@]}" >&2
        exit 1
    fi
    read -r k m <<<"${sel[0]}"
    qmk flash -kb "$k" -km "$m"

# Report flash/RAM usage of the last build.
size:
    @arm-none-eabi-size $QMK_HOME/.build/*.elf

# Check the toolchain.
doctor:
    @qmk doctor && qmk userspace-doctor

# Format the C sources. Layout tables are fenced with `clang-format off`.
fmt:
    find users keyboards -name '*.c' -o -name '*.h' | xargs -r clang-format -i

# Remove build artifacts.
clean:
    rm -rf {{ out }} "$QMK_HOME/.build"
