#ifndef SRM_CLIENT_GETREQUESTTOKENS_HPP_
#define SRM_CLIENT_GETREQUESTTOKENS_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_GetRequestTokens : public SRM_Client_Common<struct ns1__srmGetRequestTokensRequest, struct ns1__srmGetRequestTokensResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmGetRequestTokensRequest, struct ns1__srmGetRequestTokensResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_GetRequestTokens() : SRM_Client_Common_template("GetRequestTokens") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmGetRequestTokensResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_GETREQUESTTOKENS_HPP_*/
