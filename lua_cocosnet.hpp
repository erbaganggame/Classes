#include "base/ccConfig.h"
#ifndef __cocos2dx_cocosnet_h__
#define __cocos2dx_cocosnet_h__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif


#include "Cocosnet/CCNetMacros.h"
#include "Cocosnet/CCNetDelegate.h"

CC_NET_BEGIN
class LuaCocosnet :public CCNetDelegate
{
public:
	enum class CocosnetHandlerType :int
	{
		EVENT_CUSTOM_BEGAN = 10000,
		COCOSNET_ON_MESSAGE,
		COCOSNET_ON_CONNECTED,
		COCOSNET_ON_DISCONNECTED,
		COCOSNET_ON_TIMEOUT,
		COCOSNET_ON_EXCEPTION,
		EVENT_CUSTOM_ENDED = 11000,
	};
protected:
	
	// will calling when a package is coming
	virtual void onMessageReceived(const char*m_pTempBuffer, const int nRet) override;

	// when connected will calling
	virtual void onConnected() override;

	// when connect time out will calling
	virtual void onConnectTimeout() override;

	// on disconnected will call
	virtual void onDisconnected() override;

	// on exception
	virtual void onExceptionCaught(CCSocketStatus eStatus) override;

};

CC_NET_END
int register_all_cocos2dx_cocosnet(lua_State* tolua_S);
TOLUA_API int register_cocosnet_manual(lua_State* tolua_S);
#endif
#endif // __cocos2dx_cocosnet_h__
