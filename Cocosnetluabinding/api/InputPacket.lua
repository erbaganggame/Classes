
--------------------------------
-- @module InputPacket
-- @extend PacketBase
-- @parent_module ccn

--------------------------------
-- 
-- @function [parent=#InputPacket] Reset 
-- @param self
-- @return InputPacket#InputPacket self (return value: ccn.InputPacket)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] CrevasseBuffer 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] ReadShort 
-- @param self
-- @return short#short ret (return value: short)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] ReadULong 
-- @param self
-- @return unsigned long#unsigned long ret (return value: unsigned long)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] ReadInt 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] ReadInt64 
-- @param self
-- @return long long#long long ret (return value: long long)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] ReadByte 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] WriteBody 
-- @param self
-- @param #char pIn
-- @param #int nLen
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] ReadChar 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] Copy 
-- @param self
-- @param #void pInBuf
-- @param #int nLen
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#InputPacket] ReadIntDel 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @overload self         
-- @overload self, void, int         
-- @function [parent=#InputPacket] ReadString
-- @param self
-- @param #void pOutString
-- @param #int nMaxLen
-- @return bool#bool ret (return value: bool)

--------------------------------
-- @overload self, void, int         
-- @overload self         
-- @function [parent=#InputPacket] InputPacket
-- @param self
-- @param #void data
-- @param #int len
-- @return InputPacket#InputPacket self (return value: ccn.InputPacket)

return nil
