# target marcros
TARGET := AstyGwSdk
UNIT_TEST_TARGET := ut
export ROOT_DIR := $(shell pwd)
BUILD_DIR := build

include mk/config.mk
include mk/src.mk
include mk/ut.mk

B_SRC_OBJS := $(addprefix $(BUILD_DIR)/,$(SRC_OBJS))
B_UT_OBJS := $(addprefix $(BUILD_DIR)/,$(UT_OBJS))

default: $(TARGET)

$(TARGET): $(B_SRC_OBJS)
	@$(CXX) $(SHAREDFLG) $(B_SRC_OBJS) -o lib$@.so $(SO_LIBS) $(LIBS_PATH)
	@echo -e "\t" CC [lib$@.so]
	@$(AR) lib$@.a $(B_SRC_OBJS)
	@echo -e "\t" CC [lib$@.a]
	@echo Target [$@] build finished.

ut: $(TARGET) $(B_UT_OBJS)
	@echo -e "\t" CC [$(UNIT_TEST_TARGET)]
	@$(CC) $(LIBS_PATH) -Xlinker "-(" -Wl,-Bstatic $(B_UT_OBJS) -l$(TARGET) $(ST_LIBS_UT) $(ST_LIBS) \
	-Wl,-Bdynamic -Xlinker "-)" $(SO_LIBS) -o build/$(UNIT_TEST_TARGET)
	@echo Target [$(UNIT_TEST_TARGET)] build finished.

.PHONY: all
all: $(TARGET) ut

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: distclean
distclean:
	@rm -rf $(BUILD_DIR) $(TARGET).a $(TARGET).so

# dependencies
$(BUILD_DIR)/%.o: %.c*
	@echo -e "\t" CXX $<
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi;\
	$(CC) $(OBJCCFLAG) $< -o $@
