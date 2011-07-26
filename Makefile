
all: test.cpp BitBuilder.hpp
	#clang++ -I/opt/local/include -Wall -Wextra -o test test.cpp
	g++ -I/opt/local/include -Wall -Wextra -o test test.cpp
	./test

