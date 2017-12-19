NODEHEADER=/usr/local/include/node
NANHEADER=node_modules/nan

CC=g++
CFLAG= -DUSE_LIBUV -std=c++11 -O3 -shared -fPIC -static-libstdc++ -static-libgcc -s -I. -I$(NODEHEADER) -I$(NANHEADER)

LIBS=-L.

OBJS=addon.o emitter.o 
NODE=addon.node

all: task addon

addon: $(OBJS)
	$(CC) -o  $(NODE)  $^  $(CFLAG) $(LIBS)

%.o:%.cpp
	$(CC) -c  $<  $(CFLAG) $(LIBS)

task:
	@echo "install nan bindings"
	npm install nan bindings
	
clean:
	rm -rf `find . -name "*.o" -print`
	rm -rf $(NODE) 
	rm -rf node_modules
