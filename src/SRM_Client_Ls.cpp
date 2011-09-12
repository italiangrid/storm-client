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

#include "SRM_Client_Ls.hpp"

void SRM_Client_Ls::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
    print_Usage_ArrayOfAnyURI();
    print_Usage_ArrayOfTExtraInfo();
    print_Usage_TFileStorageType();
    print_Usage_(OPT_LS_FULLDETAILEDLIST, "[fullDetailedList]", "0=false, 1=true. Full details for each file are returned");
    print_Usage_(OPT_LS_ALLLEVELRECURSIVE, "[allLevelRecursive]", "0=false, 1=true. List subdirectories recursively");
    print_Usage_(OPT_LS_NUMOFLEVELS, "<numOfLevels>", "Max number of levels to visit.");
    print_Usage_(OPT_LS_OFFSET, "<offset>", "");
    print_Usage_(OPT_LS_COUNT, "<count>", "Max number of results to be returned.");
}

/** Parse request specific options */
int SRM_Client_Ls::parse_RequestOptions(char opt, int index, int argc, char** argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_ARRAYOFANYURI:
                index = parse_Arg(index, argc, argv, &(_request->arrayOfSURLs));
                break;
            case OPT_TEXTRAINFO:
                index = parse_Arg(index, argc, argv, &(_request->storageSystemInfo));
                break;
            case OPT_TFILESTORAGETYPE:
                index = parse_Arg_enum(index, argc, argv, &(_request->fileStorageType));
                break;
            case OPT_LS_FULLDETAILEDLIST:
                index = parse_Arg(index, argc, argv, &(_request->fullDetailedList), WITH_OPTION);
                break;
            case OPT_LS_ALLLEVELRECURSIVE:
                index = parse_Arg(index, argc, argv, &(_request->allLevelRecursive), WITH_OPTION);
                break;
            case OPT_LS_NUMOFLEVELS:
                index = parse_Arg(index, argc, argv, &(_request->numOfLevels), WITH_OPTION);
                break;
            case OPT_LS_OFFSET:
                index = parse_Arg(index, argc, argv, &(_request->offset), WITH_OPTION);
                break;
            case OPT_LS_COUNT:
                index = parse_Arg(index, argc, argv, &(_request->count), WITH_OPTION);
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_Ls::set_Request_Status()
{
    if (_response->srmLsResponse != NULL)
        _request_SRMStatus = _response->srmLsResponse->returnStatus;
}

int SRM_Client_Ls::execute_Request()
{ 
    int gSoapCode;

    gSoapCode = soap_call_ns1__srmLs(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return gSoapCode;
}

void SRM_Client_Ls::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "arrayOfSURLs", _request->arrayOfSURLs);
    print_Data(2, "storageSystemInfo", _request->storageSystemInfo);
    print_Data(2, "fileStorageType", _request->fileStorageType);
    print_Data(2, "fullDetailedList", _request->fullDetailedList);
    print_Data(2, "allLevelRecursive", _request->allLevelRecursive);
    print_Data(2, "numOfLevels", _request->numOfLevels);
    print_Data(2, "offset", _request->offset);
    print_Data(2, "count", _request->count);
}

void SRM_Client_Ls::printRequestOutputdata()
{
	print_Data(2, "requestToken", _response->srmLsResponse->requestToken);
	print_Data(2, string(), "details", _response->srmLsResponse->details);
}
