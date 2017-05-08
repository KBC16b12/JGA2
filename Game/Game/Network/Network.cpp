#include "stdafx.h"
#include "Network.h"

Network::Network()
{
	//DLL読み込み
	WSAStartup(MAKEWORD(2, 0), &m_wsa);
	
	//Sendデータの初期化
	m_send_sock = socket(AF_INET, SOCK_DGRAM, 0);

	m_send_addr.sin_family = AF_INET;
	m_send_addr.sin_port = htons(12345);
	m_send_addr.sin_addr.S_un.S_addr = inet_addr("");

	//Recvデータの初期化
	m_recv_sock = socket(AF_INET, SOCK_DGRAM, 0);

	m_recv_addr.sin_family = AF_INET;
	m_recv_addr.sin_port = htons(12345);
	m_recv_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	memset(m_recv_buf, NULL, sizeof(m_recv_buf));
}

Network::~Network()
{
	//ソケット開放
	closesocket(m_send_sock);
	closesocket(m_recv_sock);

	WSACleanup();
}

void Network::Init_Send(unsigned long addr)
{
	//送信先データ設定
	m_send_addr.sin_addr.S_un.S_addr = addr;
	setsockopt(m_send_sock, SOL_SOCKET, SO_BROADCAST, m_send_buf, sizeof(m_send_buf));
}

void Network::Init_Recv(unsigned long addr)
{
	//受信先データ設定
	m_recv_addr.sin_addr.S_un.S_addr = addr;
	bind(m_recv_sock, (struct sockaddr *)&m_recv_addr, sizeof(m_recv_addr));
}

void Network::Send(char* str)
{
	//送信データ設定
	sprintf(m_send_buf, "%s\n", str);
	sendto(m_send_sock, str, sizeof(m_send_buf), 0, (struct sockaddr *)&m_send_addr, sizeof(m_send_addr));
}

bool Network::IsRecvOK()
{
	fd_set fdset;
	struct timeval timeout;
	FD_ZERO(&fdset);
	FD_SET(m_recv_sock, &fdset);

	/* timeoutは０秒。つまりselectはすぐ戻ってく る */
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	/* readできるかチェック */
	select(0, &fdset, NULL, NULL, &timeout);
	return FD_ISSET(m_recv_sock, &fdset);
}

char* Network::Recv()
{
	//m_recv_sockからデータを受信
	recv(m_recv_sock, m_recv_buf, sizeof(m_recv_buf), 0);
	return m_recv_buf;
}