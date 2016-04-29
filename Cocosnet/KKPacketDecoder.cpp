//#include <arpa/inet.h>
#ifdef _WIN32
#include <winsock2.h>
typedef long long int64_t;
#else
#include <netinet/in.h>
#endif
//#include "log.h"
#include "KKPacketDecoder.h"

CC_NET_BEGIN

#if 0
0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16   17  18  19  20                                                 8192
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+------------------------------------------------------+
|  LEN  |MV |SV |'M'|'J'|COD|  SEQ  | M_CMD |ST |     from		|     to		| BODY                                                 |     
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+------------------------------------------------------+
packet:[0],mainver:[2],subver:[3],soh:[4],code:[6],seq:[7],maincmd:[9],sourcetype:[11],from[12],to[16]
#endif

KKPacketDecoder* KKPacketDecoder::GetInstance()
{
	return new KKPacketDecoder();
}
void KKPacketDecoder::Init()
{
	m_nStatus = REQ_REQUEST;
}
// return packet len
int KKPacketDecoder::ParsePacket(char * data, int len)
{
	int packet_len = 0;
	switch(m_nStatus)
	{
//		log_debug("decoder status:[%d]",m_nStatus);
		case REQ_REQUEST:
		case REQ_HEADER:
			if(GetHeadLen()>len)
			{
//				log_error("len error ! datalen[%d]",len);
				m_nStatus= REQ_HEADER;
				break;
			}
				
			if(!CheckHead(data,len))
			{
//				log_error("parser header error! len[%d]",len);
				m_nStatus = REQ_ERROR;
				return -1;
			}
			else
			{
//				log_debug("parser header success!,datalen:[%d]",len);
				m_nStatus = REQ_BODY;
			}				
		case REQ_BODY:
			packet_len = GetPacketLen(data, len);
			if(packet_len<GetHeadLen() - (int)sizeof(short))
			{
				m_nStatus = REQ_ERROR;
				return -1;
			}
			
			if(packet_len + (int)sizeof(short) > len )
			{
//				log_error("parser body error! packetlen:[%d],datalen:[%d]",packet_len,len);
				m_nStatus =REQ_BODY;
				return 0;
			}
			else
			{
		//		log_debug("packet parse success!,packetlen:[%d],datalen:[%d]",packet_len,len);
				m_nStatus = REQ_HEADER;
				return packet_len+sizeof(short);
			}
	
		case REQ_ERROR:
			//log_error("parser packet error! packet:[%d],datalen:[%d]",packet_len,len);
			break;
		default:
			return 0;
	}

	return -1;
}


//**************************************/
//protected function 
//
//
//*************************************//
int KKPacketDecoder::GetHeadLen()
{
	return sizeof(PacketHeader);
}

bool KKPacketDecoder::CheckHead(char *data,int len)
{
	PacketHeader *pHeader = (PacketHeader*)data;
	if(pHeader->main_ver !=1 || pHeader->sub_ver !=1)
		return false;
	if(pHeader->soh[0] != 'M' || pHeader->soh[1] != 'J')
		return false;
	return true;
}

int KKPacketDecoder::GetPacketLen(char * data,int len)
{
	PacketHeader *pHeader = (PacketHeader*)data;
	int packet_len = ntohs(pHeader->pack_len);
	
	return packet_len;	
}

CC_NET_END