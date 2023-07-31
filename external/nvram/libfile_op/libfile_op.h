/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// FILE_OP driver.
//
#include <stdbool.h>

#ifndef __FILE_OP_H__
#define __FILE_OP_H__

//*****************************************************************************
//
//                          TTT Driver MACRO def
//
//*****************************************************************************

//-------------------------------------
// underlying COM port related defines
//-------------------------------------

//*****************************************************************************
//
//                          FILE_OP Driver data stru def
//
//*****************************************************************************

//*****************************************************************************
//
//                          FILE_OP Driver var def
//
//*****************************************************************************


//*****************************************************************************
//                          FILE_OP Driver General Functions Prototypes
//
//*****************************************************************************
/*
#ifdef _WIN32
#define LOGD(x)
#else
#include <utils/Log.h>
#undef LOG_TAG
#define LOG_TAG "NVBACKUP"
#endif

#define NVBAK_LOG(...) \
    do { \
        LOGD(__VA_ARGS__); \
    } while (0)
*/
#define MAX_NAMESIZE  128
#define DATA_FLAG  (0xfecf)

//#define MaxFileNum   936

typedef struct {
	int NameSize;					//the size of file name
	int FielStartAddr;				//the file offset address in content block
	int Filesize;					//the size of nvram files
	char cFileName[MAX_NAMESIZE];	//the name of nvram file
} File_Title;

//the header in title block
typedef struct {
	short int iApBootNum;			//the numbers of nvram file which will resotre ervery boot in ap side.
	short int iApCleanNum;			//the numbers of nvram file which will resotre when clean boot in ap side .
	short int iMdBootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMdCleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdCoreNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdDataNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//Add for second modem for MT658*
	short int iMd2BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd2CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd2ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//End of Comment
	short int iMd5BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd5CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd5ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iViaNum;                //test for VIA
	int       iFileBufLen;			//the size of file content.
	int       BackupFlag;			//the flag of valid block
} File_Title_Header1;

typedef struct {
	short int iApBootNum;			//the numbers of nvram file which will resotre ervery boot in ap side.
	short int iApCleanNum;			//the numbers of nvram file which will resotre when clean boot in ap side .
	short int iMdBootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMdCleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdCoreNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdDataNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//Add for second modem for MT658*
	short int iMd2BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd2CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd2ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//End of Comment
	short int iMd5BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd5CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd5ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	int       iFileBufLen;			//the size of file content.
	int       BackupFlag;			//the flag of valid block
	short int iViaNum;                //test for VIA
} File_Title_Header2;


typedef struct {
	short int iApBootNum;			//the numbers of nvram file which will resotre ervery boot in ap side.
	short int iApCleanNum;			//the numbers of nvram file which will resotre when clean boot in ap side .
	short int iMdBootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMdCleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdCoreNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdDataNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//Add for second modem for MT658*
	short int iMd2BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd2CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd2ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iViaNum;                //test for VIA
	int       iFileBufLen;			//the size of file content.
	int       BackupFlag;			//the flag of valid block
	//End of Comment
	short int iMd5BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd5CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd5ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
} File_Title_Header3;


typedef struct {
	short int iApBootNum;			//the numbers of nvram file which will resotre ervery boot in ap side.
	short int iApCleanNum;			//the numbers of nvram file which will resotre when clean boot in ap side .
	short int iMdBootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMdCleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdCoreNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdDataNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//Add for second modem for MT658*
	short int iMd2BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd2CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd2ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	int       iFileBufLen;			//the size of file content.
	int       BackupFlag;			//the flag of valid block
	//End of Comment
	short int iMd5BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd5CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd5ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iViaNum;                //test for VIA
} File_Title_Header4;

typedef struct {
	short int iApBootNum;			//the numbers of nvram file which will resotre ervery boot in ap side.
	short int iApCleanNum;			//the numbers of nvram file which will resotre when clean boot in ap side .
	short int iMdBootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMdCleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdCoreNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdDataNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//Add for second modem for MT658*
	short int iMd2BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd2CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd2ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//End of Comment
	short int iMd5BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd5CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd5ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd3BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd3CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd3ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	int       iFileBufLen;			//the size of file content.
	int       BackupFlag;			//the flag of valid block
} File_Title_Header5;

typedef struct {
	short int iApBootNum;			//the numbers of nvram file which will resotre ervery boot in ap side.
	short int iApCleanNum;			//the numbers of nvram file which will resotre when clean boot in ap side .
	short int iMdBootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMdCleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdCoreNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMdDataNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//Add for second modem for MT658*
	short int iMd2BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd2CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd2ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	//End of Comment
	short int iMd3BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd3CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd3ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	int       iFileBufLen;			//the size of file content.
	int       BackupFlag;			//the flag of valid block
	short int iMd5BootNum;			//the numbers of nvram file which will resotre ervery boot in modem side.
	short int iMd5CleanNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
	short int iMd5ImpntNum;			//the numbers of nvram file which will resotre when clean boot in modem side.
} File_Title_Header6;

