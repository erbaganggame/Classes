
--------------------------------
-- @module PacketBase
-- @extend Ref
-- @parent_module ccn

--------------------------------
-- 
-- @function [parent=#PacketBase] GetTo 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] SetSeqNum 
-- @param self
-- @param #unsigned short seqNum
-- @return PacketBase#PacketBase self (return value: ccn.PacketBase)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] SetFrom 
-- @param self
-- @param #int from
-- @return PacketBase#PacketBase self (return value: ccn.PacketBase)
        
--------------------------------
-- åºåå
-- @function [parent=#PacketBase] GetSeqNum 
-- @param self
-- @return unsigned short#unsigned short ret (return value: unsigned short)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] GetFrom 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] packet_size 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] GetBodyLength 
-- @param self
-- @return unsigned short#unsigned short ret (return value: unsigned short)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] GetcbCheckCode 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] SetTo 
-- @param self
-- @param #int to
-- @return PacketBase#PacketBase self (return value: ccn.PacketBase)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] GetVersion 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] GetSubVersion 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] packet_buf 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] GetSource 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] GetMainCmd 
-- @param self
-- @return short#short ret (return value: short)
        
--------------------------------
-- 
-- @function [parent=#PacketBase] PacketBase 
-- @param self
-- @return PacketBase#PacketBase self (return value: ccn.PacketBase)
        
return nil
