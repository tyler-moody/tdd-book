MAKEFLAGS+= "j 8" # automatically do "make -j8"

CPPUTEST_HOME=../../cpputest-3.8
CPPFLAGS += -I$(CPPUTEST_HOME)/include
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest

HEADER_DIR = include
SOURCE_DIR = source
OBJECT_DIR = build
TEST_DIR = test

CPPFLAGS += -I$(HEADER_DIR)

SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/%.o, $(SOURCE_FILES))
TEST_OBJECT_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OBJECT_DIR)/%.o, $(TEST_FILES))

all:	run

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(OBJECT_DIR)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

$(OBJECT_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

testexec:	$(OBJECT_FILES) $(TEST_OBJECT_FILES)
	$(CXX) -Wall $(CPPFLAGS) $^ -o $@ $(LD_LIBRARIES)

run:	testexec
	./testexec

.SILENT: clean
clean:
	-@rm -rf build
	-@rm -f testexec
