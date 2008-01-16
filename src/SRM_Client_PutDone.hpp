#ifndef SRM_CLIENT_PUTDONE_HPP_
#define SRM_CLIENT_PUTDONE_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_PutDone : public SRM_Client_Common<struct ns1__srmPutDoneRequest, struct ns1__srmPutDoneResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmPutDoneRequest, struct ns1__srmPutDoneResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_PutDone() : SRM_Client_Common_template("PutDone") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmPutDoneResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_PUTDONE_HPP_*/
