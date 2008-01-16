#ifndef SRM_CLIENT_MV_HPP_
#define SRM_CLIENT_MV_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_Mv : public SRM_Client_Common<struct ns1__srmMvRequest, struct ns1__srmMvResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmMvRequest, struct ns1__srmMvResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_Mv() : SRM_Client_Common_template("Mv") { _verboseLevel += 'O'; }
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmMvResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_MV_HPP_*/
