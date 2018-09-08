make:
ifeq ($(OS), Windows_NT)
	gcc -o ctrlog main.c -lmingw32 -lSDL2main -lSDL2
else
	gcc -o ctrlog main.c -lSDL2
endif