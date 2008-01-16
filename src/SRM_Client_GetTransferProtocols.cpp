#include "SRM_Client_GetTransferProtocols.hpp"

void SRM_Client_GetTransferProtocols::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
}

/** Parse request specific options */
int SRM_Client_GetTransferProtocols::parse_RequestOptions(char opt, int index, int argc, char** argv)
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

void SRM_Client_GetTransferProtocols::set_Request_Status()
{
    if (_response->srmGetTransferProtocolsResponse != NULL)
        _request_SRMStatus = _response->srmGetTransferProtocolsResponse->returnStatus;
}

int SRM_Client_GetTransferProtocols::execute_Request()
{ 
    int gSoapCode;

    gSoapCode = soap_call_ns1__srmGetTransferProtocols(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return gSoapCode;
}

void SRM_Client_GetTransferProtocols::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
}

void SRM_Client_GetTransferProtocols::printRequestOutputdata()
{
	print_Data(2, "protocolInfo", _response->srmGetTransferProtocolsResponse->protocolInfo);
}
