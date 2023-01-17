CFLAGS=-Wall -g
TARGET=main
MODLES_PATH=Models

all: 
	rm -f $(TARGET)
	g++ -o $(TARGET) *.cpp $(MODLES_PATH)/*.cpp -lsqlite3
	./$(TARGET)
