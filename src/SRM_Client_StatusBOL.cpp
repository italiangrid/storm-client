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

#include "SRM_Client_StatusBOL.hpp"

SRM_Client_StatusBOL::SRM_Client_StatusBOL() : SRM_Client_Common_template("StatusBOL")
{
    _status_request = storm::soap_calloc<struct ns1__srmStatusOfBringOnlineRequestRequest>(&_soap);
    _status_response_ = storm::soap_calloc<struct ns1__srmStatusOfBringOnlineRequestResponse_>(&_soap);
}

void SRM_Client_StatusBOL::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_poll();
    print_Usage_endpoint(); 
    print_Usage_authorizationID();
    print_Usage_requestToken();
    print_Usage_ArrayOfAnyURI();
}

/** Parse request specific options */
int SRM_Client_StatusBOL::parse_RequestOptions(char opt, int index, int argc, char **argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_REQUESTTOKEN:
                index = parse_Arg(index, argc, argv, &(_request->requestToken));
                break;
            case OPT_ARRAYOFANYURI:
                index = parse_Arg(index, argc, argv, &(_request->arrayOfSourceSURLs));
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_StatusBOL::set_Request_Status()
{
    // Check if the request has been correctly executed
    if (_response->srmStatusOfBringOnlineRequestResponse == NULL)
        return;
    _request_SRMStatus = _response->srmStatusOfBringOnlineRequestResponse->returnStatus;
}

int SRM_Client_StatusBOL::execute_Request()
{ 
    int stat;

    stat = soap_call_ns1__srmStatusOfBringOnlineRequest(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return stat;
}

int SRM_Client_StatusBOL::poll_Request()
{
    int stat;

    stat = execute_Request();
    return stat;
}

void SRM_Client_StatusBOL::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "requestToken", _request->requestToken);
    print_Data(2, "arrayOfSourceSURLs", _request->arrayOfSourceSURLs);
}

void SRM_Client_StatusBOL::printRequestOutputdata()
{
    struct ns1__srmStatusOfBringOnlineRequestResponse *rep = _response->srmStatusOfBringOnlineRequestResponse;
    
    print_Data(2, "remainingTotalRequestTime", rep->remainingTotalRequestTime);
    print_Data(2, "remainingDeferredStartTime", rep->remainingDeferredStartTime);
    print_Data(2, "arrayOfFileStatuses", rep->arrayOfFileStatuses);
}
