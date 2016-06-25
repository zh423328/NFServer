// -------------------------------------------------------------------------
//    @FileName         :    NFCMoveModule.cpp
//    @Author               :    LvSheng.Huang
//    @Date                 :    2013-06-11
//    @Module               :    NFCMoveModule
//    @Desc                 :
// -------------------------------------------------------------------------

#include "NFCItemModule.h"
#include "NFComm/NFPluginModule/NFIItemCardConsumeProcessModule.h"

bool NFCItemModule::Init()
{
    return true;
}

bool NFCItemModule::Shut()
{
    return true;
}

bool NFCItemModule::Execute()
{
    //λ����
    return true;
}

bool NFCItemModule::AfterInit()
{
	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pPackModule = pPluginManager->FindModule<NFIPackModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pLogicClassModule = pPluginManager->FindModule<NFILogicClassModule>();
	m_pPropertyModule = pPluginManager->FindModule<NFIPropertyModule>();
	m_pHeroModule = pPluginManager->FindModule<NFIHeroModule>();
	m_pCommonConfigModule = pPluginManager->FindModule<NFICommonConfigModule>();
	m_pGameServerNet_ServerModule = pPluginManager->FindModule<NFIGameServerNet_ServerModule>();

	std::string strPlayerPath = pPluginManager->GetConfigPath();
	strPlayerPath += "NFDataCfg/Ini/Common/AwardPackConfig.xml";
	m_pCommonConfigModule->LoadConfig(strPlayerPath);

    m_pKernelModule->AddClassCallBack(NFrame::Player::ThisName(), this, &NFCItemModule::OnClassObjectEvent );
	CheckConfig();

	//////////////////////////////////////////////////////////////////////////
	// add msg handler
	if (!m_pGameServerNet_ServerModule->GetNetModule()->AddReceiveCallBack(NFMsg::EGMI_REQ_ITEM_OBJECT, this, &NFCItemModule::OnClienUseItem)){ return false; }


    return true;
}

int NFCItemModule::OnClassObjectEvent( const NFGUID& self, const std::string& strClassNames, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList& var )
{
    if ( CLASS_OBJECT_EVENT::COE_DESTROY == eClassEvent )
    {

    }
    else if ( CLASS_OBJECT_EVENT::COE_CREATE_NODATA == eClassEvent )
    {
        m_pKernelModule->AddEventCallBack( self, NFED_ON_CLIENT_REQUIRE_USE_ITEM_POS, this, &NFCItemModule::OnRequireUseItemPosEvent );
    }

    return 0;
}

int NFCItemModule::OnRequireUseItemPosEvent( const NFGUID& self, const int nEventID, const NFIDataList& var )
{
    return 0;
}

bool NFCItemModule::CheckConfig()
{
	NF_SHARE_PTR<NFILogicClass> pLogicCLass = m_pLogicClassModule->GetElement(NFrame::Item::ThisName());
	if (nullptr == pLogicCLass)
	{
		assert(0);
	}

	NFList<std::string>& configList = pLogicCLass->GetConfigNameList();
	std::string strConfigID;
	bool bRet = configList.First(strConfigID);

	while (bRet)
	{
		NF_SHARE_PTR<NFIPropertyManager> pPropertyManager = m_pElementModule->GetPropertyManager(strConfigID);
		if (!pPropertyManager)
		{
			assert(0);
		}
		int nType = m_pElementModule->GetPropertyInt(strConfigID, NFrame::Item::ItemType());

		if (nType < 0)
		{
			assert(0);
		}
		int nSubType = m_pElementModule->GetPropertyInt(strConfigID, NFrame::Item::ItemSubType());
		if (nSubType < 0)
		{
			assert(0);
		}
		
		int nLevel = m_pElementModule->GetPropertyInt(strConfigID, NFrame::Item::Level());
		if (nLevel < 0)
		{
			assert(0);
		}

		int nQuality = m_pElementModule->GetPropertyInt(strConfigID, NFrame::Item::Quality());
		if (nQuality < 0)
		{
			assert(0);
		}

 		//int nCoolDown = m_pElementModule->GetPropertyInt(strConfigID, NFrame::Item::CoolDownTime());
 		//if (nCoolDown <= 0)
 		//{
 		//	assert(0);
 		//}

		int nOverlayCount = m_pElementModule->GetPropertyInt(strConfigID, NFrame::Item::OverlayCount());
		if (nOverlayCount <= 0)
		{
			assert(0);
		}


		int nBuyPrice = m_pElementModule->GetPropertyInt(strConfigID, NFrame::Item::BuyPrice());
		int nSalePrice = m_pElementModule->GetPropertyInt(strConfigID, NFrame::Item::SalePrice());
		
		if (nSalePrice < 0 || nBuyPrice < 0)
		{
			assert(0);
		}

		 bRet = configList.Next(strConfigID);
	}

	return true;
}

