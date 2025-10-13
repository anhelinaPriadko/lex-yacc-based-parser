BISON = bison
FLEX  = flex
CXX   = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Файли об'єктів
OBJS = cpp_parser.tab.o lex.yy.o ast.o main.o

# Основна ціль
all: parser

# Лінкування
parser: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Генерація Bison парсера (зробимо .c + .h)
cpp_parser.tab.c cpp_parser.tab.h: cpp_parser.y
	$(BISON) -d -o cpp_parser.tab.c cpp_parser.y

# Генерація Flex лексера (залежить від Bison заголовка)
lex.yy.c: cpp_lexer.l cpp_parser.tab.h
	$(FLEX) -o lex.yy.c cpp_lexer.l

# Компіляція об'єктів
# Згенерований парсер — це .c, але компілюємо його як C++:
cpp_parser.tab.o: cpp_parser.tab.c
	$(CXX) $(CXXFLAGS) -x c++ -c $< -o $@

lex.yy.o: lex.yy.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

ast.o: ast.cpp ast.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp ast.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f parser *.o lex.yy.c cpp_parser.tab.c cpp_parser.tab.h ast.json

.PHONY: all clean