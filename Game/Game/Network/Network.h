#pragma once

#define BUFFER_SIZE 100

struct SocketData
{
	SOCKET					s_sock;
	struct sockaddr_in		s_address;
	char					s_buf[BUFFER_SIZE];
};

class Network
{
private:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	Network();

	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~Network();
public:

	static Network& GetInstance()
	{
		static Network inst;
		return inst;
	}

	/*!
	*@brief ��M�֐�
	*/
	char* Recv(ULONG addr, int port);

	/*
	*@���M���m�F�֐�
	*/
	char* RecvFrom();

	/*!
	*@brief ���M�֐�
	*/
	void Send(ULONG addr, int port, char buf[BUFFER_SIZE]);

	/*!
	*@brief �����̃A�h���X�擾
	*/
	char* GetByMyAddress();

	char* GetRecvData(ULONG addr, int port);

private:
	/*!
	*@brief ��M���X�g�T���֐�
	*/
	SocketData* SearchRecv(ULONG addr, int port);

	/*!
	*@brief	���M���X�g�T���֐�
	*/
	SocketData* SearchSend(ULONG addr, int port);

private:
	WSAData									m_wsa;

	std::vector<SocketData>					m_recv;
	std::vector<SocketData>					m_send;
};