int NFCItemModule::AddItemEffectDataProperty( const NFGUID& self, const NFGUID& xTarget, const std::string& strItemID)
{
    if (strItemID.empty())
    {
        return 1;
    }

    //////////////////////////////////////////////////////////////////////////
    NF_SHARE_PTR<NFIObject> pObject = m_pKernelModule->GetObject( xTarget );
    if ( NULL == pObject )
    {
        //m_pLogModule->LogObject(NFILogModule::NLL_ERROR_NORMAL, self, "There is no object", __FUNCTION__, __LINE__);
        return 1;
    }

    //////////////////////////////////////////////////////////////////////////
    NF_SHARE_PTR<NFIPropertyManager> pPropertyManager = m_pElementModule->GetPropertyManager(strItemID);
    if (!pPropertyManager)
    {
        return 1;
    }

    NF_SHARE_PTR<NFIProperty> pEffectDataProperty = pPropertyManager->GetElement("EffectData");
    if (!pEffectDataProperty)
    {
        return 1;
    }

    NF_SHARE_PTR<NFIPropertyManager> pEffectDataPropertyManager = m_pElementModule->GetPropertyManager(pEffectDataProperty->GetString());
    if (!pEffectDataPropertyManager)
    {
        return 1;
    }

    NF_SHARE_PTR<NFIProperty> pProperty = pEffectDataPropertyManager->First();
    while (pProperty)
    {
        if (pProperty->GetInt() != 0)
        {
            m_pPropertyModule->AddPropertyValue( xTarget, pProperty->GetKey(), NFIPropertyModule::NPG_EQUIP, pProperty->GetInt());
        }

        pProperty = pEffectDataPropertyManager->Next();
    }

    return 0;
}

bool NFCItemModule::ConsumeDataItemProperty( const NFGUID& self, const std::string& strID )
{
    if (strID.empty())
    {
        return false;
    }

    const int nVIPEXP = m_pElementModule->GetPropertyInt(strID, NFrame::ConsumeData::VIPEXP());
    const int nEXP = m_pElementModule->GetPropertyInt(strID, NFrame::ConsumeData::EXP());
    const int nHP = m_pElementModule->GetPropertyInt(strID, NFrame::ConsumeData::HP());
    const int nSP = m_pElementModule->GetPropertyInt(strID, NFrame::ConsumeData::SP());
    const int nMP = m_pElementModule->GetPropertyInt(strID, NFrame::ConsumeData::MP());
    const int nGold = m_pElementModule->GetPropertyInt(strID, NFrame::ConsumeData::Gold());
    const int nMoney = m_pElementModule->GetPropertyInt(strID, NFrame::ConsumeData::Money());
   
    if (nGold > 0 && !m_pPropertyModule->EnoughDiamond(self, nGold))
    {
        return false;
    }

    if (nHP > 0 && !m_pPropertyModule->EnoughHP(self, nHP))
    {
        return false;
    }

    if (nMoney > 0 && !m_pPropertyModule->EnoughMoney(self, nMoney))
    {
        return false;
    }

    if (nMP > 0 && !m_pPropertyModule->EnoughMP(self, nMP))
    {
        return false;
    }

    if (nSP > 0 && !m_pPropertyModule->EnoughSP(self, nSP))
    {
        return false;
    }

    if (nHP > 0 && !m_pPropertyModule->ConsumeHP(self, nHP))
    {
        return false;
    }

    if (nMoney > 0 && !m_pPropertyModule->ConsumeMoney(self, nMoney))
    {
        return false;
    }

    if (nMP > 0 && !m_pPropertyModule->ConsumeMP(self, nMP))
    {
        return false;
    }

    if (nSP > 0 && !m_pPropertyModule->ConsumeSP(self, nSP))
    {
        return false;
    }

    return true;
}
  
