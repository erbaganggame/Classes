
#include "Packet.h"
#include "cocos2d.h"
#ifdef _WIN32
#include <winsock2.h>
typedef long long int64_t;
#else
#include <netinet/in.h>
#endif
CC_NET_BEGIN
//
static BYTE m_RecvByteMap[256]=				
{
0x7d,0x21,0x1e,0x12,0x03,0x89,0xe8,0x6f,0x59,0x64,0xac,0x9a,0xd1,0x7e,0x6e,0x32,
0xdd,0x36,0x60,0x6b,0xf3,0x10,0x33,0x88,0x8b,0xa9,0x13,0xdc,0x4d,0x5a,0x7c,0xdb,
0x18,0x0a,0x87,0x29,0x3c,0x71,0x2d,0x46,0x7f,0x44,0x41,0x4f,0x25,0x43,0x73,0x7a,
0x4b,0x6d,0x0f,0x80,0x6a,0xe3,0xf2,0x38,0x69,0xe5,0xff,0x2b,0x08,0x49,0x14,0x7b,
0xf5,0xc6,0xfa,0xd5,0x8d,0x9b,0x48,0x00,0xd2,0x05,0xc1,0x28,0x3b,0x0c,0xf1,0x34,
0x66,0x9c,0xb7,0x9e,0x2f,0xa3,0xd7,0x26,0x1d,0x22,0xb2,0xc8,0x99,0x53,0x42,0x02,
0x85,0x76,0x8a,0x82,0x8f,0xcb,0x55,0x2a,0x0d,0xab,0xef,0xda,0xd0,0x1c,0x15,0x31,
0xbe,0xe2,0xf9,0xb9,0xe7,0xe4,0xf8,0xaa,0xec,0xd8,0x83,0x57,0x90,0x62,0x6c,0x8c,
0x4e,0xb3,0x95,0x1f,0x92,0xf4,0x40,0xad,0x96,0x8e,0x06,0x2e,0x4a,0xc5,0xe9,0xeb,
0xed,0xbb,0x39,0xc0,0x5d,0x11,0xa1,0xbd,0x52,0x77,0x45,0x50,0xc3,0x51,0x24,0xb6,
0xc4,0x70,0x5f,0xcd,0x30,0x5b,0x01,0x98,0x37,0xa0,0xe6,0xe0,0xfe,0x54,0x0e,0xb4,
0xc7,0xce,0x1b,0x78,0x27,0x9d,0x5c,0x61,0xb0,0xb1,0xca,0x84,0xd3,0xdf,0x97,0x68,
0xa2,0xa8,0xae,0x75,0x20,0x9f,0x58,0xcf,0xee,0x93,0xa4,0xf6,0x47,0x79,0x63,0x91,
0xb5,0xf0,0x1a,0xb8,0x07,0xd4,0xcc,0xc9,0xfc,0x09,0x86,0x74,0xbf,0xea,0x65,0xfb,
0xd9,0xa5,0xa7,0xe1,0x19,0x72,0xba,0xbc,0x0b,0x04,0x17,0xaf,0xfd,0x81,0xde,0x3a,
0x16,0x23,0x67,0x94,0x4c,0xa6,0x3f,0x3d,0x3e,0x5e,0x35,0xf7,0xc2,0x56,0x2c,0xd6
};

