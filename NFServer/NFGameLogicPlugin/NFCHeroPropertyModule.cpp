#include "NFCHeroPropertyModule.h"

bool NFCHeroPropertyModule::Init()
{
	return true;
}

bool NFCHeroPropertyModule::Shut()
{
	return true;
}

bool NFCHeroPropertyModule::Execute()
{
	return true;
}

bool NFCHeroPropertyModule::AfterInit()
{
	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pLogicClassModule = pPluginManager->FindModule<NFILogicClassModule>();
	m_pGameServerNet_ServerModule = pPluginManager->FindModule<NFIGameServerNet_ServerModule>();
	m_pUUIDModule = pPluginManager->FindModule<NFIUUIDModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pEquipPropertyModule = pPluginManager->FindModule<NFIEquipPropertyModule>();

	m_pKernelModule->AddClassCallBack(NFrame::Player::ThisName(), this, &NFCHeroPropertyModule::OnPlayerClassEvent);
	m_pKernelModule->AddClassCallBack(NFrame::NPC::ThisName(), this, &NFCHeroPropertyModule::OnNPCClassEvent);
	return true;

}

bool NFCHeroPropertyModule::BeforeShut()
{
	return true;
}

int NFCHeroPropertyModule::OnPlayerClassEvent(const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList& var)
{
	switch (eClassEvent)
	{
	case CLASS_OBJECT_EVENT::COE_CREATE_FINISH:
	{
		m_pKernelModule->AddRecordCallBack(self, NFrame::Player::R_PlayerHero(), this, &NFCHeroPropertyModule::OnObjectHeroRecordEvent);
	}
	break;
	default:
		break;
	}

	return 0;
}


int NFCHeroPropertyModule::OnNPCClassEvent(const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList& var)
{
	switch (eClassEvent)
	{
	case CLASS_OBJECT_EVENT::COE_CREATE_FINISH:
	{
	}
	break;
	default:
		break;
	}

	return 0;
}

int NFCHeroPropertyModule::OnObjectHeroRecordEvent(const NFGUID& self, const RECORD_EVENT_DATA& xEventData, const NFIDataList::TData& oldVar, const NFIDataList::TData& newVar)
{
	std::ostringstream stream;
	NF_SHARE_PTR<NFIRecord> pHeroRecord = m_pKernelModule->FindRecord(self, xEventData.strRecordName);
	if (nullptr == pHeroRecord)
	{
		return 0;
	}

	switch (xEventData.nOpType)
	{
	case NFIRecord::RecordOptype::Add:
	{
		const NFGUID& xHeroGUID = pHeroRecord->GetObject(xEventData.nRow, NFrame::Player::PlayerHero::PlayerHero_GUID);
		OnHeroPropertyUpdate(self, xHeroGUID);
	}
	break;
	case NFIRecord::RecordOptype::Del:
	{

	}
	break;
	case NFIRecord::RecordOptype::Update:
	{
		switch (xEventData.nCol)
		{
		case NFrame::Player::PlayerHero::PlayerHero_Level:
		case NFrame::Player::PlayerHero::PlayerHero_Star:
		case NFrame::Player::PlayerHero::PlayerHero_Equip1:
		case NFrame::Player::PlayerHero::PlayerHero_Equip2:
		case NFrame::Player::PlayerHero::PlayerHero_Equip3:
		case NFrame::Player::PlayerHero::PlayerHero_Equip4:
		case NFrame::Player::PlayerHero::PlayerHero_Equip5:
		case NFrame::Player::PlayerHero::PlayerHero_Equip6:
		case NFrame::Player::PlayerHero::PlayerHero_Talent1:
		case NFrame::Player::PlayerHero::PlayerHero_Talent2:
		case NFrame::Player::PlayerHero::PlayerHero_Talent3:
		case NFrame::Player::PlayerHero::PlayerHero_Talent4:
		case NFrame::Player::PlayerHero::PlayerHero_Talent5:
		{
			const NFGUID& xHeroGUID = pHeroRecord->GetObject(xEventData.nRow, NFrame::Player::PlayerHero::PlayerHero_GUID);
			OnHeroPropertyUpdate(self, xHeroGUID);
		}
		break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}

	return 0;
}

bool NFCHeroPropertyModule::OnHeroPropertyUpdate(const NFGUID & self, const NFGUID & xHeroGUID)
{
	NF_SHARE_PTR<NFIRecord> pHeroRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_PlayerHero());
	if (nullptr == pHeroRecord)
	{
		return false;
	}

	NFCDataList varFind;
	if (pHeroRecord->FindObject(NFrame::Player::PlayerHero_GUID, xHeroGUID, varFind) != 1)
	{
		return false;
	}

	NF_SHARE_PTR<NFIRecord> pHeroPropertyRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_HeroPropertyValue());
	if (nullptr == pHeroPropertyRecord)
	{
		return false;
	}

	const int nRow = varFind.Int(0);

	NFCDataList xHeroAllValue;
	bool bRet = CalHeroAllProperty(self, xHeroGUID, xHeroAllValue);
	if (bRet)
	{
		pHeroPropertyRecord->AddRow(nRow, xHeroAllValue);
	}

	return true;
}

