// Copyright (c) Istituto Nazionale di Fisica Nucleare (INFN). 2006-2010.
/* Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//#define _GNU_SOURCE
#include "storm_util.hpp"
#include <string.h>
#include "srmv2H.h"

int convertPermission(char *mode)
{
    if (strcmp("None", mode) == 0) return NONE;
    if (strcmp("X", mode) == 0)    return X;
    if (strcmp("W", mode) == 0)    return W;
    if (strcmp("R", mode) == 0)    return R;
    if (strcmp("RX", mode) == 0)   return RX;
    if (strcmp("RW", mode) == 0)   return RW;
    if (strcmp("RWX", mode) == 0)  return RWX;
    return(NONE);
}

/** Converts the file storage type */
int convertFileStorageType(char *fstype)
{
    if (strcmp("Volatile_", fstype) == 0)  return VOLATILE;
    if (strcmp("Durable_", fstype) == 0)   return DURABLE;
    if (strcmp("Permanent_", fstype) == 0) return PERMANENT;
    if (strcmp("Unknown.", fstype) == 0)   return -1; 
    return -1;
}

/** Converts the file storage type */
int convertSpaceType(char *stype)
{
    if (strcmp("Volatile", stype) == 0)  return VOLATILE;
    if (strcmp("Durable", stype) == 0)   return DURABLE;
    if (strcmp("Permanent", stype) == 0) return PERMANENT;
    if (strcmp("Unknown.", stype) == 0)   return -1;
    return -1;
}
 
/* Converts the status code from char* format into a SRM status code */
int convertStatusCode(char*  code) 
{
    if (strcmp("SRM_SUCCESS", code) == 0)     return SRM_USCORESUCCESS; // 0
    else if (strcmp("SRM_FAILURE", code) == 0)     return SRM_USCOREFAILURE; // 1 
    else if (strcmp("SRM_AUTHENTICATION_FAILURE", code) == 0)     return SRM_USCOREAUTHENTICATION_USCOREFAILURE; // 2
    else if (strcmp("SRM_AUTHORIZATION_FAILURE", code) == 0)     return SRM_USCOREAUTHORIZATION_USCOREFAILURE; // 3
    else if (strcmp("SRM_INVALID_REQUEST", code) == 0)     return SRM_USCOREINVALID_USCOREREQUEST; // 4
    else if (strcmp("SRM_INVALID_PATH", code) == 0)     return SRM_USCOREINVALID_USCOREPATH; // 5
    else if (strcmp("SRM_FILE_LIFETIME_EXPIRED", code) == 0)     return SRM_USCOREFILE_USCORELIFETIME_USCOREEXPIRED; // 6
    else if (strcmp("SRM_SPACE_LIFETIME_EXPIRED", code) == 0)     return SRM_USCORESPACE_USCORELIFETIME_USCOREEXPIRED; // 7
    else if (strcmp("SRM_EXCEED_ALLOCATION", code) == 0)     return SRM_USCOREEXCEED_USCOREALLOCATION; // 8
    else if (strcmp("SRM_NO_USER_SPACE", code) == 0)     return SRM_USCORENO_USCOREUSER_USCORESPACE; // 9
    else if (strcmp("SRM_NO_FREE_SPACE", code) == 0)     return SRM_USCORENO_USCOREFREE_USCORESPACE; // 10
    else if (strcmp("SRM_DUPLICATION_ERROR", code) == 0)     return SRM_USCOREDUPLICATION_USCOREERROR; // 11
    else if (strcmp("SRM_NON_EMPTY_DIRECTORY", code) == 0)     return SRM_USCORENON_USCOREEMPTY_USCOREDIRECTORY; // 12
    else if (strcmp("SRM_TOO_MANY_RESULTS", code) == 0)     return SRM_USCORETOO_USCOREMANY_USCORERESULTS; // 13
    else if (strcmp("SRM_INTERNAL_ERROR", code) == 0)  return SRM_USCOREINTERNAL_USCOREERROR; // 14
    else if (strcmp("SRM_FATAL_INTERNAL_ERROR", code) == 0)     return SRM_USCOREFATAL_USCOREINTERNAL_USCOREERROR; // 15
    else if (strcmp("SRM_NOT_SUPPORTED", code) == 0)     return SRM_USCORENOT_USCORESUPPORTED; // 16
    else if (strcmp("SRM_REQUEST_QUEUED", code) == 0)     return SRM_USCOREREQUEST_USCOREQUEUED; // 17
    else if (strcmp("SRM_REQUEST_INPROGRESS", code) == 0)     return SRM_USCOREREQUEST_USCOREINPROGRESS; // 18
    else if (strcmp("SRM_REQUEST_SUSPENDED", code) == 0)     return SRM_USCOREREQUEST_USCORESUSPENDED; // 19
    else if (strcmp("SRM_ABORTED", code) == 0)     return SRM_USCOREABORTED; // 20
    else if (strcmp("SRM_RELEASED", code) == 0)     return SRM_USCORERELEASED; // 21
    else if (strcmp("SRM_FILE_PINNED", code) == 0)     return SRM_USCOREFILE_USCOREPINNED; // 22
    else if (strcmp("SRM_FILE_IN_CACHE", code) == 0)     return SRM_USCOREFILE_USCOREIN_USCORECACHE; // 23
    else if (strcmp("SRM_SPACE_AVAILABLE", code) == 0)     return SRM_USCORESPACE_USCOREAVAILABLE; // 24
    else if (strcmp("SRM_LOWER_SPACE_GRANTED", code) == 0)     return SRM_USCORELOWER_USCORESPACE_USCOREGRANTED; // 25
    else if (strcmp("SRM_DONE", code) == 0)        return SRM_USCOREDONE; // 26
    else if (strcmp("SRM_PARTIAL_SUCCESS", code) == 0) return SRM_USCOREPARTIAL_USCORESUCCESS; // 27
    else if (strcmp("SRM_REQUEST_TIMED_OUT", code) == 0) return SRM_USCOREREQUEST_USCORETIMED_USCOREOUT; // 28
    else if (strcmp("SRM_LAST_COPY", code) == 0) return SRM_USCORELAST_USCORECOPY; // 29
    else if (strcmp("SRM_FILE_BUSY", code) == 0) return SRM_USCOREFILE_USCOREBUSY; // 30
    else if (strcmp("SRM_FILE_LOST", code) == 0) return SRM_USCOREFILE_USCORELOST; // 31
    else if (strcmp("SRM_FILE_UNAVAILABLE", code) == 0) return SRM_USCOREFILE_USCOREUNAVAILABLE; // 32
    else return SRM_USCORECUSTOM_USCORESTATUS; // 33
}

