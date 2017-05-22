#include "stdafx.h"
#include "Network.h"

Network::Network()
{
	//DLL�ǂݍ���
	WSAStartup(MAKEWORD(2, 0), &m_wsa);
}

Network::~Network()
{
	//�\�P�b�g�J��
	for each(SocketData data in m_send)
	{
		closesocket(data.s_sock);
	}
	for each(SocketData data in m_recv)
	{
		closesocket(data.s_sock);
	}

	WSACleanup();
}

SocketData& Network::Search_Send(unsigned long addr)
{
	for each(SocketData data in m_send)
	{
		if (data.s_address.sin_addr.S_un.S_addr == addr)
		{
			return data;
		}
	}


	SocketData sock;

	sock.s_sock = socket(AF_INET, SOCK_DGRAM, 0);
	sock.s_address.sin_family = AF_INET;
	sock.s_address.sin_port = htons(12345);
	sock.s_address.sin_addr.S_un.S_addr = addr;

	m_send.push_back(sock);

	setsockopt(m_send.back().s_sock, SOL_SOCKET, SO_BROADCAST, m_send.back().s_buf, sizeof(m_send.back().s_buf));
	return m_send.back();
}

void Network::Send(unsigned long addr, char* str)
{
	SocketData sock = Search_Send(addr);

	//���M�f�[�^�ݒ�
	sprintf(sock.s_buf, "%s\n", str);
	sendto(sock.s_sock, sock.s_buf, sizeof(sock.s_buf), 0, (struct sockaddr*)&sock.s_address, sizeof(sock.s_address));
}

SocketData& Network::Search_Recv(unsigned long addr)
{
	for each(SocketData data in m_recv)
	{
		if (data.s_address.sin_addr.S_un.S_addr == addr)
		{
			return data;
		}
	}

	SocketData sock;

	sock.s_sock = socket(AF_INET, SOCK_DGRAM, 0);
	sock.s_address.sin_family = AF_INET;
	sock.s_address.sin_port = htons(12345);
	sock.s_address.sin_addr.S_un.S_addr = addr;

	m_recv.push_back(sock);

	bind(m_recv.back().s_sock, (struct sockaddr *)&m_recv.back().s_address, sizeof(m_recv.back().s_address));

	memset(m_recv.back().s_buf, NULL, sizeof(m_recv.back().s_buf));

	return m_recv.back();
}

bool Network::IsRecvOK(unsigned long addr)
{
	SocketData sock = Search_Recv(addr);

	fd_set fdset;
	struct timeval timeout;
	FD_ZERO(&fdset);
	FD_SET(sock.s_sock, &fdset);

	/* timeout�͂O�b�B�܂�select�͂����߂��Ă��� */
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	/* read�ł��邩�`�F�b�N */
	select(0, &fdset, NULL, NULL, &timeout);
	return FD_ISSET(sock.s_sock, &fdset);
}

char* Network::Recv(unsigned long addr)
{
	SocketData sock = Search_Recv(addr);

	//sock����f�[�^����M
	recv(sock.s_sock, sock.s_buf, sizeof(sock.s_buf), 0);
	return sock.s_buf;
}