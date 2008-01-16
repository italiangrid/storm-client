#ifndef SRM_CLIENT_BOL_HPP_
#define SRM_CLIENT_BOL_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_BOL : public SRM_Client_Common<struct ns1__srmBringOnlineRequest, struct ns1__srmBringOnlineResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmBringOnlineRequest, struct ns1__srmBringOnlineResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_BOL();
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmBringOnlineResponse); }

    private:
        int parse_RequestOptions(char opt, int index, int argc, char **argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
        void set_Poll_Inputdata();
        int poll_Request();
        void set_Request_Poll_Outputdata();
    
        /* Polling status request */
        struct ns1__srmStatusOfBringOnlineRequestRequest *_status_request;
        struct ns1__srmStatusOfBringOnlineRequestResponse_ *_status_response_;
};

#endif /*SRM_CLIENT_BOL_HPP_*/
