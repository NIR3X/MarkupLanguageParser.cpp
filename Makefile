AR = ar
CXX = g++
CXXFLAGS = -std=c++2a -Wall -O2 -march=x86-64
LDFLAGS = -s -static

SRC = MarkupLanguageParser.cpp
OBJ = $(SRC:.cpp=.o)
DEST = MarkupLanguageParser.a
TEST_SRC = MarkupLanguageParserTest.cpp
TEST_DEST = MarkupLanguageParserTest.exe

build: $(OBJ)
	$(AR) r -o $(DEST) $^

build-test: build
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(DEST) -o $(TEST_DEST) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(DEST) $(TEST_DEST)
