#include "RTD_conf_reader.h"
#include "RTD_conf_structs.h"

int iInitRTDConfigFromASCII(const char * szRTDConfFile, struct suRTDConfig * psuRTDConfig, uint8_t bDebug )
{
    int iArgIdx;

    FILE              * psuRTDConfFile;
    char              *  szLine;
    int                  iLineIdx;
    int                  bufsize;
    char              *  szCodeName;
    char              *  szDataItem;

    //*******************
    //Initialize vars
    psuRTDConfig->szName[0]                      ='\0';
    psuRTDConfig->iNMeasurements                 = 0;

    bufsize=1024;

    szLine = (char * )malloc(bufsize*sizeof(char));

    if( szLine == NULL)
    {
        perror("Unable to allocate string buffer\n");
        return EXIT_FAILURE;
    }

    psuRTDConfFile = (FILE *) fopen(szRTDConfFile,"r");
    if (psuRTDConfFile == NULL)
	{
	fprintf(stderr, "Error opening RTD Configuration file! Did you provide one?\n");
	return EXIT_FAILURE;
	}

    //get line from file
    while( ( getline(&szLine,(size_t *)&bufsize,psuRTDConfFile) ) != -1 )
	{
	// If errors reading line then skip over it
	// Also skip comments, which are marked with "#"
	szCodeName = strtok(szLine, ":");
	szDataItem = strtok(NULL, "\n");

	if ( (szCodeName != NULL) && (szDataItem != NULL) && (szCodeName[0] != '#') ) //One-line value
	    {
	    char * szCodeNameTrimmed;
	    char * szDataItemTrimmed;

	    szCodeNameTrimmed = trimwhitespace(szCodeName);
	    szDataItemTrimmed = trimwhitespace(szDataItem);

	    //	    printf("SzCNTrimmed[%i]:szDataItemTrimmed[%i] --- %s : %s\n",(int)strlen(szCodeNameTrimmed),(int)strlen(szDataItemTrimmed),
	    //szCodeNameTrimmed,szDataItemTrimmed);
	    if(0) {}
	    READ_STR_TO_STRUCT(NAME,psuRTDConfig,szName)
	    READ_INT_TO_STRUCT(N_MEASUREMENTS,psuRTDConfig,iNMeasurements)
	    }
	else
	    continue;

	iLineIdx++;
	}

    //With knowledge of num measurements, initialize arrays
    if ( psuRTDConfig->iNMeasurements > 0 )
	{
	vInitRTDConfigArrays(psuRTDConfig);
	}
    else
	{
	printf("Didn't find number of measurements in ASCII file!\n");
	printf("(Should be listed as 'N_MEASUREMENTS:  [n_meas]')\n");
	printf("Exiting...\n");
	return EXIT_FAILURE;
	}

    //Finished reading vals, now read arrays
    rewind(psuRTDConfFile);

    int nMeas;
    nMeas = psuRTDConfig->iNMeasurements;
    while( ( getline(&szLine,(size_t *)&bufsize,psuRTDConfFile) ) != -1 )
	{

	// If errors reading line then skip over it
	// Also skip comments, which are marked with "#"
	szCodeName = strtok(szLine, ":");
	szDataItem = strtok(NULL, "\n");

	if ( (szCodeName != NULL) && (szDataItem == NULL) && (szCodeName[0] != '#' ) && !isspace(szCodeName[0]) ) //One-line value
	    {
	    char * szCodeNameTrimmed;

	    szCodeNameTrimmed = trimwhitespace(szCodeName);
	    if (bDebug) printf("**%s\n",szCodeNameTrimmed);

	    if(0) {}  //For dat macro logic
	    READ_STR_ARR_TO_STRUCT(MEAS_NAME,psuRTDConfig,pszSerialMeasNames,nMeas)
	    READ_STR_ARR_TO_STRUCT(MEAS_ABBREV,psuRTDConfig,pszSerialMeasAbbrev,nMeas)
	    READ_STR_ARR_TO_STRUCT(MEAS_USER,psuRTDConfig,pszUser,nMeas)

            READ_UL_ARR_TO_STRUCT(MEAS_BYTE_RTD_SIZE,psuRTDConfig,paulMeasByteRTDSize,nMeas)
            READ_UINT_ARR_TO_STRUCT(MEAS_DATA_TYPE,psuRTDConfig,pauMeasDataType,nMeas)
            READ_UINT_ARR_TO_STRUCT(MEAS_RTD_UPDATE_RATE,psuRTDConfig,pauMeasUpdateRate,nMeas)

	    READ_UL_ARR_TO_STRUCT(MEAS_SAMPLE_RATE,psuRTDConfig,paulMeasSampleRate,nMeas)
	    READ_UL_ARR_TO_STRUCT(MEAS_MIN_FREQ,psuRTDConfig,paulMeasMinFreq,nMeas)
	    READ_UL_ARR_TO_STRUCT(MEAS_MAX_FREQ,psuRTDConfig,paulMeasMaxFreq,nMeas)
	    }
	}
    
    fclose(psuRTDConfFile);

    return EXIT_SUCCESS;
}

