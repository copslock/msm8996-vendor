/* isp_pipeline46.c
 *
 * Copyright (c) 2012-2014 Qualcomm Technologies, Inc. All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

/* std headers */
#include <stdio.h>
/* isp headers */
#include "isp_pipeline.h"
#include "isp_pipeline_reg.h"
#include "isp_pipeline46_parser.h"
#include "isp_defs.h"
#include "isp_log.h"

#define ISP_MAX_APPLYING_DELAY  2

static boolean isp_pipeline46_calculate_roi_map(
  isp_zoom_params_t* zoom_params_arr,
  mct_bus_msg_stream_crop_t *stream_crop, uint32_t identity);
static boolean isp_pipeline46_update_module_cfg(int32_t fd,
  uint8_t *curr_submod_enable, isp_module_enable_info_t *enable_bit_info,
  cam_format_t sensor_fmt);

#define ISP_PIX46_CLK_USER_MAX ISP_PIX_CLK_600MHZ

static isp_hw_info_t common_hw[] = {
  {{"linearization40"},      ISP_MOD_LINEARIZATION,    MSM_ISP_STATS_MAX},
  {{"mesh_rolloff44"},       ISP_MOD_ROLLOFF,          MSM_ISP_STATS_MAX},
  {{"demux40"},              ISP_MOD_DEMUX,            MSM_ISP_STATS_MAX},
  {{"demosaic44"},           ISP_MOD_DEMOSAIC,         MSM_ISP_STATS_MAX},
  {{"bf_stats44"},           ISP_MOD_BF_STATS,         MSM_ISP_STATS_BF},
  {{"bf_scale_stats46"},     ISP_MOD_BF_SCALE_STATS,   MSM_ISP_STATS_BF_SCALE},
  {{"bg_stats46"},           ISP_MOD_BG_STATS,         MSM_ISP_STATS_BG},
  {{"hdr_be_stats46"},       ISP_MOD_HDR_BE_STATS,     MSM_ISP_STATS_HDR_BE},
  {{"rs_stats46"},           ISP_MOD_RS_STATS,         MSM_ISP_STATS_RS},
  {{"cs_stats46"},           ISP_MOD_CS_STATS,         MSM_ISP_STATS_CS},
  {{"ihist_stats46"},        ISP_MOD_IHIST_STATS,      MSM_ISP_STATS_IHIST},
  {{"bhist_stats44"},        ISP_MOD_SKIN_BHIST_STATS, MSM_ISP_STATS_BHIST},
  {{"chroma_enhan40"},       ISP_MOD_CHROMA_ENHANCE,   MSM_ISP_STATS_MAX},
  {{"bpc44"},                ISP_MOD_BPC,              MSM_ISP_STATS_MAX},
  {{"bcc44"},                ISP_MOD_BCC,              MSM_ISP_STATS_MAX},
  {{"abf44"},                ISP_MOD_ABF,              MSM_ISP_STATS_MAX},
  {{"color_correct46"},      ISP_MOD_COLOR_CORRECT,    MSM_ISP_STATS_MAX},
  {{"chroma_suppress40"},    ISP_MOD_CHROMA_SUPPRESS,  MSM_ISP_STATS_MAX},
  {{"mce40"},                ISP_MOD_MCE,              MSM_ISP_STATS_MAX},
  {{"sce40"},                ISP_MOD_SCE,              MSM_ISP_STATS_MAX},
  {{"clf46"},                ISP_MOD_CLF,              MSM_ISP_STATS_MAX},
  {{"wb46"},                 ISP_MOD_WB,               MSM_ISP_STATS_MAX},
  {{"gamma44"},              ISP_MOD_GAMMA,            MSM_ISP_STATS_MAX},
  {{"gtm46"},                ISP_MOD_GTM,              MSM_ISP_STATS_MAX},
  {{"hdr46"},                ISP_MOD_HDR,              MSM_ISP_STATS_MAX},
  {{"ltm44"},                ISP_MOD_LTM,              MSM_ISP_STATS_MAX},
  {{"gic46"},                ISP_MOD_GIC,              MSM_ISP_STATS_MAX},
  /*{{"pedestal_correct46"}, ISP_MOD_PEDESTAL,         MSM_ISP_STATS_MAX},*/
};

static isp_hw_params_t common_hw_params = {
  .hw_info_table = common_hw,
  .num_hw = ARRAY_SIZE(common_hw),
};

static isp_hw_info_t viewfinder_stream_hw[] = {
  {{"color_xform_viewfinder46"}, ISP_MOD_COLOR_XFORM_VIEWFINDER,
  MSM_ISP_STATS_MAX},
  {{"scaler_viewfinder46"},      ISP_MOD_SCALER_VIEWFINDER, MSM_ISP_STATS_MAX},
  {{"fovcrop_viewfinder46"},     ISP_MOD_FOV_VIEWFINDER,    MSM_ISP_STATS_MAX},
  {{"clamp_viewfinder40"},       ISP_MOD_CLAMP_VIEWFINDER,  MSM_ISP_STATS_MAX},
};

static isp_hw_info_t encoder_stream_hw[] = {
  {{"color_xform_encoder46"}, ISP_MOD_COLOR_XFORM_ENCODER, MSM_ISP_STATS_MAX},
  {{"scaler_encoder46"},      ISP_MOD_SCALER_ENCODER,      MSM_ISP_STATS_MAX},
  {{"fovcrop_encoder46"},     ISP_MOD_FOV_ENCODER,         MSM_ISP_STATS_MAX},
  {{"clamp_encoder40"},       ISP_MOD_CLAMP_ENCODER,       MSM_ISP_STATS_MAX},
};

static isp_hw_info_t video_stream_hw[] = {
  {{"color_xform_video46"}, ISP_MOD_COLOR_XFORM_VIDEO, MSM_ISP_STATS_MAX},
  {{"scaler_video46"},      ISP_MOD_SCALER_VIDEO,      MSM_ISP_STATS_MAX},
  {{"fovcrop_video46"},     ISP_MOD_FOV_VIDEO,         MSM_ISP_STATS_MAX},
  {{"clamp_video40"},       ISP_MOD_CLAMP_VIDEO,       MSM_ISP_STATS_MAX},
};

static isp_hw_params_t stream_hw_params[] = {
  {
    .hw_info_table = viewfinder_stream_hw,
    .num_hw = ARRAY_SIZE(viewfinder_stream_hw),
  },
  {
    .hw_info_table = encoder_stream_hw,
    .num_hw = ARRAY_SIZE(encoder_stream_hw),
  },
  {
    .hw_info_table = video_stream_hw,
    .num_hw = ARRAY_SIZE(video_stream_hw),
  },
};

static isp_pipeline_stats_func_table_t func_table = {
  .pipeline_fill_stats_info = isp_pipeline46_parser_fill_stats_info,
  .pipeline_stats_parse[MSM_ISP_STATS_BF] = isp_pipeline46_parser_bf_stats,
  .pipeline_stats_parse[MSM_ISP_STATS_BG] = isp_pipeline46_parser_bg_stats,
  .pipeline_stats_parse[MSM_ISP_STATS_RS] = isp_pipeline46_parser_rs_stats,
  .pipeline_stats_parse[MSM_ISP_STATS_CS] = isp_pipeline46_parser_cs_stats,
  .pipeline_stats_parse[MSM_ISP_STATS_IHIST] =
    isp_pipeline46_parser_ihist_stats,
  .pipeline_stats_parse[MSM_ISP_STATS_BHIST] =
    isp_pipeline46_parser_bhist_stats,
  .pipeline_stats_parse[MSM_ISP_STATS_BF_SCALE] =
    isp_pipeline46_parser_bf_scale_stats,
  .pipeline_stats_parse[MSM_ISP_STATS_HDR_BE] = isp_pipeline46_parser_hdr_be_stats,
  .pipeline_calculate_roi_map = isp_pipeline46_calculate_roi_map,
  .pipeline_update_module_cfg = isp_pipeline46_update_module_cfg,
};

static isp_pipeline_t isp_pipeline = {
  .common_hw_params = &common_hw_params,
  .stream_hw_params[ISP_HW_STREAM_VIEWFINDER] =
     &stream_hw_params[ISP_HW_STREAM_VIEWFINDER],
  .stream_hw_params[ISP_HW_STREAM_ENCODER] =
     &stream_hw_params[ISP_HW_STREAM_ENCODER],
  .stream_hw_params[ISP_HW_STREAM_VIDEO] =
     &stream_hw_params[ISP_HW_STREAM_VIDEO],
  .func_table = &func_table,
  .is_ahb_clk_cfg_supported = FALSE,
};

/** isp_pipeline46_calculate_roi_map:
 *
 *  @saved_params: ISP saved params
 *  @stream_crop: stream crop params
 *  @identity: event identity
 *
 *  Calculate ROI map based on camif output, fovcrop and
 *  scaler output
 *
 *  Return TRUE on success and FALSE on failure
 **/
static boolean isp_pipeline46_calculate_roi_map(
  isp_zoom_params_t* zoom_params_arr,
  mct_bus_msg_stream_crop_t *stream_crop, uint32_t identity)
{
  uint32_t           i = 0,
                     fov_cropped_width = 0,
                     fov_cropped_height = 0;
  isp_zoom_params_t *zoom_params = NULL;

  if (!zoom_params_arr || !stream_crop) {
    ISP_ERR("failed: zoom_params_arr %p stream_crop %p", zoom_params_arr,
      stream_crop);
    return FALSE;
  }

  for (i = 0; i < ISP_MAX_STREAMS; i++) {
    zoom_params = &zoom_params_arr[i];
    if (zoom_params->identity == identity) {
      break;
    }
    zoom_params = NULL;
  }

  if ((i >= ISP_MAX_STREAMS) || (!zoom_params)) {
    ISP_ERR("invalid ide %x", identity);
    return FALSE;
  }

  /* Since scaler is present before fov, scale fov region */
  stream_crop->x_map = (float)zoom_params->fov_output.x *
    zoom_params->scaling_ratio;
   stream_crop->y_map= (float)zoom_params->fov_output.y *
    zoom_params->scaling_ratio;
  stream_crop->width_map = (float)zoom_params->fov_output.crop_out_x *
    zoom_params->scaling_ratio;
  stream_crop->height_map = (float)zoom_params->fov_output.crop_out_y *
    zoom_params->scaling_ratio;

  /* Validate whether ROI map is within camif output */
  if ((stream_crop->x_map + stream_crop->width_map) >
    (uint32_t)zoom_params->camif_output.width) {
    ISP_ERR("failed: invalid roi map x %d dx %d camif w %d",
      stream_crop->x_map, stream_crop->width_map,
      zoom_params->camif_output.width);
  }

  if ((stream_crop->y_map + stream_crop->height_map) >
    (uint32_t)zoom_params->camif_output.height) {
    ISP_ERR("failed: invalid roi map y %d dy %d camif y %d",
      stream_crop->y_map, stream_crop->height_map,
      zoom_params->camif_output.height);
  }

  ISP_DBG("ide %x map %d %d %d %d", identity, stream_crop->x_map,
    stream_crop->y_map, stream_crop->width_map, stream_crop->height_map);
  return TRUE;
}

typedef struct {
  ISP_ModuleCfg  val;
  ISP_ModuleCfg  mask;
} module_cfg_t;

/** isp_pipeline46_create_module_cfg_mask:
 *
 *  @curr_submod_enable: submodules currently enabled
 *  @input_enable_bit_info: submod mask and submod enable
 *  @cfg: module cfg output
 *
 *  Convert submod mask and enable from enum order to
 *  register order
 *
 *  Return TRUE on success and FALSE on failure
 **/
static boolean isp_pipeline46_create_module_cfg_mask(
  uint8_t *curr_submod_enable,
  isp_module_enable_info_t *input_enable_bit_info,
  module_cfg_t *cfg)
{
  isp_hw_module_id_t module_id;

  if (!input_enable_bit_info || !cfg) {
    ISP_ERR("failed: %p %p", input_enable_bit_info, cfg);
    return FALSE;
  }

#define SET_FIELD(field, value) \
  { \
    cfg->val.field = value; \
    cfg->mask.field |= ~0; \
  }

  for (module_id = 0; module_id < ISP_MOD_MAX_NUM; module_id++) {
    if (input_enable_bit_info->submod_mask[module_id]) {
      uint8_t enable = input_enable_bit_info->submod_enable[module_id];
      switch (module_id) {
      case ISP_MOD_LINEARIZATION:
        SET_FIELD(mod_en.fields.black, enable);
        break;

      case ISP_MOD_HDR:
        /*HDR recon and mac need to enable together
          to work properly*/
        SET_FIELD(mod_en.fields.hdr_recon, enable);
        SET_FIELD(mod_en.fields.hdr_mac, enable);
        break;

      case ISP_MOD_ROLLOFF:
        SET_FIELD(mod_en.fields.rolloff, enable);
        break;

      case ISP_MOD_DEMUX:
        SET_FIELD(mod_en.fields.demux, enable);
        break;

      case ISP_MOD_BCC:
      case ISP_MOD_BPC:
        SET_FIELD(mod_en.fields.bpc,
          curr_submod_enable[ISP_MOD_BCC] ||
          curr_submod_enable[ISP_MOD_BPC]);
        SET_FIELD(bpc_cfg.fields.dbpc_en,
          curr_submod_enable[ISP_MOD_BPC]);
        SET_FIELD(bpc_cfg.fields.dbcc_en,
          curr_submod_enable[ISP_MOD_BCC]);
        break;

      case ISP_MOD_ABF:
        SET_FIELD(mod_en.fields.abf, enable);
        break;

      case ISP_MOD_DEMOSAIC:
        SET_FIELD(mod_en.fields.demosaic, enable);
        break;

      case ISP_MOD_GAMMA:
        SET_FIELD(mod_en.fields.gamma, enable);
        break;

      case ISP_MOD_LTM:
        SET_FIELD(mod_en.fields.ltm, enable);
        break;

      case ISP_MOD_GTM:
        SET_FIELD(mod_en.fields.gtm, enable);
        break;

      case ISP_MOD_GIC:
        SET_FIELD(mod_en.fields.gic, enable);
        break;

      case ISP_MOD_PEDESTAL:
        SET_FIELD(mod_en.fields.pedestal, enable);
        break;

      case ISP_MOD_CHROMA_ENHANCE:
        SET_FIELD(mod_en.fields.chroma_enhan, enable);
        break;

      case ISP_MOD_COLOR_CORRECT:
        SET_FIELD(mod_en.fields.color_correct, enable);
        break;

      case ISP_MOD_WB:
      case ISP_MOD_CLF:
        /* special logic that needs to be placed here instead of in the
         * modules WB and CAC are both residing in the CLF block, which
         * share one enable bit to disable CAC individually, we need to
         * set the WB_ONLY bit in CLF_WB_CFG_1 to disable WB individually,
         * we need to keep unity gain in CLF_WB_CFG_0 and 1; this is the
         * only place where we know whether both or either or neither
         * is enabled */
        SET_FIELD(mod_en.fields.clf,
          (curr_submod_enable[ISP_MOD_WB] ||
           curr_submod_enable[ISP_MOD_CLF]));
        SET_FIELD(wb_cfg.fields.wb_only,
          (curr_submod_enable[ISP_MOD_WB] &&
          !curr_submod_enable[ISP_MOD_CLF]));
        if (!curr_submod_enable[ISP_MOD_WB] &&
             curr_submod_enable[ISP_MOD_CLF]) {
          SET_FIELD(wb_cfg.fields.ch0_gain, FLOAT_TO_Q(7, 1.0f));
          SET_FIELD(wb_cfg.fields.ch1_gain, FLOAT_TO_Q(7, 1.0f));
          SET_FIELD(wb_cfg.fields.ch2_gain, FLOAT_TO_Q(7, 1.0f));
        }
        break;

      case ISP_MOD_CHROMA_SUPPRESS:
      case ISP_MOD_MCE:
        SET_FIELD(mod_en.fields.chroma_suppress,
          curr_submod_enable[ISP_MOD_CHROMA_SUPPRESS] ||
          curr_submod_enable[ISP_MOD_MCE]);
        SET_FIELD(cs_mce_cfg.fields.cs_en,
          curr_submod_enable[ISP_MOD_CHROMA_SUPPRESS]);
        SET_FIELD(cs_mce_cfg.fields.mce_en,
          curr_submod_enable[ISP_MOD_MCE]);
        break;

      case ISP_MOD_SCE:
        SET_FIELD(mod_en.fields.skin_enhan, enable);
        break;

      case ISP_MOD_COLOR_XFORM_VIEWFINDER:
        SET_FIELD(mod_en.fields.color_xform_view, enable);
        break;

      case ISP_MOD_SCALER_VIEWFINDER:
        SET_FIELD(mod_en.fields.scaler_view, enable);
        break;

      case ISP_MOD_FOV_VIEWFINDER:
        SET_FIELD(mod_en.fields.crop_view, enable);
        break;

      case ISP_MOD_COLOR_XFORM_ENCODER:
        SET_FIELD(mod_en.fields.color_xform_enc, enable);
        break;

      case ISP_MOD_SCALER_ENCODER:
        SET_FIELD(mod_en.fields.scaler_enc, enable);
        break;

      case ISP_MOD_FOV_ENCODER:
        SET_FIELD(mod_en.fields.crop_enc, enable);
        break;

      case ISP_MOD_COLOR_XFORM_VIDEO:
        SET_FIELD(mod_en.fields.color_xform_vid, enable);
        break;

      case ISP_MOD_SCALER_VIDEO:
        SET_FIELD(mod_en.fields.scaler_vid, enable);
        break;

      case ISP_MOD_FOV_VIDEO:
        SET_FIELD(mod_en.fields.crop_vid, enable);
        break;

      case ISP_MOD_SKIN_BHIST_STATS:
        SET_FIELD(stats_cfg.fields.bhist_sel, 1);
        break;

      case ISP_MOD_BE_STATS:
      case ISP_MOD_BG_STATS:
      case ISP_MOD_BF_STATS:
      case ISP_MOD_RS_STATS:
      case ISP_MOD_CS_STATS:
      case ISP_MOD_IHIST_STATS:
      case ISP_MOD_BF_SCALE_STATS:
      case ISP_MOD_HDR_BE_STATS:
      case ISP_MOD_HDR_BHIST_STATS:
        /* do nothing for stats, they are
           enabled/disabled in kernel */
        break;

      case ISP_MOD_CLAMP_VIEWFINDER:
      case ISP_MOD_CLAMP_ENCODER:
      case ISP_MOD_CLAMP_VIDEO:
        /* Enabled by default, no specific bit */
        break;

      default:
        ISP_ERR("invalid module id %d", module_id);
        break;
      }
    }
  }

  return TRUE;
}

/** isp_pipeline44_update_module_cfg:
 *
 *  @fd: file descriptor
 *  @enable_bit_info: input enable bit info
 *
 *  Configure module_cfg register to enable submodules
 *
 *  Return TRUE on success and FALSE on failure
 **/
static boolean isp_pipeline46_update_module_cfg(int32_t fd,
  uint8_t *curr_submod_enable,
  isp_module_enable_info_t *enable_bit_info, cam_format_t sensor_fmt)
{
  boolean                     ret = TRUE;
  int32_t                     rc = 0;
  struct msm_vfe_reg_cfg_cmd  reg_cfg_cmd[8];
  module_cfg_t                module_cfg;
  struct msm_vfe_cfg_cmd2     cfg_cmd;

  if ((fd <= 0) || !enable_bit_info) {
    ISP_ERR("failed: fd %d enable_bit_info %p sensor_fmt %d", fd,
      enable_bit_info, sensor_fmt);
    return FALSE;
  }

  memset(&reg_cfg_cmd, 0, (sizeof(reg_cfg_cmd)));
  memset(&module_cfg, 0, sizeof(module_cfg));

  ret = isp_pipeline46_create_module_cfg_mask(curr_submod_enable,
          enable_bit_info, &module_cfg);
  if (ret == FALSE) {
    ISP_ERR("failed: isp_pipeline46_create_module_cfg_mask");
    return FALSE;
  }

  cfg_cmd.cfg_data = (void *)&module_cfg;
  cfg_cmd.cmd_len = sizeof(module_cfg);
  cfg_cmd.cfg_cmd = (void *)&reg_cfg_cmd;
  cfg_cmd.num_cfg = 8;

#define SET_REG_CFG_CMD(index, offset, value) \
  { \
    reg_cfg_cmd[index].cmd_type               = VFE_CFG_MASK; \
    reg_cfg_cmd[index].u.mask_info.reg_offset = offset; \
    reg_cfg_cmd[index].u.mask_info.mask       = module_cfg.mask.value; \
    reg_cfg_cmd[index].u.mask_info.val        = module_cfg.val.value; \
  }

  SET_REG_CFG_CMD(0, ISP_MODULE_LENS_EN_OFFSET,  mod_en.values.lens_en);
  SET_REG_CFG_CMD(1, ISP_MODULE_COLOR_EN_OFFSET, mod_en.values.color_en);
  SET_REG_CFG_CMD(2, ISP_MODULE_ZOOM_EN_OFFSET,  mod_en.values.zoom_en);
  SET_REG_CFG_CMD(3, ISP_WB_CFG0_OFFSET,         wb_cfg.values.wb_cfg_0);
  SET_REG_CFG_CMD(4, ISP_WB_CFG1_OFFSET,         wb_cfg.values.wb_cfg_1);
  SET_REG_CFG_CMD(5, ISP_BPC_CFG_OFFSET,         bpc_cfg.value);
  SET_REG_CFG_CMD(6, ISP_CS_MCE_CFG_OFFSET,      cs_mce_cfg.value);
  SET_REG_CFG_CMD(7, ISP_STATS_CFG_OFFSET,       stats_cfg.value);

  /* Perform ioctl */
  rc = ioctl(fd, VIDIOC_MSM_VFE_REG_CFG, &cfg_cmd);
  if (rc < 0) {
    ISP_ERR("failed: rc %d", rc);
    ret = FALSE;
  }

  return ret;
}

