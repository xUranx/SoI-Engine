#pragma once
#include <map>
#include <RakNet/RakNetTypes.h>
#include <vector>
namespace RakNet
{
	class RakPeerInterface;
	class BitStream;
}
namespace Engine 
{
	class Server
	{
	public:
		Server() {};
		~Server() {};

		virtual void Send() {};
		virtual void Receive(RakNet::Packet *packet) {};

		std::map<int, RakNet::SystemAddress> m_clients;
	protected:
		friend class Network;
		std::vector<int> m_freeIDs;
		int m_client_num = 0;
		RakNet::RakPeerInterface* m_peer = nullptr;
	private:

	};

	class Client
	{
	public:
		Client() {};
		~Client() {};

		void setIP(char* ServerIp) { m_server_ip = ServerIp; }

		virtual void Send() {};
		virtual void Receive(RakNet::Packet *packet) {};

		//char* GetServerIP() { return m_server; }


	protected:
		friend class Network;
		char* m_server_ip;
		RakNet::RakPeerInterface* m_peer = nullptr;
	private:

	};
	class Network
	{
	public:

		Network();
		~Network();

		void init();
		void setServer(Server* server) { if (!m_mode_set)m_server = server; m_mode = 0; m_mode_set = true; }
		void setClient(Client* client) { if (!m_mode_set)m_client = client; m_mode = 1; m_mode_set = true; }
		
		bool Connect(char* ip);

		void Reseive();

		void Send();

		//RakNet::BitStream* getBitSream() { return m_bitstream; }
		RakNet::RakPeerInterface* getPeer() { return raknet; }

	private:
		//RakNet::BitStream* m_bitstream = nullptr;
		int m_mode = 0;
		bool m_mode_set = false;
		Server* m_server;
		Client* m_client;
		RakNet::RakPeerInterface* raknet;

	};
	
}
