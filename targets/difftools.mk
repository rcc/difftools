# Output Name
TARGET := difftools

# Sources
SOURCES :=	src/difftools.c \
		lib/getline.c \
		lib/cmds.c \
		src/colorize.c \
		src/detab.c \

# Libraries
LIBRARIES := readline

# Options
OPTIONS := SCM_HASH='"$(shell git rev-parse --short=16 HEAD || \
		echo 0000000000000000)"'

# Configurations (the first one is the default)
CONFIGS := release debug

# Configuration Specific Options
RELEASE_OPTIONS := CONFIG_RELEASE

DEBUG_OPTIONS := CONFIG_DEBUG DEBUG_PRINTS

# Install script
INSTALL_SCRIPT := targets/difftools.install
