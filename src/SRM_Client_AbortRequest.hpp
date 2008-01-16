#ifndef SRM_CLIENT_ABORTREQUEST_HPP_
#define SRM_CLIENT_ABORTREQUEST_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_AbortRequest : public SRM_Client_Common<struct ns1__srmAbortRequestRequest, struct ns1__srmAbortRequestResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmAbortRequestRequest, struct ns1__srmAbortRequestResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_AbortRequest() : SRM_Client_Common_template("AbortRequest") { _verboseLevel += 'O'; }
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmAbortRequestResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_ABORTREQUEST_HPP_*/
