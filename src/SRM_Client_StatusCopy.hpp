#ifndef SRM_CLIENT_STATUSCOPY_HPP_
#define SRM_CLIENT_STATUSCOPY_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_StatusCopy : public SRM_Client_Common<struct ns1__srmStatusOfCopyRequestRequest, struct ns1__srmStatusOfCopyRequestResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmStatusOfCopyRequestRequest, struct ns1__srmStatusOfCopyRequestResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_StatusCopy();
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmStatusOfCopyRequestResponse); }

    private:
        int parse_RequestOptions(char opt, int index, int argc, char **argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
        int poll_Request();
    
        /* Polling status request */
        struct ns1__srmStatusOfCopyRequestRequest *_status_request;
        struct ns1__srmStatusOfCopyRequestResponse_ *_status_response_;
};

#endif /*SRM_CLIENT_STATUSCOPY_HPP_*/
