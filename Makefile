CFLAGS=-Wall -g 
TARGET=main
TARGET_T=tests
MODLES_PATH=Models
TESTS_PATH=Tests

fiszka: 	
	rm -f $(TARGET)
	g++ -o $(TARGET) $(TARGET).cpp $(MODLES_PATH)/*.cpp -lsqlite3
	./$(TARGET)

ftests:
	rm -f $(TARGET_T)
	g++ -o $(TARGET_T) $(TESTS_PATH)/*.cpp $(MODLES_PATH)/*.cpp -lsqlite3
	./$(TARGET_T)
