/*
   File: include/mkmi/mkmi_version.hpp

   MKMI version struct
*/

#pragma once
#include <stdint.h>

namespace MKMI {
	struct VersionInfo {
		uint16_t Major;      /* Major version: API incompatibility */
		uint16_t Minor;      /* Minor version: ABI incompatibility */
		uint16_t Feature;    /* Feature version: New feature or major bugfix */
		uint16_t Patch;      /* Patch version: Minor bugfix */
	};

	const VersionInfo currentVersion {
		.Major = 0,
		.Minor = 0,
		.Feature = 0,
		.Patch = 0
	}
}
