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
	*@brief	コンストラクタ。
	*/
	Network();

	/*!
	*@brief	デストラクタ。
	*/
	~Network();
public:

	static Network& GetInstance()
	{
		static Network inst;
		return inst;
	}

	/*!
	*@brief 受信関数
	*/
	char* Recv(ULONG addr, int port);

	/*
	*@送信元確認関数
	*/
	char* RecvFrom();

	/*!
	*@brief 送信関数
	*/
	void Send(ULONG addr, int port, char buf[BUFFER_SIZE]);

	/*!
	*@brief 自分のアドレス取得
	*/
	char* GetByMyAddress();

	char* GetRecvData(ULONG addr, int port);

private:
	/*!
	*@brief 受信リスト探索関数
	*/
	SocketData* SearchRecv(ULONG addr, int port);

	/*!
	*@brief	送信リスト探索関数
	*/
	SocketData* SearchSend(ULONG addr, int port);

private:
	WSAData									m_wsa;

	std::vector<SocketData>					m_recv;
	std::vector<SocketData>					m_send;
};
