/* hdr48.h
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __hdr48_H__
#define __hdr48_H__

/* mctl headers */
#include "chromatix.h"
#include "chromatix_common.h"

/* isp headers */
#include "hdr_reg.h"
#include "isp_sub_module_common.h"

/** hdr_cfg_cmd_t:
*
*  Configure hdr config
*
 **/
typedef struct {
  ISP_HdrCfg0 cfg0;
  ISP_HdrCfg1 cfg1;
  ISP_HdrCfg2 cfg2;
  ISP_HdrCfg3 cfg3;
  ISP_HdrCfg4 cfg4;
} hdr_cfg_cmd_t;

/** hdr_cfg_2_cmd_t:
*
*  Configure hdr config
*
 **/
typedef struct {
  ISP_HdrCfg5 cfg5;
} hdr_cfg_2_cmd_t;

/** hdr_recon_cmd_t:
*
*  Configure hdr recon config
*
 **/
typedef struct {
  ISP_HdrReconCfg0 recon_cfg0;
  ISP_HdrReconCfg1 recon_cfg1;
  ISP_HdrReconCfg2 recon_cfg2;
  ISP_HdrReconCfg3 recon_cfg3;
  ISP_HdrReconCfg4 recon_cfg4;
} hdr_recon_cmd_t;

/** hdr_recon2_cmd_t:
*
*  Configure hdr recon config
*
 **/
typedef struct {
  ISP_HdrReconCfg5 recon_cfg5;
  ISP_HdrReconCfg6 recon_cfg6;
} hdr_recon2_cmd_t;

/** hdr_mac_cmd_t:
*
*  Configure hdr mac config
*
 **/
typedef struct {
  ISP_HdrMacCfg0 mac_cfg0;
  ISP_HdrMacCfg1 mac_cfg1;
  ISP_HdrMacCfg2 mac_cfg2;
  ISP_HdrMacCfg3 mac_cfg3;
  ISP_HdrMacCfg4 mac_cfg4;
  ISP_HdrMacCfg5 mac_cfg5;
  ISP_HdrMacCfg6 mac_cfg6;
  ISP_HdrMacCfg7 mac_cfg7;
} hdr_mac_cmd_t;

/** hdr_reg_cmd_t:
*
*  Configure all hdr registers
*
 **/
typedef struct {
  hdr_cfg_cmd_t cfg_cmd;
  hdr_cfg_2_cmd_t cfg_cmd2;
  hdr_recon_cmd_t recon_cmd;
  hdr_recon2_cmd_t recon_cmd2;
  hdr_mac_cmd_t mac_cmd;
} hdr_reg_cmd_t;

/** hdr48_t:
 *
 *  @lux_idx: aec lux value
 *  @real_gain: aec gain value
 *  @hdr_exp_ratio: aec exposure ratio
 *  @exp_time: aec exposure time
 *  @color_temp: awb cct type
 *  @awb_gain: awb rgb gain
 *  @rgn_idx: current region
 *  @is_3d_mode_on: 3d mode
 *  @interp_data: interpolated data to be written to registers
 *  @reg_cmd: reg cmd to be upsated to hw
 **/
typedef struct {
  float real_gain;
  float hdr_sensitivity_ratio;
  float hdr_exp_time_ratio;
  awb_gain_t awb_gain;
  boolean is_3d_mode_on;
  hdr_reg_cmd_t reg_cmd;
} hdr48_t;

/* funtion declaration */
boolean hdr48_set_hdr_mode(mct_module_t *module,
  isp_sub_module_t *isp_sub_module, mct_event_t *event);

boolean hdr48_init(isp_sub_module_t *isp_sub_module);

void hdr48_destroy(isp_sub_module_t *isp_sub_module);

boolean hdr48_streamoff(isp_sub_module_t *isp_sub_module, void *data);

boolean hdr48_streamon(isp_sub_module_t *isp_sub_module, void *data);

boolean hdr48_set_chromatix_ptr(isp_sub_module_t *isp_sub_module,
  void *data);

boolean hdr48_stats_aec_update(isp_sub_module_t *isp_sub_module,
  void *data);

boolean hdr48_stats_awb_update(isp_sub_module_t *isp_sub_module,
  void *data);

boolean hdr48_trigger_update(mct_module_t *module,
  isp_sub_module_t *isp_sub_module,
  void *data,
  uint32_t identity);

#endif /* __hdr48_H__ */
