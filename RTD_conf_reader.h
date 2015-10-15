/* 

     rtd_conf_reader.h - A bunch of C macros to facilitate reading ASCII .conf files.
                         Ripped from my own ascii_conf_reader.h

     Author: Spencer M. Hatch
             Dartmouth College

     Date  : 2015/10/07
*/


#ifndef __RTD_CONF_READER__
#define __RTD_CONF_READER__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "RTD_conf_structs.h"

#define  RTD_DEF_STRING_SIZE    1024
#define  RTD_CONF_DEBUG            1  /*Turn on debug to see what is read from the ASCII config file*/

int iInitRTDConfigFromASCII(const char * szRTDConfFile, struct suRTDConfig * psuRTDConfig, uint8_t bDebug );
void vInitRTDConfigArrays(struct suRTDConfig * psuRTDConfig);
int iRTDFree(struct suRTDConfig * psuRTDConfig);
char * trimwhitespace(char * str);


/* MACROS FOR READING SINGLE VARIABLES */
#define READ_BOOL_TO_STRUCT(pattern,pStruct,bField)			\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
        {								\
	int             iTokens;					\
	int16_t         iTemp;						\
									\
	iTokens = sscanf(szDataItemTrimmed, "%" PRIu16, &iTemp);	\
	if (iTokens == 1)						\
	    {								\
	    iTemp = atoi(szDataItemTrimmed);		                \
	    if ( iTemp > 0 )						\
		pStruct->bField = iTemp;				\
	    else							\
		pStruct->bField = 0;					\
	    if (RTD_CONF_DEBUG) printf("%s: %" PRIu8"\n",#pattern,pStruct->bField); \
	    }								\
	else								\
	    assert(0);							\
	}

#define READ_UINT_TO_STRUCT(pattern,pStruct,uField)			\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
        {								\
	int             iTokens;					\
	uint16_t        uTemp;						\
									\
	iTokens = sscanf(szDataItemTrimmed, "%" PRIu16, &uTemp);		\
	if (iTokens == 1)						\
	    {								\
	    pStruct->uField = strtoul(szDataItemTrimmed,NULL,10);	\
	    if (RTD_CONF_DEBUG) printf("%s: %" PRIu16"\n",#pattern,pStruct->uField); \
	    }								\
	else								\
	    assert(0);							\
	}

#define READ_ULL_TO_STRUCT(pattern,pStruct,ullField)			\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
        {								\
	int             iTokens;					\
	uint64_t        ullTemp;					\
									\
	iTokens = sscanf(szDataItem, "%" PRIu64, &ullTemp);		\
	if (iTokens == 1)						\
	    {								\
	    pStruct->ullField = strtoull(szDataItemTrimmed,NULL,10);    \
	    if (RTD_CONF_DEBUG) printf("%s: %" PRIu64"\n",#pattern,pStruct->ullField); \
	    }								\
	else								\
	    assert(0);							\
	}

#define READ_INT_TO_STRUCT(pattern,pStruct,iField)			\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
        {								\
	int             iTokens;					\
	int             iTemp;						\
									\
	iTokens = sscanf(szDataItem, "%i", &iTemp);			\
	if (iTokens == 1)						\
	    {								\
	    pStruct->iField = atoi(szDataItemTrimmed);			        \
	    if (RTD_CONF_DEBUG) printf("%s: %i\n",#pattern,pStruct->iField);	\
	    }								\
	else								\
	    assert(0);							\
	}

#define READ_LL_TO_STRUCT(pattern,pStruct,llField)			\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
        {								\
	int             iTokens;					\
	int64_t         llTemp;						\
									\
	iTokens = sscanf(szDataItem, "%" PRIi64, &llTemp);		\
	if (iTokens == 1)						\
	    {								\
	    pStruct->llField = atoll(szDataItemTrimmed);		\
	    if (RTD_CONF_DEBUG) printf("%s: %" PRIi64"\n",#pattern,pStruct->llField); \
	    }								\
	else								\
	    assert(0);						\
	}

#define READ_STR_TO_STRUCT(pattern,pStruct,szField)			\
    else if (strcasecmp(szCodeNameTrimmed, #pattern) == 0)		\
        {								\
	strcpy(pStruct->szField, szDataItemTrimmed);			\
	if (RTD_CONF_DEBUG) printf("%s: %s\n",#pattern,pStruct->szField);	\
        }


/* MACROS FOR ARRAY READING */
#define READ_UINT_ARR_TO_STRUCT(pattern,pStruct,pauField,nArrElem)	\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
	{								\
	char     *  szSubLine;						\
	char     *  szTrimmed;						\
	int         iCnt;						\
									\
	szSubLine = (char * )malloc(bufsize*sizeof(char));		\
	iCnt = 0;							\
									\
	while ( ( getline(&szSubLine,(size_t *)&bufsize,psuRTDConfFile) ) != -1 ) \
	    {								\
		if ( isspace(szSubLine[0]) || ( szSubLine[0] == '#' ) )	\
		    continue;						\
		else if ( szSubLine[0] == ';' )				\
		    {							\
		    if ( iCnt == 0 ) /*init to zero*/			\
			{						\
			for ( iCnt = 0; iCnt < nArrElem; iCnt++ )	\
			    {						\
				pStruct->pauField[iCnt] = 0;		\
			    }						\
			printf("Initialized %s->%s to zeros...\n",#pStruct,#pauField); \
			}						\
		    if (RTD_CONF_DEBUG) printf("\nLeaving UINT loop w/ count %i...\n\n",iCnt); \
		    break;						\
		    }							\
		else							\
		    {							\
		    szTrimmed = trimwhitespace(szSubLine);		\
		    if (RTD_CONF_DEBUG) printf("%s, ",szTrimmed);	\
		    pStruct->pauField[iCnt++] = (uint16_t) strtoul(szTrimmed,NULL,10); \
		    }							\
	    }								\
	}

#define READ_UL_ARR_TO_STRUCT(pattern,pStruct,paulField,nArrElem)	\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
	{								\
	char     *  szSubLine;						\
	char     *  szTrimmed;						\
	int         iCnt;						\
									\
	szSubLine = (char * )malloc(bufsize*sizeof(char));		\
	iCnt = 0;							\
									\
	while ( ( getline(&szSubLine,(size_t *)&bufsize,psuRTDConfFile) ) != -1 ) \
	    {								\
		if ( isspace(szSubLine[0]) || ( szSubLine[0] == '#' ) )	\
		    continue;						\
		else if ( szSubLine[0] == ';' )				\
		    {							\
		    if (RTD_CONF_DEBUG) printf("\nLeaving UL loop w/ count %i...\n\n",iCnt); \
		    break;						\
		    }							\
		else							\
		    {							\
		    szTrimmed = trimwhitespace(szSubLine);		\
		    if (RTD_CONF_DEBUG) printf("%s, ",szTrimmed);		\
		    pStruct->paulField[iCnt++] = strtoul(szTrimmed,NULL,10); \
		    }							\
	    }								\
	}

#define READ_ULL_ARR_TO_STRUCT(pattern,pStruct,paullField,nArrElem)	\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
	{								\
	char     *  szSubLine;						\
	char     *  szTrimmed;						\
	int         iCnt;						\
									\
	szSubLine = (char * )malloc(bufsize*sizeof(char));		\
	iCnt = 0;							\
									\
	while ( ( getline(&szSubLine,(size_t *)&bufsize,psuRTDConfFile) ) != -1 ) \
	    {								\
		if ( isspace(szSubLine[0]) || ( szSubLine[0] == '#' ) )	\
		    continue;						\
		else if ( szSubLine[0] == ';' )				\
		    {							\
		    if (RTD_CONF_DEBUG) printf("\nLeaving ULL loop w/ count %i...\n\n",iCnt); \
		    break;						\
		    }							\
		else							\
		    {							\
		    szTrimmed = trimwhitespace(szSubLine);		\
		    if (RTD_CONF_DEBUG) printf("%s, ",szTrimmed);		\
		    pStruct->paullField[iCnt++] = strtoull(szTrimmed,NULL,10); \
		    }							\
	    }								\
	}

#define READ_STR_ARR_TO_STRUCT(pattern,pStruct,pszField,nArrElem)	\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
	{								\
	char     *  szSubLine;						\
	char     *  szTrimmed;						\
	int         iCnt;						\
									\
	szSubLine = (char * )malloc(bufsize*sizeof(char));		\
	iCnt = 0;							\
									\
	while ( ( getline(&szSubLine,(size_t *)&bufsize,psuRTDConfFile) ) != -1 ) \
	    {								\
		if ( isspace(szSubLine[0]) || ( szSubLine[0] == '#' ) )	\
		    continue;						\
		else if ( szSubLine[0] == ';' )				\
		    {							\
		    if (RTD_CONF_DEBUG) printf("\nLeaving STR loop w/ count %i...\n\n",iCnt); \
		    break;						\
		    }							\
		else							\
		    {							\
		    szTrimmed = trimwhitespace(szSubLine);		\
		    if (RTD_CONF_DEBUG) printf("%s, ",szTrimmed);		\
		    strncpy(pStruct->pszField[iCnt++],szTrimmed,strlen(szTrimmed)); \
		    }							\
	    }								\
	}

#define READ_TWO_ELEM_UINT_ARR_TO_STRUCT(pattern,pStruct,pau2Field,nArrElem)	\
    else if ( strncasecmp(szCodeNameTrimmed, #pattern, strlen(#pattern)) == 0 ) \
	{								\
	char     *  szSubLine;						\
	char     *  szTrimmed;						\
	int         iCnt;						\
									\
	char     *  szItem1;						\
	char     *  szItem2;						\
	uint16_t    uItem1;						\
	uint16_t    uItem2;						\
									\
	szSubLine = (char * )malloc(bufsize*sizeof(char));		\
	iCnt   = 0;							\
	uItem1 = 0;							\
	uItem2 = 0;							\
									\
	while ( ( getline(&szSubLine,(size_t *)&bufsize,psuRTDConfFile) ) != -1 ) \
	    {								\
	    if ( isspace(szSubLine[0]) || ( szSubLine[0] == '#' ) )	\
		continue;						\
	    else if ( szSubLine[0] == ';' )				\
		{							\
		    if ( iCnt == 0 ) /*init to zero*/			\
			{						\
			int iCnt;					\
			for ( iCnt = 0; iCnt < nArrElem; iCnt++ )	\
			    {						\
				pStruct->pau2Field[iCnt][0] = 0;	\
				pStruct->pau2Field[iCnt][1] = 0;	\
			    }						\
			printf("Initialized %s->%s to zeros...\n",#pStruct,#pau2Field); \
			}						\
		if (RTD_CONF_DEBUG) printf("\nLeaving UINT loop w/ count %i...\n\n",iCnt); \
		break;							\
		}							\
	    else							\
		{							\
		szItem1 = strtok(szSubLine, ",");			\
		szItem2 = strtok(NULL, "\n");				\
									\
		if ( ( szItem1 != NULL ) && ( szItem2 != NULL ) )	\
		    {							\
		    pStruct->pau2Field[iCnt][0] = strtoul(szItem1,NULL,10); \
		    pStruct->pau2Field[iCnt][1] = strtoul(szItem2,NULL,10); \
		    iCnt++;						\
		    if (RTD_CONF_DEBUG) printf("szItem1: %s; szItem2: %s\t",szItem1,szItem2); \
		    }							\
		}							\
	    }								\
	}

#endif //end #ifndef __RTD_CONF_READER__
