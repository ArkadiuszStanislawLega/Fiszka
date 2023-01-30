CFLAGS=-Wall -g 
TARGET=main
TARGET_T=tests
MODELS_PATH=Models
TESTS_PATH=Tests

fiszka: 	
	rm -f $(TARGET)
	g++ -o $(TARGET) $(TARGET).cpp $(MODELS_PATH)/*.cpp -lsqlite3
	./$(TARGET)

ftests:
	rm -f $(TARGET_T)
	g++ -o $(TARGET_T) $(TESTS_PATH)/*.cpp $(MODELS_PATH)/*.cpp -lsqlite3
	./$(TARGET_T)
