// -------------------------------------------------------------------------
//    @FileName         ��    NFIEquipModule.h
//    @Author           ��    chuanbo.guo
//    @Date             ��    2016-01-12
//    @Module           ��    NFIEquipModule
//
// -------------------------------------------------------------------------

#ifndef NFI_EQUIP_MODULE_H
#define NFI_EQUIP_MODULE_H

#include <iostream>
#include "NFILogicModule.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"
#include "NFComm/NFMessageDefine/NFDefine.pb.h"

class NFIEquipModule : public NFILogicModule
{
public:
	virtual bool DressEquipForHero(const NFGUID& self, const NFGUID& hero, const NFGUID& id) = 0;
	virtual bool TakeOffEquipForm(const NFGUID& self, const NFGUID& hero, const NFGUID& id) = 0;
};

#endif