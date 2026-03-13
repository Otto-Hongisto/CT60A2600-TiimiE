# C-2025 project base IK
all:
	gcc -std=c99 -pedantic -Wall src/main.c src/yleinenkirjasto.c src/puukirjasto.c src/listakirjasto.c -o bin/app

test:
	gcc -std=c99 -pedantic -Wall -Isrc test/test_hello.c src/hello.c -o bin/tests
	./bin/tests

clean:
	rm -f bin/app bin/test
