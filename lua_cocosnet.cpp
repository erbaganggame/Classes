#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#include "Lua_cocosnet.hpp"
#include "CocosNet/Packet.h"
#include "CocosNet/CCNetDelegate.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "cocos2d.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"

CC_NET_BEGIN
USING_NS_CC;
// will calling when a package is coming
void LuaCocosnet::onMessageReceived(const char*m_pTempBuffer, const int nRet)
{
	int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, (ScriptHandlerMgr::HandlerType)CocosnetHandlerType::COCOSNET_ON_MESSAGE);
	if (0 != handler)
	{
		LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		if (nullptr != stack)
		{
			cocosnet::InputPacket*cobj = new cocosnet::InputPacket(m_pTempBuffer, nRet);
			cobj->autorelease();
			stack->pushObject(cobj,"ccn.InputPacket");
			stack->executeFunctionByHandler(handler, 1);			
		}
	}
}

// when connected will calling
void LuaCocosnet::onConnected()
{
	CCNetDelegate::onConnected();
	int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, (ScriptHandlerMgr::HandlerType)CocosnetHandlerType::COCOSNET_ON_CONNECTED);
	if (0 != handler)
	{
		LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		if (nullptr != stack)
		{
			stack->executeFunctionByHandler(handler, 0);
		}
	}
}

// when connect time out will calling
void LuaCocosnet::onConnectTimeout()
{
	CCNetDelegate::onDisconnected();
	int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, (ScriptHandlerMgr::HandlerType)CocosnetHandlerType::COCOSNET_ON_TIMEOUT);
	if (0 != handler)
	{
		LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		if (nullptr != stack)
		{
			stack->executeFunctionByHandler(handler, 0);
		}
	}
}

// on disconnected will call
void LuaCocosnet::onDisconnected()
{
	CCNetDelegate::onDisconnected();
	int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, (ScriptHandlerMgr::HandlerType)CocosnetHandlerType::COCOSNET_ON_DISCONNECTED);
	if (0 != handler)
	{
		LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		if (nullptr != stack)
		{
			stack->executeFunctionByHandler(handler, 0);
		}
	}
}

// on exception
void LuaCocosnet::onExceptionCaught(CCSocketStatus eStatus)
{
	int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, (ScriptHandlerMgr::HandlerType)CocosnetHandlerType::COCOSNET_ON_EXCEPTION);
	if (0 != handler)
	{
		LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		if (nullptr != stack)
		{
			stack->pushInt(eStatus);
			stack->executeFunctionByHandler(handler, 1);
		}
	}
}

CC_NET_END

int lua_cocos2dx_cocosnet_PacketBase_GetTo(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetTo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetTo'", nullptr);
            return 0;
        }
        int ret = cobj->GetTo();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetTo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetTo'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_SetSeqNum(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_SetSeqNum'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned short arg0;

        ok &= luaval_to_ushort(tolua_S, 2, &arg0, "ccn.PacketBase:SetSeqNum");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_SetSeqNum'", nullptr);
            return 0;
        }
        cobj->SetSeqNum(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:SetSeqNum",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_SetSeqNum'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_SetFrom(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_SetFrom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccn.PacketBase:SetFrom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_SetFrom'", nullptr);
            return 0;
        }
        cobj->SetFrom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:SetFrom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_SetFrom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_GetSeqNum(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetSeqNum'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetSeqNum'", nullptr);
            return 0;
        }
        unsigned short ret = cobj->GetSeqNum();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetSeqNum",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetSeqNum'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_GetFrom(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetFrom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetFrom'", nullptr);
            return 0;
        }
        int ret = cobj->GetFrom();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetFrom",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetFrom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_packet_size(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_packet_size'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_packet_size'", nullptr);
            return 0;
        }
        int ret = cobj->packet_size();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:packet_size",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_packet_size'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_GetBodyLength(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetBodyLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetBodyLength'", nullptr);
            return 0;
        }
        unsigned short ret = cobj->GetBodyLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetBodyLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetBodyLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_GetcbCheckCode(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetcbCheckCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetcbCheckCode'", nullptr);
            return 0;
        }
        uint16_t ret = cobj->GetcbCheckCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetcbCheckCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetcbCheckCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_SetTo(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_SetTo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccn.PacketBase:SetTo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_SetTo'", nullptr);
            return 0;
        }
        cobj->SetTo(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:SetTo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_SetTo'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_GetVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetVersion'", nullptr);
            return 0;
        }
        uint16_t ret = cobj->GetVersion();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_GetSubVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetSubVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetSubVersion'", nullptr);
            return 0;
        }
        uint16_t ret = cobj->GetSubVersion();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetSubVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetSubVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_packet_buf(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_packet_buf'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_packet_buf'", nullptr);
            return 0;
        }
        char* ret = cobj->packet_buf();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:packet_buf",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_packet_buf'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_GetSource(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetSource'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetSource'", nullptr);
            return 0;
        }
        int32_t ret = cobj->GetSource();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetSource",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetSource'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_GetMainCmd(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.PacketBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::PacketBase*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_PacketBase_GetMainCmd'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_GetMainCmd'", nullptr);
            return 0;
        }
        int32_t ret = cobj->GetMainCmd();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:GetMainCmd",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_GetMainCmd'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_PacketBase_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::PacketBase* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_PacketBase_constructor'", nullptr);
            return 0;
        }
        cobj = new cocosnet::PacketBase();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccn.PacketBase");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.PacketBase:PacketBase",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_PacketBase_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_cocosnet_PacketBase_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PacketBase)");
    return 0;
}

