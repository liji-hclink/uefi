/** @file

  Copyright 2017 NXP 

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __USB_HCD__
#define __USB_HCD__

#include <Bitops.h>
#include <Uefi.h>

#define NUM_OF_USB_CONTROLLERS                 2

/* Global constants */
#define USB_ENDPOINTS_NUM                     32

#define USB_EVENT_BUFFERS_SIZE                PAGE_SIZE
#define USB_EVENT_TYPE_MASK                   0xfe

#define USB_EVENT_TYPE_DEV                    0
#define USB_EVENT_TYPE_CARKIT                 3
#define USB_EVENT_TYPE_I2C                    4

#define USB_DEVICE_EVENT_DISCONNECT           0
#define USB_DEVICE_EVENT_RESET                1
#define USB_DEVICE_EVENT_CONNECT_DONE         2
#define USB_DEVICE_EVENT_LINK_STATUS_CHANGE   3
#define USB_DEVICE_EVENT_WAKEUP               4
#define USB_DEVICE_EVENT_EOPF                 6
#define USB_DEVICE_EVENT_SOF                  7
#define USB_DEVICE_EVENT_ERRATIC_ERROR        9
#define USB_DEVICE_EVENT_CMD_CMPL             10
#define USB_DEVICE_EVENT_OVERFLOW             11

#define USB_GEVNTCOUNT_MASK                   0xfffc
#define USB_GSNPSID_MASK                      0xffff0000
#define USB_GSNPSID_SHIFT                     16
#define USB_GSNPSREV_MASK                     0xffff

#define USB_REVISION_MASK                     0xffff

#define USB_REG_OFFSET                        0xC100
/* Global Configuration Register */
#define USB_GCTL_PWRDNSCALE(n)                ((n) << 19)
#define USB_GCTL_U2RSTECN                     BIT(16)
#define USB_GCTL_RAMCLKSEL(x)                 (((x) & USB_GCTL_CLK_MASK) << 6)
#define USB_GCTL_CLK_BUS                      (0)
#define USB_GCTL_CLK_PIPE                     (1)
#define USB_GCTL_CLK_PIPEHALF                 (2)
#define USB_GCTL_CLK_MASK                     (3)
#define USB_GCTL_PRTCAP(n)                    (((n) & (3 << 12)) >> 12)
#define USB_GCTL_PRTCAPDIR(n)                 ((n) << 12)
#define USB_GCTL_PRTCAP_HOST                  1
#define USB_GCTL_PRTCAP_DEVICE                2
#define USB_GCTL_PRTCAP_OTG                   3
#define USB_GCTL_CORESOFTRESET                BIT(11)
#define USB_GCTL_SCALEDOWN(n)                 ((n) << 4)
#define USB_GCTL_SCALEDOWN_MASK               USB_GCTL_SCALEDOWN(3)
#define USB_GCTL_DISSCRAMBLE                  BIT(3)
#define USB_GCTL_DSBLCLKGTNG                  BIT(0)

/* Global HWPARAMS1 Register */
#define USB_GHWPARAMS1_EN_PWROPT(n)           (((n) & (3 << 24)) >> 24)
#define USB_GHWPARAMS1_EN_PWROPT_NO           0
#define USB_GHWPARAMS1_EN_PWROPT_CLK          1

/* Global USB2 PHY Configuration Register */
#define USB_GUSB2PHYCFG_PHYSOFTRST            BIT(31)
#define USB_GUSB2PHYCFG_SUSPHY                BIT(6)
/* Global USB3 PIPE Control Register */
#define USB_GUSB3PIPECTL_PHYSOFTRST           BIT(31)
#define USB_GUSB3PIPECTL_DISRXDETP3           BIT(28)
#define USB_GUSB3PIPECTL_SUSPHY               BIT(17)

/* Global TX Fifo Size Register */
#define USB_GTXFIFOSIZ_TXFDEF(n)              ((n) & 0xffff)
#define USB_GTXFIFOSIZ_TXFSTADDR(n)           ((n) & 0xffff0000)

