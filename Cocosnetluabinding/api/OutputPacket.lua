
--------------------------------
-- @module OutputPacket
-- @extend PacketBase
-- @parent_module ccn

--------------------------------
-- 
-- @function [parent=#OutputPacket] WriteULong 
-- @param self
-- @param #unsigned long nValue
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] End 
-- @param self
-- @return OutputPacket#OutputPacket self (return value: ccn.OutputPacket)
        
--------------------------------
-- @overload self, string         
-- @overload self, char         
-- @function [parent=#OutputPacket] WriteString
-- @param self
-- @param #char pString
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#OutputPacket] WriteShort 
-- @param self
-- @param #short nValue
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] EncryptBuffer 
-- @param self
-- @return unsigned short#unsigned short ret (return value: unsigned short)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] WriteInt64 
-- @param self
-- @param #long long nValue
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] Begin 
-- @param self
-- @param #short nMainCmd
-- @param #unsigned short nSeq
-- @param #int nFrom
-- @param #int nTo
-- @param #char cVersion
-- @param #char cSubVersion
-- @return OutputPacket#OutputPacket self (return value: ccn.OutputPacket)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] InsertByte 
-- @param self
-- @param #unsigned char nValue
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] oldEnd 
-- @param self
-- @return OutputPacket#OutputPacket self (return value: ccn.OutputPacket)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] IsWritecbCheckCode 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] InsertInt 
-- @param self
-- @param #int nValue
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] WriteByte 
-- @param self
-- @param #unsigned char nValue
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] WriteInt 
-- @param self
-- @param #int nValue
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] Copy 
-- @param self
-- @param #void pInBuf
-- @param #int nLen
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] WriteBinary 
-- @param self
-- @param #char pBuf
-- @param #int nLen
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] SetBegin 
-- @param self
-- @param #short nCommand
-- @return OutputPacket#OutputPacket self (return value: ccn.OutputPacket)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] WritecbCheckCode 
-- @param self
-- @param #unsigned char nValue
-- @return OutputPacket#OutputPacket self (return value: ccn.OutputPacket)
        
--------------------------------
-- 
-- @function [parent=#OutputPacket] OutputPacket 
-- @param self
-- @return OutputPacket#OutputPacket self (return value: ccn.OutputPacket)
        
return nil
