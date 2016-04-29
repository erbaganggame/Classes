/****************************************************************************
Copyright (c) 2014 Lijunlin - Jason lee

Created by Lijunlin - Jason lee on 2014

jason.lee.c@foxmail.com
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCNetDelegate.h"

CC_NET_BEGIN

CCNetDelegate::CCNetDelegate()
: m_fSoTimeout(SOCKET_SOTIMEOUT)
, m_eStatus(eSocketIoClosed)
, m_fConnectingDuration(0.0f)
, m_oReadBuffer(1024*64)
, m_oWriteBuffer(1024*64)
, m_oInputPakcet()
, m_bRunSchedule(false)
{
	
}

CCNetDelegate::~CCNetDelegate()
{
	m_oSocket.ccClose();
	m_oReadBuffer.Reset();
	m_oWriteBuffer.Reset();
	unregisterScheduler();
}

// when connected will calling
void CCNetDelegate::onConnected()
{
#if DEBUG
	CCLOG("SOCKET CONNECTED!");
#endif
	m_oKKDecoder.Init();
	m_oReadBuffer.Reset();
	m_oWriteBuffer.Reset();
}

// when connect time out will calling
void CCNetDelegate::onConnectTimeout()
{
#if DEBUG
	CCLOG("SOCKET CONNECT TIMEOUT!");
#endif
}

// on disconnected will call
void CCNetDelegate::onDisconnected()
{
#if DEBUG
	CCLOG("SOCKET DISCONNECT!");
#endif
}

//void CCNetDelegate::setInetAddress(const CCInetAddress& oInetAddress)
//{
//	m_oInetAddress = oInetAddress;
//}

void CCNetDelegate::setIpPort(const char* ip, unsigned short port)
{
	CCInetAddress oInetAddress(ip, port);
	m_oInetAddress = oInetAddress;
}


//const CCInetAddress& CCNetDelegate::getInetAddress() const
//{
//	return m_oInetAddress;
//}

void CCNetDelegate::setSoTimeout(float fSoTimeout)
{
	m_fSoTimeout = fSoTimeout;
}

float CCNetDelegate::getSoTimeout() const
{
	return m_fSoTimeout;
}

//void CCNetDelegate::send(char* pBuffer, unsigned int uLen)
//{
//	if( !pBuffer || uLen == 0 || !isConnected() )
//		return;
	
/*#if USING_PACKAGE_HEAD_LENGTH
	CCBuffer* pBuf = new CCBuffer(pBuffer, uLen);
	pBuf->autorelease();
	send(pBuf);
#else 
	char* pTemp = new char[uLen];
	memcpy(pTemp, pBuffer, uLen);

	_SENDBUFFER tBuf;
	tBuf.pBuffer = pTemp;
	tBuf.nLength = (int)uLen;
	tBuf.nOffset = 0;

	//m_lSendBuffers.push_back(tBuf);
#endif */
//	m_oWriteBuffer.Put(pBuffer, uLen);
//}

void CCNetDelegate::send(/*CCBuffer* pBuffer*/ OutputPacket*pPacket)
{
	if( !isConnected() )
		return;
	/*
#if USING_PACKAGE_HEAD_LENGTH
	unsigned int u_len = pBuffer->length();
	pBuffer->moveRight(sizeof(unsigned int));
	pBuffer->moveWriterIndexToFront();
	pBuffer->writeUInt(u_len);
#endif

	pBuffer->moveReaderIndexToFront();
	char* pData = pBuffer->readWholeData();
	int nLength = (int)pBuffer->length();
	pBuffer->moveReaderIndexToFront();

	_SENDBUFFER tBuf;
	tBuf.pBuffer = pData;
	tBuf.nLength = nLength;
	tBuf.nOffset = 0;

	m_lSendBuffers.push_back(tBuf);
	*/
	m_oWriteBuffer.Put(pPacket->packet_buf(), pPacket->packet_size());
}

bool CCNetDelegate::isConnected()
{
	return m_eStatus == eSocketConnected;
}

bool CCNetDelegate::connect()
{
	if( m_eStatus != eSocketConnected && m_eStatus != eSocketConnecting )
	{
		m_oSocket.setInetAddress(m_oInetAddress);
		if( m_oSocket.ccConnect() )
		{
			registerScheduler();
			m_eStatus = eSocketConnecting;
			return true;
		}
		else
		{
			m_oSocket.ccClose();
			m_eStatus = eSocketConnectFailed;
			onExceptionCaught(eSocketConnectFailed);
		}
	}
	return false;
}

void CCNetDelegate::disconnect()
{
	if( m_eStatus == eSocketConnected )
	{
		unregisterScheduler();
		m_oSocket.ccDisconnect();
		m_eStatus = eSocketDisconnected;
		onDisconnected();
	}
}

void CCNetDelegate::close()
{
	if( m_eStatus == eSocketConnected )
	{
		unregisterScheduler();
		m_oSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
	}
}