/* Device Control Register */
#define USB_DCTL_RUN_STOP                     BIT(31)
#define USB_DCTL_CSFTRST                      BIT(30)
#define USB_DCTL_LSFTRST                      BIT(29)

/* Global Frame Length Adjustment Register */
#define GFLADJ_30MHZ_REG_SEL                   BIT(7)
#define GFLADJ_30MHZ(n)                        ((n) & 0x3f)
#define GFLADJ_30MHZ_DEFAULT                   0x20

/* Default to the FSL XHCI defines */
#define USB_ENABLE_BEAT_BURST                 0xF
#define USB_ENABLE_BEAT_BURST_MASK            0xFF
#define USB_SET_BEAT_BURST_LIMIT              0xF00

typedef struct {
  UINT32 GEvntadrlo;
  UINT32 GEvntadrhi;
  UINT32 GEvntsiz;
  UINT32 GEvntcount;
 } GEventBuffer;

typedef struct {
  UINT32 DDepcmdpar2;
  UINT32 DDepcmdpar1;
  UINT32 DDepcmdpar0;
  UINT32 DDepcmd;
 } DPhysicalEndpoint;

typedef struct { 
  UINT32 GSbuscfg0;
  UINT32 GSbuscfg1;
  UINT32 GTxthrcfg;
  UINT32 GRxthrcfg;
  UINT32 GCtl;
  UINT32 Res1;
  UINT32 GSts;
  UINT32 Res2;
  UINT32 GSnpsid;
  UINT32 GGpio;
  UINT32 GUid;
  UINT32 GUctl;
  UINT64 GBuserraddr;
  UINT64 GPrtbimap;
  UINT32 GHwparams0;
  UINT32 GHwparams1;
  UINT32 GHwparams2;
  UINT32 GHwparams3;
  UINT32 GHwparams4;
  UINT32 GHwparams5;
  UINT32 GHwparams6;
  UINT32 GHwparams7;
  UINT32 GDbgfifospace;
  UINT32 GDbgltssm;
  UINT32 GDbglnmcc;
  UINT32 GDbgbmu;
  UINT32 GDbglspmux;
  UINT32 GDbglsp;
  UINT32 GDbgepinfo0;
  UINT32 GDbgepinfo1;
  UINT64 GPrtbimapHs;
  UINT64 GPrtbimapFs;
  UINT32 Res3[28];
  UINT32 GUsb2phycfg[16];
  UINT32 GUsb2i2cctl[16];
  UINT32 GUsb2phyacc[16];
  UINT32 GUsb3pipectl[16];
  UINT32 GTxfifosiz[32];
  UINT32 GRxfifosiz[32];
  GEventBuffer GEvntBuf[32];
  UINT32 GHwparams8;
  UINT32 Res4[11];
  UINT32 GFLAdj;
  UINT32 Res5[51];
  UINT32 DCfg;
  UINT32 DCtl;
  UINT32 DEvten;
  UINT32 DSts;
  UINT32 DGcmdpar;
  UINT32 DGcmd;
  UINT32 Res6[2];
  UINT32 DAlepena;
  UINT32 Res7[55];
  DPhysicalEndpoint DPhyEpCmd[32];
  UINT32 Res8[128];
  UINT32 OCfg;
  UINT32 OCtl;
  UINT32 OEvt;
  UINT32 OEvten;
  UINT32 OSts;
  UINT32 Res9[3];
  UINT32 AdpCfg;
  UINT32 AdpCtl;
  UINT32 AdpEvt;
  UINT32 AdpEvten;
  UINT32 BcCfg;
  UINT32 Res10;
  UINT32 BcEvt;
  UINT32 BcEvten;
 } Dwc3;

EFI_STATUS
EFIAPI
InitializeUsbController (
  IN  UINTN  UsbReg
  );

#endif