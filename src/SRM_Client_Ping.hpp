#ifndef SRM_CLIENT_PING_HPP_
#define SRM_CLIENT_PING_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_Ping : public SRM_Client_Common<struct ns1__srmPingRequest, struct ns1__srmPingResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmPingRequest, struct ns1__srmPingResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_Ping() : SRM_Client_Common_template("Ping") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmPingResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_PING_HPP_*/
