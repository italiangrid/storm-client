#include "SRM_Client_PtP.hpp"

SRM_Client_PtP::SRM_Client_PtP() : SRM_Client_Common_template("PtP")
{
    _status_request = storm::soap_calloc<struct ns1__srmStatusOfPutRequestRequest>(&_soap);
    _status_response_ = storm::soap_calloc<struct ns1__srmStatusOfPutRequestResponse_>(&_soap);
}

void SRM_Client_PtP::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_poll();
    print_Usage_endpoint(); 
    print_Usage_authorizationID();
    print_Usage_ArrayOfTPutFileRequest();
    print_Usage_userRequestDescription();
    print_Usage_TOverwriteMode();
    print_Usage_ArrayOfTExtraInfo();
    print_Usage_desiredTotalTimeRequest();
    print_Usage_desiredPinLifeTime();
    print_Usage_(OPT_DESIRED_FILELITETIME, "<desiredFileLifeTime>", "Lifetime on SURL.");
    print_Usage_TFileStorageType();
    print_Usage_targetSpaceToken();
    print_Usage_TRetentionPolicyInfo();
    print_Usage_TTransferParameters();
}

/** Parse request specific options */
int SRM_Client_PtP::parse_RequestOptions(char opt, int index, int argc, char **argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_TPUTFILEREQUEST:
                index = parse_Arg(index, argc, argv, &(_request->arrayOfFileRequests));
                break;
            case OPT_REQUESTDESCRIPTION:
                index = parse_Arg(index, argc, argv, &(_request->userRequestDescription));
                break;
            case OPT_TOVERWRITEMODE:
                index = parse_Arg_enum(index, argc, argv, &(_request->overwriteOption), WITH_OPTION);
                break;
            case OPT_TEXTRAINFO:
                index = parse_Arg(index, argc, argv, &(_request->storageSystemInfo));
                break;
            case OPT_DESIRED_TOTALREQUESTTIME:
                index = parse_Arg(index, argc, argv, &(_request->desiredTotalRequestTime), WITH_OPTION);
                break;
            case OPT_DESIRED_PINLIFETIME:
                index = parse_Arg(index, argc, argv, &(_request->desiredPinLifeTime), WITH_OPTION);
                break;
            case OPT_DESIRED_FILELITETIME:
                index = parse_Arg(index, argc, argv, &(_request->desiredFileLifeTime), WITH_OPTION);
                break;
            case OPT_TFILESTORAGETYPE:
                index = parse_Arg_enum(index, argc, argv, &(_request->desiredFileStorageType));
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

void SRM_Client_PtP::set_Request_Status()
{
    // Check if the request has been correctly executed
    if (_response->srmPrepareToPutResponse == NULL)
        return;
    _request_SRMStatus = _response->srmPrepareToPutResponse->returnStatus;
}

int SRM_Client_PtP::execute_Request()
{ 
    int stat;

    stat = soap_call_ns1__srmPrepareToPut(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return stat;
}

void SRM_Client_PtP::set_Poll_Inputdata()
{
    int i, arraySize;
    
    // Set the input data of the status request (taking values from the request input data private members)
    _status_request->requestToken = _response->srmPrepareToPutResponse->requestToken;
    _status_request->authorizationID = _request->authorizationID;
    if (_request->arrayOfFileRequests != NULL) {
	    _status_request->arrayOfTargetSURLs = storm::soap_calloc<struct ns1__ArrayOfAnyURI>(&_soap);
	    arraySize = _request->arrayOfFileRequests->__sizerequestArray;
	    _status_request->arrayOfTargetSURLs->urlArray = storm::soap_calloc<char>(&_soap, arraySize);
	    _status_request->arrayOfTargetSURLs->__sizeurlArray = arraySize;
	    for (i=0; i<arraySize; i++) {
	        _status_request->arrayOfTargetSURLs->urlArray[i] = _request->arrayOfFileRequests->requestArray[i]->targetSURL; 
	    }
    }
    else
    	_status_request->arrayOfTargetSURLs = NULL;
}

int SRM_Client_PtP::poll_Request()
{
    int stat;

    stat = soap_call_ns1__srmStatusOfPutRequest(&_soap, _endpoint, _serviceName.c_str(),
                                                _status_request, _status_response_);
    return stat;
}

void SRM_Client_PtP::set_Request_Poll_Outputdata()
{
    struct ns1__srmStatusOfPutRequestResponse *status_rep;
    
    status_rep = _status_response_->srmStatusOfPutRequestResponse;
    
    _request_SRMStatus = status_rep->returnStatus;
    _response->srmPrepareToPutResponse->remainingTotalRequestTime = status_rep->remainingTotalRequestTime;
    _response->srmPrepareToPutResponse->arrayOfFileStatuses = status_rep->arrayOfFileStatuses;
}

void SRM_Client_PtP::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "storageSystemInfo", _request->storageSystemInfo);
    print_Data(2, "arrayOfFileRequests", _request->arrayOfFileRequests);
    print_Data(2, "userRequestDescription", _request->userRequestDescription);
    print_Data(2, "overwriteOption", _request->overwriteOption);
    print_Data(2, "desiredTotalRequestTime", _request->desiredTotalRequestTime);
    print_Data(2, "desiredPinLifeTime", _request->desiredPinLifeTime);
    print_Data(2, "desiredFileLifeTime", _request->desiredFileLifeTime);
    print_Data(2, "desiredFileStorageType", _request->desiredFileStorageType);
    print_Data(2, "targetSpaceToken", _request->targetSpaceToken);
    print_Data(2, "targetFileRetentionPolicyInfo", _request->targetFileRetentionPolicyInfo);
    print_Data(2, "transferParameters", _request->transferParameters);
}

void SRM_Client_PtP::printRequestOutputdata()
{
    struct ns1__srmPrepareToPutResponse *rep = _response->srmPrepareToPutResponse;
    
    print_Data(2, "requestToken", rep->requestToken);
    print_Data(2, "remainingTotalRequestTime", rep->remainingTotalRequestTime);
    print_Data(2, "arrayOfFileStatuses", rep->arrayOfFileStatuses);
}
