#ifndef SRM_CLIENT_COPY_HPP_
#define SRM_CLIENT_COPY_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_Copy : public SRM_Client_Common<struct ns1__srmCopyRequest, struct ns1__srmCopyResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmCopyRequest, struct ns1__srmCopyResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_Copy();
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmCopyResponse); }

    private:
        int parse_RequestOptions(char opt, int index, int argc, char **argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
        void set_Poll_Inputdata();
        int poll_Request();
        void set_Request_Poll_Outputdata();
    
        /* Polling status request */
        struct ns1__srmStatusOfCopyRequestRequest *_status_request;
        struct ns1__srmStatusOfCopyRequestResponse_ *_status_response_;
};

#endif /*SRM_CLIENT_COPY_HPP_*/
