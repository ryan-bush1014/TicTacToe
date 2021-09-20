build:
	gcc -Wall \
		-std=c99 \
		./*.c \
		-I"C:\libsdl\include" \
		-L"C:\libsdl\lib" \
		-lSDL2main \
		-lSDL2 \
		-o TicTacToe
