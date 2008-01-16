#include "SRM_Client_ReserveSpace.hpp"

void SRM_Client_ReserveSpace::print_Usage_Request()
{
    print_Usage_verboseLevel();
    print_Usage_endpoint();
    print_Usage_authorizationID();
    print_Usage_(OPT_REQUESTDESCRIPTION, "<userSpaceTokenDescription>", "Space token description string.");
    print_Usage_TRetentionPolicyInfo();
    print_Usage_(OPT_RS_DESIRED_SIZEOFTOTALSPACE, "<desiredSizeOfTotalSpace>",
                 "Total size of the space to reserve.");
    print_Usage_(OPT_RS_DESIRED_SIZEOFGUARANTEEDSPACE, "<desiredSizeOfGuaranteedSpace>",
                 "Minimum size of the space to reserve.");
    print_Usage_(OPT_RS_DESIRED_LIFETIMEOFRESERVEDSPACE, "<desiredLifetimeOfReservedSpace>",
                 "Lifetime of the space to reserve.");
    print_Usage_(OPT_RS_ARRAYOFEXPECTEDFILESIZES, "<arrayOfExpectedFileSizes>",
                 "Expected sizes of the files that will populate the allocated space.");
    print_Usage_ArrayOfTExtraInfo();
    print_Usage_TTransferParameters();
}

/** Parse request specific options */
int SRM_Client_ReserveSpace::parse_RequestOptions(char opt, int index, int argc, char** argv)
{
    try {        
        switch (opt) {
            case OPT_AUTHORIZATIONID:
                index = parse_Arg(index, argc, argv, &(_request->authorizationID));
                break;
            case OPT_REQUESTDESCRIPTION:
                index = parse_Arg(index, argc, argv, &(_request->userSpaceTokenDescription));
                break;
            case OPT_TRETENTIONPOLICYINFO:
                index = parse_Arg(index, argc, argv, &(_request->retentionPolicyInfo));
                break;
            case OPT_RS_DESIRED_SIZEOFTOTALSPACE:
                index = parse_Arg(index, argc, argv, &(_request->desiredSizeOfTotalSpace), WITH_OPTION);
                break;
            case OPT_RS_DESIRED_SIZEOFGUARANTEEDSPACE:
                index = parse_Arg(index, argc, argv, &(_request->desiredSizeOfGuaranteedSpace), WITH_OPTION);
                break;
            case OPT_RS_DESIRED_LIFETIMEOFRESERVEDSPACE:
                index = parse_Arg(index, argc, argv, &(_request->desiredLifetimeOfReservedSpace), WITH_OPTION);
                break;
            case OPT_RS_ARRAYOFEXPECTEDFILESIZES:
                index = parse_Arg(index, argc, argv, &(_request->arrayOfExpectedFileSizes));
                break;
            case OPT_TEXTRAINFO:
                index = parse_Arg(index, argc, argv, &(_request->storageSystemInfo));
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

void SRM_Client_ReserveSpace::set_Request_Status()
{
    if (_response->srmReserveSpaceResponse != NULL)
        _request_SRMStatus = _response->srmReserveSpaceResponse->returnStatus;
}

int SRM_Client_ReserveSpace::execute_Request()
{ 
    int gSoapCode;

    gSoapCode = soap_call_ns1__srmReserveSpace(&_soap, _endpoint, _serviceName.c_str(), _request, _response);
    return gSoapCode;
}

void SRM_Client_ReserveSpace::printRequestInputdata()
{
    print_Data(2, "authorizationID", _request->authorizationID);
    print_Data(2, "userSpaceTokenDescription", _request->userSpaceTokenDescription);
    print_Data(2, "retentionPolicyInfo", _request->retentionPolicyInfo);
    print_Data(2, "desiredSizeOfTotalSpace", _request->desiredSizeOfTotalSpace);
    print_Data(2, "desiredSizeOfGuaranteedSpace", _request->desiredSizeOfGuaranteedSpace);
    print_Data(2, "desiredLifetimeOfReservedSpace", _request->desiredLifetimeOfReservedSpace);
    print_Data(2, "arrayOfExpectedFileSizes", _request->arrayOfExpectedFileSizes);
    print_Data(2, "storageSystemInfo", _request->storageSystemInfo);
    print_Data(2, "transferParameters", _request->transferParameters);
}

void SRM_Client_ReserveSpace::printRequestOutputdata()
{
    struct ns1__srmReserveSpaceResponse* rep;
    
    rep = _response->srmReserveSpaceResponse;
    print_Data(2, "requestToken", rep->requestToken);
    print_Data(2, "estimatedProcessingTime", rep->estimatedProcessingTime);
    print_Data(2, "retentionPolicyInfo", rep->retentionPolicyInfo);
    print_Data(2, "sizeOfTotalReservedSpace", rep->sizeOfTotalReservedSpace);
    print_Data(2, "sizeOfGuaranteedReservedSpace", rep->sizeOfGuaranteedReservedSpace);
    print_Data(2, "lifetimeOfReservedSpace", rep->lifetimeOfReservedSpace);
    print_Data(2, "spaceToken", rep->spaceToken);    
}
