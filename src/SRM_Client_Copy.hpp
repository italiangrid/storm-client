#ifndef SRM_CLIENT_COPY_HPP_
#define SRM_CLIENT_COPY_HPP_
// Copyright (c) Istituto Nazionale di Fisica Nucleare (INFN). 2006-2010.
/* Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "SRM_Client_Common.hpp"

#include <iostream>

class SRM_Client_Copy : public SRM_Client_Common<struct ns1__srmCopyRequest, struct ns1__srmCopyResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmCopyRequest, struct ns1__srmCopyResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_Copy();
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmCopyResponse); }

    private:
        int parse_RequestOptions(char opt, int index, int argc, char **argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
        void set_Poll_Inputdata();
        int poll_Request();
        void set_Request_Poll_Outputdata();
    
        /* Polling status request */
        struct ns1__srmStatusOfCopyRequestRequest *_status_request;
        struct ns1__srmStatusOfCopyRequestResponse_ *_status_response_;
};

#endif /*SRM_CLIENT_COPY_HPP_*/
