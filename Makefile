SOURCE=\
	./src/Server/main.cpp\
	./src/Server/UdpServer.cpp\
	./src/Common/GameState.cpp

all: $(SOURCE)
	g++ $(SOURCE) -o minesweeper-server -I./src/Common -I./src/Server -I./linux -lsfml-network

