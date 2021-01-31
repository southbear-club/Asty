# target marcros
# asty platform server
TARGET := apsd
UNIT_TEST_TARGET := $(TARGET)_ut
export ROOT_DIR := $(shell pwd)
BUILD_DIR := build

include mk/config.mk
include mk/src.mk
include mk/ut.mk

B_SRC_OBJS := $(addprefix $(BUILD_DIR)/,$(SRC_OBJS))
B_SRC_WILL_TEST_OBJS := $(addprefix $(BUILD_DIR)/,$(SRC_WILL_TEST_OBJS))
B_UT_OBJS := $(addprefix $(BUILD_DIR)/,$(UT_OBJS))

B_SRC_OBJS += $(B_SRC_WILL_TEST_OBJS)
B_UT_OBJS += $(B_SRC_WILL_TEST_OBJS)

default: $(TARGET)

$(TARGET): $(B_SRC_OBJS)
	@echo -e "\t" CC [$@]
	@$(CC) $(LIBS_PATH) -Xlinker "-(" -Wl,-Bstatic $(B_SRC_OBJS) $(ST_LIBS) -Wl,-Bdynamic -Xlinker "-)" $(SO_LIBS) -o $@
	@echo Target [$@] build finished.

ut: $(B_UT_OBJS)
	@echo -e "\t" CC [$(UNIT_TEST_TARGET)]
	@$(CC) $(LIBS_PATH) -Xlinker "-(" -Wl,-Bstatic $(B_UT_OBJS) $(ST_LIBS_UT) $(ST_LIBS) -Wl,-Bdynamic -Xlinker "-)" $(SO_LIBS) -o $(UNIT_TEST_TARGET)
	@echo Target [$(UNIT_TEST_TARGET)] build finished.

.PHONY: all
all: $(TARGET) ut

.PHONY: clean
clean:
	@echo CLEAN ALL_OBJS
	@rm -rf $(BUILD_DIR)

.PHONY: distclean
distclean:
	@echo DIST_CLEAN ALL_OBJS
	@echo rm $(TARGET) $(UNIT_TEST_TARGET)
	@rm -rf $(BUILD_DIR) $(TARGET) $(UNIT_TEST_TARGET)

# dependencies
$(BUILD_DIR)/%.o: %.c*
	@echo -e "\t" CC $<
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi;\
	$(CC) $(OBJCCFLAG) $< -o $@