bool NFCItemModule::DoAwardPack( const NFGUID& self, const std::string& strAwardPack )
{
    std::vector<std::string> xList;
    m_pCommonConfigModule->GetStructItemList(strAwardPack, xList);

    for (int i = 0; i < xList.size(); ++i)
    {
        const std::string& strItemID = xList[i];
        const int nCout = m_pCommonConfigModule->GetAttributeInt(strAwardPack, strItemID, "Count");
        const int nIsHero = m_pCommonConfigModule->GetAttributeInt(strAwardPack, strItemID, "IsHero");
        if (m_pElementModule->ExistElement(strItemID))
        {
            if (nIsHero > 0)
            {
                m_pHeroModule->AddHero(self, strItemID);
                continue;
            }

            const int nItemType = m_pElementModule->GetPropertyInt(strItemID, NFrame::Item::ItemType());
            switch (nItemType)
            {
            case NFMsg::EIT_EQUIP:
                {
                    m_pPackModule->CreateEquip(self, strItemID);
                }
                break;
            default:
                m_pPackModule->CreateItem(self, strItemID, nCout);
                break;
            }
        }
    }

    return true;
}

void NFCItemModule::OnClienUseItem(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	CLIENT_MSG_PROCESS(nSockIndex, nMsgID, msg, nLen, NFMsg::ReqAckUseItem);

	const NFGUID& self = NFINetModule::PBToNF(xMsg.user());
	const std::string strItemID = xMsg.item().item_id();
	const NFGUID xTargetID = NFINetModule::PBToNF(xMsg.targetid());

	if(!m_pElementModule->ExistElement(strItemID) || !m_pKernelModule->GetObject(xTargetID))
	{
		return;
	}

	NF_SHARE_PTR<NFIRecord> pRecordPack = m_pKernelModule->FindRecord(self, NFrame::Player::R_BagItemList());
	if (nullptr == pRecordPack)
	{
		return;
	}

    if (!ConsumeDataItemProperty(self, strItemID))
    {
        return;
    }

    if (!m_pPackModule->DeleteItem(self, strItemID, 1))
    {
        return;
    }

	NFMsg::EItemType eItemType = (NFMsg::EItemType)m_pElementModule->GetPropertyInt(strItemID, NFrame::Item::ItemType());
	switch (eItemType)
	{
	case NFMsg::EItemType::EIT_CARD:
	{
		NFIItemCardConsumeProcessModule* pConsumeProcessModule = GetConsumeModule<NFIItemCardConsumeProcessModule>(eItemType);
		if (pConsumeProcessModule)
		{
			if (pConsumeProcessModule->ConsumeLegal(self, strItemID, NFCDataList()) > 0)
			{
				pConsumeProcessModule->ConsumeProcess(self, strItemID, NFCDataList());
			}
		}

	}
		break;
	default:
		break;
	}
	
	/*	AddItemEffectDataProperty(self, xTargetID, strItemID);

		const std::string& strAwardPackID = m_pElementModule->GetPropertyString(strItemID, "AwardData");
		if (!strAwardPackID.empty())
		{
			DoAwardPack( self, strAwardPackID);
		}
		  */
}