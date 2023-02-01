CFLAGS=-Wall -g 
TARGET=main
TARGET_T=tests
MODELS_PATH=Models
DATABASE_PATH=Database
TESTS_PATH=Tests
ALL_PATHS=$(DATABASE_PATH)/*.cpp $(MODELS_PATH)/*.cpp -lsqlite3

fiszka: 	
	rm -f $(TARGET)
	g++ -o $(TARGET) $(TARGET).cpp $(ALL_PATHS)
	./$(TARGET)

ftests:
	rm -f $(TARGET_T)
	g++ -o $(TARGET_T) $(TESTS_PATH)/*.cpp $(ALL_PATHS) 
	./$(TARGET_T)
