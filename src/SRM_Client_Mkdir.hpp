#ifndef SRM_CLIENT_MKDIR_HPP_
#define SRM_CLIENT_MKDIR_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_Mkdir : public SRM_Client_Common<struct ns1__srmMkdirRequest, struct ns1__srmMkdirResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmMkdirRequest, struct ns1__srmMkdirResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_Mkdir() : SRM_Client_Common_template("Mkdir") { _verboseLevel += 'O'; }
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmMkdirResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_MKDIR_HPP_*/
