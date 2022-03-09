CC = gcc

TARGET = mutex

CFLAGS = -g -Wall

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o  $(TARGET) $(TARGET).c -pthread

clean:
	$(RM) $(TARGET)
