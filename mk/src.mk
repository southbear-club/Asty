SRC_OBJS = \
src/entry/main.o \
src/entry/init_global_source.o \
src/entry/module_list.o \
src/entry/log_cfg.o

SRC_WILL_TEST_OBJS = \
src/common/utils/asty_slab.o \
src/common/utils/asty_md5.o \
src/common/utils/asty_coredump.o \
src/common/utils/asty_string.o \
src/common/utils/asty_system_call.o \
src/core/version.o \
src/core/asty_config.o \
src/core/asty_log.o \
src/module/basic/module_manage/module_manage.o \
src/module/open_api/device_gw/device_gateway.o