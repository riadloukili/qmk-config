set shell := ["bash", "-euo", "pipefail", "-c"]

out := "build"

_default:
    @just --list --unsorted

# Clone qmk_firmware into ./.qmk_firmware and check the toolchain.
init:
    qmk setup -y

# NOTE: filter examples:
#   just build                     every target
#   just build charybdis           every keymap for matching keyboards
#   just build charybdis riad      that combination
#   just build "" riad             every keyboard using the riad keymap
# Build targets from qmk.json, narrowed by optional substring filters.
build kb="" km="": && _collect
    #!/usr/bin/env bash
    set -euo pipefail
    kb={{ quote(kb) }}
    km={{ quote(km) }}
    mapfile -t targets < <(qmk userspace-list 2>&1 \
        | sed -n 's/.*Keyboard: \(.*\), keymap: \(.*\)/\1 \2/p')
    if [ ${#targets[@]} -eq 0 ]; then
        echo "no build targets in qmk.json, add one with 'qmk userspace-add'" >&2
        exit 1
    fi
    matched=0
    for t in "${targets[@]}"; do
        read -r k m <<<"$t"
        if [ -n "$kb" ]; then case "$k" in *"$kb"*) ;; *) continue ;; esac; fi
        if [ -n "$km" ]; then case "$m" in *"$km"*) ;; *) continue ;; esac; fi
        echo "==> $k:$m"
        qmk compile -kb "$k" -km "$m"
        matched=$((matched + 1))
    done
    if [ "$matched" -eq 0 ]; then
        echo "no target matches kb=$kb km=$km" >&2
        exit 1
    fi

# List the build targets defined in qmk.json.
targets:
    @qmk userspace-list

# Render each target's keymap to an SVG beside its keymap.c, same filter args as `build`.
draw kb="" km="":
    #!/usr/bin/env bash
    set -euo pipefail
    kb={{ quote(kb) }}
    km={{ quote(km) }}
    mkdir -p {{ out }}
    # NOTE: layer names come from the enum, so they cannot drift from the code.
    # NOTE: [A-Z_]* not [A-Z]+, or _NUM_US truncates to NUM and collides with
    # the layer actually named NUM.
    mapfile -t layers < <(sed -n 's/^\s*_\([A-Z_]*\).*/\1/p' users/riad/riad.h)
    mapfile -t targets < <(qmk userspace-list 2>&1 \
        | sed -n 's/.*Keyboard: \(.*\), keymap: \(.*\)/\1 \2/p')
    for t in "${targets[@]}"; do
        read -r k m <<<"$t"
        if [ -n "$kb" ]; then case "$k" in *"$kb"*) ;; *) continue ;; esac; fi
        if [ -n "$km" ]; then case "$m" in *"$km"*) ;; *) continue ;; esac; fi
        # NOTE: the keymap can live at any ancestor of the target, since QMK
        # searches upwards (3x5/elitec builds from 3x5/keymaps/riad).
        dir=""
        p="keyboards/$k"
        while [ "$p" != "keyboards" ] && [ "$p" != "." ]; do
            [ -d "$p/keymaps/$m" ] && { dir="$p/keymaps/$m"; break; }
            p=$(dirname "$p")
        done
        [ -n "$dir" ] || { echo "no keymap dir for $k:$m" >&2; exit 1; }
        echo "==> $dir/keymap.svg"
        # NOTE: layer grids are macros in layers/*.h, so expand them first.
        # riad.h is stubbed out, which leaves key aliases (HR_A, MOU_Z) as
        # tokens: c2json needs LAYOUT(...) calls, the drawing wants aliases.
        stub="{{ out }}/draw-stub"
        mkdir -p "$stub" && : >"$stub/riad.h"
        cpp -P -I "$stub" "$dir/keymap.c" >"{{ out }}/$m.i"
        qmk c2json -kb "$k" -km "$m" --no-cpp "{{ out }}/$m.i" >"{{ out }}/$m.json"
        keymap parse -q "{{ out }}/$m.json" -l "${layers[@]}" -o "{{ out }}/$m.yaml"
        keymap draw "{{ out }}/$m.yaml" -o "$dir/keymap.svg"
    done

# NOTE: QMK hardcodes its artifact copy to the userspace root
# (builddefs/common_rules.mk), so move them afterwards.
_collect:
    @mkdir -p {{ out }}
    @find . -maxdepth 1 -type f \( -name '*.uf2' -o -name '*.hex' -o -name '*.bin' \) \
        -exec mv -f {} {{ out }}/ \;
    @ls -1 {{ out }}

# WARN: put the half into bootloader first (tap reset twice, or QK_BOOT).
# Build and flash. Same filter args as `build`, but must resolve to one target.
flash kb="" km="":
    #!/usr/bin/env bash
    set -euo pipefail
    kb={{ quote(kb) }}
    km={{ quote(km) }}
    mapfile -t targets < <(qmk userspace-list 2>&1 \
        | sed -n 's/.*Keyboard: \(.*\), keymap: \(.*\)/\1 \2/p')
    sel=()
    for t in "${targets[@]}"; do
        read -r k m <<<"$t"
        if [ -n "$kb" ]; then case "$k" in *"$kb"*) ;; *) continue ;; esac; fi
        if [ -n "$km" ]; then case "$m" in *"$km"*) ;; *) continue ;; esac; fi
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
