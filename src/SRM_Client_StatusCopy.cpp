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

#include "SRM_Client_StatusCopy.hpp"

SRM_Client_StatusCopy::SRM_Client_StatusCopy() : SRM_Client_Common_template("StatusCopy")
{
    _status_request = storm::soap_calloc<struct ns1__srmStatusOfCopyRequestRequest>(&_soap);
    _status_response_ = storm::soap_calloc<struct ns1__srmStatusOfCopyRequestResponse_>(&_soap);
}

void SRM_Client_StatusCopy::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_poll();
    print_Usage_endpoint(); 
    print_Usage_authorizationID();
    print_Usage_requestToken();
    print_Usage_ArrayOfAnyURI(OPT_ARRAYOFANYURI, "Source SURLs");
    print_Usage_ArrayOfAnyURI(OPT_ARRAYOFANYURI_2, "Target SURLs");
}

/** Parse request specific options */
int SRM_Client_StatusCopy::parse_RequestOptions(char opt, int index, int argc, char **argv)
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
            case OPT_ARRAYOFANYURI_2:
                index = parse_Arg(index, argc, argv, &(_request->arrayOfTargetSURLs));
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_StatusCopy::set_Request_Status()
{
    // Check if the request has been correctly executed
    if (_response->srmStatusOfCopyRequestResponse == NULL)
        return;
    _request_SRMStatus = _response->srmStatusOfCopyRequestResponse->returnStatus;
}

int SRM_Client_StatusCopy::execute_Request()
{ 
    int stat;

    stat = soap_call_ns1__srmStatusOfCopyRequest(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return stat;
}

int SRM_Client_StatusCopy::poll_Request()
{
    int stat;

    stat = execute_Request();
    return stat;
}

void SRM_Client_StatusCopy::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "requestToken", _request->requestToken);
    print_Data(2, "arrayOfSourceSURLs", _request->arrayOfSourceSURLs);
    print_Data(2, "arrayOfTargetSURLs", _request->arrayOfTargetSURLs);
}

void SRM_Client_StatusCopy::printRequestOutputdata()
{
    struct ns1__srmStatusOfCopyRequestResponse *rep = _response->srmStatusOfCopyRequestResponse;
    
    print_Data(2, "remainingTotalRequestTime", rep->remainingTotalRequestTime);
    print_Data(2, "arrayOfFileStatuses", rep->arrayOfFileStatuses);
}
