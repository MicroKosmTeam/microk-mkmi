/*
   File: include/mkmi/mkmi_module.h

   MKMI module manager
*/

#pragma once
#include <stdint.h>
#include <mkmi_version.h>
#include <mkmi_buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MKMI_ModuleID {
	char     *Name;            /* Module literal name */
	char     *Author;          /* Author's name (literal) */

	uint64_t Codename;         /* Module codename (unique per each writer) */
	uint64_t Writer;           /* Person or organization that wrote the module (codename) */
};

struct MKMI_Module {
	/* Module ID: basic module information */
	MKMI_ModuleID ID;
	/* Module version: current version */
	MKMI_VersionInfo Version;
	
	/* All functions: */
	size_t (*OnInterrupt)();
	size_t (*OnMessage)();

	/* Versioning info: if not included, any version is accepted */
	MKMI_VersionInfo MinimumVersion; /* Minimum MKMI version accepted */
	MKMI_VersionInfo MaximumVersion; /* Maximum MKMI version accepted */
};

#ifdef __cplusplus
}
#endif
