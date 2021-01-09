# version
RELEASE_VERSION = v1.0.0

# 调试模式使能
ndebug = false

# make flag
MAKEFLAG := -s --no-print-directory

# compile marcro
CC := g++
AR := ar rcs
SHAREDFLG := -shared

# compile flags
INC := -I$(ROOT_DIR)/include -I$(ROOT_DIR)/src

LIBS_PATH := -L$(ROOT_DIR)/lib -L.

ST_LIBS = -lglog -lthrift

ST_LIBS_UT = -lgtest

SO_LIBS = -lpthread -ldl -lrt

DMARCROS := -DLANGUAGE_ZH -DSOFT_VERSION=\"$(RELEASE_VERSION)\" -DLOGURU_WITH_STREAMS=1

# 调试模式
ifeq ($(ndebug), true)
DMARCROS += -DNDEBUG
else
DMARCROS += -DDEBUG
endif

DMARCROS += -D__const__= -pipe -W -Wall -Wno-unused-parameter \
			-fPIC -fno-omit-frame-pointer

# -ggdb
CCFLAG := -c $(INC) -O2 -g3 -Wall -std=c++11 $(DMARCROS)
OBJCCFLAG := $(CCFLAG)
