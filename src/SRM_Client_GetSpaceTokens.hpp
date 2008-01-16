#ifndef SRM_CLIENT_GETSPACETOKENS_HPP_
#define SRM_CLIENT_GETSPACETOKENS_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_GetSpaceTokens : public SRM_Client_Common<struct ns1__srmGetSpaceTokensRequest, struct ns1__srmGetSpaceTokensResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmGetSpaceTokensRequest, struct ns1__srmGetSpaceTokensResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_GetSpaceTokens() : SRM_Client_Common_template("GetSpaceTokens") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmGetSpaceTokensResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_GETSPACETOKENS_HPP_*/
