#pragma once
#include <map>
namespace RakNet
{
	class RakPeerInterface;
}
namespace Engine 
{
	class Network
	{
	public:

		Network();
		~Network();

		void init();
		void setServer(Server* server) { if (!m_mode_set)m_server = server; m_mode = 0; m_mode_set = true; }
		void setClient(Client* client) { if (!m_mode_set)m_client = client; m_mode = 1; m_mode_set = true; }
		
	private:
		int m_mode = 0;
		bool m_mode_set = false;
		Server* m_server;
		Client* m_client;
		RakNet::RakPeerInterface* raknet;
	};
	
	class Server
	{
	public:
		Server() {};
		~Server() {};

		virtual void Send() {};
		virtual void Reseive() {};

	private:
		friend class Network;
		int m_client_count = 0;
		std::map<int, char> m_clients;

	};

	class Client
	{
	public:
		Client() {};
		~Client() {};

		void setIP(char* ServerIp) { m_server = ServerIp; }

		virtual void Send() {};
		virtual void Reseive() {};

		//char* GetServerIP() { return m_server; }


	private:
		void connect(RakNet::RakPeerInterface*);
		friend class Network;
		char* m_server;

	};
}
