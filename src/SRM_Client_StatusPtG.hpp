#ifndef SRM_CLIENT_STATUSPTG_HPP_
#define SRM_CLIENT_STATUSPTG_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_StatusPtG : public SRM_Client_Common<struct ns1__srmStatusOfGetRequestRequest, struct ns1__srmStatusOfGetRequestResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmStatusOfGetRequestRequest, struct ns1__srmStatusOfGetRequestResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_StatusPtG();
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmStatusOfGetRequestResponse); }

    private:
        int parse_RequestOptions(char opt, int index, int argc, char **argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
        int poll_Request();
    
        /* Polling status request */
        struct ns1__srmStatusOfGetRequestRequest *_status_request;
        struct ns1__srmStatusOfGetRequestResponse_ *_status_response_;
};

#endif /*SRM_CLIENT_STATUSPTG_HPP_*/
