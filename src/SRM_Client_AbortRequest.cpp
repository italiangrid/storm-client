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

#include "SRM_Client_AbortRequest.hpp"

void SRM_Client_AbortRequest::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
    print_Usage_requestToken();
}

/** Parse request specific options */
int SRM_Client_AbortRequest::parse_RequestOptions(char opt, int index, int argc, char** argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_REQUESTTOKEN:
                index = parse_Arg(index, argc, argv, &(_request->requestToken));
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_AbortRequest::set_Request_Status()
{
    if (_response->srmAbortRequestResponse != NULL)
        _request_SRMStatus = _response->srmAbortRequestResponse->returnStatus;
}

int SRM_Client_AbortRequest::execute_Request()
{ 
    int gSoapCode;

    gSoapCode = soap_call_ns1__srmAbortRequest(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return gSoapCode;
}

void SRM_Client_AbortRequest::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "requestToken", _request->requestToken);
}

void SRM_Client_AbortRequest::printRequestOutputdata() { }
