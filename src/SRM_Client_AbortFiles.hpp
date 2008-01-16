#ifndef SRM_CLIENT_ABORTFILES_HPP_
#define SRM_CLIENT_ABORTFILES_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_AbortFiles : public SRM_Client_Common<struct ns1__srmAbortFilesRequest, struct ns1__srmAbortFilesResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmAbortFilesRequest, struct ns1__srmAbortFilesResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_AbortFiles() : SRM_Client_Common_template("AbortFiles") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmAbortFilesResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_ABORTFILES_HPP_*/
