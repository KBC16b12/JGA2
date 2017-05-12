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
	*@brief	コンストラクタ。
	*/
	Network();

	/*!
	*@brief	デストラクタ。
	*/
	~Network();
public:
	/*!
	*@brief	インスタンス取得
	*/
	static Network& GetInstance()
	{
		static Network inst;
		return inst;
	}

	/*!
	*@brief 戻り値がtrueなら受信OK
	*/
	bool IsRecvOK(unsigned long addr);

	/*!
	*@brief 送信関数
	*/
	void Send(unsigned long addr, char* str);

	/*!
	*@brief 受信関数
	*/
	char* Recv(unsigned long addr);

private:

	/*!
	*@brief 送信関数の初期化関数
	*/
	SocketData& Search_Send(unsigned long addr);

	/*!
	*@brief 受信関数の初期化関数
	*/
	SocketData& Search_Recv(unsigned long addr);

	WSAData						m_wsa;

	std::vector<SocketData>		m_send;
	std::vector<SocketData>		m_recv;
};

