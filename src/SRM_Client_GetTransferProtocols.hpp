#ifndef SRM_CLIENT_GETTRANSFERPROTOCOLS_HPP_
#define SRM_CLIENT_GETTRANSFERPROTOCOLS_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_GetTransferProtocols : public SRM_Client_Common<struct ns1__srmGetTransferProtocolsRequest, struct ns1__srmGetTransferProtocolsResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmGetTransferProtocolsRequest, struct ns1__srmGetTransferProtocolsResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_GetTransferProtocols() : SRM_Client_Common_template("GetTransferProtocols") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmGetTransferProtocolsResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_GETTRANSFERPROTOCOLS_HPP_*/
