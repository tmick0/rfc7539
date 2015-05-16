CC=gcc
CCFLAGS=-Wall -Werror -g -I../src
LDFLAGS=../rfc7539.a

SOURCES=$(wildcard *.c)
TARGETS=$(SOURCES:.c=)
TESTRUN=$(SOURCES:.c=.test)

.PHONY: clean run

all: $(TARGETS)

%: %.c
	$(CC) $(CCFLAGS) -o $@ $< $(LDFLAGS)
	
%.test: %
	@echo ! Testing $<...; 					\
	./$<;							\
	rc=$$?;							\
	if [ $$rc != 0 ]; then					\
		echo ! $< failed \($$rc\);			\
		exit $$rc;					\
	else							\
		echo ! $< ok;					\
	fi;							\
	
run: $(TESTRUN)
	
clean:
	rm -f $(TARGETS) 
