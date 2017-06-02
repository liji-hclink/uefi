#/** LS1046A board package.
#
#    Copyright (c) 2015, Freescale Semiconductor, Inc. All rights reserved.
#
#    This program and the accompanying materials
#    are licensed and made available under the terms and conditions of the BSD License
#    which accompanies this distribution. The full text of the license may be found at
#    http://opensource.org/licenses/bsd-license.php
#
#    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#**/

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = LS1046aRdbPkg
  PLATFORM_GUID                  = 60169ec4-d2b4-44f8-825e-f8684fd42e4f
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/LS1046aRdb
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = LS1046aRdbPkg/LS1046aRdbPkgNonXipBoot.fdf


!include LS1046aRdbPkg.dsc

[Components.common]
!if $(SD_BOOT_ENABLE) == TRUE
  LS1046aRdbPkg/Library/LS1046aPrePiOcram/LS1046aPrePiSd.inf
!endif
!if $(NAND_BOOT_ENABLE) == TRUE
  LS1046aRdbPkg/Library/LS1046aPrePiOcram/LS1046aPrePiNand.inf
!endif
[PcdsFixedAtBuild.common]

!if $(SD_BOOT_ENABLE) == TRUE
  gLS1046aRdbTokenSpaceGuid.PcdFdSdxcLba|0x108
  gLS1046aRdbTokenSpaceGuid.PcdBootMode|0x2
  gLS1046aRdbTokenSpaceGuid.PcdPpaSdxcLba|0x1108
!endif
!if $(NAND_BOOT_ENABLE) == TRUE
  gLS1046aRdbTokenSpaceGuid.PcdFdNandLba|0x1
  gLS1046aRdbTokenSpaceGuid.PcdBootMode|0x1
  gLS1046aRdbTokenSpaceGuid.PcdPpaNandLba|0x10
!endif
