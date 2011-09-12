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

#include "SRM_Client_BOL.hpp"

SRM_Client_BOL::SRM_Client_BOL() : SRM_Client_Common_template("BringOnline")
{
    _status_request = storm::soap_calloc<struct ns1__srmStatusOfBringOnlineRequestRequest>(&_soap);
    _status_response_ = storm::soap_calloc<struct ns1__srmStatusOfBringOnlineRequestResponse_>(&_soap);
}

void SRM_Client_BOL::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_poll();
    print_Usage_endpoint(); 
    print_Usage_authorizationID();
    print_Usage_ArrayOfTGetFileRequest();
    print_Usage_userRequestDescription();
    print_Usage_ArrayOfTExtraInfo();
    print_Usage_TFileStorageType();
    print_Usage_desiredTotalTimeRequest();
    print_Usage_(OPT_BOL_DESIRED_LITETIME, "<desiredLifeTime>", "Lifetime on online.");
    print_Usage_targetSpaceToken();
    print_Usage_TRetentionPolicyInfo();
    print_Usage_TTransferParameters();
    print_Usage_(OPT_BOL_DEFERRED_STARTTIME, "<deferredStartTime>", "The specified SURLs are not going to be used before that time.");
}

/** Parse request specific options */
int SRM_Client_BOL::parse_RequestOptions(char opt, int index, int argc, char **argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_TGETFILEREQUEST:
                index = parse_Arg(index, argc, argv, &(_request->arrayOfFileRequests));
                break;
            case OPT_REQUESTDESCRIPTION:
                index = parse_Arg(index, argc, argv, &(_request->userRequestDescription));
                break;
            case OPT_TEXTRAINFO:
                index = parse_Arg(index, argc, argv, &(_request->storageSystemInfo));
                break;
            case OPT_TFILESTORAGETYPE:
                index = parse_Arg_enum(index, argc, argv, &(_request->desiredFileStorageType));
                break;
            case OPT_DESIRED_TOTALREQUESTTIME:
                index = parse_Arg(index, argc, argv, &(_request->desiredTotalRequestTime), WITH_OPTION);
                break;
            case OPT_BOL_DESIRED_LITETIME:
                index = parse_Arg(index, argc, argv, &(_request->desiredLifeTime), WITH_OPTION);
                break;
            case OPT_SPACETOKEN:
                index = parse_Arg(index, argc, argv, &(_request->targetSpaceToken));
                break;
            case OPT_TRETENTIONPOLICYINFO:
                index = parse_Arg(index, argc, argv, &(_request->targetFileRetentionPolicyInfo));
                break;
            case OPT_TTRANSFERPARAMETERS:
                index = parse_Arg(index, argc, argv, &(_request->transferParameters));
                break;
            case OPT_BOL_DEFERRED_STARTTIME:
                index = parse_Arg(index, argc, argv, &(_request->deferredStartTime), WITH_OPTION);
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_BOL::set_Request_Status()
{
    // Check if the request has been correctly executed
    if (_response->srmBringOnlineResponse == NULL)
        return;
    _request_SRMStatus = _response->srmBringOnlineResponse->returnStatus;
}

int SRM_Client_BOL::execute_Request()
{ 
    int stat;

    stat = soap_call_ns1__srmBringOnline(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return stat;
}

void SRM_Client_BOL::set_Poll_Inputdata()
{
    int i, arraySize;
    
    // Set the input data of the status request (taking values from the request input data private members)
    _status_request->requestToken = _response->srmBringOnlineResponse->requestToken;
    _status_request->authorizationID = _request->authorizationID;
    if (_request->arrayOfFileRequests != NULL) {
	    _status_request->arrayOfSourceSURLs = storm::soap_calloc<struct ns1__ArrayOfAnyURI>(&_soap);
	    arraySize = _request->arrayOfFileRequests->__sizerequestArray;
	    _status_request->arrayOfSourceSURLs->urlArray = storm::soap_calloc<char>(&_soap, arraySize);
	    _status_request->arrayOfSourceSURLs->__sizeurlArray = arraySize;
	    for (i=0; i<arraySize; i++) {
	        _status_request->arrayOfSourceSURLs->urlArray[i] = _request->arrayOfFileRequests->requestArray[i]->sourceSURL; 
	    }
    }
    else
    	_status_request->arrayOfSourceSURLs = NULL;
}

int SRM_Client_BOL::poll_Request()
{
    int stat;

    stat = soap_call_ns1__srmStatusOfBringOnlineRequest(&_soap, _endpoint, _serviceName.c_str(),
                                                        _status_request, _status_response_);
    return stat;
}

void SRM_Client_BOL::set_Request_Poll_Outputdata()
{
    struct ns1__srmStatusOfBringOnlineRequestResponse *status_rep;
    
    status_rep = _status_response_->srmStatusOfBringOnlineRequestResponse;
    
    _request_SRMStatus = status_rep->returnStatus;
    _response->srmBringOnlineResponse->remainingTotalRequestTime = status_rep->remainingTotalRequestTime;
    _response->srmBringOnlineResponse->arrayOfFileStatuses = status_rep->arrayOfFileStatuses;
}

void SRM_Client_BOL::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "arrayOfFileRequests", _request->arrayOfFileRequests);
    print_Data(2, "userRequestDescription", _request->userRequestDescription);
    print_Data(2, "storageSystemInfo", _request->storageSystemInfo);
    print_Data(2, "desiredFileStorageType", _request->desiredFileStorageType);
    print_Data(2, "desiredTotalRequestTime", _request->desiredTotalRequestTime);
    print_Data(2, "desiredLifeTime", _request->desiredLifeTime);
    print_Data(2, "targetSpaceToken", _request->targetSpaceToken);
    print_Data(2, "targetFileRetentionPolicyInfo", _request->targetFileRetentionPolicyInfo);
    print_Data(2, "transferParameters", _request->transferParameters);
    print_Data(2, "deferredStartTime", _request->deferredStartTime);
}

void SRM_Client_BOL::printRequestOutputdata()
{
    struct ns1__srmBringOnlineResponse *rep = _response->srmBringOnlineResponse;
    
    print_Data(2, "requestToken", rep->requestToken);
    print_Data(2, "remainingTotalRequestTime", rep->remainingTotalRequestTime);
    print_Data(2, "remainingDeferredStartTime", rep->remainingDeferredStartTime);
    print_Data(2, "arrayOfFileStatuses", rep->arrayOfFileStatuses);
}
