CC          =	gcc
# Flags that are sent to the compiler change the std if you wish

CFLAGS      =	-Wall -std=c99 -pedantic -g  

serial: src/serial_read.c
	$(CC) $(CFLAGS) src/serial_read.c -o ./bin/runSerial

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*