//
static BYTE m_SendByteMap[256]=				
{
0x47,0xa6,0x5f,0x04,0xe9,0x49,0x8a,0xd4,0x3c,0xd9,0x21,0xe8,0x4d,0x68,0xae,0x32,
0x15,0x95,0x03,0x1a,0x3e,0x6e,0xf0,0xea,0x20,0xe4,0xd2,0xb2,0x6d,0x58,0x02,0x83,
0xc4,0x01,0x59,0xf1,0x9e,0x2c,0x57,0xb4,0x4b,0x23,0x67,0x3b,0xfe,0x26,0x8b,0x54,
0xa4,0x6f,0x0f,0x16,0x4f,0xfa,0x11,0xa8,0x37,0x92,0xef,0x4c,0x24,0xf7,0xf8,0xf6,
0x86,0x2a,0x5e,0x2d,0x29,0x9a,0x27,0xcc,0x46,0x3d,0x8c,0x30,0xf4,0x1c,0x80,0x2b,
0x9b,0x9d,0x98,0x5d,0xad,0x66,0xfd,0x7b,0xc6,0x08,0x1d,0xa5,0xb6,0x94,0xf9,0xa2,
0x12,0xb7,0x7d,0xce,0x09,0xde,0x50,0xf2,0xbf,0x38,0x34,0x13,0x7e,0x31,0x0e,0x07,
0xa1,0x25,0xe5,0x2e,0xdb,0xc3,0x61,0x99,0xb3,0xcd,0x2f,0x3f,0x1e,0x00,0x0d,0x28,
0x33,0xed,0x63,0x7a,0xbb,0x60,0xda,0x22,0x17,0x05,0x62,0x18,0x7f,0x44,0x89,0x64,
0x7c,0xcf,0x84,0xc9,0xf3,0x82,0x88,0xbe,0xa7,0x5c,0x0b,0x45,0x51,0xb5,0x53,0xc5,
0xa9,0x96,0xc0,0x55,0xca,0xe1,0xf5,0xe2,0xc1,0x19,0x77,0x69,0x0a,0x87,0xc2,0xeb,
0xb8,0xb9,0x5a,0x81,0xaf,0xd0,0x9f,0x52,0xd3,0x73,0xe6,0x91,0xe7,0x97,0x70,0xdc,
0x93,0x4a,0xfc,0x9c,0xa0,0x8d,0x41,0xb0,0x5b,0xd7,0xba,0x65,0xd6,0xa3,0xb1,0xc7,
0x6c,0x0c,0x48,0xbc,0xd5,0x43,0xff,0x56,0x79,0xe0,0x6b,0x1f,0x1b,0x10,0xee,0xbd,
0xab,0xe3,0x71,0x35,0x75,0x39,0xaa,0x74,0x06,0x8e,0xdd,0x8f,0x78,0x90,0xc8,0x6a,
0xd1,0x4e,0x36,0x14,0x85,0x40,0xcb,0xfb,0x76,0x72,0x42,0xdf,0xd8,0xec,0xac,0x3a
};

int InputPacket::CrevasseBuffer() 
{
	BYTE *pcbDataBuffer = (BYTE *)base::packet_buf() + base::PACKET_HEADER_SIZE;
	WORD wDataSize = base::GetBodyLength() - base::PACKET_HEADER_SIZE + sizeof(short);
	
	BYTE cbCheckCode = base::GetcbCheckCode();
	for (int i=0;i<wDataSize;i++)
	{
		pcbDataBuffer[i]=m_RecvByteMap[pcbDataBuffer[i]];
		cbCheckCode+=pcbDataBuffer[i];
	}

	if(cbCheckCode!=0) 
	{

		return -1;
	}

	return wDataSize;
}


WORD OutputPacket::EncryptBuffer()
{	
	if(IsWritecbCheckCode())  
		return 0;
	BYTE *pcbDataBuffer = (BYTE *)base::packet_buf() + base::PACKET_HEADER_SIZE;
	WORD wDataSize = base::GetBodyLength() - base::PACKET_HEADER_SIZE + sizeof(short);
 
	BYTE cbCheckCode=0;
	for (WORD i=0;i<wDataSize;i++)
	{
		cbCheckCode+=pcbDataBuffer[i];
		pcbDataBuffer[i]=m_SendByteMap[pcbDataBuffer[i]];
	}
	WritecbCheckCode(~cbCheckCode+1);

	return wDataSize;
}

	PacketBase::PacketBase(void){}

	char *PacketBase::packet_buf(void)	{ return m_strBuf; }
	int PacketBase::packet_size(void)	{ return m_nPacketSize; }

	//Get body length
	unsigned short PacketBase::GetBodyLength(void)
	{
		unsigned short nLen;
		_readHeader((char*)&nLen, sizeof(short), 0);
		unsigned short len = ntohs(nLen);
		return len;
	}

	/*协议主版本号*/
	unsigned char PacketBase::GetVersion(void)
	{
		unsigned char c;
		_readHeader(&c, sizeof(char), 2);	// 
		return c;
	}

	/*协议子版本号*/
	unsigned char PacketBase::GetSubVersion(void)
	{
		unsigned char c;
		_readHeader(&c, sizeof(char), 3);	//
		return c;
	}

	/*校验code*/
	BYTE PacketBase::GetcbCheckCode(void)
	{
		BYTE code;
		_readHeader((char*)&code, sizeof(BYTE), 6);// cb code
		return code;
	}

	///*序列�
	unsigned short PacketBase::GetSeqNum(void)
	{
		unsigned short i = 0;
		_readHeader((char*)&i, sizeof(short), 7);	//
		unsigned short seq = ntohs(i);
		return seq;
	}

	/*设置序列�?*/
	void PacketBase::SetSeqNum(unsigned short seqNum)
	{
		unsigned short seq = htons(seqNum);
		_writeHeader((char*)&seq, sizeof(short), 7);
	}

	void PacketBase::SetFrom(int from)
	{
		int nFrom = htonl(from);
		_writeHeader((char*)&nFrom, sizeof(int), 12);
	}

	int PacketBase::GetFrom()
	{
		int id = 0;
		_readHeader((char*)&id, sizeof(int), 12);
		return ntohl(id);
	}

	void PacketBase::SetTo(int to)
	{
		int nTo = htonl(to);
		_writeHeader((char*)&nTo, sizeof(int), 16);
	}

	int PacketBase::GetTo()
	{
		int nTo = 0;
		_readHeader((char*)&nTo, sizeof(int), 16);
		return ntohl(nTo);
	}

	/*主命令字*/
	short PacketBase::GetMainCmd(void)
	{
		short nCmdType = 0;
		_readHeader((char*)&nCmdType, sizeof(short), 9);// 
		short cmd = ntohs(nCmdType);
		return cmd;
	}

	/*消息来源 */
	char PacketBase::GetSource(void)
	{
		char c;
		_readHeader(&c, sizeof(char), 11);	//  
		return c;
	}




