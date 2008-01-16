#include "SRM_Client_PutDone.hpp"

void SRM_Client_PutDone::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
    print_Usage_requestToken();
    print_Usage_ArrayOfAnyURI();
}

/** Parse request specific options */
int SRM_Client_PutDone::parse_RequestOptions(char opt, int index, int argc, char** argv)
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
                index = parse_Arg(index, argc, argv, &(_request->arrayOfSURLs));
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_PutDone::set_Request_Status()
{
    if (_response->srmPutDoneResponse != NULL)
        _request_SRMStatus = _response->srmPutDoneResponse->returnStatus;
}

int SRM_Client_PutDone::execute_Request()
{ 
    int gSoapCode;

    gSoapCode = soap_call_ns1__srmPutDone(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return gSoapCode;
}

void SRM_Client_PutDone::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "requestToken", _request->requestToken);
    print_Data(2, "arrayOfSURLs", _request->arrayOfSURLs);
}

void SRM_Client_PutDone::printRequestOutputdata()
{
    print_Data(2, "arrayOfFileStatuses", _response->srmPutDoneResponse->arrayOfFileStatuses);
}
