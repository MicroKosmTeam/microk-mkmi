/*
   File: include/mkmi/mkmi_module.hpp

   MKMI module manager
*/

#pragma once
#include <stdint.h>
#include <mkmi_version.h>

struct MKMI_Module {
	/* Mandatory data */
	char     *Name;            /* Module literal name */
	uint64_t Codename;         /* Module codename (unique per each writer) */
	/* If conflicting codenames are found, bad things will happen */
	char     *Author;          /* Author's name (literal) */
	uint64_t Writer;           /* Person or organization that wrote the module (codename) */

	/* Mandatory functions */
	uint64_t (*InitFunction)();
	void     (*DeinitFunction)();
	uint64_t (*RequestOperator)();

	/* Optional data */
	/* Versioning info: if not included, any version is accepted */
	MKMI_VersionInfo MinimumVersion; /* Minimum MKMI version accepted */
	MKMI_VersionInfo MaximumVersion; /* Maximum MKMI version accepted */

	/* Optional functions */

	/* Debug data */

	/* Debug functions */
};
