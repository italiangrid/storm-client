#include "SRM_Client_PtG.hpp"

SRM_Client_PtG::SRM_Client_PtG() : SRM_Client_Common_template("PtG")
{
    _status_request = storm::soap_calloc<struct ns1__srmStatusOfGetRequestRequest>(&_soap);
    _status_response_ = storm::soap_calloc<struct ns1__srmStatusOfGetRequestResponse_>(&_soap);
}

void SRM_Client_PtG::print_Usage_Request()
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
    print_Usage_desiredPinLifeTime();
    print_Usage_targetSpaceToken();
    print_Usage_TRetentionPolicyInfo();
    print_Usage_TTransferParameters();
}

/** Parse request specific options */
int SRM_Client_PtG::parse_RequestOptions(char opt, int index, int argc, char **argv)
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
                index = parse_Arg(index, argc, argv, &(_request->desiredTotalRequestTime), true);
                break;
            case OPT_DESIRED_PINLIFETIME:
                index = parse_Arg(index, argc, argv, &(_request->desiredPinLifeTime), true);
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
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_PtG::set_Request_Status()
{
    // Check if the request has been correctly executed
    if (_response->srmPrepareToGetResponse == NULL)
        return;
    _request_SRMStatus = _response->srmPrepareToGetResponse->returnStatus;
}

int SRM_Client_PtG::execute_Request()
{ 
    int stat;

    stat = soap_call_ns1__srmPrepareToGet(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return stat;
}

void SRM_Client_PtG::set_Poll_Inputdata()
{
    int i, arraySize;
    
    // Set the input data of the status request (taking values from the request input data private members)
    _status_request->requestToken = _response->srmPrepareToGetResponse->requestToken;
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

int SRM_Client_PtG::poll_Request()
{
    int stat;

    stat = soap_call_ns1__srmStatusOfGetRequest(&_soap, _endpoint, _serviceName.c_str(),
                                                _status_request, _status_response_);
    return stat;
}

void SRM_Client_PtG::set_Request_Poll_Outputdata()
{
    struct ns1__srmStatusOfGetRequestResponse *status_rep;
    
    status_rep = _status_response_->srmStatusOfGetRequestResponse;
    
    _request_SRMStatus = status_rep->returnStatus;
    _response->srmPrepareToGetResponse->remainingTotalRequestTime = status_rep->remainingTotalRequestTime;
    _response->srmPrepareToGetResponse->arrayOfFileStatuses = status_rep->arrayOfFileStatuses;
}

void SRM_Client_PtG::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "arrayOfFileRequests", _request->arrayOfFileRequests);
    print_Data(2, "userRequestDescription", _request->userRequestDescription);
    print_Data(2, "storageSystemInfo", _request->storageSystemInfo);
    print_Data(2, "desiredFileStorageType", _request->desiredFileStorageType);
    print_Data(2, "desiredTotalRequestTime", _request->desiredTotalRequestTime);
    print_Data(2, "desiredPinLifeTime", _request->desiredPinLifeTime);
    print_Data(2, "targetSpaceToken", _request->targetSpaceToken);
    print_Data(2, "targetFileRetentionPolicyInfo", _request->targetFileRetentionPolicyInfo);
    print_Data(2, "transferParameters", _request->transferParameters);
}

void SRM_Client_PtG::printRequestOutputdata()
{
    struct ns1__srmPrepareToGetResponse *rep = _response->srmPrepareToGetResponse;
    
    print_Data(2, "requestToken", rep->requestToken);
    print_Data(2, "remainingTotalRequestTime", rep->remainingTotalRequestTime);
    print_Data(2, "arrayOfFileStatuses", rep->arrayOfFileStatuses);
}
