#ifndef AFX_LOOPBUFFER1_H__C1CEB05C_7A47_40FA_809E_C00D9922AD76__INCLUDED_
#define AFX_LOOPBUFFER1_H__C1CEB05C_7A47_40FA_809E_C00D9922AD76__INCLUDED_
#include "cocos2d.h"
#include "CCNetMacros.h"
CC_NET_BEGIN
//ѭ��������
class CLoopBuffer  
{
public:
	char* buf_;
	char* wptr_; //дָ��
	char* rptr_; //��ָ��
	char* hptr_; //��������ͷָ��
	char* tptr_; //��������βָ��
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

