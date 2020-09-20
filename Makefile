CC=gcc
loc=$(shell pwd)

all:
	${CC} -shared -o build/libsysfstest.so -fPIC src/sysfs.c
	${CC} -o build/sysfstest src/sysfs.h src/main.c build/libsysfstest.so

clean: build/sysfstest build/*.so
	rm build/*.so
	rm build/sysfstest

test: build/sysfstest
	./build/sysfstest
	

install: build/sysfstest build/libsysfstest.so
	cp build/libsysfstest.so /usr/lib
	cp src/sysfs.h /usr/include

uninstall:
	rm /usr/lib/libsysfstest.so
	rm /usr/include/sysfs.h


