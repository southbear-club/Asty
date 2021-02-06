# version
RELEASE_VERSION = 1.0.0

# 调试模式使能
ndebug = false

# make path
export MAKE := "/usr/bin/make"

# make flag
MAKEFLAG := -s --no-print-directory

# compile marcro
CC := g++
# 生成uuid的命令
APP_UUID := $(shell uuid -v 4)
# 编译时间
COMPILE_TIME := $(shell date +"%A %Y-%m-%d %H:%M:%S %z")

# compile flags
INC := -I/usr/include -I$(ROOT_DIR)/include -I$(ROOT_DIR)/src \
		-I/usr/local/include/mongocxx/v_noabi \
		-I/usr/local/include/libmongoc-1.0 \
		-I/usr/local/include/bsoncxx/v_noabi \
		-I/usr/local/include/libbson-1.0

LIBS_PATH := -L$(ROOT_DIR)/lib -L/usr/local/lib

#-levent 
ST_LIBS = -lgflags -lprotobuf -lleveldb -lsnappy \
		  -lprotoc -lglog -lbrpc \
		  -lmongocxx-static -lbsoncxx-static -lmongoc-static-1.0 -lbson-static-1.0 \
		  -lssl -lcrypto -lz

ST_LIBS_UT = -lgtest

SO_LIBS = \
		-lpthread -ldl -lrt -lresolv

DMARCROS := -DLANGUAGE_ZH -DSOFT_VERSION=\"$(RELEASE_VERSION)\" -DLOGURU_WITH_STREAMS=1 \
			-DAPP_UUID=\"$(APP_UUID)\" -DAPP_COMPILE_TIME=\""$(COMPILE_TIME)"\"

# 调试模式
ifeq ($(ndebug), true)
DMARCROS += -DNDEBUG
else
DMARCROS += -DDEBUG
endif

# 指定树莓派4b
DMARCROS += -DRASBERRY_PI_4B

DMARCROS += -DBRPC_WITH_GLOG=1 -DGFLAGS_NS=google \
			-D__const__= -pipe -W -Wall -Wno-unused-parameter \
			-fPIC -fno-omit-frame-pointer -Wno-implicit-fallthrough -fstack-protector-all

# -ggdb
CCFLAG := -c $(INC) -O2 -g3 -Wall -std=c++17 $(DMARCROS)
OBJCCFLAG := $(CCFLAG)
