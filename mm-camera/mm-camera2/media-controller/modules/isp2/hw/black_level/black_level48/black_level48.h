/* black_level48.h
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __BLACK_LEVEL48_H__
#define __BLACK_LEVEL48_H__

/* mctl headers */
#include "chromatix.h"

/* isp headers */
#include "black_level48_reg.h"
#include "isp_sub_module_common.h"

/** black_level48_t:
 *
 *  @ISP_black_level_reg_t: Black Level registers
 *  @trigger_index: trigger index
 *  @aec_ratio: aec ratio
 *  @chromatix_channel_balance_gains_type: demux green gain to
 *                                       program black level
 *                                       scale
 **/
typedef struct {
  ISP_black_level_reg_t                 Reg;
  aec_update_t                          aec_update;
  float                                 dig_gain;
  uint32_t                              pipe_cfg_blss_offset;
} black_level48_t;

boolean black_level48_init(mct_module_t *module,
                           isp_sub_module_t *isp_sub_module);

void black_level48_destroy(mct_module_t *module,
                           isp_sub_module_t *isp_sub_module);

boolean black_level48_trigger_update(mct_module_t *module,
  isp_sub_module_t *isp_sub_module, mct_event_t *event);

boolean black_level48_stats_aec_update(isp_sub_module_t *isp_sub_module, void *data);

boolean black_level48_set_chromatix_ptr(isp_sub_module_t *isp_sub_module, void *data);

boolean black_level48_streamoff(isp_sub_module_t *isp_sub_module, void *data);

boolean black_level48_fetch_blklvl_offset(mct_module_t *module,
  isp_sub_module_t *isp_sub_module, mct_event_t *event);

boolean black_level48_set_digital_gain(isp_sub_module_t *isp_sub_module,
  float *new_dig_gain);

#endif /* __BPC44_H__ */
