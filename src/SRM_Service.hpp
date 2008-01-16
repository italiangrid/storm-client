#ifndef SRM_SERVICE_HPP_
#define SRM_SERVICE_HPP_

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
