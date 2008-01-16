#ifndef SRM_CLIENT_EXTENDFILELIFETIME_HPP_
#define SRM_CLIENT_EXTENDFILELIFETIME_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_ExtendFileLifeTime : public SRM_Client_Common<struct ns1__srmExtendFileLifeTimeRequest, struct ns1__srmExtendFileLifeTimeResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmExtendFileLifeTimeRequest, struct ns1__srmExtendFileLifeTimeResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_ExtendFileLifeTime() : SRM_Client_Common_template("ExtendFileLifeTime") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmExtendFileLifeTimeResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_EXTENDFILELIFETIME_HPP_*/
