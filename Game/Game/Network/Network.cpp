#include "stdafx.h"
#include "Network.h"


Network::Network()
{
	//DLLì«Ç›çûÇ›
	WSAStartup(MAKEWORD(2, 2), &m_wsa);
}

Network::~Network()
{
	closesocket(m_recv.back().s_sock);

	WSACleanup();
}

SocketData* Network::SearchRecv(ULONG addr, int port)
{
	for (int i = 0; i < (int)m_recv.size(); i++)
	{
		if (m_recv.back().s_address.sin_port == htons(port) &&
			m_recv.back().s_address.sin_addr.S_un.S_addr == addr)
		{
			return &m_recv[i];
		}
	}

	SocketData sock;

	m_recv.push_back(sock);

	m_recv.back().s_sock = socket(AF_INET, SOCK_DGRAM, 0);

	m_recv.back().s_address.sin_family = AF_INET;
	m_recv.back().s_address.sin_port = htons(port);
	m_recv.back().s_address.sin_addr.S_un.S_addr = addr;

	bind(m_recv.back().s_sock, (struct sockaddr *)&m_recv.back().s_address, sizeof(m_recv.back().s_address));

	u_long val = 1;
	ioctlsocket(m_recv.back().s_sock, FIONBIO, &val);

	return &m_recv.back();
}

char* Network::Recv(ULONG addr, int port)
{
	SocketData* net = SearchRecv(addr, port);

	memset(net->s_buf, NULL, sizeof(net->s_buf));

	if (recv(net->s_sock, net->s_buf, sizeof(net->s_buf), 0) < 1)
	{
		return "";
	}

	return net->s_buf;
}

char* Network::RecvFrom()
{
	struct sockaddr_in from;

	int sockaddr_in_size = sizeof(struct sockaddr_in);

	SocketData* net = SearchRecv(INADDR_ANY, 12345);

	memset(net->s_buf, NULL, sizeof(net->s_buf));

	recvfrom(net->s_sock, net->s_buf, BUFFER_SIZE - 1, 0, (struct sockaddr *)&from, &sockaddr_in_size);

	int len = strlen(net->s_buf);

	if (0 < len)
	{
		return inet_ntoa(from.sin_addr);
	}
	return "";
}

SocketData* Network::SearchSend(ULONG addr, int port)
{
	for (int i = 0; i < (int)m_send.size(); i++)
	{
		if (m_send.back().s_address.sin_port == htons(port) &&
			m_send.back().s_address.sin_addr.S_un.S_addr == addr)
		{
			return &m_send[i];
		}
	}

	SocketData sock;

	m_send.push_back(sock);

	m_send.back().s_sock = socket(AF_INET, SOCK_DGRAM, 0);

	m_send.back().s_address.sin_family = AF_INET;
	m_send.back().s_address.sin_port = htons(port);
	m_send.back().s_address.sin_addr.S_un.S_addr = addr;

	int yes = 1;

	setsockopt(m_send.back().s_sock, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes));

	return &m_send.back();
}


void Network::Send(ULONG addr, int port, char buf[BUFFER_SIZE])
{
	SocketData* net = SearchSend(addr, port);

	strcpy(net->s_buf, buf);
	strcat(net->s_buf, "\n");
	sendto(net->s_sock, net->s_buf, sizeof(net->s_buf), 0, (struct sockaddr *)&net->s_address, sizeof(net->s_address));
}

char* Network::GetByMyAddress()
{
	LPHOSTENT host;
	IN_ADDR addr, *ip;

	addr.s_addr = inet_addr(NULL);
	if (addr.s_addr == INADDR_NONE)
	{
		host = gethostbyname(NULL);
	}
	else
	{
		host = gethostbyaddr((const char *)&addr, sizeof(IN_ADDR), AF_INET);
	}

	if (host == NULL) {
		return "";
	}

	ip = (IN_ADDR *)host->h_addr_list[0];

	return inet_ntoa(*ip);
}
