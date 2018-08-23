MAKEFLAGS+= "j 8" # automatically do "make -j8"

CPPFLAGS += -Wall -Wextra -std=c++14

CPPUTEST_HOME=../../cpputest-3.8
CPPFLAGS += -I$(CPPUTEST_HOME)/include
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest

HEADER_DIR = include
SOURCE_DIR = source
OBJECT_DIR = build
TEST_DIR = test
STUB_HEADER_DIR = stub/include
STUB_SOURCE_DIR = stub/source
STUB_TEST_DIR = stub/test

CPPFLAGS += -I$(HEADER_DIR)
CPPFLAGS += -I$(STUB_HEADER_DIR)

SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

STUB_FILES = $(wildcard $(STUB_SOURCE_DIR)/*.cpp)
STUB_TEST_FILES = $(wildcard $(STUB_TEST_DIR)/*.cpp)

OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/%.o, $(SOURCE_FILES))
TEST_OBJECT_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OBJECT_DIR)/%.o, $(TEST_FILES))
STUB_OBJECT_FILES = $(patsubst $(STUB_SOURCE_DIR)/%.cpp, $(OBJECT_DIR)/%.o, $(STUB_FILES))
STUB_TEST_OBJECT_FILES = $(patsubst $(STUB_TEST_DIR)/%.cpp, $(OBJECT_DIR)/%.o, $(STUB_TEST_FILES))

all:	run

run:	testexec
	./testexec

testexec:	$(STUB_TEST_OBJECT_FILES) $(STUB_OBJECT_FILES) $(TEST_OBJECT_FILES) $(OBJECT_FILES) 
	echo $(STUB_OBJECT_FILES)
	$(CXX) $(CPPFLAGS) $^ -o $@ $(LD_LIBRARIES)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(OBJECT_DIR)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

$(OBJECT_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

$(OBJECT_DIR)/%.o: $(STUB_SOURCE_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

$(OBJECT_DIR)/%.o: $(STUB_TEST_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.SILENT: clean
clean:
	-@rm -rf build
	-@rm -f testexec
