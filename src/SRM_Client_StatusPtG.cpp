#include "SRM_Client_StatusPtG.hpp"

SRM_Client_StatusPtG::SRM_Client_StatusPtG() : SRM_Client_Common_template("StatusPtG")
{
    _status_request = storm::soap_calloc<struct ns1__srmStatusOfGetRequestRequest>(&_soap);
    _status_response_ = storm::soap_calloc<struct ns1__srmStatusOfGetRequestResponse_>(&_soap);
}

void SRM_Client_StatusPtG::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_poll();
    print_Usage_endpoint(); 
    print_Usage_authorizationID();
    print_Usage_requestToken();
    print_Usage_ArrayOfAnyURI();
}

/** Parse request specific options */
int SRM_Client_StatusPtG::parse_RequestOptions(char opt, int index, int argc, char **argv)
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

void SRM_Client_StatusPtG::set_Request_Status()
{
    // Check if the request has been correctly executed
    if (_response->srmStatusOfGetRequestResponse == NULL)
        return;
    _request_SRMStatus = _response->srmStatusOfGetRequestResponse->returnStatus;
}

int SRM_Client_StatusPtG::execute_Request()
{ 
    int stat;

    stat = soap_call_ns1__srmStatusOfGetRequest(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return stat;
}

int SRM_Client_StatusPtG::poll_Request()
{
    int stat;

    stat = execute_Request();
    return stat;
}

void SRM_Client_StatusPtG::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "requestToken", _request->requestToken);
    print_Data(2, "arrayOfSourceSURLs", _request->arrayOfSourceSURLs);
}

void SRM_Client_StatusPtG::printRequestOutputdata()
{
    struct ns1__srmStatusOfGetRequestResponse *rep = _response->srmStatusOfGetRequestResponse;
    
    print_Data(2, "remainingTotalRequestTime", rep->remainingTotalRequestTime);
    print_Data(2, "arrayOfFileStatuses", rep->arrayOfFileStatuses);
}
