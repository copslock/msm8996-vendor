/* bhist_stats_reg.h
 *
 * Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __BHIST_STATS_REG_H__
#define __BHIST_STATS_REG_H__

#define ISP_MODULE_NAME ISP_MOD_SKIN_BHIST_STATS
#define ISP_MODULE_STRING "bhist_stats"
#define ISP_LOG_NAME ISP_LOG_BHIST_STATS

#define NUM_DMI 3
#define DMI_RAM_START STATS_BHIST_RAM0

#define BHIST_STATS_OFF 0x00000BE4
#define BHIST_STATS_LEN 2

#define BHIST_CGC_OVERRIDE TRUE
#define BHIST_CGC_OVERRIDE_REGISTER 0x30
#define BHIST_CGC_OVERRIDE_BIT 4

/** ISP_StatsBhist_CfgCmdType:
 *
 *  @rgnHOffset: H offset
 *  @rgnVOffset: V offset
 *  @rgnHNum: H num
 *  @rgnVNum: V num
 **/
typedef struct ISP_StatsBhist_CfgCmdType {
  /*  VFE_STATS_BHIST_RGN_OFFSET_CFG   */
  uint32_t        rgnHOffset            :   13;
  uint32_t      /* reserved */          :    3;
  uint32_t        rgnVOffset            :   14;
  uint32_t       /*reserved */          :    2;
  /*  VFE_STATS_BHIST_RGN_SIZE_CFG */
  uint32_t        rgnHNum               :    12;
  uint32_t      /* reserved 23:31 */    :     4;
  uint32_t        rgnVNum               :    13;
  uint32_t      /* reserved 23:31 */    :     3;
} __attribute__((packed, aligned(4))) ISP_StatsBhist_CfgCmdType;

#endif /* __BHIST_STATS_REG_H__ */
