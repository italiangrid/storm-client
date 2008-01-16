#ifndef SRM_CLIENT_RESERVESPACE_HPP_
#define SRM_CLIENT_RESERVESPACE_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_ReserveSpace : public SRM_Client_Common<struct ns1__srmReserveSpaceRequest, struct ns1__srmReserveSpaceResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmReserveSpaceRequest, struct ns1__srmReserveSpaceResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_ReserveSpace() : SRM_Client_Common_template("ReserveSpace") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmReserveSpaceResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_RESERVESPACE_HPP_*/
