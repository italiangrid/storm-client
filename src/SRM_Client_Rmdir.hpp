#ifndef SRM_CLIENT_RMDIR_HPP_
#define SRM_CLIENT_RMDIR_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_Rmdir : public SRM_Client_Common<struct ns1__srmRmdirRequest, struct ns1__srmRmdirResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmRmdirRequest, struct ns1__srmRmdirResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_Rmdir() : SRM_Client_Common_template("Rmdir") { _verboseLevel += 'O'; }
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmRmdirResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_RMDIR_HPP_*/
