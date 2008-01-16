#include "SRM_Client_StatusPtP.hpp"

SRM_Client_StatusPtP::SRM_Client_StatusPtP() : SRM_Client_Common_template("StatusPtP")
{
    _status_request = storm::soap_calloc<struct ns1__srmStatusOfPutRequestRequest>(&_soap);
    _status_response_ = storm::soap_calloc<struct ns1__srmStatusOfPutRequestResponse_>(&_soap);
}

void SRM_Client_StatusPtP::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_poll();
    print_Usage_endpoint(); 
    print_Usage_authorizationID();
    print_Usage_requestToken();
    print_Usage_ArrayOfAnyURI();
}

/** Parse request specific options */
int SRM_Client_StatusPtP::parse_RequestOptions(char opt, int index, int argc, char **argv)
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
                index = parse_Arg(index, argc, argv, &(_request->arrayOfTargetSURLs));
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_StatusPtP::set_Request_Status()
{
    // Check if the request has been correctly executed
    if (_response->srmStatusOfPutRequestResponse == NULL)
        return;
    _request_SRMStatus = _response->srmStatusOfPutRequestResponse->returnStatus;
}

int SRM_Client_StatusPtP::execute_Request()
{ 
    int stat;

    stat = soap_call_ns1__srmStatusOfPutRequest(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return stat;
}

int SRM_Client_StatusPtP::poll_Request()
{
    int stat;

    stat = execute_Request();
    return stat;
}

void SRM_Client_StatusPtP::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "requestToken", _request->requestToken);
    print_Data(2, "arrayOfTargetSURLs", _request->arrayOfTargetSURLs);
}

void SRM_Client_StatusPtP::printRequestOutputdata()
{
    struct ns1__srmStatusOfPutRequestResponse *rep = _response->srmStatusOfPutRequestResponse;
    
    print_Data(2, "remainingTotalRequestTime", rep->remainingTotalRequestTime);
    print_Data(2, "arrayOfFileStatuses", rep->arrayOfFileStatuses);
}
