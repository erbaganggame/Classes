#ifndef __KK_PACKET_DECODER_H
#define __KK_PACKET_DECODER_H

//#include <Singleton.h>
//#include <ICC_Decoder.h>
#include "cocos2d.h"
#include "CCNetMacros.h"
CC_NET_BEGIN
#pragma pack(1)
typedef struct  _PacketHeader
{
	unsigned short pack_len;     /******** packet len 0-65535  ********/
	unsigned char main_ver;     /*main version */
	unsigned char sub_ver;       /*sub version */
	unsigned char soh[2];        /**** packet flag ****/
	unsigned char code;     	/*Encrypt flag*/
	unsigned short seq;         /* seq number ------packet number */
	unsigned short main_cmd;    /***** main cmd ****/
	unsigned char source_type;  /*client type ,android ro iosclient*/
	int from;					/****** packet come from ******/
	int to;						/****** packet send to where *****/
} PacketHeader;
#pragma pack()

class KKPacketDecoder// : public ICC_Decoder
 {
	public:
		KKPacketDecoder():m_nStatus(REQ_REQUEST)
		{
		}
		virtual ~KKPacketDecoder(){}
		static KKPacketDecoder* GetInstance();
		virtual int ParsePacket(char * data, int len);
		void Init();
	protected:
		int GetHeadLen();
		bool CheckHead(char *data,int len);
		int GetPacketLen(char * data,int len);
	private:
		KKPacketDecoder(const KKPacketDecoder&){}
		KKPacketDecoder& operator=(const KKPacketDecoder&){return *this;} 
		
		typedef enum REQSTATUS
		{	
			REQ_REQUEST=0, 
			REQ_HEADER, 
			REQ_BODY, 
			REQ_DONE, 
			REQ_PROCESS, 
			REQ_ERROR 
		} EREQSTATUS;

		//当前解包状态
		int m_nStatus;

 };

CC_NET_END

#endif
