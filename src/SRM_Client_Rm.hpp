#ifndef SRM_CLIENT_RM_HPP_
#define SRM_CLIENT_RM_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_Rm : public SRM_Client_Common<struct ns1__srmRmRequest, struct ns1__srmRmResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmRmRequest, struct ns1__srmRmResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_Rm() : SRM_Client_Common_template("Rm") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmRmResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_RM_HPP_*/
