#ifndef SRM_CLIENT_PTP_HPP_
#define SRM_CLIENT_PTP_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_PtP : public SRM_Client_Common<struct ns1__srmPrepareToPutRequest, struct ns1__srmPrepareToPutResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmPrepareToPutRequest, struct ns1__srmPrepareToPutResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_PtP();
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmPrepareToPutResponse); }

    private:
        int parse_RequestOptions(char opt, int index, int argc, char **argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
        void set_Poll_Inputdata();
        int poll_Request();
        void set_Request_Poll_Outputdata();
    
        /* Polling status request */
        struct ns1__srmStatusOfPutRequestRequest *_status_request;
        struct ns1__srmStatusOfPutRequestResponse_ *_status_response_;
};

#endif /*SRM_CLIENT_PTP_HPP_*/
