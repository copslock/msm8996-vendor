#pragma once
// AUTOGENERATED FILE: DO NOT EDIT

#include <stdint.h>
#include "object.h"

/***********************************************************
 Copyright (c) 2018 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
************************************************************/

/**
 * Interface used to obtain the credentials associated to REE clients registered
 * via SMC Invoke.
 */

/** @cond */

#define ITzdRegister_OP_getClientEnv 0
#define ITzdRegister_OP_getTrustedClientEnv 1

static inline int32_t
ITzdRegister_release(Object self)
{
  return Object_invoke(self, Object_OP_release, 0, 0);
}

static inline int32_t
ITzdRegister_retain(Object self)
{
  return Object_invoke(self, Object_OP_retain, 0, 0);
}

  /**
      Obtain a Client Env from tzd. Used to manage third parties.

      @param[in]  clientId     A null terminated ID to use for this client.
      @param[in]  credentials  A credential buffer CBOR encoded.
      @param[in]  whitelist    A Whitelist of class ids for the client.
      @param[out] obj          Client environment.

      @return
      Object_OK on success.
  */
static inline int32_t
ITzdRegister_getClientEnv(Object self, const void *clientId_ptr, size_t clientId_len, const void *credentials_ptr, size_t credentials_len, const uint32_t *whitelist_ptr, size_t whitelist_len, Object *env_ptr)
{
  ObjectArg a[4];
  a[0].bi = (ObjectBufIn) { clientId_ptr, clientId_len * 1 };
  a[1].bi = (ObjectBufIn) { credentials_ptr, credentials_len * 1 };
  a[2].bi = (ObjectBufIn) { whitelist_ptr, whitelist_len * sizeof(uint32_t) };

  int32_t result = Object_invoke(self, ITzdRegister_OP_getClientEnv, a, ObjectCounts_pack(3, 0, 0, 1));

  *env_ptr = a[3].o;

  return result;
}

  /**
      Obtain a Client Env from tzd for trusted clients. For use by vendors.

      @param[in]  clientId     A null terminated ID to use for this client.
      @param[in]  credentials  A credential buffer CBOR encoded.
      @param[out] obj          Client environment.

      @return
      Object_OK on success.
  */
static inline int32_t
ITzdRegister_getTrustedClientEnv(Object self, const void *clientId_ptr, size_t clientId_len, const void *credentials_ptr, size_t credentials_len, Object *env_ptr)
{
  ObjectArg a[3];
  a[0].bi = (ObjectBufIn) { clientId_ptr, clientId_len * 1 };
  a[1].bi = (ObjectBufIn) { credentials_ptr, credentials_len * 1 };

  int32_t result = Object_invoke(self, ITzdRegister_OP_getTrustedClientEnv, a, ObjectCounts_pack(2, 0, 0, 1));

  *env_ptr = a[2].o;

  return result;
}



