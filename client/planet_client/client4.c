#include <stdio.h>
#include <string>
#include <enet/enet.h>

#define HOST "192.168.1.173"
#define PORT (4242)
#define BUFFERSIZE (1000)

#include <pthreadextend.h>

#include <unistd.h>

char  buffer[BUFFERSIZE];
char  sendBuffer[BUFFERSIZE];

char recMess[BUFFERSIZE];

ENetHost  *client;
ENetAddress  address;
ENetEvent  event;
ENetPeer  *peer;
ENetPacket  *packet;
int idx=0;

pthread_t thread_loop;

static void *fn_loop(void *p_data)
{
	while (1) 
	{
      		while (enet_host_service(client, &event, 0) > 0) 
		{
        		switch (event.type) 
			{
          			case ENET_EVENT_TYPE_RECEIVE:
            				puts( (char*) event.packet->data);
                                        peer=event.peer;
                                        idx=0;
                                        for (int i=9;i<(int)event.packet->dataLength;i++)
                                        {
                                                recMess[idx++]=(char)event.packet->data[i];
                                        }
                                        recMess[idx++]='\0';
                                        printf("recMess=|%s|\n",recMess);
                                        enet_packet_destroy (event.packet);

            				break;
          			case ENET_EVENT_TYPE_DISCONNECT:
            				printf("You have been disconnected.\n");
					break;
        		}
      		}
	}
}

void envoyerCommande(char *buf)
{
	sprintf(sendBuffer,"xxxxyyyy%c%s",0x04,buf);
       	packet = enet_packet_create(sendBuffer, 
		strlen(sendBuffer)+1, 
		ENET_PACKET_FLAG_RELIABLE);
       	enet_peer_send(peer, 0, packet);
}

void envoyerCommandes()
{
	envoyerCommande("Helloooo"); // Connexion
/*
	envoyerCommande("C1"); // Connexion
	envoyerCommande("C2"); // Connexion
	envoyerCommande("C3"); // Connexion

	envoyerCommande("c0107"); // 0 cube 107 
	envoyerCommande("c1106"); //
	envoyerCommande("c2095"); //
	envoyerCommande("c3094"); //

	envoyerCommande("c0096"); //
	envoyerCommande("c1099"); //
	envoyerCommande("c2083"); //
	envoyerCommande("c3093"); //

	envoyerCommande("d03051"); //
	envoyerCommande("d12051"); //
	envoyerCommande("d21051"); //
	envoyerCommande("d30051"); //
*/

}

int  main(int argc, char ** argv) 
{
  	int connected=0;
	char buffer[BUFFERSIZE];
	int index;
	char ch;

  	if (argc !=1 ) 
	{
      		printf("Usage: ./client4\n");
      		exit(1);
    	}

    	if (enet_initialize() != 0) 
	{
      		printf("Could not initialize enet.\n");
      		exit(1);
    	}

    	client = enet_host_create(NULL, 1, 2, 0, 0);

    	if (client == NULL) 
	{
      		printf("Could not create client.\n");
      		exit(1);
    	}

    	enet_address_set_host(&address, HOST);
    	address.port = PORT;

    	peer = enet_host_connect(client, &address, 2, 0);

    	if (peer == NULL) 
	{
      		printf("Could not connect to server\n");
      		exit(1);
    	}

    	if (enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) 
	{
      		printf("Connection to %s succeeded.\n", HOST);

		/*
      		//strncpy(buffer, argv[1], BUFFERSIZE);
		sprintf(buffer,"xxxxyyyy%c%s",0x04,argv[1]);
      		packet = enet_packet_create(buffer, strlen(buffer)+1, ENET_PACKET_FLAG_RELIABLE);
      		enet_peer_send(peer, 0, packet);
		*/
    	} 
	else 
	{
      		enet_peer_reset(peer);
      		printf("Could not connect to %s.\n", HOST);
      		exit(1);
    	}

	pthread_create(&thread_loop, NULL, fn_loop, NULL);

	envoyerCommandes();

	index=0;
	while (1)
	{
		/*
        	printf("Input: ");
        	//gets(buffer);

        	if (strlen(buffer) == 0) 
		{ 
			continue; 
		}

        	if (strncmp("q", buffer, BUFFERSIZE) == 0) 
		{
          		enet_peer_disconnect(peer, 0);
          		break;
        	} 
		*/

		ch=getchar();
		if (ch!=EOF)
		{
			if (ch!=10)
				buffer[index++]=ch;
			else
			{
				buffer[index++]=0;
				index=0;

				sprintf(sendBuffer,"xxxxyyyy%c%s",0x04,buffer);
        			packet = enet_packet_create(sendBuffer, 
					strlen(sendBuffer)+1, 
					ENET_PACKET_FLAG_RELIABLE);
        			enet_peer_send(peer, 0, packet);
			}
		}

      	}
    	enet_deinitialize();
}