int lua_register_cocos2dx_cocosnet_PacketBase(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccn.PacketBase");
    tolua_cclass(tolua_S,"PacketBase","ccn.PacketBase","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"PacketBase");
        tolua_function(tolua_S,"new",lua_cocos2dx_cocosnet_PacketBase_constructor);
        tolua_function(tolua_S,"GetTo",lua_cocos2dx_cocosnet_PacketBase_GetTo);
        tolua_function(tolua_S,"SetSeqNum",lua_cocos2dx_cocosnet_PacketBase_SetSeqNum);
        tolua_function(tolua_S,"SetFrom",lua_cocos2dx_cocosnet_PacketBase_SetFrom);
        tolua_function(tolua_S,"GetSeqNum",lua_cocos2dx_cocosnet_PacketBase_GetSeqNum);
        tolua_function(tolua_S,"GetFrom",lua_cocos2dx_cocosnet_PacketBase_GetFrom);
        tolua_function(tolua_S,"packet_size",lua_cocos2dx_cocosnet_PacketBase_packet_size);
        tolua_function(tolua_S,"GetBodyLength",lua_cocos2dx_cocosnet_PacketBase_GetBodyLength);
        tolua_function(tolua_S,"GetcbCheckCode",lua_cocos2dx_cocosnet_PacketBase_GetcbCheckCode);
        tolua_function(tolua_S,"SetTo",lua_cocos2dx_cocosnet_PacketBase_SetTo);
        tolua_function(tolua_S,"GetVersion",lua_cocos2dx_cocosnet_PacketBase_GetVersion);
        tolua_function(tolua_S,"GetSubVersion",lua_cocos2dx_cocosnet_PacketBase_GetSubVersion);
        tolua_function(tolua_S,"packet_buf",lua_cocos2dx_cocosnet_PacketBase_packet_buf);
        tolua_function(tolua_S,"GetSource",lua_cocos2dx_cocosnet_PacketBase_GetSource);
        tolua_function(tolua_S,"GetMainCmd",lua_cocos2dx_cocosnet_PacketBase_GetMainCmd);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocosnet::PacketBase).name();
    g_luaType[typeName] = "ccn.PacketBase";
    g_typeCast["PacketBase"] = "ccn.PacketBase";
    return 1;
}

