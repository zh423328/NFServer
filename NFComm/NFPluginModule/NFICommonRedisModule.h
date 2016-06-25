// -------------------------------------------------------------------------
//    @FileName         :    NFICommonRedisModule.h
//    @Author           :    Chuanbo.Guo
//    @Date             :    2012-12-15
//    @Module           :    NFICommonRedisModule
//
// -------------------------------------------------------------------------

#ifndef NFI_COMMON_REDIS_MODULE_H
#define NFI_COMMON_REDIS_MODULE_H

#include "NFILogicModule.h"

class NFICommonRedisModule
    : public NFILogicModule
{
public:
	virtual std::string GetPropertyCacheKey(const std::string& strClassName) = 0;
	virtual std::string GetRecordCacheKey(const std::string& strClassName) = 0;

    virtual NF_SHARE_PTR<NFIPropertyManager> GetCachePropertyInfo(const NFGUID& self, const std::string& strClassName) = 0;
    virtual NF_SHARE_PTR<NFIRecordManager> GetCacheRecordInfo(const NFGUID& self, const std::string& strClassName) = 0;

    virtual bool SetCachePropertyInfo(const NFGUID& self, const std::string& strClassName, NF_SHARE_PTR<NFIPropertyManager> pPropertyManager) = 0;
    virtual bool SetCacheRecordInfo(const NFGUID& self, const std::string& strClassName, NF_SHARE_PTR<NFIRecordManager> pRecordManager) = 0;

    virtual bool RemoveCachePropertyInfo(const NFGUID& self, const std::string& strClassName) = 0;
    virtual bool RemoveCacheRecordInfo(const NFGUID& self, const std::string& strClassName) = 0;

    virtual NF_SHARE_PTR<NFIPropertyManager> NewPropertyManager(const std::string& strClassName) = 0;
    virtual NF_SHARE_PTR<NFIRecordManager> NewRecordManager(const std::string& strClassName) = 0;

    virtual bool ConvertPBToPropertyManager(const NFMsg::ObjectPropertyList& xMsg, NF_SHARE_PTR<NFIPropertyManager>& pPropertyManager) = 0;
    virtual bool ConvertPBToRecordManager(const NFMsg::ObjectRecordList& xMsg, NF_SHARE_PTR<NFIRecordManager>& pRecordManager) = 0;

    virtual bool ConvertPropertyManagerToPB(const NF_SHARE_PTR<NFIPropertyManager>& pPropertyManager, NFMsg::ObjectPropertyList& xMsg, const bool bCheckCache = true) = 0;
    virtual bool ConvertRecordManagerToPB(const NF_SHARE_PTR<NFIRecordManager>& pRecordManager, NFMsg::ObjectRecordList& xMsg, const bool bCheckCache = true) = 0;

};

#endif