bool NFCHeroPropertyModule::CalHeroAllProperty(const NFGUID& self, const NFGUID& xHeroGUID, NFIDataList& xDataList)
{
	NF_SHARE_PTR<NFIRecord> pHeroRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_PlayerHero());
	if (nullptr == pHeroRecord)
	{
		return false;
	}

	NFCDataList varFind;
	if (pHeroRecord->FindObject(NFrame::Player::PlayerHero_GUID, xHeroGUID, varFind) != 1)
	{
		return false;
	}

	const int nRow = varFind.Int(0);

	NF_SHARE_PTR<NFIRecord> pHeroPropertyRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_HeroPropertyValue());
	if (nullptr == pHeroPropertyRecord)
	{
		return false;
	}

	NFCDataList xHeroPropertyValue;
	CalHeroBaseProperty(self, xHeroGUID, xHeroPropertyValue);

	NFCDataList xHeroTalentValue;
	CalHeroTalentProperty(self, xHeroGUID, xHeroTalentValue);

	NFCDataList xHeroEquipValue;
	CalHeroEquipProperty(self, xHeroGUID, xHeroEquipValue);

	for (int i = 0; i < pHeroPropertyRecord->GetCols(); ++i)
	{
		int nPropertyValue = 0;
		int nTalentValue = 0;
		int nEquipValue = 0;

		if (xHeroPropertyValue.GetCount() == pHeroPropertyRecord->GetCols())
		{
			nPropertyValue = xHeroPropertyValue.Int(i);
		}
		if (xHeroTalentValue.GetCount() == pHeroPropertyRecord->GetCols())
		{
			nTalentValue = xHeroTalentValue.Int(i);
		}
		if (xHeroEquipValue.GetCount() == pHeroPropertyRecord->GetCols())
		{
			nEquipValue = xHeroEquipValue.Int(i);
		}

		int nAllValue = nPropertyValue + nTalentValue + nEquipValue;

		xDataList.AddInt(nAllValue);
	}

	return true;
}

bool NFCHeroPropertyModule::CalHeroBaseProperty(const NFGUID& self, const NFGUID& xHeroGUID, NFIDataList& xDataList)
{
	NF_SHARE_PTR<NFIRecord> pHeroRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_PlayerHero());
	if (nullptr == pHeroRecord)
	{
		return false;
	}

	NFCDataList varFind;
	if (pHeroRecord->FindObject(NFrame::Player::PlayerHero_GUID, xHeroGUID, varFind) != 1)
	{
		return false;
	}

	const int nRow = varFind.Int(0);

	NF_SHARE_PTR<NFIRecord> pHeroPropertyRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_HeroPropertyValue());
	if (nullptr == pHeroPropertyRecord)
	{
		return false;
	}

	/////////////PropertyBase/////////////////////////////////////////
	xDataList.Clear();

	const std::string& strConfigID = pHeroRecord->GetString(nRow, NFrame::Player::PlayerHero::PlayerHero_ConfigID);
	const std::string& strPropertyEffectData = m_pElementModule->GetPropertyString(strConfigID, NFrame::NPC::EffectData());
	if (!strPropertyEffectData.empty())
	{
		for (int i = 0; i < pHeroPropertyRecord->GetCols(); ++i)
		{
			const std::string& strColTag = pHeroPropertyRecord->GetColTag(i);
			int nValue = m_pElementModule->GetPropertyInt(strPropertyEffectData, strColTag);
			xDataList.AddInt(nValue);
		}
	}

	return true;
}

