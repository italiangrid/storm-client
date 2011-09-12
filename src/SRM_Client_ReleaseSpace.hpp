#ifndef SRM_CLIENT_RELEASESPACE_HPP_
#define SRM_CLIENT_RELEASESPACE_HPP_
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

class SRM_Client_ReleaseSpace : public SRM_Client_Common<struct ns1__srmReleaseSpaceRequest, struct ns1__srmReleaseSpaceResponse_>
{
    typedef SRM_Client_Common<struct ns1__srmReleaseSpaceRequest, struct ns1__srmReleaseSpaceResponse_> SRM_Client_Common_template;
    
public:
    SRM_Client_ReleaseSpace() : SRM_Client_Common_template("ReleaseSpace") { _verboseLevel += 'O'; }
    void printRequestInputdata();
    void printRequestOutputdata();
    void* getRequestOutputdata() { return static_cast<void*> (_response->srmReleaseSpaceResponse);}

    private:
        int parse_RequestOptions(char opt, int index, int argc, char** argv);
        void print_Usage_Request();
        void set_Request_Status();
        int execute_Request();
};

#endif /*SRM_CLIENT_RELEASESPACE_HPP_*/
