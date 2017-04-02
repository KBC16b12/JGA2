#pragma once

#define BUFFER_SIZE 2048
class Network
{
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	Network();

	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~Network();

	/*!
	*@brief �������֐�
	*/
	void Init(char* addr);

	/*!
	*@brief ���M�֐�
	*/
	void Send(char* str);

	/*!
	*@brief ��M�֐�
	*/
	char* Recv();

private:
	WSAData					m_wsa;

	SOCKET					m_send_sock;
	struct sockaddr_in		m_send_addr;
	char					m_send_buf[BUFFER_SIZE];

	SOCKET					m_recv_sock;
	struct sockaddr_in		m_recv_addr;
	char					m_recv_buf[BUFFER_SIZE];

};

