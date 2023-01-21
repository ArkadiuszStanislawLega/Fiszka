CFLAGS=-Wall -g
TARGET=main
TATGET_T=tests
MODLES_PATH=Models

fiszka: 	
	rm -f $(TARGET)
	g++ -o $(TARGET) $(TARGET).cpp $(MODLES_PATH)/*.cpp -lsqlite3
	./$(TARGET)

test:
	rm -f $(TARGET_T)
	g++ -o $(TARGET_T) $(TARGET_T).cpp $(MODLES_PATH)/*.cpp -lsqlite3
	./$(TARGET_T)
