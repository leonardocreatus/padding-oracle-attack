EXEC = main
CFLAGS = -O2 -c -std=c++17 -lcurl

INC = -I ./include

all: main

main: main.o OraclePaddingAttack.o CURLplusplus.o Converter.o
	@g++ main.o OraclePaddingAttack.o CURLplusplus.o Converter.o -lcurl -o app ${INC}

main.o: main.cpp OraclePaddingAttack.o Converter.o
	@g++ ${CFLAGS} main.cpp  ${INC}

OraclePaddingAttack.o: OraclePaddingAttack.hpp OraclePaddingAttack.cpp CURLplusplus.o Converter.o
	@g++ ${CFLAGS} OraclePaddingAttack.cpp CURLplusplus.o Converter.o ${INC}

CURLplusplus.o: CURLplusplus.hpp CURLplusplus.cpp
	@g++ ${CFLAGS} CURLplusplus.cpp ${INC}

Converter.o: Converter.hpp Converter.cpp
	@g++ ${CFLAGS} Converter.cpp ${INC}

run: 
	main

clean:
	@rm -f main.o CURLplusplus.o Converter.o OraclePaddingAttack.o app

All: main