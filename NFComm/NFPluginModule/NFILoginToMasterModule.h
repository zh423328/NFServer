// -------------------------------------------------------------------------
//    @FileName         ��    NFILoginNet_ClientModule.h
//    @Author           ��    LvSheng.Huang
//    @Date             ��    2012-12-15
//    @Module           ��    NFILoginNet_ClientModule
//
// -------------------------------------------------------------------------

#ifndef NFI_LOGINNET_CLIENTMODULE_H
#define NFI_LOGINNET_CLIENTMODULE_H

#include <iostream>
#include "NFILogicModule.h"
#include "NFINetClientModule.hpp"
#include "NFComm/NFMessageDefine/NFMsgPreGame.pb.h"

class NFILoginToMasterModule
    : public NFILogicModule
{
public:
	virtual NFINetClientModule* GetClusterModule() = 0;
    virtual NFMapEx<int, NFMsg::ServerInfoReport>& GetWorldMap() = 0;
};

#endif
