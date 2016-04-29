#ifndef _PacketBase_H_20130917
#define _PacketBase_H_20130917

#include <string>
#include <string.h>
#include <assert.h>
#include "cocos2d.h"
#include "CCNetMacros.h"

USING_NS_CC;

CC_NET_BEGIN

#define	TCP_DEFAULT_BUFFER_LEN  8192


#define PACKET_DEFAULT_VER		1
#define PACKET_DEFAULT_SUBVER	1
#define PACKET_HEAD_LEN 20


typedef long long int64_t;

typedef unsigned long   DWORD;

typedef unsigned char	BYTE;

typedef unsigned short	WORD;


#if 0
0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16   17  18  19  20                                                 8192
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+------------------------------------------------------+
|  LEN  |MV |SV |'M'|'J'|COD|  SEQ  | M_CMD |ST |     from		|     to		| BODY                                                 |     
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+------------------------------------------------------+
packet:[0],mainver:[2],subver:[3],soh:[4],code:[6],seq:[7],maincmd:[9],sourcetype:[11],from[12],to[16]
#endif

#if __BYTE_ORDER == __BIG_ENDIAN

#else
	#if __BYTE_ORDER == __LITTLE_ENDIAN
	
	#endif
#endif

#if( CC_TARGET_PLATFORM != CC_PLATFORM_IOS  )
#ifndef htonll
#define htonll(X)    (((X) & 0xff00000000000000LL) >> 56\
                    | ((X) & 0x00ff000000000000LL) >> 40\
                    | ((X) & 0x0000ff0000000000LL) >> 24\
                    | ((X) & 0x000000ff00000000LL) >> 8\
                    | ((X) & 0x00000000ff000000LL) << 8\
                    | ((X) & 0x0000000000ff0000LL) << 24\
                    | ((X) & 0x000000000000ff00LL) << 40\
                    | ((X) & 0x00000000000000ffLL) << 56)

#define ntohll(X) htonll(X)
#endif
#endif
class  PacketBase :public Ref
{
public:
	enum
	{
		PACKET_HEADER_SIZE = (PACKET_HEAD_LEN),
		PACKET_BUFFER_SIZE = TCP_DEFAULT_BUFFER_LEN
	};
	PacketBase(void);

	char *packet_buf(void);
	int packet_size(void);

	//Get body length
	unsigned short GetBodyLength(void);
	/*协议主版本号*/
	unsigned char GetVersion(void);
	/*协议子版本号*/
	unsigned char GetSubVersion(void);

	/*校验code*/
	BYTE GetcbCheckCode(void);
	
    ///*序列�
	unsigned short GetSeqNum(void);
	/*设置序列�?*/
	void SetSeqNum(unsigned short seqNum);
	
	void SetFrom(int from);
	int GetFrom();

	void SetTo(int to);
	int GetTo();
	
	short GetMainCmd(void);

	char GetSource(void);

	


protected:
	/////////////////////////////////////////////////////////////////////////////////
	void _reset(void);
	// readHeader
	void _readHeader(void *pOut, int nLen, int nPos);
	
	// writeHeader
	void _writeHeader(void *pIn, int nLen, int nPos);
	
	////////////////////////////////////////////////////////////////////////////////
	bool _copy(const void *pInBuf, int nLen);
	////////////////////////////////////////////////////////////////////////////////
	void _begin(short nMainCmd, unsigned short nSeq, int from, int to, char cVersion, char cSubVersion);
	void _end();
	void _SetBegin(short nCmdType);
	void _oldend();
	// 
	bool _Read(void *pOut, int nLen);
	// 
	bool _ReadDel(void *pOut, int nLen);
	//
	void _readundo(int nLen);
	//
	char *_readpoint(int nLen);
	//  
	bool _Write(const void *pIn, int nLen);
	// 
	bool _Insert(const void *pIn, int nLen);
	// 
	bool _writezero(void);


private:
	char m_strBuf[PACKET_BUFFER_SIZE]; 
	int m_nPacketSize;
	int m_nBufPos;
};

//输出�?
class  InputPacket : public PacketBase
{
public:
	typedef PacketBase base;

	int64_t ReadInt64();
	
	int ReadInt(void);
	unsigned long ReadULong(void);
	int ReadIntDel(void);
	short ReadShort(void);
	BYTE ReadByte(void);
	
	InputPacket();
	InputPacket(const void* data, int len);

	bool ReadString(void *pOutString, int nMaxLen);

	char *ReadChar(void);

	std::string ReadString(void);

	//int ReadBinary(char *pBuf, int nMaxLen);

	//int ReadPureBinary(char *pBuf, int nLen);
	void Reset(void);
	bool Copy(const void *pInBuf, int nLen);
	bool WriteBody(const char *pIn, int nLen);

	int CrevasseBuffer();
};


class  OutputPacket : public PacketBase
{
public:
	OutputPacket(void);

	typedef PacketBase base;

	bool WriteInt64(int64_t nValue);
	
	bool WriteInt(int nValue);
	bool WriteULong(unsigned long nValue);
	bool WriteByte(BYTE nValue);
	bool WriteShort(short nValue);
	//ײ
	bool InsertInt(int nValue);
	bool InsertByte(BYTE nValue);
	bool WriteString(const char *pString);

	bool WriteString(const std::string &strDate);

	bool WriteBinary(const char *pBuf, int nLen);
	bool Copy(const void *pInBuf, int nLen);
	void Begin(short nMainCmd, unsigned short nSeq = 0, int nFrom = 0, int nTo = 0, char cVersion = PACKET_DEFAULT_VER, char cSubVersion = PACKET_DEFAULT_SUBVER);
	void End(void);
	void oldEnd(void);
	//
	void SetBegin(short nCommand);
	//Ч
	void WritecbCheckCode(BYTE nValue);

	bool IsWritecbCheckCode(void);

	WORD EncryptBuffer();

private:
	//���ܱ�־
	bool m_isCheckCode;
};

CC_NET_END
#endif

