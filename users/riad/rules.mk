SRC += riad.c host_layout.c host_api.c host_layouts/us.c host_layouts/ca.c

# `qmk console` reports the active host layout.
CONSOLE_ENABLE = yes

ALLOW_WARNINGS = no

# Raw HID, for the host layout query API.
RAW_ENABLE = yes
