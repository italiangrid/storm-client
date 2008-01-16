#include "SRM_Client_ReleaseFiles.hpp"

void SRM_Client_ReleaseFiles::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
    print_Usage_requestToken();
    print_Usage_ArrayOfAnyURI();
    print_Usage_(OPT_RELEASEFILES_DOREMOVE, "[doRemove]", "0=False, 1=True. The pin on the file is released and the \"copy\" or \"state\"");
    print_Usage_(' ', NULL, "is removed and the SRM may release the resource");
}

/** Parse request specific options */
int SRM_Client_ReleaseFiles::parse_RequestOptions(char opt, int index, int argc, char** argv)
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
            case OPT_RELEASEFILES_DOREMOVE:
            	index = parse_Arg(index, argc, argv, &(_request->doRemove), WITH_OPTION);
            	break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_ReleaseFiles::set_Request_Status()
{
    if (_response->srmReleaseFilesResponse != NULL)
        _request_SRMStatus = _response->srmReleaseFilesResponse->returnStatus;
}

int SRM_Client_ReleaseFiles::execute_Request()
{ 
    int gSoapCode;

    gSoapCode = soap_call_ns1__srmReleaseFiles(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return gSoapCode;
}

void SRM_Client_ReleaseFiles::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "requestToken", _request->requestToken);
    print_Data(2, "arrayOfSURLs", _request->arrayOfSURLs);
    print_Data(2, "doRemove", _request->doRemove);
}

void SRM_Client_ReleaseFiles::printRequestOutputdata()
{
    print_Data(2, "arrayOfFileStatuses", _response->srmReleaseFilesResponse->arrayOfFileStatuses);
}