void vInitRTDConfigArrays(struct suRTDConfig * psuRTDConfig)
{

    int nMeas;
    int iMeasIdx;
    int iArgIdx;

    nMeas = psuRTDConfig->iNMeasurements;

    psuRTDConfig->pszSerialMeasNames  = (char **     ) malloc(nMeas*sizeof(char *));
    psuRTDConfig->pszSerialMeasAbbrev = (char **     ) malloc(nMeas*sizeof(char *));
    psuRTDConfig->pszUser             = (char **     ) malloc(nMeas*sizeof(char *));

    for( iMeasIdx = 0; iMeasIdx < nMeas; iMeasIdx++ )
	{
	psuRTDConfig->pszSerialMeasNames[iMeasIdx]       = (char *     ) malloc(RTD_DEF_STRING_SIZE*sizeof(char));
	psuRTDConfig->pszSerialMeasAbbrev[iMeasIdx]      = (char *     ) malloc(RTD_DEF_STRING_SIZE*sizeof(char));
	psuRTDConfig->pszUser[iMeasIdx]                  = (char *     ) malloc(RTD_DEF_STRING_SIZE*sizeof(char));
	}

    psuRTDConfig->paulMeasByteRTDSize = (uint32_t *  ) malloc(nMeas*sizeof(uint32_t));
    psuRTDConfig->pauMeasDataType     = (uint16_t *  ) malloc(nMeas*sizeof(uint16_t));
    psuRTDConfig->pauMeasUpdateRate   = (uint16_t *  ) malloc(nMeas*sizeof(uint16_t));
    
    psuRTDConfig->paulMeasSampleRate   = (uint32_t *  ) malloc(nMeas*sizeof(uint32_t));
    psuRTDConfig->paulMeasMinFreq      = (uint32_t *  ) malloc(nMeas*sizeof(uint32_t));
    psuRTDConfig->paulMeasMaxFreq      = (uint32_t *  ) malloc(nMeas*sizeof(uint32_t));

}

/* int iInitMeasurementFromASCII(struct suRTDConfig * psuRTDConfig, int16_t iMeasIdx,char * szOutPrefix,  */
/* 			      uint8_t bCombineMSBLSBMeas, uint8_t bDoCheckSFIDIncrement, uint8_t bTStampMode ) */
/* { */
/*     size_t   szTempLen; */
/*     size_t   szAbbrevLen; */

/*     int iTmpIdx; */

/*     psuMeasInfo->szAbbrev[0]         = '\0'; */
/*     psuMeasInfo->szOutFile[0]        = '\0'; */
/*     psuMeasInfo->szTStampFile[0]     = '\0'; */

/*     psuMeasInfo->llSampIdx           =  0; */
/*     psuMeasInfo->llTotalSampCount    =  0; */
/*     psuMeasInfo->llPCMWdOffset_TSSW  = -1;       //In any case, set these based on TM descriptions */
/*     psuMeasInfo->llTSIdx             =  0; */
/*     psuMeasInfo->uTSSWIdx            = -1;        */
/*     psuMeasInfo->llTSSW_SampleNum    = -1;        */
/*     psuMeasInfo->llTSSW_MFCVal       = -1; */
/*     psuMeasInfo->uTSSWIdx            = -1; */

/*     szTempLen = 0; */
/*     while ( psuRTDConfig->pszSerialMeasNames[iMeasIdx][szTempLen] != '\0' ) */
/* 	szTempLen++; */
/*     strncpy(psuMeasInfo->szName, psuRTDConfig->pszSerialMeasNames[iMeasIdx], //Name of measurement, e.g., "Langmuir Probe Measurement 1 MSB" */
/* 	    szTempLen );     */

/*     szAbbrevLen = 0; */
/*     while ( psuRTDConfig->pszSerialMeasAbbrev[iMeasIdx][szAbbrevLen] != '\0' ) */
/* 	szAbbrevLen++; */
/*     strncpy(psuMeasInfo->szAbbrev, psuRTDConfig->pszSerialMeasAbbrev[iMeasIdx],	//Abbreviation for measurement, e.g., "LP01MSB" */
/* 	    szAbbrevLen ); */
    