char* reconvertStatusCode(int  code) 
{
    if (code == 0)  return "SRM_SUCCESS"; // 0
    if (code == 1)  return "SRM_FAILURE"; // 1 
    if (code == 2)  return "SRM_AUTHENTICATION_FAILURE"; // 2
    if (code == 3)  return "SRM_AUTHORIZATION_FAILURE"; // 3
    if (code == 4)  return "SRM_INVALID_REQUEST"; // 4
    if (code == 5)  return "SRM_INVALID_PATH"; // 5
    if (code == 6)  return "SRM_FILE_LIFETIME_EXPIRED"; // 6
    if (code == 7)  return "SRM_SPACE_LIFETIME_EXPIRED"; // 7
    if (code == 8)  return "SRM_EXCEED_ALLOCATION"; // 8
    if (code == 9)  return "SRM_NO_USER_SPACE"; // 9
    if (code == 10) return "SRM_NO_FREE_SPACE"; // 10
    if (code == 11) return "SRM_DUPLICATION_ERROR"; // 1
    if (code == 12) return "SRM_NON_EMPTY_DIRECTORY"; // 12
    if (code == 13) return "SRM_TOO_MANY_RESULTS"; // 13
    if (code == 14) return "SRM_INTERNAL_ERROR"; // 14
    if (code == 15) return "SRM_FATAL_INTERNAL_ERROR"; // 15
    if (code == 16) return "SRM_NOT_SUPPORTED"; // 16
    if (code == 17) return "SRM_REQUEST_QUEUED"; // 17
    if (code == 18) return "SRM_REQUEST_INPROGRESS"; // 18
    if (code == 19) return "SRM_REQUEST_SUSPENDED"; // 19
    if (code == 20) return "SRM_ABORTED"; // 20
    if (code == 21) return "SRM_RELEASED"; // 21
    if (code == 22) return "SRM_FILE_PINNED"; // 22
    if (code == 23) return "SRM_FILE_IN_CACHE"; // 23
    if (code == 24) return "SRM_SPACE_AVAILABLE"; // 24
    if (code == 25) return "SRM_LOWER_SPACE_GRANTED"; // 25
    if (code == 26) return "SRM_DONE"; // 26
    if (code == 27) return "SRM_PARTIAL_SUCCESS"; // 27
    if (code == 28) return "SRM_REQUEST_TIMED_OUT"; // 28
    if (code == 29) return "SRM_LAST_COPY"; // 29
    if (code == 30) return "SRM_FILE_BUSY"; // 30
    if (code == 31) return "SRM_FILE_LOST"; // 31
    if (code == 32) return "SRM_FILE_UNAVAILABLE"; // 32
    if (code == 33) return "SRM_CUSTOM_STATUS"; // 33
}

