#ifndef SRM_CLIENT_GETREQUESTSUMMARY_HPP_
#define SRM_CLIENT_GETREQUESTSUMMARY_HPP_

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_GetRequestSummary : public SRM_Client_Common<struct ns1__srmGetRequestSummaryRequest, struct ns1__srmGetRequestSummaryResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmGetRequestSummaryRequest, struct ns1__srmGetRequestSummaryResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_GetRequestSummary() : SRM_Client_Common_template("GetRequestSummary") {}
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmGetRequestSummaryResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_GETREQUESTSUMMARY_HPP_*/
