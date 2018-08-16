CPPUTEST_HOME=../cpputest-3.8
CPPFLAGS += -I$(CPPUTEST_HOME)/include
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest

SOURCE_DIR = source
OBJECT_DIR = build
TEST_DIR = test

COMMON_FILES = $(wildcard $(SOURCE_DIR)/common/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp) $(COMMON_FILES)
PRODUCT_FILES = $(COMMON_FILES) $(SOURCE_DIR)/main.cpp

OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/%.o, $(PRODUCT_FILES))
TEST_OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/%.o, $(TEST_FILES))

all:	product testexec

product:	$(OBJECT_FILES)
	$(CXX) -o $@ $^ $(LD_LIBRARIES)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

testexec:	$(TEST_OBJECT_FILES)
	$(CXX) -Wall $(CPPFLAGS) $^ -o $@ $(LD_LIBRARIES)