int lua_cocos2dx_cocosnet_InputPacket_Reset(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_Reset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_Reset'", nullptr);
            return 0;
        }
        cobj->Reset();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:Reset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_Reset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_CrevasseBuffer(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_CrevasseBuffer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_CrevasseBuffer'", nullptr);
            return 0;
        }
        int ret = cobj->CrevasseBuffer();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:CrevasseBuffer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_CrevasseBuffer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_ReadShort(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_ReadShort'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_ReadShort'", nullptr);
            return 0;
        }
        int32_t ret = cobj->ReadShort();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:ReadShort",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_ReadShort'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_ReadULong(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_ReadULong'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_ReadULong'", nullptr);
            return 0;
        }
        unsigned long ret = cobj->ReadULong();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:ReadULong",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_ReadULong'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_ReadInt(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_ReadInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_ReadInt'", nullptr);
            return 0;
        }
        int ret = cobj->ReadInt();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:ReadInt",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_ReadInt'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_ReadInt64(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_ReadInt64'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_ReadInt64'", nullptr);
            return 0;
        }
        long long ret = cobj->ReadInt64();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:ReadInt64",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_ReadInt64'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_ReadByte(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_ReadByte'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_ReadByte'", nullptr);
            return 0;
        }
        uint16_t ret = cobj->ReadByte();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:ReadByte",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_ReadByte'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_WriteBody(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_WriteBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccn.InputPacket:WriteBody"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccn.InputPacket:WriteBody");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_WriteBody'", nullptr);
            return 0;
        }
        bool ret = cobj->WriteBody(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:WriteBody",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_WriteBody'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_ReadChar(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_ReadChar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_ReadChar'", nullptr);
            return 0;
        }
        char* ret = cobj->ReadChar();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:ReadChar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_ReadChar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_Copy(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_Copy'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccn.InputPacket:Copy");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_Copy'", nullptr);
            return 0;
        }
        bool ret = cobj->Copy(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:Copy",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_Copy'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_ReadIntDel(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_ReadIntDel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_InputPacket_ReadIntDel'", nullptr);
            return 0;
        }
        int ret = cobj->ReadIntDel();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.InputPacket:ReadIntDel",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_ReadIntDel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_ReadString(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.InputPacket",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocosnet::InputPacket*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_InputPacket_ReadString'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            std::string ret = cobj->ReadString();
            tolua_pushcppstring(tolua_S,ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            void* arg0;
            #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccn.InputPacket:ReadString");

            if (!ok) { break; }
            bool ret = cobj->ReadString(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccn.InputPacket:ReadString",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_ReadString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_InputPacket_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::InputPacket* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            const void* arg0;
            #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccn.InputPacket:InputPacket");

            if (!ok) { break; }
            cobj = new cocosnet::InputPacket(arg0, arg1);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccn.InputPacket");
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj = new cocosnet::InputPacket();
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccn.InputPacket");
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccn.InputPacket:InputPacket",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_InputPacket_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_cocosnet_InputPacket_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (InputPacket)");
    return 0;
}

int lua_register_cocos2dx_cocosnet_InputPacket(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccn.InputPacket");
    tolua_cclass(tolua_S,"InputPacket","ccn.InputPacket","ccn.PacketBase",nullptr);

    tolua_beginmodule(tolua_S,"InputPacket");
        tolua_function(tolua_S,"new",lua_cocos2dx_cocosnet_InputPacket_constructor);
        tolua_function(tolua_S,"Reset",lua_cocos2dx_cocosnet_InputPacket_Reset);
        tolua_function(tolua_S,"CrevasseBuffer",lua_cocos2dx_cocosnet_InputPacket_CrevasseBuffer);
        tolua_function(tolua_S,"ReadShort",lua_cocos2dx_cocosnet_InputPacket_ReadShort);
        tolua_function(tolua_S,"ReadULong",lua_cocos2dx_cocosnet_InputPacket_ReadULong);
        tolua_function(tolua_S,"ReadInt",lua_cocos2dx_cocosnet_InputPacket_ReadInt);
        tolua_function(tolua_S,"ReadInt64",lua_cocos2dx_cocosnet_InputPacket_ReadInt64);
        tolua_function(tolua_S,"ReadByte",lua_cocos2dx_cocosnet_InputPacket_ReadByte);
        tolua_function(tolua_S,"WriteBody",lua_cocos2dx_cocosnet_InputPacket_WriteBody);
        tolua_function(tolua_S,"ReadChar",lua_cocos2dx_cocosnet_InputPacket_ReadChar);
        tolua_function(tolua_S,"Copy",lua_cocos2dx_cocosnet_InputPacket_Copy);
        tolua_function(tolua_S,"ReadIntDel",lua_cocos2dx_cocosnet_InputPacket_ReadIntDel);
        tolua_function(tolua_S,"ReadString",lua_cocos2dx_cocosnet_InputPacket_ReadString);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocosnet::InputPacket).name();
    g_luaType[typeName] = "ccn.InputPacket";
    g_typeCast["InputPacket"] = "ccn.InputPacket";
    return 1;
}

