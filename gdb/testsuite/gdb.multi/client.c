/* C ECHO client example using sockets */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void
client (void)
{
  union address_u
  {
    struct sockaddr sa;
    struct sockaddr_in sa_in;
    struct sockaddr_storage sa_stor;
  };

  int sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    {
      perror ("Could not create socket");
      exit (1);
    }

  puts ("Socket created");

  union address_u server;
  server.sa_in.sin_addr.s_addr = inet_addr ("127.0.0.1");
  server.sa_in.sin_family = AF_INET;
  server.sa_in.sin_port = htons(8888);

  while (1)
    {
      if (connect (sock, &server.sa, sizeof (server.sa_in)) < 0)
	{
	  perror ("connect failed, retrying in 1s:");
	  sleep (1);
	}
      else
	{
	  puts ("Connected\n");
	  break;
	}
    }

  while(1)
    {
      char message[1000], server_reply[2000];

      printf ("Enter message: ");
      scanf ("%s", message);

      // Send some data
      if (send (sock, message, strlen (message), 0) < 0)
	{
	  puts ("Send failed");
	  exit (1);
	}

      // Receive a reply from the server
      int recved = recv (sock, server_reply, 2000, 0);
      if (recved < 0)
	{
	  puts ("recv failed");
	  break;
	}
      printf ("Server reply: %.*s\n", recved, server_reply);
    }

  close (sock);
}

int
main ()
{
  client ();
  return 0;
}
