// -------------------------------------------------------------------------
//    @FileName			:    NFLuaScriptPlugin.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-07-14 08:51
//    @Module           :   NFLuaScriptPlugin
//
// -------------------------------------------------------------------------

#ifndef NF_LUA_SCRIPT_LUGIN_H
#define NF_LUA_SCRIPT_LUGIN_H

///
#include "NFComm/NFPluginModule/NFIPlugin.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"

class NFLuaScriptPlugin : public NFIPlugin
{
public:
    NFLuaScriptPlugin(NFIPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif