/*
*******************************************************************************
*
* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
*
*******************************************************************************
*/

/*
*******************************************************************************
*
* IMPORTANT NOTE:
*  This file is AUTO-GENERATED by Vision SDK use case generation tool
*
*******************************************************************************
*/

#ifndef _chains_networkRxCameraAnalytics_tda2xx_H_
#define _chains_networkRxCameraAnalytics_tda2xx_H_

#include <include/link_api/system.h>
#include <include/link_api/nullSrcLink.h>
#include <include/link_api/decLink.h>
#include <include/link_api/dupLink.h>
#include <include/link_api/algorithmLink_sparseOpticalFlow.h>
#include <include/link_api/algorithmLink_sparseOpticalFlowDraw.h>
#include <include/link_api/algorithmLink_laneDetect.h>
#include <include/link_api/algorithmLink_laneDetectDraw.h>
#include <include/link_api/algorithmLink_featurePlaneComputation.h>
#include <include/link_api/algorithmLink_objectDetection.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/algorithmLink_objectDraw.h>
#include <include/link_api/mergeLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/algorithmLink_dmaSwMs.h>
#include <include/link_api/grpxSrcLink.h>
#include <include/link_api/displayLink.h>

typedef struct {
       UInt32    NullSourceLinkID;
       UInt32    IPCOut_A15_0_IPU1_0_0LinkID;
       UInt32    IPCIn_IPU1_0_A15_0_0LinkID;
       UInt32    DecodeLinkID;
       UInt32    Dup_captureLinkID;
       UInt32    IPCOut_IPU1_0_EVE2_4LinkID;
       UInt32    IPCIn_EVE2_IPU1_0_0LinkID;
       UInt32    Alg_SparseOpticalFlowLinkID;
       UInt32    IPCOut_EVE2_A15_0_0LinkID;
       UInt32    IPCIn_A15_0_EVE2_3LinkID;
       UInt32    IPCOut_IPU1_0_A15_0_3LinkID;
       UInt32    IPCIn_A15_0_IPU1_0_2LinkID;
       UInt32    Merge_sofLinkID;
       UInt32    Sync_sofLinkID;
       UInt32    Alg_SparseOpticalFlowDrawLinkID;
       UInt32    IPCOut_A15_0_IPU1_0_2LinkID;
       UInt32    IPCIn_IPU1_0_A15_0_3LinkID;
       UInt32    IPCOut_IPU1_0_DSP2_2LinkID;
       UInt32    IPCIn_DSP2_IPU1_0_0LinkID;
       UInt32    Alg_LaneDetectLinkID;
       UInt32    IPCOut_DSP2_A15_0_0LinkID;
       UInt32    IPCIn_A15_0_DSP2_1LinkID;
       UInt32    IPCOut_IPU1_0_A15_0_1LinkID;
       UInt32    IPCIn_A15_0_IPU1_0_0LinkID;
       UInt32    Merge_ldLinkID;
       UInt32    Sync_ldLinkID;
       UInt32    Alg_LaneDetectDrawLinkID;
       UInt32    IPCOut_A15_0_IPU1_0_1LinkID;
       UInt32    IPCIn_IPU1_0_A15_0_2LinkID;
       UInt32    IPCOut_IPU1_0_EVE1_0LinkID;
       UInt32    IPCIn_EVE1_IPU1_0_0LinkID;
       UInt32    Alg_FeaturePlaneComputationLinkID;
       UInt32    IPCOut_EVE1_DSP1_0LinkID;
       UInt32    IPCIn_DSP1_EVE1_0LinkID;
       UInt32    Alg_ObjectDetectionLinkID;
       UInt32    IPCOut_DSP1_IPU1_0_0LinkID;
       UInt32    IPCIn_IPU1_0_DSP1_1LinkID;
       UInt32    Merge_pd_tsrLinkID;
       UInt32    Sync_pd_tsrLinkID;
       UInt32    Alg_ObjectDrawLinkID;
       UInt32    Merge_algLinkID;
       UInt32    Sync_algLinkID;
       UInt32    Alg_DmaSwMsLinkID;
       UInt32    Display_algLinkID;
       UInt32    GrpxSrcLinkID;
       UInt32    Display_GrpxLinkID;

       NullSrcLink_CreateParams                NullSourcePrm;
       IpcLink_CreateParams                    IPCOut_A15_0_IPU1_0_0Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_A15_0_0Prm;
       DecLink_CreateParams                    DecodePrm;
       DupLink_CreateParams                    Dup_capturePrm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_EVE2_4Prm;
       IpcLink_CreateParams                    IPCIn_EVE2_IPU1_0_0Prm;
       AlgorithmLink_SparseOpticalFlowCreateParams Alg_SparseOpticalFlowPrm;
       IpcLink_CreateParams                    IPCOut_EVE2_A15_0_0Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_EVE2_3Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_A15_0_3Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_IPU1_0_2Prm;
       MergeLink_CreateParams                  Merge_sofPrm;
       SyncLink_CreateParams                   Sync_sofPrm;
       AlgorithmLink_sparseOpticalFlowDrawCreateParams Alg_SparseOpticalFlowDrawPrm;
       IpcLink_CreateParams                    IPCOut_A15_0_IPU1_0_2Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_A15_0_3Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_DSP2_2Prm;
       IpcLink_CreateParams                    IPCIn_DSP2_IPU1_0_0Prm;
       AlgorithmLink_LaneDetectCreateParams    Alg_LaneDetectPrm;
       IpcLink_CreateParams                    IPCOut_DSP2_A15_0_0Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_DSP2_1Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_A15_0_1Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_IPU1_0_0Prm;
       MergeLink_CreateParams                  Merge_ldPrm;
       SyncLink_CreateParams                   Sync_ldPrm;
       AlgorithmLink_LaneDetectDrawCreateParams Alg_LaneDetectDrawPrm;
       IpcLink_CreateParams                    IPCOut_A15_0_IPU1_0_1Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_A15_0_2Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_EVE1_0Prm;
       IpcLink_CreateParams                    IPCIn_EVE1_IPU1_0_0Prm;
       AlgorithmLink_FeaturePlaneComputationCreateParams Alg_FeaturePlaneComputationPrm;
       IpcLink_CreateParams                    IPCOut_EVE1_DSP1_0Prm;
       IpcLink_CreateParams                    IPCIn_DSP1_EVE1_0Prm;
       AlgorithmLink_ObjectDetectionCreateParams Alg_ObjectDetectionPrm;
       IpcLink_CreateParams                    IPCOut_DSP1_IPU1_0_0Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_DSP1_1Prm;
       MergeLink_CreateParams                  Merge_pd_tsrPrm;
       SyncLink_CreateParams                   Sync_pd_tsrPrm;
       AlgorithmLink_ObjectDrawCreateParams    Alg_ObjectDrawPrm;
       MergeLink_CreateParams                  Merge_algPrm;
       SyncLink_CreateParams                   Sync_algPrm;
       AlgorithmLink_DmaSwMsCreateParams       Alg_DmaSwMsPrm;
       DisplayLink_CreateParams                Display_algPrm;
       GrpxSrcLink_CreateParams                GrpxSrcPrm;
       DisplayLink_CreateParams                Display_GrpxPrm;
} chains_networkRxCameraAnalytics_tda2xxObj;

Void chains_networkRxCameraAnalytics_tda2xx_SetLinkId(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Void chains_networkRxCameraAnalytics_tda2xx_ResetLinkPrms(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Void chains_networkRxCameraAnalytics_tda2xx_SetPrms(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Void chains_networkRxCameraAnalytics_tda2xx_ConnectLinks(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Int32 chains_networkRxCameraAnalytics_tda2xx_Create(chains_networkRxCameraAnalytics_tda2xxObj *pObj, Void *appObj);

Int32 chains_networkRxCameraAnalytics_tda2xx_Start(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Int32 chains_networkRxCameraAnalytics_tda2xx_Stop(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Int32 chains_networkRxCameraAnalytics_tda2xx_Delete(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Void chains_networkRxCameraAnalytics_tda2xx_printBufferStatistics(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Void chains_networkRxCameraAnalytics_tda2xx_printStatistics(chains_networkRxCameraAnalytics_tda2xxObj *pObj);

Void chains_networkRxCameraAnalytics_tda2xx_SetAppPrms(chains_networkRxCameraAnalytics_tda2xxObj *pObj, Void *appObj);

#endif /* _chains_networkRxCameraAnalytics_tda2xx_H_ */
