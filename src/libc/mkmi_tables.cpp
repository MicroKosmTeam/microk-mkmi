#include <mkmi.h>

void PrintTableList(TableListElement *list, size_t elements) {
	for (size_t i = 0; i < elements; i++) {
		char tableSig[5] = { '\0' };
		Memcpy(tableSig, list[i].Signature, 4);

		MKMI_Printf("Table:\r\n"
			    " Signature:                  %s\r\n"
			    " Pointer:                    0x%x\r\n",
			    tableSig, list[i].TablePointer);

		if(list[i].TablePointer != 0) {
			TableHeader *table = (TableHeader*)list[i].TablePointer;
			MKMI_Printf("%s:\r\n"
				    " Signature:                  %s\r\n"
				    " Revision:                   0x%x\r\n"
				    " Cheksum:                    0x%x\r\n",
				    tableSig, tableSig, table->Revision, table->Checksum);

			if(Strcmp(tableSig, "KBST") == 0) {
				KBST *kbst = (KBST*)table;
				MKMI_Printf(" Memory:\r\n"
					    "  Free physical memory:       %dkb\r\n"
					    "  Used physical memory:       %dkb\r\n"
					    "  Reserved physical memory:   %dkb\r\n",
					    kbst->FreePhysicalMemory / 1024, kbst->UsedPhysicalMemory / 1024, kbst->ReservedPhysicalMemory / 1024);
			} else if (Strcmp(tableSig, "BFST") == 0) {
				BFST *bfst = (BFST*)table;
				MKMI_Printf(" Files:\r\n"
					    "  File count:                 %d\r\n",
					    bfst->NumberOfFiles);

				for(size_t file = 0; file < bfst->NumberOfFiles; ++file) {
					MKMI_Printf("  File:\r\n"
						    "   Address:                   0x%x\r\n"
						    "   Size:                      %dkb\r\n"
						    "   Path:                      %s\r\n"
						    "   Cmdline:                   %s\r\n",
						    bfst->Files[file].Address,
						    bfst->Files[file].Size / 1024,
						    bfst->Files[file].Path,
						    bfst->Files[file].Cmdline
						    );
				}

			}
		}
	}
}

void PrintUserTCB() {
	UserTCB *userTCB = (UserTCB*)0x7fffffffe000;
	char sig[5] = { '\0' };
	Memcpy(sig, userTCB->Signature, 4);

	MKMI_Printf("User TCB:\r\n"
		    " Signature:                  %s\r\n"
		    " Revision:                   0x%x\r\n"
		    " Cheksum:                    0x%x\r\n"
		    " System tables:              0x%x\r\n"
		    " System table list offset:   0x%x\r\n"
		    " Service tables:             0x%x\r\n"
		    " Service table list offset:  0x%x\r\n",
		    sig, userTCB->Revision, userTCB->Checksum, userTCB->SystemTables, userTCB->SystemTableListOffset, userTCB->ServiceTables, userTCB->ServiceTableListOffset);

	MKMI_Printf(" System table list:\r\n");
	PrintTableList((TableListElement*)((uintptr_t)userTCB + userTCB->SystemTableListOffset), userTCB->SystemTables);

	MKMI_Printf(" Service table list:\r\n");
	PrintTableList((TableListElement*)((uintptr_t)userTCB + userTCB->ServiceTableListOffset), userTCB->ServiceTables);

}


UserTCB *GetUserTCB() {
	return (UserTCB*)0x7fffffffe000;
}

TableListElement *GetSystemTableList(UserTCB *userTCB) {
	if(userTCB == NULL) return NULL;

	return (TableListElement*)((uintptr_t)userTCB + userTCB->SystemTableListOffset);
}

TableListElement *GetServiceTableList(UserTCB *userTCB) {
	if(userTCB == NULL) return NULL;

	return (TableListElement*)((uintptr_t)userTCB + userTCB->ServiceTableListOffset);
}

TableHeader *GetTableWithSignature(TableListElement *list, uint8_t elements, const char *signature) {
	if(list == NULL || signature == NULL || elements == 0) return NULL;

	for (size_t i = 0; i < elements; i++) {
		if(list[i].TablePointer != 0 && Memcmp(list[i].Signature, signature, 4) == 0) {
			return (TableHeader*)list[i].TablePointer;
		}
	}

	return NULL;
}

BootFile *GetFileFromBFST(BFST *bfst, const char *path) {
	if(bfst == NULL || path == NULL) return NULL;

	for(size_t file = 0; file < bfst->NumberOfFiles; ++file) {
		if(Strcmp(bfst->Files[file].Path, path) == 0) {
			return &bfst->Files[file];
		}
	}
	
	return NULL;
}
