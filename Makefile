.PHONY: default run compile test_display test_keyboard clean test


default:
	gcc -o chip8.out src/display.c src/main.c src/chip8.c src/utility.c -lSDL

run:
	gcc -o chip8.out src/display.c src/main.c src/chip8.c src/utility.c -lSDL && ./chip8.out

compile:
	gcc -o chip8.out src/display.c src/main.c src/chip8.c src/utility.c -lSDL

test_display:
	gcc -o display_test.out -lSDL test/display.c src/display.c

test_keyboard:
	gcc -o keyboard.out -lSDL test/keyboard.c src/display.c

clean:
	rm *.out