int lua_cocos2dx_cocosnet_OutputPacket_WriteULong(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteULong'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned long arg0;

        ok &= luaval_to_ulong(tolua_S, 2, &arg0, "ccn.OutputPacket:WriteULong");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteULong'", nullptr);
            return 0;
        }
        bool ret = cobj->WriteULong(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:WriteULong",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteULong'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_End(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_End'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_End'", nullptr);
            return 0;
        }
        cobj->End();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:End",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_End'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_WriteString(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteString'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccn.OutputPacket:WriteString");

            if (!ok) { break; }
            bool ret = cobj->WriteString(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccn.OutputPacket:WriteString"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            bool ret = cobj->WriteString(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccn.OutputPacket:WriteString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_WriteShort(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteShort'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccn.OutputPacket:WriteShort");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteShort'", nullptr);
            return 0;
        }
        bool ret = cobj->WriteShort(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:WriteShort",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteShort'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_EncryptBuffer(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_EncryptBuffer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_EncryptBuffer'", nullptr);
            return 0;
        }
        unsigned short ret = cobj->EncryptBuffer();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:EncryptBuffer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_EncryptBuffer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_WriteInt64(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteInt64'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        long long arg0;

        ok &= luaval_to_long_long(tolua_S, 2,&arg0, "ccn.OutputPacket:WriteInt64");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteInt64'", nullptr);
            return 0;
        }
        bool ret = cobj->WriteInt64(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:WriteInt64",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteInt64'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_Begin(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_Begin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccn.OutputPacket:Begin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_Begin'", nullptr);
            return 0;
        }
        cobj->Begin(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        int32_t arg0;
        unsigned short arg1;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccn.OutputPacket:Begin");

        ok &= luaval_to_ushort(tolua_S, 3, &arg1, "ccn.OutputPacket:Begin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_Begin'", nullptr);
            return 0;
        }
        cobj->Begin(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        int32_t arg0;
        unsigned short arg1;
        int arg2;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccn.OutputPacket:Begin");

        ok &= luaval_to_ushort(tolua_S, 3, &arg1, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccn.OutputPacket:Begin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_Begin'", nullptr);
            return 0;
        }
        cobj->Begin(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 4) 
    {
        int32_t arg0;
        unsigned short arg1;
        int arg2;
        int arg3;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccn.OutputPacket:Begin");

        ok &= luaval_to_ushort(tolua_S, 3, &arg1, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccn.OutputPacket:Begin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_Begin'", nullptr);
            return 0;
        }
        cobj->Begin(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 5) 
    {
        int32_t arg0;
        unsigned short arg1;
        int arg2;
        int arg3;
        int32_t arg4;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccn.OutputPacket:Begin");

        ok &= luaval_to_ushort(tolua_S, 3, &arg1, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 6,&arg4, "ccn.OutputPacket:Begin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_Begin'", nullptr);
            return 0;
        }
        cobj->Begin(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 6) 
    {
        int32_t arg0;
        unsigned short arg1;
        int arg2;
        int arg3;
        int32_t arg4;
        int32_t arg5;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccn.OutputPacket:Begin");

        ok &= luaval_to_ushort(tolua_S, 3, &arg1, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 6,&arg4, "ccn.OutputPacket:Begin");

        ok &= luaval_to_int32(tolua_S, 7,&arg5, "ccn.OutputPacket:Begin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_Begin'", nullptr);
            return 0;
        }
        cobj->Begin(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:Begin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_Begin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_InsertByte(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_InsertByte'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "ccn.OutputPacket:InsertByte");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_InsertByte'", nullptr);
            return 0;
        }
        bool ret = cobj->InsertByte(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:InsertByte",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_InsertByte'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_oldEnd(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_oldEnd'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_oldEnd'", nullptr);
            return 0;
        }
        cobj->oldEnd();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:oldEnd",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_oldEnd'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_IsWritecbCheckCode(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_IsWritecbCheckCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_IsWritecbCheckCode'", nullptr);
            return 0;
        }
        bool ret = cobj->IsWritecbCheckCode();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:IsWritecbCheckCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_IsWritecbCheckCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_InsertInt(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_InsertInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccn.OutputPacket:InsertInt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_InsertInt'", nullptr);
            return 0;
        }
        bool ret = cobj->InsertInt(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:InsertInt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_InsertInt'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_WriteByte(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteByte'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "ccn.OutputPacket:WriteByte");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteByte'", nullptr);
            return 0;
        }
        bool ret = cobj->WriteByte(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:WriteByte",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteByte'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_WriteInt(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccn.OutputPacket:WriteInt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteInt'", nullptr);
            return 0;
        }
        bool ret = cobj->WriteInt(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:WriteInt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteInt'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_Copy(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_Copy'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccn.OutputPacket:Copy");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_Copy'", nullptr);
            return 0;
        }
        bool ret = cobj->Copy(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:Copy",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_Copy'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_WriteBinary(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteBinary'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccn.OutputPacket:WriteBinary"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccn.OutputPacket:WriteBinary");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteBinary'", nullptr);
            return 0;
        }
        bool ret = cobj->WriteBinary(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:WriteBinary",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_WriteBinary'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_SetBegin(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_SetBegin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccn.OutputPacket:SetBegin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_SetBegin'", nullptr);
            return 0;
        }
        cobj->SetBegin(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:SetBegin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_SetBegin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_WritecbCheckCode(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.OutputPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::OutputPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_OutputPacket_WritecbCheckCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "ccn.OutputPacket:WritecbCheckCode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_WritecbCheckCode'", nullptr);
            return 0;
        }
        cobj->WritecbCheckCode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:WritecbCheckCode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_WritecbCheckCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_OutputPacket_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::OutputPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_OutputPacket_constructor'", nullptr);
            return 0;
        }
        cobj = new cocosnet::OutputPacket();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccn.OutputPacket");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.OutputPacket:OutputPacket",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_OutputPacket_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_cocosnet_OutputPacket_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (OutputPacket)");
    return 0;
}

