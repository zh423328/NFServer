// -------------------------------------------------------------------------
//    @FileName			:    NFCHeroModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFCHeroModule
//
// -------------------------------------------------------------------------

#ifndef NFC_HERO_MODULE_MODULE_H
#define NFC_HERO_MODULE_MODULE_H

#include "NFComm/NFCore/NFMap.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIGameLogicModule.h"
#include "NFComm/NFPluginModule/NFIHeroModule.h"
#include "NFComm/NFPluginModule/NFILogicModule.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFILogicClassModule.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"
#include "NFComm/NFPluginModule/NFIGameServerNet_ServerModule.h"
#include "NFComm/NFPluginModule/NFIUUIDModule.h"
#include "NFComm/NFPluginModule/NFIElementModule.h"
#include "NFComm/NFPluginModule/NFIGuildEctypeModule.h"
#include "NFComm/NFPluginModule/NFISceneProcessModule.h"

class NFCHeroModule
    : public NFIHeroModule
{
public:
    NFCHeroModule( NFIPluginManager* p )
    {
        pPluginManager = p;
    }
    virtual ~NFCHeroModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();
    virtual bool BeforeShut();

    virtual bool AddHero(const NFGUID& self, const std::string& strID);
    virtual bool AddHeroExp(const NFGUID& self, const NFGUID& xHeroID, const int nExp);
    virtual bool HeroStarUp(const NFGUID& self, const NFGUID& xHeroID);
    virtual bool HeroSkillUp(const NFGUID& self, const NFGUID& xHeroID, const int nIndex);
    virtual bool HeroTalentUp(const NFGUID& self, const NFGUID& xHeroID, const int nIndex);

	virtual bool HeroWearSkill(const NFGUID& self, const NFGUID& xHeroID, const std::string& xSkillID);
	virtual bool SetFightHero(const NFGUID& self, const int nPos, const NFGUID& xHeroID);

	virtual bool CreateHero(const NFGUID& self, const NFGUID& xHeroID);
	virtual bool DestroyHero(const NFGUID& self, const NFGUID& xHeroID);
	virtual NFGUID GetHeroGUID(const NFGUID& self, const std::string& strID);

protected:
	void OnSetFightHeroMsg( const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen );
   
protected:
    NFILogicClassModule* m_pLogicClassModule;
    NFIElementModule* m_pElementModule;
	NFIKernelModule* m_pKernelModule;
	NFIGameServerNet_ServerModule* m_pGameServerNet_ServerModule;
    NFIUUIDModule* m_pUUIDModule;
    NFISceneProcessModule* m_pSceneProcessModule;
private:
};

#endif
