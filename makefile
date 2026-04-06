# C-2025 project base IK
all:
	gcc -std=c99 -pedantic -Wall src/main.c src/yleinen.c src/puu.c src/lista.c -o bin/app

.PHONY: test

test:
	gcc -std=c99 -pedantic -Wall -Isrc -Iunity \
		test/testRunner.c test/puutesti.c test/listatesti.c \
		unity/unity.c \
		src/yleinen.c src/puu.c src/lista.c \
		-o bin/tests
		./bin/tests


clean:
	rm -f bin/*

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/app
