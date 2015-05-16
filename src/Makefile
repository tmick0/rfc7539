CC=gcc
AR=ar
CCFLAGS=-Wall -Werror -g
TARGET=../rfc7539.a

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(AR) rcs $(TARGET) $(OBJECTS)

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c -o $@ $<
	
%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJECTS) $(TARGET) 
