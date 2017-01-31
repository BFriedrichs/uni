all: server client

server: server.c messaging.c shared.c
	gcc -o server messaging.c shared.c server.c
client: client.c messaging.c
	gcc -o client messaging.c client.c

clean:
	rm server client
