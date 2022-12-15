TARGET=main

all: clean $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
