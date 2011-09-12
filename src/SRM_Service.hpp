#ifndef SRM_SERVICE_HPP_
#define SRM_SERVICE_HPP_
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

#include <string>

class SRM_Service {

public:
    SRM_Service() {};
    virtual ~SRM_Service() {}
    
    virtual std::string getServiceName() = 0;
    virtual void setEndpoint(std::string endpoint) = 0;
    virtual void setRequestInputData(void* inputData) = 0;
    virtual void setPollflag(bool pollState) = 0;
    
    virtual char* getEndpoint() = 0;
    virtual bool getPollflag() = 0;
    virtual std::string getVerboseLevel() = 0;
    virtual bool getVerboseLevel_Input() = 0;
    virtual bool getVerboseLevel_GlobalOptions() = 0;
    virtual bool getVerboseLevel_Endpoint() = 0;
    virtual bool getVerboseLevel_Output() = 0;
    virtual bool getVerboseLevel_SepLines() = 0;
    virtual int getRequestStatusCode() = 0;
    virtual char* getRequestStatusExplanation() = 0;
    virtual void* getRequestInputdata() = 0;
    virtual void* getRequestOutputdata() = 0;
    
    virtual int parseFromCommandLine(int index, int argc, char** argv) = 0;
    virtual std::string getParseErrorExplanation() = 0;
    
    virtual int execute() = 0;
    virtual int poll() = 0;
    
    virtual void printUsage() = 0;
    virtual void printRequestInputdata() = 0;
    virtual void printRequestOutputdata() = 0;
    virtual void printRequestStatus() = 0;
    
    static const int NO_FAILURE = 0;
    static const int PARSE_FAILURE = 1;
    static const int PRINT_USAGE = 2;
};

#endif /*SRM_SERVICE_HPP_*/
