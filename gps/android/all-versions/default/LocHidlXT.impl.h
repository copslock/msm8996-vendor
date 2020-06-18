/*
 * Copyright (c) 2018 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef LOC_HIDL_VERSION
#error "LOC_HIDL_VERSION must be set before including this file."
#endif

#include <loc_cfg.h>
#include <dlfcn.h>
#include <log_util.h>

namespace vendor {
namespace qti {
namespace gnss {
namespace LOC_HIDL_VERSION {
namespace implementation {

// Methods from ::vendor::qti::gnss::V1_0::IGnssXT follow.
Return<void> LocHidlXT::init() {
    FROM_HIDL_CLIENT();

    UTIL_READ_CONF_DEFAULT("/vendor/etc/gps.conf");

    createXtAdapterInstance* createInstanceFn = NULL;
    const char *error = NULL;
    dlerror();
    void *handle = dlopen("libxtadapter.so", RTLD_NOW);
    if (NULL == handle)  {
        LOC_LOGE("dlopen for libxtadapter.so failed");
        return Void();
    } else if (NULL != (error = dlerror()))  {
        LOC_LOGE("dlopen for libxtadapter.so failed, error = %s", error);
        return Void();
    }

    createInstanceFn = (createXtAdapterInstance*)
            dlsym(handle, "createXtAdapterInstance");
    if ((error = dlerror()) != NULL)  {
        LOC_LOGE("dlsym for createXtAdapterInstance failed, error = %s",
                error);
        createInstanceFn = NULL;
    }

    if (NULL == createInstanceFn) {
        LOC_LOGE("createInstanceFn NULL");
        return Void();
    }

    (*createInstanceFn)();
    return Void();
}

Return<void> LocHidlXT::setUserPref(bool userPref) {
    FROM_HIDL_CLIENT();

    setXtAdapterUserPref* setUserPrefFn = NULL;
    const char *error = NULL;
    dlerror();
    void *handle = dlopen("libxtadapter.so", RTLD_NOW);
    if (NULL == handle)  {
        LOC_LOGE("dlopen for libxtadapter.so failed");
        return Void();
    } else if (NULL != (error = dlerror()))  {
        LOC_LOGE("dlopen for libxtadapter.so failed, error = %s", error);
        return Void();
    }

    setUserPrefFn = (setXtAdapterUserPref*)
        dlsym(handle, "setXtAdapterUserPref");
    if ((error = dlerror()) != NULL)  {
        LOC_LOGE("dlsym for setXtAdapterUserPref failed, error = %s",
                error);
        setUserPrefFn = NULL;
    }

    if (NULL == setUserPrefFn) {
        LOC_LOGE("setUserPrefFn NULL");
        return Void();
    }

    (*setUserPrefFn)(userPref);
    return Void();
}

}  // namespace implementation
}  // namespace LOC_HIDL_VERSION
}  // namespace gnss
}  // namespace qti
}  // namespace vendor
