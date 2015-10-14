//RTD_structs.h

#ifndef __DART_RTD_STRUCTS_H__
#define __DART_RTD_STRUCTS_H__

static const char * szRTDConfigValNames[]   = {"NAME",
					       "N_MEASUREMENTS"};

static const char  * szRTDConfigArrNames[]   = {"MEAS_NAME",
						"MEAS_ABBREV",
						"MEAS_USER",
						"MEAS_BYTE_RTD_SIZE",
						"MEAS_DATA_TYPE",
						"MEAS_RTD_UPDATE_RATE",
						"MEAS_SAMPLE_RATE",
						"MEAS_MIN_FREQ",
						"MEAS_MAX_FREQ"};

enum DARTRTD_enumDataTypes { UINT16, UINT32, UINT64, INT16, INT32, INT64, COMPLEX };

struct suRTDConfig
{

    char            szName[128];
    int16_t         iNMeasurements;

    //Arrays to hold measurement info from ASCII file
    char      **    pszSerialMeasNames;
    char      **    pszSerialMeasAbbrev;
    char      **    pszUser;

    uint32_t  *     paulMeasByteRTDSize;
    uint16_t  *     pauMeasDataType;
    uint16_t  *     pauMeasUpdateRate;

    uint32_t  *     paulMeasSampleRate;
    uint32_t  *     paulMeasMinFreq;
    uint32_t  *     paulMeasMaxFreq;

};

#endif //end #ifndef __DART_RTD_STRUCTS_H__
