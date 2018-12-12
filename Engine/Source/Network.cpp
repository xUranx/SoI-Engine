#include "Network.h"
#include <Raknet/RakPeerInterface.h>
#include <stdio.h>
#include <Log.h>
namespace Engine 
{

#define MAX_CLIENTS 2
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

	void Client::connect(RakNet::RakPeerInterface* peer)
	{
		Message("Connecting...");
		peer->Connect(m_server, SERVER_PORT, 0, 0);
	}
}