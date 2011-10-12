CONFIGS := debug release snow

# Sources
SOURCES :=	src/main.c \
		lib/logging.c \
		lib/getline.c \
		lib/dict.c \
		lib/cmds.c \
		lib/cmds_script.c \
		lib/cmds_shell.c \
		src/cmds/version.c \

ifeq ($(CONFIG),snow)
SOURCES +=	lib/threadpool.c \
		lib/net/util.c \
		lib/net/pkv.c \
		lib/net/connection.c \
		lib/net/listen.c \

endif

# Libraries
LIBRARIES := readline

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

# Snow
ifeq ($(CONFIG),snow)
# Options
OPTIONS += MAX_LOGLEVEL=5 DEFAULT_LOGLEVEL=4
OPTIONS += THREADPOOLTESTCMD NETCONNECTIONTESTCMD
# Flags
CFLAGS += $(DEBUG_CFLAGS)
endif

INSTALL_SCRIPT = targets/install
