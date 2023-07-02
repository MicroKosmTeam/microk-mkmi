/*
   File: include/mkmi/mkmi_version.h

   MKMI version struct
*/

#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MKMI_VersionInfo {
	uint16_t Major;      /* Major version: API incompatibility */
	uint16_t Minor;      /* Minor version: ABI incompatibility */
	uint16_t Feature;    /* Feature version: New feature or major bugfix */
	uint16_t Patch;      /* Patch version: Minor bugfix */
}__attribute__((packed));

extern const MKMI_VersionInfo MKMI_CurrentVersion;

#ifdef __cplusplus
}
#endif