/*     szTempLen = 0; */
/*     while ( psuRTDConfig->pszUser[iMeasIdx][szTempLen] != '\0' ) */
/* 	szTempLen++; */
/*     strncpy(psuMeasInfo->szUser, psuRTDConfig->pszUser[iMeasIdx],			   //Who is the user? E.g., Dartmouth, U Iowa */
/* 	    szTempLen ); */
    
/*     psuMeasInfo->uWord               = psuRTDConfig->pauWord[iMeasIdx] - 1;  //Beginning word in the frame, -1 for counting from zero */
/*     psuMeasInfo->uWdInt              = psuRTDConfig->pauWdInt[iMeasIdx];     //Word interval */
/*     psuMeasInfo->uMinorFrame         = psuRTDConfig->pauFrame[iMeasIdx];     //Which minor frame is it in? */
/*     psuMeasInfo->uMinorFrInt         = psuRTDConfig->pauFrInt[iMeasIdx];     //How often does it show up? */
/*     psuMeasInfo->ulSPS               = psuRTDConfig->paulSPS[iMeasIdx]; */

/*     //Now handle initialization of buffers */
/*     psuMeasInfo->paullSample         = (uint64_t *) malloc(psuMeasInfo->uSampsPerMinorFrame * sizeof(uint64_t)); */
/*     if ( psuMeasInfo->paullSample == NULL ) */
/* 	return EXIT_FAILURE; */
	
/*     for ( iTmpIdx = 0; iTmpIdx < psuMeasInfo->uSampsPerMinorFrame; iTmpIdx++ ) */
/* 	{ */
/* 	psuMeasInfo->paullSample[iTmpIdx] = -1; */

/* 	sprintf(psuMeasInfo->szTStampFile,"%s--%s--%s.txt",szOutPrefix,psuMeasInfo->szAbbrev,szTStampSuffix); */
/* 	psuMeasInfo->psuTStampFile    = (FILE *) fopen(psuMeasInfo->szTStampFile,"w"); */
/* 	psuMeasInfo->pallPCMWdOffsets  = (int64_t *) malloc(psuMeasInfo->uSampsPerMinorFrame * sizeof(int64_t)); */
/* 	if ( psuMeasInfo->pallPCMWdOffsets == NULL ) */
/* 	    return EXIT_FAILURE; */
/* 	} */
/*     else */
/* 	{ */
/* 	    printf("Invalid uTSCalcType for measurement %s: %" PRIu16 "\n",psuMeasInfo->szName,psuMeasInfo->uTSCalcType); */
/* 	    printf("Exiting...\n"); */
/* 	    return EXIT_FAILURE; */
/* 	} */

/*     return EXIT_SUCCESS; */
/* } */

int iRTDFree(struct suRTDConfig * psuRTDConfig)
{
    if ( psuRTDConfig->pszSerialMeasNames != NULL )
	free( psuRTDConfig->pszSerialMeasNames );
    if ( psuRTDConfig->pszSerialMeasAbbrev != NULL )
	free( psuRTDConfig->pszSerialMeasAbbrev );
    if ( psuRTDConfig->pszUser != NULL )
	free( psuRTDConfig->pszUser );
    
    if ( psuRTDConfig->paulMeasByteRTDSize != NULL )
	free( psuRTDConfig->paulMeasByteRTDSize );
    if ( psuRTDConfig->pauMeasDataType != NULL )
	free( psuRTDConfig->pauMeasDataType );
    if ( psuRTDConfig->pauMeasUpdateRate != NULL )
	free( psuRTDConfig->pauMeasUpdateRate );

    if ( psuRTDConfig->paulMeasSampleRate != NULL )
	free( psuRTDConfig->paulMeasSampleRate );
    if ( psuRTDConfig->paulMeasMinFreq != NULL )
	free( psuRTDConfig->paulMeasMinFreq );
    if ( psuRTDConfig->paulMeasMaxFreq != NULL )
	free( psuRTDConfig->paulMeasMaxFreq );

    free( psuRTDConfig );

    return (EXIT_SUCCESS);
}

char * trimwhitespace(char * str)
{
    char *end;
  
    // Trim leading space
    while(isspace(*str)) str++;
    
    if(*str == 0)  // All spaces?
	return str;
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    
    // Write new null terminator
    *(end+1) = 0;
    
    return str;
}
