/*
   File: include/mkmi/mkmi_module.hpp

   MKMI module manager
*/

#pragma once
#include <stdint.h>
#include <mkmi_version.hpp>

namespace MKMI {
	struct Module {
		/* Mandatory data */
		char     *Name;            /* Module literal name */
		uint64_t Codename;         /* Module codename (unique per each writer) */
		                           /* If conflicting codenames are found, bad things will happen */
		char     *Author;          /* Author's name (literal) */
		uint64_t Writer;           /* Person or organization that wrote the module (codename) */

		/* Mandatory functions */
		uint64_t (*EntryFunction)();
		uint64_t (*RequestFunction)(uint64_t request, va_list ap);
		void     (*ExitFunction)();

		/* Optional data */
		/* Versioning info: if not included, any version is accepted */
		VersionInfo MinimumVersion; /* Minimum MKMI version accepted */
		VersionInfo MaximumVersion; /* Minimum MKMI version accepted */

		/* Optional functions */

		/* Debug data */

		/* Debug functions */
	};

	void LoadModule();
	void UnloadModule();
}