/** isp_pipeline46_open:
 *
 *  @isp_version: ISP version
 *  @isp_id: ISP hw id
 *
 *  Initialize ISP pipeline resources based on isp_version
 *  and isp_id
 *
 *  Return TRUE on success and FALSE on failure
 **/

isp_pipeline_t *isp_pipeline46_open(uint32_t isp_version, uint32_t isp_id)
{
  isp_pipeline_t *curr_pipeline;

  if (isp_id >= ISP_HW_MAX) {
    ISP_ERR("failed: invalid isp id %d", isp_id);
    return NULL;
  }

  curr_pipeline = (isp_pipeline_t *)malloc(sizeof(*curr_pipeline));
  if (!curr_pipeline) {
    ISP_ERR("failed");
    return NULL;
  }
  memcpy(curr_pipeline, &isp_pipeline, sizeof(*curr_pipeline));

  if(isp_version >= ISP_MSM8994_V1) {
    curr_pipeline->isp_version = SET_ISP_VERSION(ISP_VERSION_46, ISP_REVISION_V1);
    curr_pipeline->num_pix = 1;
    curr_pipeline->num_rdi = 3;
    curr_pipeline->num_wms = 7;
    curr_pipeline->num_register = ISP46_NUM_REG_DUMP;
    curr_pipeline->isp_id = isp_id;
    curr_pipeline->is_camif_crop_supported = FALSE;
    curr_pipeline->is_camif_raw_op_fmt_supported = FALSE;

    if (isp_id == ISP_HW_0) {
      curr_pipeline->max_width = 6240;
      curr_pipeline->max_height = 16383;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_ENCODER].max_width = 6240;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_ENCODER].max_height = 16383;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_VIEWFINDER].max_width = 2816;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_VIEWFINDER].max_height = 16383;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_VIDEO].max_width = 4608;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_VIDEO].max_height = 16383;
    } else if (isp_id == ISP_HW_1) {
      curr_pipeline->max_width = 4288;
      curr_pipeline->max_height = 16383;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_ENCODER].max_width = 4288;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_ENCODER].max_height = 16383;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_VIEWFINDER].max_width = 2816;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_VIEWFINDER].max_height = 16383;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_VIDEO].max_width = 4288;
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_VIDEO].max_height = 16383;
    }

    curr_pipeline->hw_stream_info[ISP_HW_STREAM_IDEAL_RAW].max_width =
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_ENCODER].max_width;
    curr_pipeline->hw_stream_info[ISP_HW_STREAM_IDEAL_RAW].max_height =
      curr_pipeline->hw_stream_info[ISP_HW_STREAM_ENCODER].max_height;

    curr_pipeline->max_nominal_pix_clk = ISP_PIX46_CLK_USER_MAX;
    curr_pipeline->max_turbo_pix_clk = ISP_PIX_CLK_600MHZ;

  } else {
    ISP_ERR("failed: invalid isp version %x", isp_version);
    return NULL;
  }

  curr_pipeline->num_stats_comp_grp = 2;
  curr_pipeline->max_scale_ratio = 34;
  curr_pipeline->num_hw_streams = ARRAY_SIZE(stream_hw_params);
  curr_pipeline->hw_stream_ids[ISP_HW_STREAM_ENCODER] = ISP_HW_STREAM_ENCODER;
  curr_pipeline->hw_stream_ids[ISP_HW_STREAM_VIEWFINDER] = ISP_HW_STREAM_VIEWFINDER;
  curr_pipeline->hw_stream_ids[ISP_HW_STREAM_VIDEO] = ISP_HW_STREAM_VIDEO;
  curr_pipeline->pipeline_applying_delay = ISP_MAX_APPLYING_DELAY;

  return curr_pipeline;
}
