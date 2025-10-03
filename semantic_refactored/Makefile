# -------- C++ COMPILER SETTINGS --------
CXX := g++
CXXFLAGS := -std=c++17 -O2 -g -Wall -Wextra  -Wpedantic

# ---------- PROJECT STRUCTURE ----------

SRC_DIR := src
BUILD_DIR := build
INCLUDE := -Iinclude -I$(BUILD_DIR)

SRCS := $(wildcard $(SRC_DIR)/*.cpp) \
        $(wildcard $(SRC_DIR)/*/*.cpp)

OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS)) \
        $(BUILD_DIR)/parser.o \
        $(BUILD_DIR)/lexer.o

# ------------ DEFAULT RULES ------------

TARGET := dc

default: $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ------ FLEX AND BISON GENERATORS ------

$(BUILD_DIR)/parser.cpp $(BUILD_DIR)/parser.hpp: $(SRC_DIR)/parser.y | $(BUILD_DIR)
	bison -dv -o $(BUILD_DIR)/parser.cpp $<

$(BUILD_DIR)/lexer.cpp: $(SRC_DIR)/lexer.l $(BUILD_DIR)/parser.hpp | $(BUILD_DIR)
	cd $(BUILD_DIR) && flex -s -o lexer.cpp ../$(SRC_DIR)/lexer.l

# ---- C++ SOURCE FILES COMPILATION ----

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(BUILD_DIR)/parser.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

$(BUILD_DIR)/parser.o: $(BUILD_DIR)/parser.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

$(BUILD_DIR)/lexer.o: $(BUILD_DIR)/lexer.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

distclean: clean
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean distclean default
