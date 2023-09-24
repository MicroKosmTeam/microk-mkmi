#pragma once
#include <stdint.h>
#include <stddef.h>

struct TableHeader {
	uint8_t Signature[4];
	uint8_t Revision;

	uint8_t Checksum;
}__attribute__((packed));

struct UserTCB : public TableHeader {
	uint8_t SystemTables;
	uint32_t SystemTableListOffset;

	uint8_t ServiceTables;
	uint32_t ServiceTableListOffset;
}__attribute__((packed));

struct TableListElement {
	uint8_t Signature[4];
	uintptr_t TablePointer;
}__attribute__((packed));

struct KBST : public TableHeader {
	size_t FreePhysicalMemory;
	size_t UsedPhysicalMemory;
	size_t ReservedPhysicalMemory;
}__attribute__((packed));

struct BootFile {
	uintptr_t Address;
	size_t Size;
	char Path[256];
	char Cmdline[256];
}__attribute__((packed));

struct BFST: public TableHeader {
	size_t NumberOfFiles;
	BootFile Files[];
}__attribute__((packed));


void PrintTableList(TableListElement *list, size_t elements);
void PrintUserTCB();

UserTCB *GetUserTCB();
TableListElement *GetSystemTableList(UserTCB *userTCB);
TableListElement *GetServiceTableList(UserTCB *userTCB);
TableHeader *GetTableWithSignature(TableListElement *list, uint8_t elements, const char *signature);
BootFile *GetFileFromBFST(BFST *bfst, const char *path);