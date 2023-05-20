EXEC = main
CFLAGS = -O2 -c -std=c++17 -lcurl

INC = -I ./include

all: main

main: main.o CURLplusplus.o
	@g++ main.o CURLplusplus.o -lcurl -o app ${INC}

main.o: main.cpp CURLplusplus.o
	@g++ ${CFLAGS} main.cpp  ${INC}

CURLplusplus.o: CURLplusplus.hpp CURLplusplus.cpp
	@g++ ${CFLAGS} CURLplusplus.cpp ${INC}

run: 
	main

clean:
	@rm -f main.o CURLplusplus.o

All: main