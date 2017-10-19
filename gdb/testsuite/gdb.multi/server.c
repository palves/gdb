/* C ECHO server example using sockets */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void
server (void)
{
  union address_u
  {
    struct sockaddr sa;
    struct sockaddr_in sa_in;
    struct sockaddr_storage sa_stor;
  };

  int socket_desc = socket (AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1)
    {
      perror ("Could not create socket");
      exit (1);
    }

  puts ("Socket created");

  /* Allow rapid reuse of this port. */
  int tmp = 1;
  setsockopt (socket_desc, SOL_SOCKET, SO_REUSEADDR, (char *) &tmp,
	      sizeof (tmp));

  union address_u server;
  server.sa_in.sin_family = AF_INET;
  server.sa_in.sin_addr.s_addr = INADDR_ANY;
  server.sa_in.sin_port = htons(8888);

  if (bind (socket_desc, &server.sa, sizeof(server.sa_in)) < 0)
    {
      perror ("bind failed. Error");
      exit (1);
    }
  puts ("bind done");

  listen (socket_desc, 3);

  puts ("Waiting for incoming connections...");

  union address_u client;
  socklen_t c = sizeof (struct sockaddr_in);
  int client_sock = accept (socket_desc, &client.sa, &c);
  if (client_sock < 0)
    {
      perror ("accept failed");
      exit (1);
    }
  puts ("Connection accepted");

  while (1)
    {
      char client_message[2000];
      int read_size = recv (client_sock, client_message,
			    sizeof (client_message), 0);
      if (read_size == 0)
	{
	  puts ("Client disconnected\n");
	  break;
	}
      else if (read_size == -1)
	{
	  perror ("recv failed");
	}
      write (client_sock, client_message, read_size);
    }
}

int
main ()
{
  server ();
  return 0;
}
