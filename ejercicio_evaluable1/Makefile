CC=gcc
CFLAGS=-g -Wall
OBJS_SERVER=servidor.o impl_serv.o
OBJS_CLIENT=cliente.o libclaves.so

all: $(OBJS_SERVER) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o servidor_ejev1 $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o cliente_ejev1 $(OBJS_CLIENT)

libclaves.so: claves.o
	$(CC) $(CFLAGS) -shared -fPIC -o libclaves.so claves.o 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -fr $(OBJS_SERVER)
	rm -fr $(OBJS_CLIENT)