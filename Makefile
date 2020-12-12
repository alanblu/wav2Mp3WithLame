build:
	g++ -std=gnu++17 -Wall src/main.cpp src/LameHandler.h src/LameHandler.cpp src/GetFiles.h src/GetFiles.cpp  -lmp3lame -lpthread -o bin/wavToMp3 -lm
clean:
	\rm -fr ll
