# all: 
# 	make static
# 	make shared

# static:
# 	gcc -c -Wall -Wextra -Wwrite-strings src/lib.cpp src/bin/main.cpp -I include
# 	ar -rcs libhashset.a *.o
# 	mkdir -p build/lib/release
# 	mkdir -p build/objects
# 	mv *.o build/objects
# 	mv *.a build/lib/release

# shared:
# 	gcc -c -Wall -Wextra -Wwrite-strings src/lib.cpp src/bin/main.cpp -I include -fPIC
# 	gcc -shared -o libhashset.so lib.o
# 	mkdir -p build/lib/release
# 	mkdir -p build/objects
# 	mv *.o build/objects
# 	mv *.so build/lib/release

# debug:
# 	gcc -g -c -Wall -Wextra -Wwrite-strings src/lib.cpp src/bin/main.cpp -I include -fPIC
# 	gcc -shared -o libhashset.so lib.o
# 	mkdir -p build/lib/debug
# 	mkdir -p build/objects
# 	mv *.o build/objects
# 	mv *.so build/lib/debug

test:
	g++ -c tests/test.cpp -I ./include
	g++ -o test test.o
	mkdir -p build/bin
	mkdir -p build/objects
	mv *.o build/objects
	mv test build/bin
	build/bin/test

# install:
# 	sudo mv build/lib/release/libhashset.so /usr/lib

clean:
	rm -rf build
