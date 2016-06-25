// -------------------------------------------------------------------------
//    @FileName         ��    NFIProxyServerNet_ClientModule.h
//    @Author           ��    LvSheng.Huang
//    @Date             ��    2012-12-15
//    @Module           ��    NFIProxyServerNet_ClientModule
//
// -------------------------------------------------------------------------

#ifndef NFI_PROXYNET_CLIENTMODULE_H
#define NFI_PROXYNET_CLIENTMODULE_H

#include <iostream>
#include "NFILogicModule.h"
#include "NFINetClientModule.hpp"

class NFIProxyServerToWorldModule
    : public  NFILogicModule
{
public:
	virtual NFINetClientModule* GetClusterModule() = 0;
    virtual bool VerifyConnectData(const std::string& strAccount, const std::string& strKey) = 0;
};

#endif