void CCNetDelegate::runSchedule(float dt)
{
	switch( m_eStatus )
	{
	case eSocketConnecting:
		{
			switch( m_oSocket.ccIsConnected() )
			{
			case eSocketConnected:
				{
					m_eStatus = eSocketConnected;
					onConnected();
				}
				break;
			case eSocketConnectFailed:
				{
					unregisterScheduler();
                    m_oSocket.ccClose();
					m_eStatus = eSocketConnectFailed;
					onExceptionCaught(eSocketConnectFailed);
				}
				break;
			case eSocketConnecting:
				{
					if( m_fConnectingDuration > m_fSoTimeout )
					{
						unregisterScheduler();
						m_oSocket.ccDisconnect();
						m_eStatus = eSocketDisconnected;
						onConnectTimeout();
						m_fConnectingDuration = 0.0f;
					}
					else
					{
						m_fConnectingDuration += dt;
					}
				}
				break;
			default:
				break;
			}
		}
		break;
	case eSocketConnected:
		{
#if HANDLE_ON_SINGLE_FRAME
			while( m_oSocket.ccIsReadable() )
#else
			if( m_oSocket.ccIsReadable() )
#endif
			{
				if( this->runRead() ) return;
			}

#if HANDLE_ON_SINGLE_FRAME
			while( m_oWriteBuffer.DataCount()>0 && m_oSocket.ccIsWritable() )
#else
			if( m_oWriteBuffer.DataCount()>0 && m_oSocket.ccIsWritable() )
#endif
			{
				if( this->runWrite() ) return;
			}
		}
		break;
	default:
		break;
	}	
}

bool CCNetDelegate::runRead()
{
	int nRet = m_oSocket.ccRead(m_pTempBuffer, SOCKET_READ_BUFFER_SIZE);
#if 1
	CCLOG("CCSOCKET READ %d", nRet);
#endif
	if( nRet == eSocketIoError || nRet == eSocketIoClosed )
	{
		unregisterScheduler();
		m_oSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
		return true;
	}
	else if (nRet == eSocketAgain || nRet == eSocketBlock)
	{
		return false;
	}
	else
	{
		if (m_oReadBuffer.Put(m_pTempBuffer, nRet) == nRet)
		{
			while (m_oReadBuffer.DataCount() >= PACKET_HEAD_LEN)
			{
				nRet = m_oReadBuffer.Peek(m_pTempBuffer, SOCKET_READ_BUFFER_SIZE);
				nRet = m_oKKDecoder.ParsePacket(m_pTempBuffer, nRet);
				if (nRet > 0)
				{
					//m_oInputPakcet.Copy(m_pTempBuffer, nRet);
					onMessageReceived(m_pTempBuffer, nRet);
					m_oReadBuffer.Erase(nRet);
				}
				else if (nRet == 0)
				{
					break;
				}
				else
				{
					unregisterScheduler();
					m_oSocket.ccClose();
					m_eStatus = eSocketIoClosed;
					onDisconnected();
					return true;
				}
			}
			
		}
		else
		{

#if 1
			CCLOG("ReadBuffer output %d", nRet);
#endif
			unregisterScheduler();
			m_oSocket.ccClose();
			m_eStatus = eSocketIoClosed;
			onDisconnected();
			return true;
		}
	}
	return false;
}

bool CCNetDelegate::runWrite()
{
	//_SENDBUFFER& tBuffer = m_lSendBuffers.front();
	int nSendLen = m_oWriteBuffer.Peek(m_pTempBuffer, SOCKET_READ_BUFFER_SIZE);
	int nRet = m_oSocket.ccWrite(m_pTempBuffer,nSendLen);
#if 1
	CCLOG("CCSOCKET WRITE %d", nRet);
#endif
	if( nRet == eSocketIoError )
	{
		unregisterScheduler();
		m_oSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
		return true;
	}
	else if (nRet == eSocketAgain)
	{
		return false;
	}
	else if (nRet == eSocketBlock)
	{
		m_oWriteBuffer.Erase(nRet);
		return false;
	}
	else
	{
		m_oWriteBuffer.Erase(nRet);
		return false;
	}
	/*else if( nRet == tBuffer.nLength - tBuffer.nOffset )
	{
		CC_SAFE_DELETE_ARRAY(tBuffer.pBuffer);
		m_lSendBuffers.pop_front();
	}
	else
	{
		tBuffer.nOffset += nRet;
	}*/
	return false;
}

void CCNetDelegate::registerScheduler()
{
	if( m_bRunSchedule )
		return;
	
	CCDirector::sharedDirector()->getScheduler()->schedule(
		schedule_selector(CCNetDelegate::runSchedule), 
		this, 
		0.0f, 
		false
	);
	//CCDirector::getInstance()->getScheduler()->schedule()
	m_bRunSchedule = true;
}

void CCNetDelegate::unregisterScheduler()
{
	if( !m_bRunSchedule )
		return;

	CCDirector::sharedDirector()->getScheduler()->unschedule(
		schedule_selector(CCNetDelegate::runSchedule),
		this
	);
	m_bRunSchedule = false;
}

CC_NET_END