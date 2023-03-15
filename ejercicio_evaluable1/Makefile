CC=gcc
CFLAGS=-g -Wall
OBJS_SERVER=servidor.o impl_serv.o
OBJS_CLIENT=cliente.o 
LDLIBS = -lpthread -lrt

all: libclaves.so impl_serv.o $(OBJS_SERVER) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o servidor_ejev1 $(OBJS_SERVER) $(LDLIBS)
	$(CC) $(CFLAGS) -o cliente_ejev1 $(OBJS_CLIENT) -L. -lclaves

libimplserv.a: impl_serv.o
	ar rc libimplserv.a impl_serv.o

libclaves.so: claves.c
	$(CC) $(CFLAGS) -shared -fPIC -o libclaves.so claves.c -lrt

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) libclaves.so libimplserv.a servidor_ejev1 cliente_ejev1