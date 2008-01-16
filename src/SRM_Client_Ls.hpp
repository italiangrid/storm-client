#ifndef SRM_CLIENT_LS_HPP_
#define SRM_CLIENT_LS_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_Ls : public SRM_Client_Common<struct ns1__srmLsRequest, struct ns1__srmLsResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmLsRequest, struct ns1__srmLsResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_Ls() : SRM_Client_Common_template("Ls") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmLsResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_LS_HPP_*/
