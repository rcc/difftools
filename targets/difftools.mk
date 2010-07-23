# Output Name
TARGET := difftools

# Sources
SOURCES :=	src/difftools.c \
		lib/logging.c \
		lib/getline.c \
		lib/cmds.c \
		src/colorize.c \
		src/detab.c \
		src/tohtml.c \


# Libraries
LIBRARIES := readline

# Options
OPTIONS := VERSION='"0.2"'

# Configurations (the first one is the default)
CONFIGS := release debug

# Configuration Specific Options
RELEASE_OPTIONS := CONFIG_RELEASE
RELEASE_OPTIONS += MAX_LOGLEVEL=3 DEFAULT_LOGLEVEL=2

DEBUG_OPTIONS := CONFIG_DEBUG
DEBUG_OPTIONS += MAX_LOGLEVEL=5 DEFAULT_LOGLEVEL=4
