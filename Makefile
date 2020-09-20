CC=gcc
loc=$(shell pwd)

all: src/sysfs.c src/sysfs.h
	${CC} -shared -o build/libsysfstest.so -fPIC src/sysfs.c
	${CC} -o build/sysfstest src/sysfs.h src/main.c build/libsysfstest.so

clear: 
	rm build/*.so
	rm build/sysfstest

test: build/sysfstest
	./build/sysfstest
	

install: build/sysfstest build/libsysfstest.so
	cp build/libsysfstest.so /usr/lib
	cp src/sysfs.h /usr/include
	cp build/sysfstest /bin

uninstall:
	rm /usr/lib/libsysfstest.so
	rm /usr/include/sysfs.h
	rm /bin/sysfstest