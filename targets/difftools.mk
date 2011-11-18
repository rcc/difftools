CONFIGS := debug release

# Sources
SOURCES :=	src/main.c \
		src/prepost.c \
		lib/logging.c \
		lib/dict.c \
		lib/cmds.c \
		lib/getline.c \

SOURCES +=	src/cmds/colorize.c \
		src/cmds/detab.c \
		src/cmds/tohtml.c \
		src/cmds/version.c \

# Libraries
LIBRARIES :=

# Version
include buildsystem/git.mk
OPTIONS += SCMVERSION='"$(SCMVERSION)"'
OPTIONS += SCMBRANCH='"$(SCMBRANCH)"'
CPPFLAGS += -DBUILD_DATE='"$(shell date)"'

# Release
ifeq ($(CONFIG),release)
# Options
OPTIONS += MAX_LOGLEVEL=3 DEFAULT_LOGLEVEL=2
# Flags
CFLAGS += -O2
endif

# Config
ifeq ($(CONFIG),debug)
# Options
OPTIONS += MAX_LOGLEVEL=5 DEFAULT_LOGLEVEL=4
# Flags
CFLAGS += -O0 -g
endif

INSTALL_SCRIPT = targets/install
