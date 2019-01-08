#include "Network.h"
#include <RakNet/RakPeerInterface.h>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/BitStream.h>
#include <Log.h>
namespace Engine 
{

#define MAX_CLIENTS 3
#define SERVER_PORT 60005
#define CLIENT_PORT 60006

	Network::Network()
	{
		raknet = RakNet::RakPeerInterface::GetInstance();
	}
	Network::~Network()
	{
		raknet->Shutdown(0);
		RakNet::RakPeerInterface::DestroyInstance(raknet);
	}

	void Network::init()
	{
		if (m_mode)
		{
			RakNet::SocketDescriptor sd;
			Message("Info: Starting Peer. ");
			int check = raknet->Startup(1, &sd, 1);
			Message("Result: %i\n", check);
			m_client->m_peer = raknet;
		}
		else
		{
			RakNet::SocketDescriptor sd(SERVER_PORT,0);
			Message("Info: Starting Server! ");
			int check = raknet->Startup(MAX_CLIENTS, &sd, 1);
			Message("Result: %i\n", check);
			raknet->SetMaximumIncomingConnections(MAX_CLIENTS);
			m_server->m_peer = raknet;
		}
	}

	bool Network::Connect(char * ip)
	{	
		Message("Connecting... ");
		int result = raknet->Connect(ip, SERVER_PORT, 0, 0);
		Message("Result: %i\n", result);
		if (m_mode)
		{
			m_client->setIP(ip);
		}
		else
		{
			
		}
		return true;
	}

	void Network::Reseive()
	{
		RakNet::Packet *packet;
		for (packet = raknet->Receive(); raknet->DeallocatePacket(packet), packet = raknet->Receive();)
		{
			bool isthere = false;
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
				//printf("Msg #%i was delivered.\n", msgNumber);
				break;
			default:
				//Message("Server: Message with identifier %i has arrived.\n", packet->data[0]);
				if (m_mode)
				{
					m_client->Receive(packet);
				}
				else
				{
					m_server->Receive(packet);
				}
				break;
			}
		}
	}
	void Network::Send()
	{
		if (m_mode)
		{
			m_client->Send();
		}
		else
		{
			m_server->Send();
		}
	}
}