int lua_register_cocos2dx_cocosnet_OutputPacket(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccn.OutputPacket");
    tolua_cclass(tolua_S,"OutputPacket","ccn.OutputPacket","ccn.PacketBase",nullptr);

    tolua_beginmodule(tolua_S,"OutputPacket");
        tolua_function(tolua_S,"new",lua_cocos2dx_cocosnet_OutputPacket_constructor);
        tolua_function(tolua_S,"WriteULong",lua_cocos2dx_cocosnet_OutputPacket_WriteULong);
        tolua_function(tolua_S,"End",lua_cocos2dx_cocosnet_OutputPacket_End);
        tolua_function(tolua_S,"WriteString",lua_cocos2dx_cocosnet_OutputPacket_WriteString);
        tolua_function(tolua_S,"WriteShort",lua_cocos2dx_cocosnet_OutputPacket_WriteShort);
        tolua_function(tolua_S,"EncryptBuffer",lua_cocos2dx_cocosnet_OutputPacket_EncryptBuffer);
        tolua_function(tolua_S,"WriteInt64",lua_cocos2dx_cocosnet_OutputPacket_WriteInt64);
        tolua_function(tolua_S,"Begin",lua_cocos2dx_cocosnet_OutputPacket_Begin);
        tolua_function(tolua_S,"InsertByte",lua_cocos2dx_cocosnet_OutputPacket_InsertByte);
        tolua_function(tolua_S,"oldEnd",lua_cocos2dx_cocosnet_OutputPacket_oldEnd);
        tolua_function(tolua_S,"IsWritecbCheckCode",lua_cocos2dx_cocosnet_OutputPacket_IsWritecbCheckCode);
        tolua_function(tolua_S,"InsertInt",lua_cocos2dx_cocosnet_OutputPacket_InsertInt);
        tolua_function(tolua_S,"WriteByte",lua_cocos2dx_cocosnet_OutputPacket_WriteByte);
        tolua_function(tolua_S,"WriteInt",lua_cocos2dx_cocosnet_OutputPacket_WriteInt);
        tolua_function(tolua_S,"Copy",lua_cocos2dx_cocosnet_OutputPacket_Copy);
        tolua_function(tolua_S,"WriteBinary",lua_cocos2dx_cocosnet_OutputPacket_WriteBinary);
        tolua_function(tolua_S,"SetBegin",lua_cocos2dx_cocosnet_OutputPacket_SetBegin);
        tolua_function(tolua_S,"WritecbCheckCode",lua_cocos2dx_cocosnet_OutputPacket_WritecbCheckCode);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocosnet::OutputPacket).name();
    g_luaType[typeName] = "ccn.OutputPacket";
    g_typeCast["OutputPacket"] = "ccn.OutputPacket";
    return 1;
}