bool NFCHeroPropertyModule::CalHeroTalentProperty(const NFGUID& self, const NFGUID& xHeroGUID, NFIDataList& xDataList)
{
	NF_SHARE_PTR<NFIRecord> pHeroRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_PlayerHero());
	if (nullptr == pHeroRecord)
	{
		return false;
	}

	NFCDataList varFind;
	if (pHeroRecord->FindObject(NFrame::Player::PlayerHero_GUID, xHeroGUID, varFind) != 1)
	{
		return false;
	}

	const int nRow = varFind.Int(0);

	NF_SHARE_PTR<NFIRecord> pHeroPropertyRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_HeroPropertyValue());
	if (nullptr == pHeroPropertyRecord)
	{
		return false;
	}

	////////////////////Talent//////////////////////////////////////////////////////
	xDataList.Clear();

	for (int i = 0; i < pHeroPropertyRecord->GetCols(); ++i)
	{
		xDataList.AddInt(0);
	}

	for (int i = NFrame::Player::PlayerHero_Talent1; i <= NFrame::Player::PlayerHero_Talent5; ++i)
	{
		const std::string& strTalentID = pHeroRecord->GetString(nRow, i);
		const std::string& strTalentEffectData = m_pElementModule->GetPropertyString(strTalentID, NFrame::Talent::EffectData());
		if (!strTalentEffectData.empty())
		{
			//one talent
			for (int j = 0; j < pHeroPropertyRecord->GetCols(); ++j)
			{
				const std::string& strColTag = pHeroPropertyRecord->GetColTag(j);
				int nValue = m_pElementModule->GetPropertyInt(strTalentEffectData, strColTag);
				int nOldValue = xDataList.Int(j);

				xDataList.SetInt(j, nOldValue + nValue);
			}
		}
	}

	return true;
}

bool NFCHeroPropertyModule::CalHeroEquipProperty(const NFGUID& self, const NFGUID& xHeroGUID, NFIDataList& xDataList)
{
	NF_SHARE_PTR<NFIRecord> pHeroRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_PlayerHero());
	if (nullptr == pHeroRecord)
	{
		return false;
	}

	NFCDataList varFind;
	if (pHeroRecord->FindObject(NFrame::Player::PlayerHero_GUID, xHeroGUID, varFind) != 1)
	{
		return false;
	}

	const int nRow = varFind.Int(0);

	NF_SHARE_PTR<NFIRecord> pHeroPropertyRecord = m_pKernelModule->FindRecord(self, NFrame::Player::R_HeroPropertyValue());
	if (nullptr == pHeroPropertyRecord)
	{
		return false;
	}

	////////////////////Equip//////////////////////////////////////////////////////
	xDataList.Clear();

	for (int i = 0; i < pHeroPropertyRecord->GetCols(); ++i)
	{
		xDataList.AddInt(0);
	}

	for (int i = NFrame::Player::PlayerHero_Equip1; i <= NFrame::Player::PlayerHero_Equip6; ++i)
	{
		NFCDataList EquipDataList;
		const NFGUID xEquipID = pHeroRecord->GetObject(nRow, i);
		if (!xEquipID.IsNull() && m_pEquipPropertyModule->CalEquipProperty(self, xEquipID, EquipDataList))
		{
			//one equip
			for (int j = 0; j < pHeroPropertyRecord->GetCols(); ++j)
			{
				int nOldValue = xDataList.Int(j);
				int nEquipValue = EquipDataList.Int(j);

				xDataList.SetInt(j, nOldValue + nEquipValue);
			}
		}
	}

	return true;
}
