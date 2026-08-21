SRC += riad.c host_layout.c host_api.c host_layouts/us.c host_layouts/ca.c

# NOTE: `qmk console` reports the active host layout.
CONSOLE_ENABLE = yes

ALLOW_WARNINGS = no

# NOTE: raw HID, for the host layout query API.
RAW_ENABLE = yes

# NOTE: combos.c defines key_combos[], which QMK sizes with ARRAY_SIZE from
# inside keymap_introspection.c. Pointing that at the file is what puts the
# table in the userspace instead of a board's keymap.c; it is included there,
# so it must stay out of SRC.
COMBO_ENABLE = yes
INTROSPECTION_KEYMAP_C = combos.c