int lua_cocos2dx_cocosnet_CCNetDelegate_disconnect(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.CCNetDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::CCNetDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_CCNetDelegate_disconnect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_disconnect'", nullptr);
            return 0;
        }
        cobj->disconnect();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:disconnect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_disconnect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_CCNetDelegate_getSoTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.CCNetDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::CCNetDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_CCNetDelegate_getSoTimeout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_getSoTimeout'", nullptr);
            return 0;
        }
        double ret = cobj->getSoTimeout();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:getSoTimeout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_getSoTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_CCNetDelegate_setSoTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.CCNetDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::CCNetDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_CCNetDelegate_setSoTimeout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccn.CCNetDelegate:setSoTimeout");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_setSoTimeout'", nullptr);
            return 0;
        }
        cobj->setSoTimeout(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:setSoTimeout",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_setSoTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_CCNetDelegate_isConnected(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.CCNetDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::CCNetDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_CCNetDelegate_isConnected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_isConnected'", nullptr);
            return 0;
        }
        bool ret = cobj->isConnected();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:isConnected",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_isConnected'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_CCNetDelegate_setIpPort(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.CCNetDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::CCNetDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_CCNetDelegate_setIpPort'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        unsigned short arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccn.CCNetDelegate:setIpPort"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_ushort(tolua_S, 3, &arg1, "ccn.CCNetDelegate:setIpPort");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_setIpPort'", nullptr);
            return 0;
        }
        cobj->setIpPort(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:setIpPort",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_setIpPort'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_CCNetDelegate_send(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.CCNetDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::CCNetDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_CCNetDelegate_send'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocosnet::OutputPacket* arg0;

        ok &= luaval_to_object<cocosnet::OutputPacket>(tolua_S, 2, "ccn.OutputPacket",&arg0, "ccn.CCNetDelegate:send");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_send'", nullptr);
            return 0;
        }
        cobj->send(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:send",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_send'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_CCNetDelegate_close(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.CCNetDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::CCNetDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_CCNetDelegate_close'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_close'", nullptr);
            return 0;
        }
        cobj->close();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:close",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_close'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_CCNetDelegate_connect(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccn.CCNetDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosnet::CCNetDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosnet_CCNetDelegate_connect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_connect'", nullptr);
            return 0;
        }
        bool ret = cobj->connect();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:connect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_connect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosnet_CCNetDelegate_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocosnet::CCNetDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosnet_CCNetDelegate_constructor'", nullptr);
            return 0;
        }
        cobj = new cocosnet::LuaCocosnet();

        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccn.CCNetDelegate");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccn.CCNetDelegate:CCNetDelegate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosnet_CCNetDelegate_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_cocosnet_CCNetDelegate_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCNetDelegate)");
    return 0;
}