//the type of nvram file
typedef enum {
	APBOOT = 0,						//resotre ervery boot in ap side.
	APCLN,							//resotre when clean boot in ap side.
	MDBOOT,							//resotre ervery boot in modem side.
	MDCLN,							//resotre when clean boot in modem side.
	MDIMP,
	MDCOR,
	MDDATA,
	//Add for second modem for MT658*
	MD2BOOT,							//resotre ervery boot in modem side.
	MD2CLN,							//resotre when clean boot in modem side.
	MD2IMP,
	//End of Comment
	//LTE support
	MD5BOOT,							//resotre ervery boot in modem side.
	MD5CLN,							//resotre when clean boot in modem side.
	MD5IMP,
	VIA,
	/*Add for C2K modem*/
	MD3BOOT,							//resotre ervery boot in modem side.
	MD3CLN,							//resotre when clean boot in modem side.
	MD3IMP,
	/*Add for C2K modem-End*/
	ALL								//all files
} MetaData;

//#ifndef bool
//#define bool int
//#define false 0
//#define true 1
//#endif

extern char *strDMFileFolderPath;

#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************************
//FUNCTION:
//		FileOp_CreateNVMFolder
//DESCRIPTION:
//		this function is called to create the directory for ap side
//
//PARAMETERS:
//		None
//
//RETURN VALUE:
//		TRUE is success, otherwise is fail
//
//DEPENDENCY:
//		None
//
//GLOBALS AFFECTED
//		None
********************************************************************************/
bool FileOp_CreateNVMFolder(void );


/********************************************************************************
//FUNCTION:
//		RestoreData
//DESCRIPTION:
//		this function is called to read the the information and content of nvram files in binregion and generate
//		the file of title and content
//
//PARAMETERS:
//		None
//
//RETURN VALUE:
//		TRUE is success, otherwise is fail
//
//DEPENDENCY:
//		None
//
//GLOBALS AFFECTED
//		None
********************************************************************************/
bool FileOp_RestoreData(MetaData eRestoreType);

/********************************************************************************
//FUNCTION:
//		BackupData
//DESCRIPTION:
//		this function is called to read the the information and content of nvram files in binregion and generate
//		the file of title and content
//
//PARAMETERS:
//		None
//
//RETURN VALUE:
//		TRUE is success, otherwise is fail
//
//DEPENDENCY:
//		None
//
//GLOBALS AFFECTED
//		None
********************************************************************************/
bool FileOp_BackupData(MetaData eBackupType);

/********************************************************************************
//FUNCTION:
//		BackupAll
//DESCRIPTION:
//		this function is called to backup data from fat2 parittion to bin region
//
//PARAMETERS:
//		None
//
//RETURN VALUE:
//		None
//
//DEPENDENCY:
//		None
//
//GLOBALS AFFECTED
//		None
********************************************************************************/
void FileOp_BackupAll(void );

/********************************************************************************
//FUNCTION:
//		RestoreAll
//DESCRIPTION:
//		this function is called to restore all files from bin region to fat2 partition
//
//PARAMETERS:
//		None
//
//RETURN VALUE:
//		None
//
//DEPENDENCY:
//		None
//
//GLOBALS AFFECTED
//		None
********************************************************************************/
void FileOp_RestoreAll(void );

/********************************************************************************
//FUNCTION:
//		DeleteAll
//DESCRIPTION:
//		this function is called to delete all files in fat2 partition
//
//PARAMETERS:
//		None
//
//RETURN VALUE:
//		None
//
//DEPENDENCY:
//		None
//
//GLOBALS AFFECTED
//		None
********************************************************************************/
void FileOp_DeleteAll(void );

/********************************************************************************
//FUNCTION:
//		DeleteAll
//DESCRIPTION:
//		this function is called to delete all files in fat2 partition
//
//PARAMETERS:
//		None
//
//RETURN VALUE:
//		None
//
//DEPENDENCY:
//		None
//
//GLOBALS AFFECTED
//		None
********************************************************************************/
void FileOp_DeleteRdebData(void );


/********************************************************************************
//FUNCTION:
//		RestoreBootData
//DESCRIPTION:
//		this function is called to restore the APBOOT and MDBOOT file to FAT2 partition from binregion
//
//PARAMETERS:
//		None
//
//RETURN VALUE:
//		None
//
//DEPENDENCY:
//		None
//
//GLOBALS AFFECTED
//		None
********************************************************************************/
void FileOp_RestoreBootData(void );

bool FileOp_BackupAll_NvRam(void);
bool FileOp_RestoreAll_NvRam(void);
bool FileOp_RestoreFromBinRegion(bool bCleanBoot);
bool FileOp_IsSyncWithBinRegion();
bool FileOp_BackupToBinRegion_All();
bool FileOp_RestoreFromBinRegion_ToFile();
bool FileOp_CheckBackUpResult();

bool FileOp_RecoveryData();
bool FileOp_SetCleanBootFlag(bool bSetFlag);
bool FileOp_GetCleanBootFlag(unsigned int * iCleanBootFlag);
bool FileOp_RestoreFromFiles(int eBackupType);
bool FileOp_BackupDataToFiles(int * iFileMask, bool bWorkForBinRegion);
bool FileOp_RestoreData_All(void);
bool FileOp_BackupData_Special(char * buffer, int count , int mode);
bool FileOp_CreateBinRegionBadBlockBitMap();
bool FileOp_CmpBackupFileNum();

bool FileOp_RestoreFromBinRegionForDM();
bool FileOp_BackupToBinRegionForDM();
bool FileOp_BackupToBinRegion_All_Ex(int value);
bool FileOp_BackupToBinRegion_All_Exx(unsigned char *time_value);
#ifdef __cplusplus
}
#endif

#endif /* __FILE_OP_H__ */
