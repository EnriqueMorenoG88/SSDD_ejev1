#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)


# Start the server executable in the background
./servidor_ejev1 &

# Wait for the server to start up before starting the client
sleep 1

# Start the client executable
./cliente_ejev1


chmod +x run_server_client.sh
chmod +x servidor_ejev1
chmod +x cliente_ejev1

killall -9 servidor_ejev1