//protected:
	/////////////////////////////////////////////////////////////////////////////////
	void PacketBase::_reset(void)
	{
		memset(m_strBuf, 0, PACKET_BUFFER_SIZE);
		m_nBufPos = PACKET_HEADER_SIZE;
		m_nPacketSize = PACKET_HEADER_SIZE;
	}
	// readHeader
	void PacketBase::_readHeader(void *pOut, int nLen, int nPos)
	{
		if (nPos >= 0 && nPos + nLen <= PACKET_HEADER_SIZE)
		{
			memcpy(pOut, m_strBuf + nPos, nLen);
		}
	}

	// writeHeader
	void PacketBase::_writeHeader(void *pIn, int nLen, int nPos)
	{
		if (nPos >= 0 && nPos + nLen <= PACKET_HEADER_SIZE)
		{
			memcpy(m_strBuf + nPos, pIn, nLen);
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	bool PacketBase::_copy(const void *pInBuf, int nLen)
	{
		if (nLen > PACKET_BUFFER_SIZE)
			return false;

		_reset();
		memcpy(m_strBuf, pInBuf, nLen);
		m_nPacketSize = nLen;
		return true;
	}
	////////////////////////////////////////////////////////////////////////////////
	void PacketBase::_begin(short nMainCmd, unsigned short nSeq, int from, int to, char cVersion, char cSubVersion)
	{
		_reset();
		short cmd = htons(nMainCmd);
		short seq = htons(nSeq);
		int nFrom = htonl(from);
		int nTo = htonl(to);
		_writeHeader(&cVersion, sizeof(char), 2);		//  
		_writeHeader(&cSubVersion, sizeof(char), 3);	// 
		_writeHeader((char*)"MJ", sizeof(char) * 2, 4);			// magic word

		_writeHeader((char*)&seq, sizeof(short), 7);	//
		_writeHeader((char*)&cmd, sizeof(short), 9);	// 
		_writeHeader((char*)"1", sizeof(char), 11);	// 
		_writeHeader((char*)&nFrom, sizeof(int), 12);
		_writeHeader((char*)&nTo, sizeof(int), 16);


	}

	void PacketBase::_end()
	{
		short nBody = m_nPacketSize - sizeof(short);	// 
		short len = htons(nBody);
		_writeHeader((char*)&len, sizeof(short), 0);	// 
		BYTE code = 0;
		_writeHeader((char*)&code, sizeof(BYTE), 6);	// 
	}

	void PacketBase::_SetBegin(short nCmdType)
	{
		short cmd = htons(nCmdType);
		_writeHeader((void*)&cmd, sizeof(short), 9);// 
	}

	void PacketBase::_oldend()
	{
		short nBody = m_nPacketSize - sizeof(short);
		short len = ntohs(nBody);
		_writeHeader((void*)&len, sizeof(short), 0);	//  
	}

	// 
	bool PacketBase::_Read(void *pOut, int nLen)
	{
		if ((nLen + m_nBufPos) > m_nPacketSize || (nLen + m_nBufPos) > PACKET_BUFFER_SIZE)
			return false;

		memcpy(pOut, m_strBuf + m_nBufPos, nLen);
		m_nBufPos += nLen;
		return true;
	}
	// 
	bool PacketBase::_ReadDel(void *pOut, int nLen)
	{
		if (!_Read(pOut, nLen))
			return false;
		memcpy(m_strBuf + m_nBufPos - nLen, m_strBuf + m_nBufPos, PACKET_BUFFER_SIZE - m_nBufPos);
		m_nBufPos -= nLen;
		m_nPacketSize -= nLen;
		_end();
		return true;
	}
	//
	void PacketBase::_readundo(int nLen)
	{
		m_nBufPos -= nLen;
	}
	//
	char *PacketBase::_readpoint(int nLen)
	{
		if ((nLen + m_nBufPos) > m_nPacketSize)
			return NULL;
		char *p = &m_strBuf[m_nBufPos];
		m_nBufPos += nLen;
		return p;
	}
	//  
	bool PacketBase::_Write(const void *pIn, int nLen)
	{
		if ((m_nPacketSize < 0) || ((nLen + m_nPacketSize) > PACKET_BUFFER_SIZE))
			return false;
		memcpy(m_strBuf + m_nPacketSize, pIn, nLen);
		m_nPacketSize += nLen;
		return true;
	}
	// 
	bool PacketBase::_Insert(const void *pIn, int nLen)
	{
		if ((nLen + m_nPacketSize) > PACKET_BUFFER_SIZE)
			return false;
		memcpy(m_strBuf + PACKET_HEADER_SIZE + nLen, m_strBuf + PACKET_HEADER_SIZE, m_nPacketSize - PACKET_HEADER_SIZE);
		memcpy(m_strBuf + PACKET_HEADER_SIZE, pIn, nLen);
		m_nPacketSize += nLen;
		_end();
		return true;
	}
	// 
	bool PacketBase::_writezero(void)
	{
		if ((m_nPacketSize + 1) > PACKET_BUFFER_SIZE)
			return false;
		memset(m_strBuf + m_nPacketSize, '\0', sizeof(char));
		m_nPacketSize++;
		return true;
	}



//输出�?

	int64_t InputPacket::ReadInt64()
	{
		int64_t nValue = -1;
		base::_Read(&nValue, sizeof(int64_t));
		return ntohll(nValue);
	}

	int InputPacket::ReadInt(void)		{ int nValue = -1; base::_Read((void*)&nValue, sizeof(int)); return ntohl(nValue); } //ʼ
	unsigned long InputPacket::ReadULong(void) { unsigned long nValue = 0; base::_Read((void*)&nValue, sizeof(unsigned long)); return ntohl(nValue); }
	int InputPacket::ReadIntDel(void)	{ int nValue = -1; base::_ReadDel((void*)&nValue, sizeof(int)); return ntohl(nValue); }
	short InputPacket::ReadShort(void)	{ short nValue = -1; base::_Read((void*)&nValue, sizeof(short)); return ntohs(nValue); }
	BYTE InputPacket::ReadByte(void)		{ BYTE nValue = 0; base::_Read((void*)&nValue, sizeof(BYTE)); return nValue; }

	InputPacket::InputPacket(){};
	InputPacket::InputPacket(const void* data, int len)
	{
		base::_copy(data, len);
	};

	bool InputPacket::ReadString(void *pOutString, int nMaxLen)
	{
		int nLen = ReadInt();
		if (nLen == -1)
			return false;
		if (nLen > nMaxLen || nLen == -1)
		{
			base::_readundo(sizeof(short));
			return false;
		}
		return base::_Read(pOutString, nLen);
	}

	char *InputPacket::ReadChar(void)
	{
		int nLen = ReadInt();

		if (nLen == -1)
			return NULL;
		return base::_readpoint(nLen);
	}

	std::string InputPacket::ReadString(void)
	{
		char *p = ReadChar();
		return (p == NULL ? "" : p);
	}

	/*
	int InputPacket::ReadBinary(char *pBuf, int nMaxLen)
	{
		int nLen = ReadInt();
		if (nLen == -1)
			return -1;
		if (nLen > nMaxLen)
		{
			base::_readundo(sizeof(int));
			return -1;
		}
		if (base::_Read(pBuf, nLen))
			return nLen;
		return 0;
	}

	int InputPacket::ReadPureBinary(char *pBuf, int nLen)
	{
		if (nLen <1 || nLen >= GetBodyLength())
			return -1;
		if (base::_Read(pBuf, nLen))
			return nLen;
		return 0;
	}
	*/

	void InputPacket::Reset(void)
	{
		base::_reset();
	}
	bool InputPacket::Copy(const void *pInBuf, int nLen)
	{
		return base::_copy(pInBuf, nLen);
	}
	bool InputPacket::WriteBody(const char *pIn, int nLen)
	{
		return base::_Write(pIn, nLen);
	}




	OutputPacket::OutputPacket(void){ m_isCheckCode = false; }



	bool OutputPacket::WriteInt64(int64_t nValue)
	{
		int64_t value = htonll(nValue);
		return base::_Write((void*)&value, sizeof(int64_t));
	}

	bool OutputPacket::WriteInt(int nValue)		{ int value = htonl(nValue); return base::_Write((void*)&value, sizeof(int)); }
	bool OutputPacket::WriteULong(unsigned long nValue) { unsigned long value = htonl(nValue); return base::_Write((void*)&value, sizeof(unsigned long)); }
	bool OutputPacket::WriteByte(BYTE nValue)		{ return base::_Write((void*)&nValue, sizeof(BYTE)); }
	bool OutputPacket::WriteShort(short nValue)	{ short value = htons(nValue); return base::_Write((void*)&value, sizeof(short)); }
	//ײ
	bool OutputPacket::InsertInt(int nValue)		{ int value = htonl(nValue); return base::_Insert((void*)&value, sizeof(int)); }
	bool OutputPacket::InsertByte(BYTE nValue)	{ return base::_Insert((void*)&nValue, sizeof(BYTE)); }
	bool OutputPacket::WriteString(const char *pString)
	{
		int nLen = (int)strlen(pString);
		if (nLen + 1 + sizeof(int) + base::packet_size() > PACKET_BUFFER_SIZE)
			return false;

		WriteInt(nLen + 1);
		return base::_Write(pString, nLen) && base::_writezero();
	}

	bool OutputPacket::WriteString(const std::string &strDate)
	{
		int nLen = (int)strDate.size();
		if (nLen + 1 + sizeof(int) + base::packet_size() > PACKET_BUFFER_SIZE)
			return false;

		WriteInt(nLen + 1);
		return base::_Write(strDate.c_str(), nLen) && base::_writezero();
	}

	bool OutputPacket::WriteBinary(const char *pBuf, int nLen)
	{
		WriteInt(nLen);
		if (nLen + base::packet_size() > PACKET_BUFFER_SIZE)
			return false;
		return base::_Write(pBuf, nLen);
	}
	bool OutputPacket::Copy(const void *pInBuf, int nLen)
	{
		return base::_copy(pInBuf, nLen);
	}
	void OutputPacket::Begin(short nMainCmd, unsigned short nSeq , int nFrom , int nTo , char cVersion , char cSubVersion )
	{
		base::_begin(nMainCmd, nSeq, nFrom, nTo, cVersion, cSubVersion);
		m_isCheckCode = false;
	}
	void OutputPacket::End(void)
	{
		m_isCheckCode = false;
		base::_end();
	}
	void OutputPacket::oldEnd(void)
	{
		m_isCheckCode = false;
		base::_oldend();
	}
	//
	void OutputPacket::SetBegin(short nCommand)
	{
		base::_SetBegin(nCommand);
	}
	//Ч
	void OutputPacket::WritecbCheckCode(BYTE nValue)
	{
		base::_writeHeader((char*)&nValue, sizeof(BYTE), 6); //Ч
		m_isCheckCode = true;
	}

	bool OutputPacket::IsWritecbCheckCode(void)
	{
		return m_isCheckCode;
	}

	CC_NET_END

