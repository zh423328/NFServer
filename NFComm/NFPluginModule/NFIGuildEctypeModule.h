// -------------------------------------------------------------------------
//    @FileName         ��    NFIGuildEctypeModule.h
//    @Author           ��    LvSheng.Huang
//    @Date             ��    2012-12-15
//    @Module           ��    NFIGuildEctypeModule
//
// -------------------------------------------------------------------------

#ifndef NFI_GUILDECTYPE_MODULE_H
#define NFI_GUILDECTYPE_MODULE_H

#include <iostream>
#include "NFILogicModule.h"
#include "NFIBuffConfigModule.h"


class NFIGuildEctypeModule
    : public NFILogicModule
{
public:
    virtual bool CreateGuilEctype(const NFGUID& self, const NFGUID& guild) = 0;
    virtual bool DestroyGuildEctype(const NFGUID& self, const NFGUID& guild) = 0;
    virtual bool ApplyEnterGuilEctype(const NFGUID& self, const NFGUID& guild) = 0;
};

#endif