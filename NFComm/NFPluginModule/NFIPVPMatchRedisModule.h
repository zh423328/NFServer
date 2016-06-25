// -------------------------------------------------------------------------
//    @FileName         :    NFIPVPMatchRedisModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFIPVPMatchRedisModule
//
// -------------------------------------------------------------------------

#ifndef NFI_PVPMATCH_REDIS_MODULE_H
#define NFI_PVPMATCH_REDIS_MODULE_H

#include "NFILogicModule.h"
#include "NFComm/NFMessageDefine/NFMsgDefine.h"

class NFIPVPMatchRedisModule
    : public NFILogicModule
{

public:
    virtual bool GetPlayerRoomID(const NFGUID& self, NFGUID& xRoomID) = 0;
    virtual bool GetPlayerRoomIDList(const std::vector<NFGUID>& xPlayerList, std::vector<NFGUID>& vecRoomIDList) = 0;
    virtual bool GetRoomInfo(const NFGUID& xRoomID, NFMsg::PVPRoomInfo& xRoomInfo) = 0;
    virtual bool GetRoomInfoList(const std::vector<NFGUID>& xRoomIDList, std::vector<NFMsg::PVPRoomInfo>& vecRoomInfoList) = 0;
    virtual bool GetStatusRoomID(const int nPVPMode, const int nGrade, const int nStatus, std::vector<NFGUID>& xRoomIDList) = 0;

    virtual bool SetPlayerRoomID(const NFGUID& self, const NFGUID& xRoomID) = 0;
    virtual bool SetPlayerRoomIDList(const std::vector<NFGUID>& xPlayerList, std::vector<NFGUID>& vecRoomIDList) = 0;
    virtual bool SetRoomInfo(const NFGUID& xRoomID, NFMsg::PVPRoomInfo& xRoomInfo) = 0;
    virtual bool SetRoomInfoList(const std::vector<NFGUID>& xRoomIDList, std::vector<NFMsg::PVPRoomInfo>& vecRoomInfoList) = 0;
    virtual bool SetStatusRoomID(const int nPVPMode, const int nGrade, const int nStatus, const NFGUID& xRoomID) = 0;

    virtual bool DeletePlayerRoomID(const NFGUID& self, const NFGUID& xRoomID) = 0;
    virtual bool DeletePlayerRoomIDList(const std::vector<NFGUID>& xPlayerList) = 0;
    virtual bool DeleteRoomInfo(const NFGUID& xRoomID) = 0;
    virtual bool DeleteRoomInfoList(const std::vector<NFGUID>& xRoomIDList) = 0;
    virtual bool DeleteStatusRoomID(const int nPVPMode, const int nGrade, const int nStatus, const NFGUID& xRoomID) = 0;
    virtual bool DeletetStatusRoomID(const int nPVPMode, const int nGrade, const int nStatus, const std::vector<NFGUID>& xRoomIDList) = 0;

    virtual bool PushSinglePlayer(const NFGUID& self, const int nPVPMode, const int nGrade) = 0;
    virtual bool PopSinglePlayer(NFGUID& self, const int nPVPMode, const int nGrade) = 0;
    virtual bool PopSinglePlayerList(const int nPVPMode, const int nGrade, const int nCount, std::vector<NFGUID>& xPlayerList) = 0;
    virtual int GetSinglePlayerCount(NFGUID& self, const int nPVPMode, const int nGrade) = 0;

};

#endif