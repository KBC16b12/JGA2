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
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	Network();

	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~Network();
public:
	/*!
	*@brief	�C���X�^���X�擾
	*/
	static Network& GetInstance()
	{
		static Network inst;
		return inst;
	}

	/*!
	*@brief �߂�l��true�Ȃ��MOK
	*/
	bool IsRecvOK(unsigned long addr);

	/*!
	*@brief ���M�֐�
	*/
	void Send(unsigned long addr, char* str);

	/*!
	*@brief ��M�֐�
	*/
	char* Recv(unsigned long addr);

private:

	/*!
	*@brief ���M�֐��̏������֐�
	*/
	SocketData& Search_Send(unsigned long addr);

	/*!
	*@brief ��M�֐��̏������֐�
	*/
	SocketData& Search_Recv(unsigned long addr);

	WSAData						m_wsa;

	std::vector<SocketData>		m_send;
	std::vector<SocketData>		m_recv;
};

