#include "SRM_Client_Rmdir.hpp"

void SRM_Client_Rmdir::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
    print_Usage_SURL();
    print_Usage_ArrayOfTExtraInfo();
    print_Usage_(OPT_RMDIR_RECURSIVE, "<recursive>", "0=false, 1=true. If true");
}

/** Parse request specific options */
int SRM_Client_Rmdir::parse_RequestOptions(char opt, int index, int argc, char** argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_SURL:
                index = parse_Arg(index, argc, argv, &(_request->SURL));
                break;
            case OPT_TEXTRAINFO:
                index = parse_Arg(index, argc, argv, &(_request->storageSystemInfo));
                break;
            case OPT_RMDIR_RECURSIVE:
                index = parse_Arg(index, argc, argv, &(_request->recursive), WITH_OPTION);
                break;
        }
    }
    catch (...) {
        throw;
    }
    return index;
}

void SRM_Client_Rmdir::set_Request_Status()
{
    if (_response->srmRmdirResponse != NULL)
        _request_SRMStatus = _response->srmRmdirResponse->returnStatus;
}

int SRM_Client_Rmdir::execute_Request()
{ 
    int gSoapCode;

    gSoapCode = soap_call_ns1__srmRmdir(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return gSoapCode;
}

void SRM_Client_Rmdir::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "SURL", _request->SURL);
    print_Data(2, "storageSystemInfo", _request->storageSystemInfo);
    print_Data(2, "recursive", _request->recursive);
}

void SRM_Client_Rmdir::printRequestOutputdata() {}