int lua_register_cocos2dx_cocosnet_CCNetDelegate(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccn.CCNetDelegate");
    tolua_cclass(tolua_S,"CCNetDelegate","ccn.CCNetDelegate","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"CCNetDelegate");
        tolua_function(tolua_S,"new",lua_cocos2dx_cocosnet_CCNetDelegate_constructor);
        tolua_function(tolua_S,"disconnect",lua_cocos2dx_cocosnet_CCNetDelegate_disconnect);
        tolua_function(tolua_S,"getSoTimeout",lua_cocos2dx_cocosnet_CCNetDelegate_getSoTimeout);
        tolua_function(tolua_S,"setSoTimeout",lua_cocos2dx_cocosnet_CCNetDelegate_setSoTimeout);
        tolua_function(tolua_S,"isConnected",lua_cocos2dx_cocosnet_CCNetDelegate_isConnected);
        tolua_function(tolua_S,"setIpPort",lua_cocos2dx_cocosnet_CCNetDelegate_setIpPort);
        tolua_function(tolua_S,"send",lua_cocos2dx_cocosnet_CCNetDelegate_send);
        tolua_function(tolua_S,"close",lua_cocos2dx_cocosnet_CCNetDelegate_close);
        tolua_function(tolua_S,"connect",lua_cocos2dx_cocosnet_CCNetDelegate_connect);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocosnet::CCNetDelegate).name();
    g_luaType[typeName] = "ccn.CCNetDelegate";
    g_typeCast["CCNetDelegate"] = "ccn.CCNetDelegate";
    return 1;
}
TOLUA_API int register_all_cocos2dx_cocosnet(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccn",0);
	tolua_beginmodule(tolua_S,"ccn");

	lua_register_cocos2dx_cocosnet_PacketBase(tolua_S);
	lua_register_cocos2dx_cocosnet_OutputPacket(tolua_S);
	lua_register_cocos2dx_cocosnet_CCNetDelegate(tolua_S);
	lua_register_cocos2dx_cocosnet_InputPacket(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}


int tolua_cocos2dx_cocosnet_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, "ccn.CCNetDelegate", 0, &tolua_err) ||
		!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
		!tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 4, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		cocosnet::LuaCocosnet* self = (cocosnet::LuaCocosnet*)tolua_tousertype(tolua_S, 1, 0);
		if (NULL != self) {
			int handler = (toluafix_ref_function(tolua_S, 2, 0));
			ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType)((int)tolua_tonumber(tolua_S, 3, 0) + (int)cocosnet::LuaCocosnet::CocosnetHandlerType::COCOSNET_ON_MESSAGE);
			ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerType);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'registerScriptHandler'.", &tolua_err);
	return 0;
#endif
}

int tolua_cocos2dx_cocosnet_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, "ccn.CCNetDelegate", 0, &tolua_err) ||
		!tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 3, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		cocosnet::LuaCocosnet* self = (cocosnet::LuaCocosnet*)tolua_tousertype(tolua_S, 1, 0);
		if (NULL != self) {
			ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType)((int)tolua_tonumber(tolua_S, 2, 0) + (int)cocosnet::LuaCocosnet::CocosnetHandlerType::COCOSNET_ON_MESSAGE);

			ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'unregisterScriptHandler'.", &tolua_err);
	return 0;
#endif
}


TOLUA_API int register_cocosnet_manual(lua_State* tolua_S)
{
	if (nullptr == tolua_S)
		return 0;

	lua_pushstring(tolua_S, "ccn.CCNetDelegate");
	lua_rawget(tolua_S, LUA_REGISTRYINDEX);
	if (lua_istable(tolua_S, -1))
	{
		lua_pushstring(tolua_S, "registerScriptHandler");
		lua_pushcfunction(tolua_S, tolua_cocos2dx_cocosnet_registerScriptHandler00);
		lua_rawset(tolua_S, -3);
		lua_pushstring(tolua_S, "unregisterScriptHandler");
		lua_pushcfunction(tolua_S, tolua_cocos2dx_cocosnet_unregisterScriptHandler00);
		lua_rawset(tolua_S, -3);
	}
	lua_pop(tolua_S, 1);

	return 1;
}

#endif

