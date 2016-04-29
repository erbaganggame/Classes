#ifndef AFX_LOOPBUFFER1_H__C1CEB05C_7A47_40FA_809E_C00D9922AD76__INCLUDED_
#define AFX_LOOPBUFFER1_H__C1CEB05C_7A47_40FA_809E_C00D9922AD76__INCLUDED_
#include "cocos2d.h"
#include "CCNetMacros.h"
CC_NET_BEGIN
//循环缓冲区
class CLoopBuffer  
{
public:
	char* buf_;
	char* wptr_; //写指针
	char* rptr_; //读指针
	char* hptr_; //缓冲区的头指针
	char* tptr_; //缓冲区的尾指针
	int count_;
public:
	CLoopBuffer();
	CLoopBuffer(int bufsize);
	virtual ~CLoopBuffer();
	void InitMember();
	void Init(int bufsize);
	void Reset();
	////return real size of write in buffer
	int Put(char* buf, int size);
	////return real size of read from buffer
	//// get data and erase the data is readed
	int Get(char* buf, int size);
	////return real size of read from buffer
	//// get data but not erase the data is readed
	int Peek(char* buf, int size);
	////erase size of buffer
	int Erase(int size);
	////returan total free buffer size
	int Count(); 
	int FreeCount();
	int DataCount();	
};

CC_NET_END
#endif // !defined(AFX_LOOPBUFFER1_H__C1CEB05C_7A47_40FA_809E_C00D9922AD76__INCLUDED_)

