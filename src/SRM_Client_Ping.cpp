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

#include "SRM_Client_Ping.hpp"

void SRM_Client_Ping::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
}

/** Parse request specific options */
int SRM_Client_Ping::parse_RequestOptions(char opt, int index, int argc, char** argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_Ping::set_Request_Status()
{
    if (_soap.error == 0) {
    	_request_SRMStatus = storm::soap_calloc<struct ns1__TReturnStatus>(&_soap);
    	_request_SRMStatus->statusCode = SRM_USCORESUCCESS;
    	_request_SRMStatus->explanation = "SRM server successfully contacted";
    }
    else
	_request_SRMStatus = NULL;
}

int SRM_Client_Ping::execute_Request()
{ 
    int gSoapCode;

    cout << "execute Request with:" << _serviceName.c_str() << endl;
    cout << "started calling ns1__srmPing:" << endl;
    gSoapCode = soap_call_ns1__srmPing(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    cout << "finished calling ns1__srmPing:" << endl;
    
    return gSoapCode;
}

void SRM_Client_Ping::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
}

void SRM_Client_Ping::printRequestOutputdata()
{
    print_Data(2, "versionInfo", _response->srmPingResponse->versionInfo);
    print_Data(2, "otherInfo", _response->srmPingResponse->otherInfo);
}
