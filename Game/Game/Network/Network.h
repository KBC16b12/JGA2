#pragma once

#define BUFFER_SIZE 100
class Network
{
public:
	/*!
	*@brief	コンストラクタ。
	*/
	Network();

	/*!
	*@brief	デストラクタ。
	*/
	~Network();

	/*!
	*@brief 送信関数の初期化関数
	*/
	void Init_Send(unsigned long addr);

	/*!
	*@brief 受信関数の初期化関数
	*/
	void Init_Recv(unsigned long addr);

	/*!
	*@brief 送信関数
	*/
	void Send(char* str);

	/*!
	*@brief 受信関数の前にこれがtrueか判定すること
	*/
	bool IsRecvOK();

	/*!
	*@brief 受信関数
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

