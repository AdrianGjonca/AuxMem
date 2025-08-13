# === Directories ===
SRC_DIR    := SOURCE
INC_DIR    := HEADER
BUILD_DIR  := build
TEST_DIR   := TESTS

# === Compiler & Flags ===
CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -fPIC -I$(INC_DIR)
AR      := ar
ARFLAGS := rcs

# === Library Name ===
LIBNAME     := auxmem
STATIC_LIB  := lib$(LIBNAME).a
SHARED_LIB  := lib$(LIBNAME).so

# === Library Sources ===
SRC  := $(wildcard $(SRC_DIR)/*.c)
OBJ  := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# === Test Sources ===
TEST_SRC  := $(wildcard $(TEST_DIR)/*.c)
TEST_BIN  := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_SRC))

# === Default Target ===
.PHONY: all clean test
all: $(STATIC_LIB) $(SHARED_LIB)

# === Build Static Library ===
$(STATIC_LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

# === Build Shared Library ===
$(SHARED_LIB): $(OBJ)
	$(CC) -shared -o $@ $^

# === Compile Object Files for Library ===
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(wildcard $(INC_DIR)/*.h)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# === Build Test Executables (linked with static lib) ===
$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(STATIC_LIB)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -L. -l$(LIBNAME) -o $@

# === Run All Tests ===
test: $(TEST_BIN)
	@for t in $(TEST_BIN); do \
		echo "Running $$t:"; \
		LD_LIBRARY_PATH=. ./$$t || exit 1; \
		echo ""; \
	done

# === Clean Up ===
clean:
	rm -rf $(BUILD_DIR) $(STATIC_LIB) $(SHARED_LIB)

