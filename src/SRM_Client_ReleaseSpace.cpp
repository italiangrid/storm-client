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

#include "SRM_Client_ReleaseSpace.hpp"

void SRM_Client_ReleaseSpace::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
    print_Usage_(OPT_SPACETOKEN, "<spaceToken>", "Space token");
    print_Usage_ArrayOfTExtraInfo();
    print_Usage_(OPT_RELEASESPACE_FORCERELEASE, "<forceFileRelease>",
                 "0=false, 1=true. Release the space regardless of the files it contains");
	print_Usage_(' ', NULL, "and their status.");
}

/** Parse request specific options */
int SRM_Client_ReleaseSpace::parse_RequestOptions(char opt, int index, int argc, char** argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_SPACETOKEN:
                index = parse_Arg(index, argc, argv, &(_request->spaceToken));
                break;
            case OPT_TEXTRAINFO:
                index = parse_Arg(index, argc, argv, &(_request->storageSystemInfo));
                break;
            case OPT_RELEASESPACE_FORCERELEASE:
                index = parse_Arg_enum(index, argc, argv, &(_request->forceFileRelease));
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_ReleaseSpace::set_Request_Status()
{
    if (_response->srmReleaseSpaceResponse != NULL)
        _request_SRMStatus = _response->srmReleaseSpaceResponse->returnStatus;
}

int SRM_Client_ReleaseSpace::execute_Request()
{ 
    int gSoapCode;

    gSoapCode = soap_call_ns1__srmReleaseSpace(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return gSoapCode;
}

void SRM_Client_ReleaseSpace::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "spaceToken", _request->spaceToken);
    print_Data(2, "storageSystemInfo", _request->storageSystemInfo);
    print_Data(2, "forceFileRelease", _request->forceFileRelease);
}

void SRM_Client_ReleaseSpace::printRequestOutputdata() {}
