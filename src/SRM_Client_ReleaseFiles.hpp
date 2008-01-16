#ifndef SRM_CLIENT_RELEASEFILES_HPP_
#define SRM_CLIENT_RELEASEFILES_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_ReleaseFiles : public SRM_Client_Common<struct ns1__srmReleaseFilesRequest, struct ns1__srmReleaseFilesResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmReleaseFilesRequest, struct ns1__srmReleaseFilesResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_ReleaseFiles() : SRM_Client_Common_template("ReleaseFiles") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmReleaseFilesResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_RELEASEFILES_HPP_*/
