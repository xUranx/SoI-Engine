#include "Network.h"
#include <Raknet/RakPeerInterface.h>
#include <Raknet/MessageIdentifiers.h>
#include <Log.h>
namespace Engine 
{

#define MAX_CLIENTS 3
#define SERVER_PORT 60000

	Network::Network()
	{
		raknet = RakNet::RakPeerInterface::GetInstance();
	}
	Network::~Network()
	{
		RakNet::RakPeerInterface::DestroyInstance(raknet);
	}

	void Network::init()
	{
		if (m_mode)
		{
			RakNet::SocketDescriptor sd;
			raknet->Startup(1, &sd, 1);
		}
		else
		{
			RakNet::SocketDescriptor sd;
			raknet->Startup(MAX_CLIENTS, &sd, 1);
			Message("Starting Server!");
			raknet->SetMaximumIncomingConnections(MAX_CLIENTS);
		}
	}

	bool Network::Connect(char * ip)
	{	
		Message("Connecting...");
		raknet->Connect(ip, SERVER_PORT, 0, 0);
		return true;
	}

	void Network::Update()
	{
		RakNet::Packet *packet;
		for (packet = raknet->Receive(); raknet->DeallocatePacket(packet), packet = raknet->Receive();)
		{
			switch (packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				Message("Server: Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				Message("Server: Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				Message("Server: Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				Message("Server: Our connection request has been accepted.\n");
				break;
			case ID_NEW_INCOMING_CONNECTION:
				Message("Server: A connection is incoming.\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				Message("Server: The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (!m_mode) {
					Message("Server: A client has disconnected.\n");
				}
				else {
					Message("Server: We have been disconnected.\n");
				}
				break;
			case ID_CONNECTION_LOST:
				if (!m_mode) {
					Message("Server: A client lost the connection.\n");
				}
				else {
					Message("Server: Connection lost.\n");
				}
				break;
			default:
				Message("Server: Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}
	}
}