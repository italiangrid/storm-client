#include "SRM_Client_Copy.hpp"

SRM_Client_Copy::SRM_Client_Copy() : SRM_Client_Common_template("Copy")
{
    _status_request = storm::soap_calloc<struct ns1__srmStatusOfCopyRequestRequest>(&_soap);
    _status_response_ = storm::soap_calloc<struct ns1__srmStatusOfCopyRequestResponse_>(&_soap);
}

void SRM_Client_Copy::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_poll();
    print_Usage_endpoint(); 
    print_Usage_authorizationID();
    print_Usage_ArrayOfTCopyFileRequest();
    print_Usage_userRequestDescription();
    print_Usage_TOverwriteMode();
    print_Usage_desiredTotalTimeRequest();
    print_Usage_(OPT_COPY_DESIRED_TARGETSURLLITETIME, "<desriredTargetSURLLifeTime>", "Lifetime on target SURL.");
    print_Usage_TFileStorageType();
    print_Usage_targetSpaceToken();
    print_Usage_TRetentionPolicyInfo();
    print_Usage_ArrayOfTExtraInfo(OPT_TEXTRAINFO, "storageSystemInfo for source SURLs.");
    print_Usage_ArrayOfTExtraInfo(OPT_TEXTRAINFO_2, "storageSystemInfo for target SURLs.");
}

/** Parse request specific options */
int SRM_Client_Copy::parse_RequestOptions(char opt, int index, int argc, char **argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_TCOPYFILEREQUEST:
                index = parse_Arg(index, argc, argv, &(_request->arrayOfFileRequests));
                break;
            case OPT_REQUESTDESCRIPTION:
                index = parse_Arg(index, argc, argv, &(_request->userRequestDescription));
                break;
            case OPT_TOVERWRITEMODE:
                index = parse_Arg_enum(index, argc, argv, &(_request->overwriteOption), true);
                break;
            case OPT_DESIRED_TOTALREQUESTTIME:
                index = parse_Arg(index, argc, argv, &(_request->desiredTotalRequestTime), true);
                break;
            case OPT_COPY_DESIRED_TARGETSURLLITETIME:
                index = parse_Arg(index, argc, argv, &(_request->desiredTargetSURLLifeTime), true);
                break;
            case OPT_TFILESTORAGETYPE:
                index = parse_Arg_enum(index, argc, argv, &(_request->targetFileStorageType));
                break;
            case OPT_SPACETOKEN:
                index = parse_Arg(index, argc, argv, &(_request->targetSpaceToken));
                break;
            case OPT_TRETENTIONPOLICYINFO:
                index = parse_Arg(index, argc, argv, &(_request->targetFileRetentionPolicyInfo));
                break;
            case OPT_TEXTRAINFO:
                index = parse_Arg(index, argc, argv, &(_request->sourceStorageSystemInfo));
                break;
            case OPT_TEXTRAINFO_2:
                index = parse_Arg(index, argc, argv, &(_request->targetStorageSystemInfo));
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_Copy::set_Request_Status()
{
    // Check if the request has been correctly executed
    if (_response->srmCopyResponse == NULL)
        return;
    _request_SRMStatus = _response->srmCopyResponse->returnStatus;
}

int SRM_Client_Copy::execute_Request()
{ 
    int stat;

    stat = soap_call_ns1__srmCopy(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return stat;
}

void SRM_Client_Copy::set_Poll_Inputdata()
{
    int i, arraySize;
    
    // Set the input data of the status request (taking values from the request input data private members)
    _status_request->requestToken = _response->srmCopyResponse->requestToken;
    _status_request->authorizationID = _request->authorizationID;
    if (_request->arrayOfFileRequests != NULL) {
	    _status_request->arrayOfSourceSURLs = storm::soap_calloc<struct ns1__ArrayOfAnyURI>(&_soap);
	    _status_request->arrayOfTargetSURLs = storm::soap_calloc<struct ns1__ArrayOfAnyURI>(&_soap);
	    arraySize = _request->arrayOfFileRequests->__sizerequestArray;
	    
	    _status_request->arrayOfSourceSURLs->urlArray = storm::soap_calloc<char>(&_soap, arraySize);
	    _status_request->arrayOfTargetSURLs->urlArray = storm::soap_calloc<char>(&_soap, arraySize);
	    _status_request->arrayOfSourceSURLs->__sizeurlArray = arraySize;
	    _status_request->arrayOfTargetSURLs->__sizeurlArray = arraySize;
	    
	    for (i=0; i<arraySize; i++) {
	        _status_request->arrayOfSourceSURLs->urlArray[i] = _request->arrayOfFileRequests->requestArray[i]->sourceSURL;
	        _status_request->arrayOfTargetSURLs->urlArray[i] = _request->arrayOfFileRequests->requestArray[i]->targetSURL; 
	    }
    }
    else {
    	_status_request->arrayOfSourceSURLs = NULL;
    	_status_request->arrayOfTargetSURLs = NULL;
    }
}

int SRM_Client_Copy::poll_Request()
{
    int stat;

    stat = soap_call_ns1__srmStatusOfCopyRequest(&_soap, _endpoint, _serviceName.c_str(),
                                                _status_request, _status_response_);
    return stat;
}

void SRM_Client_Copy::set_Request_Poll_Outputdata()
{
    struct ns1__srmStatusOfCopyRequestResponse *status_rep;
    
    status_rep = _status_response_->srmStatusOfCopyRequestResponse;
    
    _request_SRMStatus = status_rep->returnStatus;
    _response->srmCopyResponse->remainingTotalRequestTime = status_rep->remainingTotalRequestTime;
    _response->srmCopyResponse->arrayOfFileStatuses = status_rep->arrayOfFileStatuses;
}

void SRM_Client_Copy::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "arrayOfFileRequests", _request->arrayOfFileRequests);
    print_Data(2, "userRequestDescription", _request->userRequestDescription);
    print_Data(2, "overwriteOption", _request->overwriteOption);
    print_Data(2, "desiredTotalRequestTime", _request->desiredTotalRequestTime);
    print_Data(2, "desiredTargetSURLLifeTime", _request->desiredTargetSURLLifeTime);
    print_Data(2, "targetFileStorageType", _request->targetFileStorageType);
    print_Data(2, "targetSpaceToken", _request->targetSpaceToken);
    print_Data(2, "targetFileRetentionPolicyInfo", _request->targetFileRetentionPolicyInfo);
    print_Data(2, "sourceStorageSystemInfo", _request->sourceStorageSystemInfo);
    print_Data(2, "targetStorageSystemInfo", _request->targetStorageSystemInfo);
}

void SRM_Client_Copy::printRequestOutputdata()
{
    struct ns1__srmCopyResponse *rep = _response->srmCopyResponse;
    
    print_Data(2, "requestToken", rep->requestToken);
    print_Data(2, "remainingTotalRequestTime", rep->remainingTotalRequestTime);
    print_Data(2, "arrayOfFileStatuses", rep->arrayOfFileStatuses);
}
