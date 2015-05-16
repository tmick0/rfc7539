
.PHONY: all test clean rfc7539.a

all: rfc7539.a

rfc7539.a:
	make -C src

test: all
	make -C test
	make -C test run
	
clean:
	make -C src clean
	make -C test clean
