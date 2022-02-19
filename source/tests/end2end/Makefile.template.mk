END2END_$(END2END_TEST_ID)_HOST_SOURCES=$(wildcard \
	$(SOURCE_DIR)/tests/end2end/$(END2END_TEST_ID)/*.host.c)
END2END_$(END2END_TEST_ID)_KEFIR_SOURCES=$(wildcard \
	$(SOURCE_DIR)/tests/end2end/$(END2END_TEST_ID)/*.kefir.c)
END2END_$(END2END_TEST_ID)_SOURCES += $(END2END_$(END2END_TEST_ID)_HOST_SOURCES)
END2END_$(END2END_TEST_ID)_SOURCES += $(END2END_$(END2END_TEST_ID)_KEFIR_SOURCES)
END2END_$(END2END_TEST_ID)_DEPENDENCIES := $(END2END_$(END2END_TEST_ID)_HOST_SOURCES:$(SOURCE_DIR)/%.c=$(BIN_DIR)/%.d)
END2END_$(END2END_TEST_ID)_OBJECTS := $(END2END_$(END2END_TEST_ID)_SOURCES:$(SOURCE_DIR)/%.c=$(BIN_DIR)/%.o)


$(END2END_BIN_PATH)/$(END2END_TEST_ID).test: $(END2END_$(END2END_TEST_ID)_OBJECTS)
$(END2END_BIN_PATH)/$(END2END_TEST_ID).test: END2END_TEST_OBJS := $(END2END_$(END2END_TEST_ID)_OBJECTS)

DEPENDENCIES += $(END2END_$(END2END_TEST_ID)_DEPENDENCIES)
OBJECT_FILES += $(END2END_$(END2END_TEST_ID)_OBJECTS)
BINARIES += $(END2END_BIN_PATH)/$(END2END_TEST_ID).test
TESTS += $(END2END_BIN_PATH)/$(END2END_TEST_ID).test.done

# Asmgen tests
END2END_$(END2END_TEST_ID)_ASMGEN_SOURCES=$(wildcard \
	$(SOURCE_DIR)/tests/end2end/$(END2END_TEST_ID)/*.kefir.asmgen.c)

END2END_$(END2END_TEST_ID)_ASMGEN_TEST_EXPECTED := $(END2END_$(END2END_TEST_ID)_ASMGEN_SOURCES:$(SOURCE_DIR)/%.kefir.asmgen.c=$(SOURCE_DIR)/%.asmgen.expected)
END2END_$(END2END_TEST_ID)_ASMGEN_TEST_RESULTS := $(END2END_$(END2END_TEST_ID)_ASMGEN_SOURCES:$(SOURCE_DIR)/%.kefir.asmgen.c=$(BIN_DIR)/%.asmgen.output)
END2END_$(END2END_TEST_ID)_ASMGEN_TESTS := $(END2END_$(END2END_TEST_ID)_ASMGEN_SOURCES:$(SOURCE_DIR)/%.kefir.asmgen.c=$(BIN_DIR)/%.test.asmgen.done)

END2END_ASMGEN_EXPECTED_FILES += $(END2END_$(END2END_TEST_ID)_ASMGEN_TEST_EXPECTED)
TEST_RESULTS += $(END2END_$(END2END_TEST_ID)_ASMGEN_TEST_RESULTS)
TESTS += $(END2END_$(END2END_TEST_ID)_ASMGEN_TESTS)