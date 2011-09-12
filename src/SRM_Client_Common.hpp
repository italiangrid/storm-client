#ifndef SRM_CLIENT_COMMON_HPP_
#define SRM_CLIENT_COMMON_HPP_
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

#include <stdexcept>
#include "srmv2H.h"
#include "storm_util.hpp"
#include "soap_util.hpp"
#include "SRM_Service.hpp"

#ifdef GSI_PLUGINS
#include <cgsi_plugin.h>
#endif

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename type_t>
bool string2num(type_t& x, const string& s) {
  istringstream ss(s);
  return (ss >> x).fail();
}

template<class T>
inline std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template<typename srm_request_t, typename srm_response_t>
class SRM_Client_Common : public virtual SRM_Service {
    
protected:
    virtual void print_Usage_Request() = 0;
    virtual void set_Request_Status() = 0;
    virtual int parse_RequestOptions(char opt, int index, int argc, char** argv) = 0;
    virtual int execute_Request() = 0;
    virtual void set_Poll_Inputdata() {}
    virtual int poll_Request() { return _soap.error; }
    virtual void set_Request_Poll_Outputdata() {}
    
public:
    virtual void printRequestInputdata() = 0;
    virtual void printRequestOutputdata() = 0;
    virtual void* getRequestOutputdata() = 0;

    SRM_Client_Common(string serviceName) : _serviceName(serviceName), _programName("clientSRM"),
                                            _pollFlag(false), _verboseLevel_print_NULL(false),
                                            _verboseLevel_print_Input(false),
                                            _verboseLevel_print_GlobalOptions(false),
                                            _verboseLevel_print_Endpoint(true),
                                            _verboseLevel_print_Output(true),
                                            _verboseLevel_print_SepLines(true)
    {
        // Initialize GSOAP stuff and CGSI plugin
        soap_init(&_soap);
#ifdef GSI_PLUGINS
        if (_serviceName == "Copy") {
        _flags = CGSI_OPT_DISABLE_NAME_CHECK|CGSI_OPT_DELEG_FLAG;
        } else {
        	_flags = CGSI_OPT_DISABLE_NAME_CHECK;
        }
        soap_register_plugin_arg(&_soap, client_cgsi_plugin, &_flags);
#endif
        // Allocate memory for the request input/output data structures
        _request = storm::soap_calloc<srm_request_t>(&_soap);
        _response = storm::soap_calloc<srm_response_t>(&_soap);
    }
    
    ~SRM_Client_Common()
    {
        soap_destroy(&_soap);
        soap_end(&_soap);
        soap_done(&_soap);
    }
    
    /** Get service name */
    string getServiceName() { return _serviceName; }
    
    /** Set endpoint */
    void setEndpoint(string endpoint) { _endpoint = soap_strdup(&_soap, endpoint.c_str()); }
     
    /** Get endpoint */
    char* getEndpoint() { return _endpoint; }
    
    /** Set request inoutdata */
    void setRequestInputData(void* inputData) { _request = (srm_request_t*) inputData; }
    
    /** Get explanation of parsing error */
    string getParseErrorExplanation() { return _parse_error_explanation; }
    
    /** Get the value of the poll flag */
    bool getPollflag() { return _pollFlag; }
    
    /** Set the value of the poll flag */
    void setPollflag(bool pollState) { _pollFlag = pollState; }
    
    /** Get the verbose level */
    string getVerboseLevel() { return _verboseLevel; }
    
    /** Get the verbose level for Inputdata */
    bool getVerboseLevel_Input() { return _verboseLevel_print_Input; }
    
    /** Get the verbose level for Global options */
    bool getVerboseLevel_GlobalOptions() { return _verboseLevel_print_GlobalOptions; }
    
    /** Get the verbose level for Endpoint */
    bool getVerboseLevel_Endpoint() { return _verboseLevel_print_Endpoint; }
    
    /** Get the verbose level for Output */
    bool getVerboseLevel_Output() { return _verboseLevel_print_Output; }
    
    /** Get the verbose level for separation lines */
    bool getVerboseLevel_SepLines() { return _verboseLevel_print_SepLines; }
        
    /** Get the status code of the SRM request */
    int getRequestStatusCode()
    {
        if (_request_SRMStatus == NULL)
            return -1;
        return _request_SRMStatus->statusCode;
    }
    
    /** Get the status explanation of the SRM request */
    char* getRequestStatusExplanation()
    {
        if (_request_SRMStatus == NULL)
            return NULL;
        return _request_SRMStatus->explanation;
    }
    
    void* getRequestInputdata()
    {
        return static_cast<void*> (_request);
    }
    
    /** Parse options from command line */
    int parseFromCommandLine(int index, int argc, char **argv)
    {
        int prev_index;
        char opt;
        bool invalidOption;
        
        if (!(_parse_error_explanation.empty()))
			_parse_error_explanation.clear();
        
        if (index == argc)
            return PRINT_USAGE;
        try {
            while (index < argc) {
                opt = getOpt(argv[index]); 
                prev_index = index;           
                index = parse_CommonGlobalOptions(opt, index, argc, argv);
                if (prev_index != index)
                    continue;
                index = parse_RequestOptions(opt, index, argc, argv);
                if (index == prev_index) {
                    _parse_error_explanation = argv[index];
                    return PARSE_FAILURE;
                }
            }
        }
        catch (PrintUsage) {
            return PRINT_USAGE;
        }
        catch (InvalidOption e) {
            _parse_error_explanation = e.getExplanation();
            return PARSE_FAILURE;
        }
        return NO_FAILURE;
    }
    
    /** Parse options common to all (almost all) requests */
    int parse_CommonGlobalOptions(char opt, int index, int argc, char **argv)
    {
        try {
            switch (opt) {
                case OPT_ENDPOINT:
                    index = parse_Arg(index, argc, argv, &_endpoint);
                    break;
                case OPT_POLLFLAG:
                    _pollFlag = true;
                    index++;
                    break;
                case OPT_VERBOSELEVEL:
                    index = parse_Arg_VerboseLevel(index, argc, argv, &_verboseLevel);
                    break;
                case OPT_HELP:
                    throw PrintUsage();
            }
        }
        catch (...) {
            throw;
        }
        return index;
    }
    
    /** Executes the request */
    int execute()
    {
        int stat;
        
        stat = execute_Request();
        if (stat == 0) {
            set_Request_Status();
            set_Poll_Inputdata();
        }
        return stat;
    }
    
    /** Poll the status of the request */
    int poll()
    {
        int stat;
        
        stat = poll_Request();
        set_Request_Poll_Outputdata();
        return stat;
    }

    /** Print the status of the request: the gSoap status if the request failed
      * at gSoap level, otherwise the SRM status. */
    void printRequestStatus() {
        cout << "Request status:\n";
        if (!(_parse_error_explanation.empty())) {
        	cout << "\nInvalid argument: " << _parse_error_explanation << endl << endl;
        	return;
        }
        	
        switch (_soap.error) {
            case SOAP_OK:
            	if (_request_SRMStatus != NULL)
                	print_Data(2, NULL, _request_SRMStatus);
                break;
            default:
                cout << "gSoap code: " << _soap.error << endl << endl;
                cout << "soap_print_fault:\n";
                soap_print_fault(&_soap, stdout);
                cout << "\n\nsoap_print_fault_location:\n";
                soap_print_fault_location(&_soap, stdout);
        }
    }

protected:
	/*************************************************************************/
    /******** Utilities for fill request arguments from the command line *****/
    /*************************************************************************/
    
    /** Assign to a variable of type arg_t* the parsed argument.
     * It allocates memory for "req_param".
     * "hasOption" specifies if the argument to be parsed is identified by an option or not. 
     * Retruns the next index in "argv". */
    template<typename arg_t>
    int parse_Arg(int index, int argc, char** argv, arg_t** req_param, bool hasOption)
    {
        string opt;
        string optArg;
        
        *req_param = NULL;
        try {
            if (hasOption)
                index = getOptArg(index, argc, argv, &opt, &optArg);
            else {
                optArg = argv[index];
                index++;
            }
        }
        catch (...) {
            throw;
        }
        
        *req_param = storm::soap_calloc<arg_t>(&_soap);
        if (string2num(**req_param, optArg))
            throw InvalidOption(opt, "not a number");
        
        return index;
    }
    
    /** Assign to a variable of type arg_t the parsed argument.
     * It does NOT allocate memory for "req_param".
     * "hasOption" specifies if the argument to be parsed is identified by an option or not. 
     * Retruns the next index in "argv". */
    template<typename arg_t>
    int parse_Arg(int index, int argc, char** argv, arg_t* req_param, bool hasOption)
    {
        string opt;
        string optArg;
        
        try {
            if (hasOption)
                index = getOptArg(index, argc, argv, &opt, &optArg);
            else {
                optArg = argv[index];
                index++;
            }
        }
        catch (...) {
            throw;
        }
        
        if (string2num(*req_param, optArg))
            throw InvalidOption(opt, "not a number");
        
        return index;
    }
    
    /** Assign to a variable of type char* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, char** req_param)
    {
        string optArg;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, NULL, &optArg);
        }
        catch (...) {
            throw;
        }
        *req_param = soap_strdup(&_soap, optArg.c_str());
        
        return index;
    }
    
    /** Assign to a variable of type xsd__boolean* the parsed argument.
     * It allocates memory for "req_param".
     * Returns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, xsd__boolean** req_param, bool hasOption)
    {
    	string opt;
        string optArg;
        int parsedVal;
        xsd__boolean boolVal;
        
        *req_param = NULL;
        try {
        	if (hasOption)
            	index = getOptArg(index, argc, argv, &opt, &optArg);
        	else {
        		optArg = argv[index];
        		index++;
        	}
            string2num(parsedVal, optArg);
        }
		catch (...) {
            parsedVal = 1;
            index++;
        }
        
        if (parsedVal == 0)
            	boolVal = xsd__boolean(0);
        	else if (parsedVal == 1)
        		boolVal = xsd__boolean(1);
    		else
    			throw InvalidOption(opt, "illegal value: " + optArg);
			
        *req_param = storm::soap_calloc<xsd__boolean>(&_soap);
        **req_param = boolVal;
        
        return index;
    }
    
    /** Assign to a variable of type xsd__boolean the parsed argument.
     * It DOES NOT allocate memory for "req_param".
     * Returns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, xsd__boolean* req_param, bool hasOption)
    {
    	string opt;
        string optArg;
        int parsedVal;
        xsd__boolean boolVal;
        
        try {
        	if (hasOption)
            	index = getOptArg(index, argc, argv, &opt, &optArg);
        	else {
        		optArg = argv[index];
        		index++;
        	}
            string2num(parsedVal, optArg);
        }
		catch (...) {
            parsedVal = 1;
            index++;
        }
        
        if (parsedVal == 0)
            	boolVal = xsd__boolean(0);
        	else if (parsedVal == 1)
        		boolVal = xsd__boolean(1);
    		else
    			throw InvalidOption(opt, "illegal value: " + optArg);
			
        *req_param = boolVal;
        
        return index;
    }

    /** Assign to a variable of type struct ns1__ArrayOfTExtraInfo* the parsed argument.
     * It allocates memory for "req_param".
     * Returns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__ArrayOfTExtraInfo** req_param)
    {
    	struct ns1__ArrayOfTExtraInfo* extraInfoStructure;
        string opt;
        string optArg;
        int numItems;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, &opt, &optArg);
        }
        catch (...) {
            throw;
        }
            
        // The format of the string to parse is: <key1.value1[,key2.value2[,...]]>
        vector<string> tokens;
        numItems = tokenize(optArg, &tokens, ',');
        // Allocate memory for the req_param structure
        extraInfoStructure = storm::soap_calloc<struct ns1__ArrayOfTExtraInfo>(&_soap);
		extraInfoStructure->__sizeextraInfoArray = numItems;
		if (numItems > 0)
        	extraInfoStructure->extraInfoArray = storm::soap_calloc<struct ns1__TExtraInfo>(&_soap, numItems);
    	else
    		extraInfoStructure->extraInfoArray = NULL;
        // Fill the output structure with the couples (key.value)
        for (int i=0; i<numItems; i++) {
        	struct ns1__TExtraInfo* extraInfo;
        	vector<string> couple;
        	int nc;
        	// Retrieve couple[i]
        	nc = tokenize(tokens[i], &couple, '.', 2);
        	if (nc > 2)
        		throw InvalidOption(opt, "illegal format (key.value)");
        	if (nc > 0) {
        		extraInfo = extraInfoStructure->extraInfoArray[i] = storm::soap_calloc<struct ns1__TExtraInfo>(&_soap);
				if (!(couple[1].empty()))
    				extraInfo->value = soap_strdup(&_soap, couple[1].c_str());
				else
					extraInfo->value = NULL;
				couple.pop_back();
    			if (!(couple[0].empty()))
        			extraInfo->key = soap_strdup(&_soap, couple[0].c_str());
				else
					extraInfo->key = NULL;
    			couple.pop_back();
        	}
        	else
        		extraInfoStructure->extraInfoArray[i] = NULL;
        }
        *req_param = extraInfoStructure;
        return index;
    }
    
    /** Assign to a variable of type struct ns1__ArrayOfTPutFileRequest* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__ArrayOfTPutFileRequest** req_param)
    {
        struct ns1__ArrayOfTPutFileRequest* req;
        string opt;
        string optArg;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, &opt, &optArg);
        }
        catch (...) {
            throw;
        }
        
        /* Find the number of TPutFileRequest elements */
        int numElements = 1;
        int i = index;
        for (; i<argc; i++) {
            if (*argv[i] == '-')
                break;
            numElements++;
        }
        
        /* Memory allocation for the output structure */
        req = storm::soap_calloc<struct ns1__ArrayOfTPutFileRequest>(&_soap);
        req->requestArray = storm::soap_calloc<struct ns1__TPutFileRequest>(&_soap, numElements);
        req->__sizerequestArray = numElements;
        /* Parse arguments */
        for (i=0; i<numElements; i++, index++) {
        	vector<string> arg;
        	int n = tokenize(optArg, &arg, ',', 2);
        	if (n > 2)
        		throw InvalidOption(opt, "illegal format (SURL,expectedFileSize)");
        	if (n > 0) {
        		try {
            		req->requestArray[i] = storm::soap_calloc<struct ns1__TPutFileRequest>(&_soap);
            		// Get SURL
            		char* str = const_cast<char*> (arg[0].c_str());
            		parse_SURL(0, 1, &str, &(req->requestArray[i]->targetSURL), WITHOUT_OPTION);
            		// Get expectedFileSize
            		if (!(arg[1].empty())) {
            			str = const_cast<char*> (arg[1].c_str());
            			parse_Arg(0, 1, &str,  &(req->requestArray[i]->expectedFileSize), WITHOUT_OPTION);
            		}
            		if (index < argc)
                    	optArg = argv[index];
        		} catch (...) {
        			throw;
        		}
        	}
        }
        *req_param = req;
        return (index-1);
    }
    
    /** Assign to a variable of type struct ns1__TRetentionPolicyInfo* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__TRetentionPolicyInfo** req_param)
    {
        struct ns1__TRetentionPolicyInfo* req;
        string opt;
        string optArg;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, &opt, &optArg);
        }
        catch (...) {
            throw;
        }
        vector<string> arg;
        int n = tokenize(optArg, &arg, ',', 2);
        if (n > 2)
        	throw InvalidOption(opt, "illegal format (<retentionPolicy,accessLatency>)");
    	if (n > 0) {
    		try {
	    		if (arg[0].empty())
	            	throw InvalidOption(opt, "retentionPolicy is required");
	        	req = storm::soap_calloc<struct ns1__TRetentionPolicyInfo>(&_soap);
	        	char* str = const_cast<char*> (arg[0].c_str());
	        	parse_Arg_enum(0, 1, &str, &(req->retentionPolicy), WITHOUT_OPTION);
	        	if (!(arg[1].empty())) {
	        		str = const_cast<char*> (arg[1].c_str());
	                parse_Arg_enum(0, 1, &str, &(req->accessLatency), WITHOUT_OPTION);
	        	}
    		} 
    		catch (...) {
    			throw;
    		}
    		
    	}
        *req_param = req;
        return index;
    }
    
    /** Assign to a variable of type struct ns1__TDirOption* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__TDirOption** req_param)
    {
        struct ns1__TDirOption* req;
        string opt;
        string optArg;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, &opt, &optArg);
        }
        catch (...) {
        	throw;
        }
        vector<string> arg;
        int n = tokenize(optArg, &arg, ',');
        if ((n<1) || (n>3))
        	throw InvalidOption(opt, "<isDir,recursive,numLevels>");
    
        req = storm::soap_calloc<struct ns1__TDirOption>(&_soap);
        // Get <isDir>
        if (arg[0].empty())
            throw InvalidOption(opt, "isDir parameter is required");
        try {
            char* str = const_cast<char*> (arg[0].c_str());
          	parse_Arg(0, 1, &str, &(req->isSourceADirectory), WITHOUT_OPTION);
          	switch (n) {
	      		case 3: // Get <numLevels>
	      			if (!(arg[2].empty())) {
		                str = const_cast<char*> (arg[2].c_str());
		                parse_Arg(0, 1, &str, &(req->numOfLevels), WITHOUT_OPTION);
		            }
	            case 2: // Get <recursive>
	            	if (!(arg[1].empty())) {
		                str = const_cast<char*> (arg[1].c_str());
		                parse_Arg(0, 1, &str, &(req->allLevelRecursive), WITHOUT_OPTION);
		            }
	          	}
        }
        catch (InvalidOption e) {
        	throw InvalidOption(opt, e.getExplanation());
        }
        catch (...) {
            throw;
        }
        
        *req_param = req;
        
        return index;
    }
    
    /** Assign to a variable of type struct ns1__ArrayOfTGetFileRequest* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__ArrayOfTGetFileRequest** req_param)
    {
        struct ns1__TDirOption* dirOpt;
        vector<struct ns1__TDirOption*> dirOpts;
        vector<char*> surls;
        string opt;
        string optArg;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, &opt, &optArg);
        }
        catch (...) {
            throw;
        }
        
        index--;
        // Parse options and storing values in vector 'surls'.
        while (optArg[0] != '-') {
            // Parse SURL
            char* surl;
            char* str = const_cast<char*> (optArg.c_str());
            parse_SURL(0, 1, &str, &surl, WITHOUT_OPTION);
            surls.push_back(surl);
            index++;
            if (index == argc) {
                dirOpts.push_back(NULL);
                optArg = '-';
                continue;
            }
            // Parse TDirOption
            try {
                getOptArg(index, argc, argv, &opt, &optArg);
            }
            catch (...) {
            }
            if (opt[0] == NO_OPT) { // Current optArg is another SURL
                dirOpts.push_back(NULL);
                continue;
            }
            else if (opt[1] != OPT_TDIROPTION) { // Stop parsing ArryayOfTGetFileRequest
                dirOpts.push_back(NULL);
                optArg = '-';
                continue;
            } else { // TDirOption found
            	try {
                	index = parse_Arg(index, argc, argv, &dirOpt);
                	dirOpts.push_back(dirOpt);
                	if (index == argc)
                    	break;
                	else
                    	optArg = argv[index];
            	}
            	catch (...) {
            		throw;
        		}
            }
        }
        // Now the number of elements is known and the parsed values can be assigned to req
        int numElements = surls.size();
        struct ns1__ArrayOfTGetFileRequest* req = storm::soap_calloc<struct ns1__ArrayOfTGetFileRequest>(&_soap);
        req->__sizerequestArray = numElements;
        req->requestArray = storm::soap_calloc<struct ns1__TGetFileRequest>(&_soap, numElements);
        for (int i=0; i<numElements; i++) {
            req->requestArray[i] = storm::soap_calloc<struct ns1__TGetFileRequest>(&_soap);
            req->requestArray[i]->sourceSURL = surls[i];
            req->requestArray[i]->dirOption = dirOpts[i];
        }
        *req_param = req;
        
        return index;
    }
    
    /** Assign to a variable of type struct ns1__ArrayOfTCopyFileRequest* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__ArrayOfTCopyFileRequest** req_param)
    {
        struct ns1__TDirOption* dirOpt;
        vector<struct ns1__TDirOption*> dirOpts;
        vector<char*> surls;
        string opt;
        string optCpFileReq;
        string optArg;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, &optCpFileReq, &optArg);
        }
        catch (...) {
            throw;
        }
        
        index--;
        // Parse options and storing values in vector 'surls'
        while (optArg[0] != '-') {
            // Parse sourceSURL
            char* surl;
            char* str = const_cast<char*> (optArg.c_str());
            parse_SURL(0, 1, &str, &surl, WITHOUT_OPTION);
            surls.push_back(surl);
            index++;
            if (index == argc)
                throw InvalidOption(optCpFileReq, "targetSURL is required!");
            // Parse targetSURL
            try {
                getOptArg(index, argc, argv, &opt, &optArg);
            }
            catch (...) {
                // getOptArg() sets 'opt' to NO_OPT if no options are found (e.g. there is another SURL)
            }
            if (opt[0] != NO_OPT)
                throw InvalidOption(optCpFileReq, "targetSURL is required!");
            index = parse_SURL(index, argc, argv, &surl, WITHOUT_OPTION);
            surls.push_back(surl);
            if (index == argc) { // No more options, go on...
                dirOpts.push_back(NULL);
                optArg = '-';
                continue;
            }
            // Parse TDirOption
            try {
                getOptArg(index, argc, argv, &opt, &optArg);
            }
            catch (...) {
            	// getOptArg() sets 'opt' to NO_OPT if no options are found (e.g. there is another SURL)
            }
            if (opt[0] == NO_OPT) { // TDirOption NOT found
                dirOpts.push_back(NULL);
                continue;
            }
            else if (opt[1] != OPT_TDIROPTION) { // Stop parsing ArryayOfTCopyFileRequest
                dirOpts.push_back(NULL);
                optArg = '-';
                continue;
            } else { // TDirOption found
            	try {
	                index = parse_Arg(index, argc, argv, &dirOpt);
	                dirOpts.push_back(dirOpt);
	                if (index == argc)
	                    break;
	                else
	                    optArg = argv[index];
            	}
            	catch (...) {
                	throw;
        		}
            }
        }
        // Now the number of elements is known and the parsed values can be assigned to req
        int numElements = dirOpts.size();
        struct ns1__ArrayOfTCopyFileRequest* req = storm::soap_calloc<struct ns1__ArrayOfTCopyFileRequest>(&_soap);
        req->__sizerequestArray = numElements;
        req->requestArray = storm::soap_calloc<struct ns1__TCopyFileRequest>(&_soap, numElements);
        int i, j;
        for (i=0, j=0; i<numElements; i++) {
            req->requestArray[i] = storm::soap_calloc<struct ns1__TCopyFileRequest>(&_soap);
            req->requestArray[i]->sourceSURL = surls[j++];
            req->requestArray[i]->targetSURL = surls[j++];
            req->requestArray[i]->dirOption = dirOpts[i];
        }
        *req_param = req;
        
        return index;
    }
    
    /** Assign to a variable of type struct ns1__ArrayOfAnyURI* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__ArrayOfAnyURI** req_param)
    {
        vector<char*> surls;
        string opt;
        string optArg;
        
        *req_param = NULL;
        
        try {
            index = getOptArg(index, argc, argv, &opt, &optArg);
            opt = NO_OPT;
            index--;
        }
        catch (...) {
            throw;
        }
        // Parse SURLs storing values in vector 'surls'
        while (opt[0] == NO_OPT) {
        	char* surl;
            char* str = const_cast<char*> (optArg.c_str());
            try {
                parse_SURL(0, 1, &str, &surl, WITHOUT_OPTION);
            }
            catch (...) {
                throw;
            }
            surls.push_back(surl);
            index++;
            if (index == argc)
                break;
            try {
                getOptArg(index, argc, argv, &opt, &optArg);
            }
            catch (...) {
                break;
            }
        }
        
        // Now we know the number of elements and we can assign the parsed values to req
        int numElements = surls.size();
        struct ns1__ArrayOfAnyURI* req = storm::soap_calloc<struct ns1__ArrayOfAnyURI>(&_soap);
        req->__sizeurlArray = numElements;
        req->urlArray = storm::soap_calloc<char>(&_soap, numElements);
        for (int i=0; i<numElements; i++) {
            req->urlArray[i] = surls[i];
        }
        *req_param = req;
        
        return index;
    }
    
    /** Assign to a variable of type ns1__ArrayOfString* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__ArrayOfString** req_param)
    {
        struct ns1__ArrayOfString* req;
        vector<string> tokens;
        string optArg;
        int numElements;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, NULL, &optArg);
        }
        catch (...) {
            throw;
        }
        
		numElements = tokenize(optArg, &tokens, ',');
        req = storm::soap_calloc<struct ns1__ArrayOfString>(&_soap);
        if (numElements > 0)
        	req->stringArray = storm::soap_calloc<char>(&_soap, numElements);
    	else
    		// WARNING: wanted behavior (for test purposes)
    		req->stringArray = NULL;
        req->__sizestringArray = numElements;
        for (int i=0; i<numElements; i++) {
            req->stringArray[i] = soap_strdup(&_soap, tokens[i].c_str());
        }
        *req_param = req;
        return index;
    }
    
    /** Assign to a variable of type struct ns1__ArrayOfUnsignedLong* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__ArrayOfUnsignedLong** req_param)
    {
        string opt;
        string optArg;
        
        *req_param = NULL;
        try {
            index = getOptArg(index, argc, argv, &opt, &optArg);
        }
        catch (...) {
            throw;
        }
        vector<string> token;
        int numElements = tokenize(optArg, &token, ',');
        struct ns1__ArrayOfUnsignedLong* req = storm::soap_calloc<struct ns1__ArrayOfUnsignedLong>(&_soap);
        req->__sizeunsignedLongArray = numElements;
        if (numElements > 0) {
            req->unsignedLongArray = static_cast<ULONG64*> (soap_malloc(&_soap, sizeof(ULONG64)*numElements));
            int i = 0;
	        for (; i<numElements; i++) {
                ULONG64 u;
                if (string2num(u, token[i]))
                    throw InvalidOption(opt, "one element is not a number: " + token[i]);
                req->unsignedLongArray[i] = u;
	        }
        }
        *req_param = req;
        return index;
    }
    
    /** Assign to a variable of type struct ns1__TTransferParameters* the parsed argument.
     * It allocates memory for "req_param".
     * Retruns the next index in "argv". */
    int parse_Arg(int index, int argc, char** argv, struct ns1__TTransferParameters** req_param)
    {
        string opt;
        string optArg;
        char currentOpt;
        bool missingArg;
        
        *req_param = NULL;
        missingArg = true;
        currentOpt = OPT_TTRANSFERPARAMETERS;
        try {
            getOptArg(index, argc, argv, &opt, &optArg);
        }
        catch (...) {
            opt = argv[index];  // Used when InvalidOption(opt, "missing argument") is thrown
            ++index;
            if (index == argc)
            	throw;
            currentOpt = getOpt(argv[index]);
        }
        struct ns1__TTransferParameters* req = storm::soap_calloc<struct ns1__TTransferParameters>(&_soap);
        
        if (currentOpt == OPT_TTRANSFERPARAMETERS) {
            try {
                index = getOptArg(index, argc, argv, &opt, &optArg);
            }
            catch (...) {
                throw;
            }
            missingArg = false;
            vector<string> token;
            tokenize(optArg, &token, ',', 2);
            if (!(token[0].empty())) {
                char* str = const_cast<char*> (token[0].c_str());
                parse_Arg_enum(0, 1, &str, &(req->accessPattern), WITHOUT_OPTION);
            }
            if (!(token[1].empty())) {
                char* str = const_cast<char*> (token[1].c_str());
                parse_Arg_enum(0, 1, &str, &(req->connectionType), WITHOUT_OPTION);
            }
            if (index == argc)
            	currentOpt = NO_OPT;
        	else
            	currentOpt = getOpt(argv[index]);
        }
        if (currentOpt == OPT_TTRANSFERPARAMETERS_CN) {
            try {
                index = parse_Arg(index, argc, argv, &(req->arrayOfClientNetworks));
            }
            catch (...) {
                throw;
            }
            missingArg = false;
            if (index == argc)
            	currentOpt = NO_OPT;
        	else
            	currentOpt = getOpt(argv[index]);
        }
        
        if (currentOpt == OPT_TTRANSFERPARAMETERS_TP) {
            try {
                index = parse_Arg(index, argc, argv, &(req->arrayOfTransferProtocols));
            }
            catch (...) {
                throw;
            }
            missingArg = false;
        }
        
        if (missingArg)
            throw InvalidOption(opt, "missing argument.");
        *req_param = req;
        return index;
    }
    
    /** Assign to a variable of type char* the parsed argument.
     * It allocates memory for "req_param".
     * The difference with parse_Arg() for char* is that here can be called a function
     * that checks the SURL.
     * "hasOption" specifies if the argument to be parsed is identified by an option or not.
     * Retruns the next index in "argv". */
    int parse_SURL(int index, int argc, char** argv, char **req_param, bool hasOption =true)
    {
        *req_param = NULL;
        try {
            if (hasOption)
                index = parse_Arg(index, argc, argv, req_param);
            else {
                *req_param = soap_strdup(&_soap, argv[index]);
                index++;
            }
            
            // Here can be called a function that checks the SURL
            // and throws an InvalidOption exception in case of
            // malformed SURL
        }
        catch (...) {
            throw;
        }
        return index;
    }
    
    /** Parse the verbose level
     * Retruns the next index in "argv". */
    int parse_Arg_VerboseLevel(int index, int argc, char** argv, string* verboseLevel)
    {
        string opt;
        string optArg;
        char* str;
        
        try {
            getOptArg(index, argc, argv, &opt, &optArg);
            index = parse_Arg(index, argc, argv, &str);
            *verboseLevel = string(str);
            if ((*verboseLevel).find('N') != string::npos) 
                _verboseLevel_print_NULL = true;
            if ((*verboseLevel).find('I') != string::npos) 
                _verboseLevel_print_Input = true;
            if ((*verboseLevel).find('G') != string::npos) 
                _verboseLevel_print_GlobalOptions = true;
            if ((*verboseLevel).find('E') != string::npos) 
                _verboseLevel_print_Endpoint = false;
            if ((*verboseLevel).find('O') != string::npos) 
                _verboseLevel_print_Output = false;
            if ((*verboseLevel).find('S') != string::npos) 
                _verboseLevel_print_SepLines = false;
        }
        catch (...) {
            return ++index;
        }
        return index;
    }
    
    /** Assign to a variable of type enum* the parsed argument.
     * It allocates memory for "req_param".
     * "hasOption" specifies if the argument to be parsed is identified by an option or not.
     * Retruns the next index in "argv". */
    template<typename enum_t>
    int parse_Arg_enum(int index, int argc, char** argv, enum_t **req_param, bool hasOption =true)
    {
        int val;
        
        *req_param = NULL;
        try {
            index = parse_Arg(index, argc, argv, &val, hasOption);
        }
        catch (...) {
            throw;
        }
        *req_param = storm::soap_calloc<enum_t>(&_soap);
        **req_param = enum_t(val);
        return index;
    }
    
    /** Assign to a variable of type enum the parsed argument.
     * It does NOT allocate memory for "req_param".
     * "hasOption" specifies if the argument to be parsed is identified by an option or not.
     * Retruns the next index in "argv". */
    template<typename enum_t>
    int parse_Arg_enum(int index, int argc, char** argv, enum_t *req_param, bool hasOption =true)
    {
        int val;
        
        try {
            index = parse_Arg(index, argc, argv, &val, hasOption);
        }
        catch (...) {
            throw;
        }
        *req_param = enum_t(val);
        return index;
    }
    
    /*************************************************************************/
    /****************** Utilities for print usage messages *******************/
    /*************************************************************************/
    void printUsage()
    {
        cout << "\nUsage: " << _programName << " " << _serviceName << " [options]\n";
        cout << endl << _serviceName << " OPTIONS\n";
        print_Usage_Request();
        cout << endl;
    }
    
    void print_Usage_(const char opt, const char* usage, const char* description)
    {
        static const int IDENT_DESCR = 45;
        string usage_str;
        int idnt;
        
        if (opt == ' ')
        	usage_str = "   ";
        else 
        	usage_str = "  -";
        usage_str += opt;
        usage_str += "  ";
        if (usage != NULL)
            usage_str += usage;
        if (usage_str.length() >= IDENT_DESCR) {
            usage_str += "\n";
            idnt = IDENT_DESCR;
        }
        else 
            idnt = IDENT_DESCR - usage_str.length();
        usage_str.append(idnt, ' ');
        if (description != NULL)
            usage_str += description;
            
        usage_str += "\n";
            
        cout << usage_str;
    }
    
    void print_Usage_verboseLevel()
    {
        print_Usage_(OPT_VERBOSELEVEL, "[N][I][G][E][O][S]", "Versose level, meaning of the flags:");
        print_Usage_(' ', NULL, "N: print NULL fields.");
        print_Usage_(' ', NULL, "I: print inputa data.");
        print_Usage_(' ', NULL, "G: print global options values.");
        print_Usage_(' ', NULL, "E: do not print endpoint.");
        print_Usage_(' ', NULL, "O: do not print outputdata.");
        print_Usage_(' ', NULL, "S: do not print separation lines.");
    }
    
    void print_Usage_authorizationID()
    {
        print_Usage_(OPT_AUTHORIZATIONID, "<authorizationID>", "Authorization ID.");
    }
    
    void print_Usage_userRequestDescription()
    {
        print_Usage_(OPT_REQUESTDESCRIPTION, "<userRequestDescription>", "Easy to remember description string.");
    }
    
    void print_Usage_desiredTotalTimeRequest()
    {
        print_Usage_(OPT_DESIRED_TOTALREQUESTTIME, "<desiredTotalTimeRequest>", "Description..........");
    }
    
    void print_Usage_desiredPinLifeTime()
    {
        print_Usage_(OPT_DESIRED_PINLIFETIME, "<desiredPinLifeTime>", "Pin lifetime.");
    }
    
    void print_Usage_requestToken()
    {
        print_Usage_(OPT_REQUESTTOKEN, "<requestToken>", "Token of the request.");
    }
    
    void print_Usage_targetSpaceToken()
    {
        print_Usage_(OPT_SPACETOKEN, "<targetSpaceToken>", "Space token.");
    }
    
    void print_Usage_endpoint()
    {
        print_Usage_(OPT_ENDPOINT, "<endpoint>", "Endpoint to contact (e.g.: httpg://hostname:port/).");
    }
    
    void print_Usage_poll()
    {
        print_Usage_(OPT_POLLFLAG, NULL, "polling mode On.");
    }
    
    void print_Usage_TOverwriteMode()
    {
        print_Usage_(OPT_TOVERWRITEMODE, "<overwriteMode>", "Overwrite mode (0=never, 1=always, 2=when_files_are_different).");
    }
    
    void print_Usage_TFileStorageType()
    {
        print_Usage_(OPT_TFILESTORAGETYPE, "<fileStorageType>", "File storage type (0=volatile, 1=durable, 2=permanent).");
    }
    
    void print_Usage_TRetentionPolicyInfo()
    {
        print_Usage_(OPT_TRETENTIONPOLICYINFO, "<retentionPolicy,accessLatency>","Retention policy (0=replica, 1=output, 2=custodial),(0=online, 1=nearline).");
    }
    
    void print_Usage_ArrayOfAnyURI(char opt =OPT_ARRAYOFANYURI, const char* descr ="Array of SURLs.")
    {
        print_Usage_(opt, "<SURL1 [SURL2 [...]]>", descr);
    }
    
    void print_Usage_ArrayOfTExtraInfo(const char opt =OPT_TEXTRAINFO,
                                       const char* descr ="Storage system information (storageSystemInfo).")
    {
        print_Usage_(opt, "<key1.value1[,key2.value2[,...]]>", descr);
    }
    
    void print_Usage_ArrayOfTPutFileRequest()
    {
        print_Usage_(OPT_TPUTFILEREQUEST, "<SURL[,expectedFileSize] [SURL[,expectedFileSize] [...]]>",
                     "Array of SURLs and (optionals) desired sizes.");
    }
    
    void print_Usage_ArrayOfTGetFileRequest()
    {
    	string usage;
    	
    	usage += "<SURL [-";
    	usage += OPT_TDIROPTION;
    	usage +=  " <isDir,recursive,numLevels>] [SURL [-";
    	usage += OPT_TDIROPTION;
    	usage += " <isDir,recursive,numLevels>]] [...]>";
        print_Usage_(OPT_TGETFILEREQUEST, usage.c_str(), "isDir: 0=false, 1=true. SURL is a directory or not.");
		print_Usage_(' ', NULL, "recursive: 0=false, 1=true.");
		print_Usage_(' ', NULL, "numLevels: >=0.");
    }
    
    void print_Usage_ArrayOfTCopyFileRequest()
    {
    	string usage;
    	
    	usage += "<sourceSURL targetSURL [-";
    	usage += OPT_TDIROPTION;
    	usage += " <isDir,recursive,nLevels>] [sourceSURL targetSURL [-";
    	usage += OPT_TDIROPTION;
    	usage += " <isDir,recursive,nLevels>]] [...]>";
        print_Usage_(OPT_TCOPYFILEREQUEST, usage.c_str(), "isDir: 0=false, 1=true. SURL is a directory or not.");
        print_Usage_(' ', NULL, "recursive: 0=false, 1=true.");
		print_Usage_(' ', NULL, "numLevels: >=0.");
    }
    
    void print_Usage_TTransferParameters()
    {
        string usage;
        
        usage += "<[[accessPattern],[connectionType]] [-";
        usage += OPT_TTRANSFERPARAMETERS_CN;
        usage += " string1[,string2[,...]]] [-";
        usage += OPT_TTRANSFERPARAMETERS_TP;
        usage += " protocol1[,protocol2[,...]]]>";
        print_Usage_(OPT_TTRANSFERPARAMETERS, usage.c_str(), "Transfer parameters:");
        print_Usage_(' ', NULL, "accessPattern: 0=TRANSFER_MODE, 1=PROCESSING_MODE.");
        print_Usage_(' ', NULL, "connectionType: 0=WAN, 1=LAN.");
        usage = '-';
        usage += OPT_TTRANSFERPARAMETERS_CN;
        usage += ": List of client networks.";
        print_Usage_(' ', NULL, usage.c_str());
        usage = '-';
        usage += OPT_TTRANSFERPARAMETERS_TP;
        usage += ": List of protocols.";
        print_Usage_(' ', NULL, usage.c_str());
    }
    
    void print_Usage_SURL()
    {
        print_Usage_(OPT_SURL, "<SURL>", "SURL.");
    }
    
    /*************************************************************************/
    /****************** Utilities for print request fields *******************/
    /*************************************************************************/
    
    void print_NULL(int indent1, const char * fieldName, bool newLine =true)
    {
        string indent(indent1, ' ');
        
        if (!_verboseLevel_print_NULL)
            return;
        if (fieldName == NULL)
            cout << indent << "NULL";
        else
            cout << indent << fieldName << "=NULL";
        if (newLine)
            cout << endl;
    }    
    
    template<typename type_t>
    void print_Data(int indent1, const char *fieldName, type_t fieldValue, bool newLine =true)
    {
        string indent(indent1, ' ');
        string lhp("");
        
        if (fieldName != NULL) {
            lhp = fieldName;
            lhp += "=";
        }
        cout << indent << lhp << fieldValue;
        if (newLine)
            cout << endl;
    }
    
    template<typename type_t>
    void print_Data(int indent1, const char *fieldName, type_t* fieldValue, bool newLine =true)
    {
        string indent(indent1, ' ');
        string lhp("");
        
        if (fieldValue == NULL)
            print_NULL(indent1, fieldName, newLine);
        else {
            if (fieldName != NULL) {
                lhp = fieldName;
                lhp += "=";
            }
            cout << indent << lhp << *fieldValue;
            if (newLine)
            cout << endl;
        }
    }
    
    void print_Data(int indent1, const char *fieldName, char* fieldValue, bool newLine =true)
    {
        string indent(indent1, ' ');
        string lhp("");
        
        if (fieldValue == NULL)
            print_NULL(indent1, fieldName, newLine);
        else {
            if (fieldName != NULL) {
                lhp = fieldName;
                lhp += "=";
            }
            cout << indent << lhp << "\"" << fieldValue << "\"";
            if (newLine)
                cout << endl;
        }
    }
   
    void print_Data(int indent1, const char *fieldName, struct ns1__TReturnStatus *fieldValue)
    {
        string indent(indent1, ' ');
        int subIndent1, subIndent2;
        
        if (fieldValue == NULL) {
        	print_NULL(indent1, fieldName);
            return;
        }
        
        if (fieldName != NULL) {
        	indent += fieldName;
        	indent += ":";
            cout << indent;
            subIndent1 = subIndent2 = 1;
        } else {
        	subIndent1 = indent1;
        	subIndent2 = 0;
        }
        print_Data(subIndent1, "statusCode", reconvertStatusCode(fieldValue->statusCode), !(NEW_LINE));
        cout << "(" << fieldValue->statusCode << ")\n";
        indent1 = indent.length() + subIndent2;
        print_Data(indent1, "explanation", fieldValue->explanation);
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTExtraInfo *fieldValue)
    {
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizeextraInfoArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
        	if (fieldValue->extraInfoArray[i] != NULL) {
	            sstr.str(string());
	            sstr << indent << "[" << i << "] key";
	            print_Data(0, sstr.str().c_str(),  fieldValue->extraInfoArray[i]->key);
	            sstr.str(string());
	            sstr << indent << "[" << i << "] value";
	            print_Data(0, sstr.str().c_str(),  fieldValue->extraInfoArray[i]->value);
        	}
    	else
    		cout << indent << "[" << i << "] NULL\n";
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTPutFileRequest *fieldValue)
    {
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizerequestArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] targetSURL";
            print_Data(0, sstr.str().c_str(), fieldValue->requestArray[i]->targetSURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] expectedFileSize";
            print_Data(0, sstr.str().c_str(), fieldValue->requestArray[i]->expectedFileSize);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__TRetentionPolicyInfo *fieldValue)
    {
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        cout << indent << fieldName << "=(";
        print_Data(0, NULL, fieldValue->retentionPolicy, !(NEW_LINE));
        cout << ",";
        print_Data(0, NULL, fieldValue->accessLatency, !(NEW_LINE));
        cout << ")\n";
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfString* fieldValue)
    {
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizestringArray;
        cout << indent << fieldName << "(size=" << arraySize << ")\n";
        for (i=0; i<arraySize; i++) {
            cout << indent << "[" << i << "] ";
            print_Data(0, NULL, fieldValue->stringArray[i]);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__TTransferParameters *fieldValue)
    {
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        cout << indent << fieldName << ":\n";
        indent1 += 4;
        indent = string(indent1, ' ');
        print_Data(indent1, "accessPattern", fieldValue->accessPattern);
        print_Data(indent1, "connectionType", fieldValue->connectionType);
        print_Data(indent1, "arrayOfClientNetworks", fieldValue->arrayOfClientNetworks);
        print_Data(indent1, "arrayOfTransferProtocols", fieldValue->arrayOfTransferProtocols);
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTPutRequestFileStatus* fieldValue)
    {
        struct ns1__TPutRequestFileStatus **statusArray;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, statusArraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        statusArraySize = fieldValue->__sizestatusArray;
        statusArray = fieldValue->statusArray;
        
        cout << indent << fieldName << " (size=" << statusArraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<statusArraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] SURL";
            print_Data(2, sstr.str().c_str(), statusArray[i]->SURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] status";
            print_Data(2, sstr.str().c_str(), statusArray[i]->status);
            sstr.str(string());
            sstr << indent << "[" << i << "] fileSize";
            print_Data(2, sstr.str().c_str(), statusArray[i]->fileSize);
            sstr.str(string());
            sstr << indent << "[" << i << "] estimatedWaitTime";
            print_Data(2, sstr.str().c_str(), statusArray[i]->estimatedWaitTime);
            sstr.str(string());
            sstr << indent << "[" << i << "] remainingPinLifetime";
            print_Data(2, sstr.str().c_str(), statusArray[i]->remainingPinLifetime);
            sstr.str(string());
            sstr << indent << "[" << i << "] remainingFileLifetime";
            print_Data(2, sstr.str().c_str(), statusArray[i]->remainingFileLifetime);
            sstr.str(string());
            sstr << indent << "[" << i << "] TURL";
            print_Data(2, sstr.str().c_str(), statusArray[i]->transferURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] transferProtocolInfo";
            print_Data(2, sstr.str().c_str(), statusArray[i]->transferProtocolInfo);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__TDirOption *fieldValue)
    {
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        cout << indent << fieldName << " (";
        print_Data(0, "isSourceADirectory", fieldValue->isSourceADirectory, !(NEW_LINE));
        cout <<",";
        print_Data(0, "allLevelRecursive", fieldValue->allLevelRecursive, !(NEW_LINE));
        cout <<",";
        print_Data(0, "numOfLevels", fieldValue->numOfLevels, !(NEW_LINE));
        cout <<")\n";
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTGetFileRequest *fieldValue)
    {
        struct ns1__TGetFileRequest **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizerequestArray;
        array = fieldValue->requestArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] SURL";
            print_Data(2, sstr.str().c_str(), array[i]->sourceSURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] dirOption";
            print_Data(2, sstr.str().c_str(), array[i]->dirOption);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTCopyFileRequest *fieldValue)
    {
        struct ns1__TCopyFileRequest **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizerequestArray;
        array = fieldValue->requestArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] sourceSURL";
            print_Data(2, sstr.str().c_str(), array[i]->sourceSURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] targetSURL";
            print_Data(2, sstr.str().c_str(), array[i]->targetSURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] dirOption";
            print_Data(2, sstr.str().c_str(), array[i]->dirOption);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTGetRequestFileStatus *fieldValue)
    {
        struct ns1__TGetRequestFileStatus **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizestatusArray;
        array = fieldValue->statusArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
        	sstr.str(string());
            sstr << indent << "[" << i << "] status";
            print_Data(2, sstr.str().c_str(), array[i]->status);
            sstr.str(string());
            sstr << indent << "[" << i << "] sourceSURL";
            print_Data(2, sstr.str().c_str(), array[i]->sourceSURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] fileSize";
            print_Data(2, sstr.str().c_str(), array[i]->fileSize);
            sstr.str(string());
            sstr << indent << "[" << i << "] estimatedWaitTime";
            print_Data(2, sstr.str().c_str(), array[i]->estimatedWaitTime);
            sstr.str(string());
            sstr << indent << "[" << i << "] remainingPinTime";
            print_Data(2, sstr.str().c_str(), array[i]->remainingPinTime);
            sstr.str(string());
            sstr << indent << "[" << i << "] transferURL";
            print_Data(2, sstr.str().c_str(), array[i]->transferURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] transferProtocolInfo";
            print_Data(2, sstr.str().c_str(), array[i]->transferProtocolInfo);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTBringOnlineRequestFileStatus *fieldValue)
    {
        struct ns1__TBringOnlineRequestFileStatus **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizestatusArray;
        array = fieldValue->statusArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] sourceSURL";
            print_Data(2, sstr.str().c_str(), array[i]->sourceSURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] fileSize";
            print_Data(2, sstr.str().c_str(), array[i]->fileSize);
            sstr.str(string());
            sstr << indent << "[" << i << "] estimatedWaitTime";
            print_Data(2, sstr.str().c_str(), array[i]->estimatedWaitTime);
            sstr.str(string());
            sstr << indent << "[" << i << "] remainingPinTime";
            print_Data(2, sstr.str().c_str(), array[i]->remainingPinTime);
            sstr.str(string());
            sstr << indent << "[" << i << "] status";
            print_Data(2, sstr.str().c_str(), array[i]->status);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTCopyRequestFileStatus *fieldValue)
    {
        struct ns1__TCopyRequestFileStatus **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizestatusArray;
        array = fieldValue->statusArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] sourceSURL";
            print_Data(2, sstr.str().c_str(), array[i]->sourceSURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] targetSURL";
            print_Data(2, sstr.str().c_str(), array[i]->targetSURL);
            sstr.str(string());
            sstr << indent << "[" << i << "] fileSize";
            print_Data(2, sstr.str().c_str(), array[i]->fileSize);
            sstr.str(string());
            sstr << indent << "[" << i << "] estimatedWaitTime";
            print_Data(2, sstr.str().c_str(), array[i]->estimatedWaitTime);
            sstr.str(string());
            sstr << indent << "[" << i << "] remainingFileLifetime";
            print_Data(2, sstr.str().c_str(), array[i]->remainingFileLifetime);
            sstr.str(string());
            sstr << indent << "[" << i << "] status";
            print_Data(2, sstr.str().c_str(), array[i]->status);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfAnyURI *fieldValue)
    {
        char **array;
        string indent(indent1, ' ');
        ostringstream sstr;
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizeurlArray;
        array = fieldValue->urlArray;
        
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] SURL";
            print_Data(2, sstr.str().c_str(), array[i]);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, enum ns1__TRequestType *fieldValue)
    {
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        cout << indent << fieldName << "=";
        switch (*fieldValue) {
            case 0: cout << "PREPARE_TO_GET";
                    break;
            case 1: cout << "PREPARE_TO_PUT";
                    break;
            case 2: cout << "COPY";
                    break;
            case 3: cout << "BRING_ON_LINE";
                    break;
            case 4: cout << "RESERVE_SPACE";
                    break;
            case 5: cout << "UPDATE_SPACE";
                    break;
            case 6: cout << "CHANGE_SPACE_FOR_FILES";
                    break;
            case 7: cout << "LS";
        }
        cout <<"\n";
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTRequestSummary *fieldValue)
    {
        string indent(indent1, ' ');
        ostringstream sstr;
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizesummaryArray;
        struct ns1__TRequestSummary** array = fieldValue->summaryArray;
        
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] requestToken";
            print_Data(2, sstr.str().c_str(), array[i]->requestToken);
            sstr.str(string());
            sstr << indent << "[" << i << "] status";
            print_Data(2, sstr.str().c_str(), array[i]->status);
            sstr.str(string());
            sstr << indent << "[" << i << "] requestType";
            print_Data(2, sstr.str().c_str(), array[i]->requestType);
            sstr.str(string());
            sstr << indent << "[" << i << "] totalNumFilesInRequest";
            print_Data(2, sstr.str().c_str(), array[i]->totalNumFilesInRequest);
            sstr.str(string());
            sstr << indent << "[" << i << "] numOfCompletedFiles";
            print_Data(2, sstr.str().c_str(), array[i]->numOfCompletedFiles);
            sstr.str(string());
            sstr << indent << "[" << i << "] numOfWaitingFiles";
            print_Data(2, sstr.str().c_str(), array[i]->numOfWaitingFiles);
            sstr.str(string());
            sstr << indent << "[" << i << "] numOfFailedFiles";
            print_Data(2, sstr.str().c_str(), array[i]->numOfFailedFiles);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfUnsignedLong *fieldValue)
    {
        ULONG64 *array;
        string indent(indent1, ' ');
        ostringstream sstr;
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizeunsignedLongArray;
        array = fieldValue->unsignedLongArray;
        
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] ";
            print_Data(2, sstr.str().c_str(), array[i]);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTMetaDataSpace *fieldValue)
    {
        struct ns1__TMetaDataSpace **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizespaceDataArray;
        array = fieldValue->spaceDataArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] spaceToken";
            print_Data(2, sstr.str().c_str(), array[i]->spaceToken);
            sstr.str(string());
            sstr << indent << "[" << i << "] status";
            print_Data(2, sstr.str().c_str(), array[i]->status);
            sstr.str(string());
            sstr << indent << "[" << i << "] retentionPolicyInfo";
            print_Data(2, sstr.str().c_str(), array[i]->retentionPolicyInfo);
            
            sstr.str(string());
            sstr << indent << "[" << i << "] owner";
            print_Data(2, sstr.str().c_str(), array[i]->owner);
            sstr.str(string());
            sstr << indent << "[" << i << "] totalSize";
            print_Data(2, sstr.str().c_str(), array[i]->totalSize);
            sstr.str(string());
            sstr << indent << "[" << i << "] guaranteedSize";
            print_Data(2, sstr.str().c_str(), array[i]->guaranteedSize);
            sstr.str(string());
            sstr << indent << "[" << i << "] unusedSize";
            print_Data(2, sstr.str().c_str(), array[i]->unusedSize);
            sstr.str(string());
            sstr << indent << "[" << i << "] lifetimeAssigned";
            print_Data(2, sstr.str().c_str(), array[i]->lifetimeAssigned);
            sstr.str(string());
            sstr << indent << "[" << i << "] lifetimeLeft";
            print_Data(2, sstr.str().c_str(), array[i]->lifetimeLeft);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTSURLReturnStatus *fieldValue)
    {
        struct ns1__TSURLReturnStatus **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizestatusArray;
        array = fieldValue->statusArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] SURL";
            print_Data(2, sstr.str().c_str(), array[i]->surl);
            sstr.str(string());
            sstr << indent << "[" << i << "] status";
            print_Data(2, sstr.str().c_str(), array[i]->status);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTSURLLifetimeReturnStatus *fieldValue)
    {
        struct ns1__TSURLLifetimeReturnStatus **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizestatusArray;
        array = fieldValue->statusArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] SURL";
            print_Data(2, sstr.str().c_str(), array[i]->surl);
            sstr.str(string());
            sstr << indent << "[" << i << "] status";
            print_Data(2, sstr.str().c_str(), array[i]->status);
            sstr.str(string());
            sstr << indent << "[" << i << "] fileLifetime";
            print_Data(2, sstr.str().c_str(), array[i]->fileLifetime);
            sstr.str(string());
            sstr << indent << "[" << i << "] pinLifetime";
            print_Data(2, sstr.str().c_str(), array[i]->pinLifetime);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTSupportedTransferProtocol *fieldValue)
    {
        struct ns1__TSupportedTransferProtocol **array;
        ostringstream sstr;
        string indent(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizeprotocolArray;
        array = fieldValue->protocolArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] transferProtocol";
            print_Data(2, sstr.str().c_str(), array[i]->transferProtocol);
            sstr.str(string());
            sstr << indent << "[" << i << "] attributes";
            print_Data(2, sstr.str().c_str(), array[i]->attributes);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__ArrayOfTRequestTokenReturn *fieldValue)
    {
        ostringstream sstr;
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        int arraySize = fieldValue->__sizetokenArray;
        struct ns1__TRequestTokenReturn** array = fieldValue->tokenArray;
        cout << indent << fieldName << " (size=" << arraySize << ")\n";
        indent1 += 2;
        indent = string(indent1, ' ');
        int i;
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << i << "] requestToken";
            print_Data(2, sstr.str().c_str(), array[i]->requestToken);
            sstr.str(string());
            sstr << indent << "[" << i << "] createdAtTime";
            print_Data(2, sstr.str().c_str(), array[i]->createdAtTime);
        }
    }
    
    void print_Data(int indent1, const char *fieldName, enum ns1__TPermissionMode *fieldValue, bool newLine =true)
    {
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        cout << indent << fieldName << "=";
        switch (*fieldValue) {
            case NONE: 
                cout << "NONE";
                break;
            case X:
                cout << "--X";
                break;
            case W:
                cout << "-W-";
                break;
            case WX:
                cout << "-WX";
                break;
            case R:
                cout << "R--";
                break;
            case RX:
                cout << "R-X";
                break;
            case RW:
                cout << "RW-";
                break;
            case RWX:
                cout << "RWX";
                break;
            default:
                cout << "Error illegal value (probably a bug)";
        }
        if (newLine)
            cout <<"\n";
    }
    
    void print_Data(int indent1, const char *fieldName, enum ns1__TPermissionMode fieldValue, bool newLine =true)
    {
        print_Data(indent1, fieldName, &fieldValue, newLine);
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__TUserPermission *fieldValue)
    {
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        cout << indent << fieldName << " (";
        print_Data(0, "userID", fieldValue->userID, !(NEW_LINE));
        cout <<",";
        print_Data(0, "mode", fieldValue->mode, !(NEW_LINE));
        cout <<")\n";
    }
    
    void print_Data(int indent1, const char *fieldName, struct ns1__TGroupPermission *fieldValue)
    {
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        cout << indent << fieldName << " (";
        print_Data(0, "groupID", fieldValue->groupID, !(NEW_LINE));
        cout <<",";
        print_Data(0, "mode", fieldValue->mode, !(NEW_LINE));
        cout <<")\n";
    }
    
    void print_Data(int indent1, const char *fieldName, enum ns1__TFileType *fieldValue)
    {
        string indent(indent1, ' ');
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        cout << indent << fieldName << "=";
        switch (*fieldValue) {
            case FILE_: 
                cout << "File";
                break;
            case DIRECTORY:
                cout << "Directory";
                break;
            case LINK:
                cout << "Link";
                break;
            default:
                cout << "Error illegal value (probably a bug)";
        }
        cout <<"\n";
    }
    
    void print_Data(int indent1, string prefix, const char *fieldName, struct ns1__ArrayOfTMetaDataPathDetail *fieldValue)
    {
        struct ns1__TMetaDataPathDetail **array;
        ostringstream sstr;
        string indent_base(indent1, ' ');
        int i, arraySize;
        
        if (fieldValue == NULL) {
            print_NULL(indent1, fieldName);
            return;
        }
        arraySize = fieldValue->__sizepathDetailArray;
        array = fieldValue->pathDetailArray;
        cout << indent_base << fieldName << " (size=" << arraySize << ")\n";
        string indent = string(indent1 + 2, ' ');
        for (i=0; i<arraySize; i++) {
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] path";
            print_Data(2, sstr.str().c_str(), array[i]->path);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] size";
            print_Data(2, sstr.str().c_str(), array[i]->size);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] createdAtTime";
            print_Data(2, sstr.str().c_str(), array[i]->createdAtTime);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] lastModificationTime";
            print_Data(2, sstr.str().c_str(), array[i]->lastModificationTime);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] fileStorageType";
            print_Data(2, sstr.str().c_str(), array[i]->fileStorageType);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] retentionPolicyInfo";
            print_Data(2, sstr.str().c_str(), array[i]->retentionPolicyInfo);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] fileLocality";
            print_Data(2, sstr.str().c_str(), array[i]->fileLocality);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] arrayOfSpaceTokens";
            print_Data(2, sstr.str().c_str(), array[i]->arrayOfSpaceTokens);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] type";
            print_Data(2, sstr.str().c_str(), array[i]->type);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] lifetimeAssigned";
            print_Data(2, sstr.str().c_str(), array[i]->lifetimeAssigned);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] lifetimeLeft";
            print_Data(2, sstr.str().c_str(), array[i]->lifetimeLeft);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] ownerPermission";
            print_Data(2, sstr.str().c_str(), array[i]->ownerPermission);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] groupPermission";
            print_Data(2, sstr.str().c_str(), array[i]->groupPermission);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] otherPermission";
            print_Data(2, sstr.str().c_str(), array[i]->otherPermission);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] checkSumType";
            print_Data(2, sstr.str().c_str(), array[i]->checkSumType);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] checkSumValue";
            print_Data(2, sstr.str().c_str(), array[i]->checkSumValue);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] status";
            print_Data(2, sstr.str().c_str(), array[i]->status);
            sstr.str(string());
            sstr << indent << "[" << prefix << i << "] arrayOfSubPaths";
            string nested_prefix = prefix + to_string(i) + "-";
            print_Data(indent1, nested_prefix, sstr.str().c_str(), array[i]->arrayOfSubPaths);
        }
    }
    
    char getOpt(string opt)
    {
        if (opt.length() < 2)
            return NO_OPT;
        if (opt[0] != '-')
            return NO_OPT;
        return opt[1];
    }
    
private:
    int getOptArg(int index, int argc, char** argv, string* opt, string* arg)
    {
        string s;
        string so;
        string sa;
        
        if (opt != NULL)
            *opt = NO_OPT;
        if (index == argc) {
            if (opt == NULL)
                throw InvalidOption("BUG (exception thrown by getOptArg()): out of boundary in 'argv'");
        }
        s = argv[index++];
        if (s[0] == '-') { // Interpreting option and argument
            if (s.length() == 2) {  // There is a space between option and argument
                so = s;
                if (opt != NULL)
                    *opt = so;
                if (index == argc) { // Only optiont, argument is missing
                    throw InvalidOption(so, "missing argument", InvalidOption::MISSING_ARG);
                }
                sa = argv[index++];
                if (sa[0] == '-')   // Found another option instead of the argument
                    throw InvalidOption(so, "missing argument", InvalidOption::MISSING_ARG);
            } else { // Option and argument are NOT separated by a space
                    so = s.substr(0, 2);
                    sa = s.substr(2);
            }
        } else { // Interpreting argument without option
            so = NO_OPT;
            sa = s;
        }
        
        if (opt != NULL)
            *opt = so;
        if (arg != NULL)
            *arg = sa;
        return index;
    }
    
    /** Tokenize 'str' into tokens separated by 'separator'. 'minSize' is the minumum number of
     *  tokens returned (empty strings are added to reach minSize).
     *  @param str String to tokenize
     *  @param tokens Found tokens
     *  @param minSize Minimum number of tokens to be returned (default is zero).
     */
    int tokenize(string& str, vector<string>* tokens, char separator, int minSize =0)
    {
    	int start, end, size;
    	
    	start = end = 0;
    	while (end < str.length()) {
    		end = str.find(separator, end);
    		if (end == string::npos)
    			end = str.length();
			tokens->push_back(str.substr(start, (end-start)));
			start = ++end;
    	}
    	size = tokens->size();
    	for (; size<minSize; size++)
    		tokens->push_back(string());
		return size;
    }

protected:
    static const char NO_OPT = '|';
    static const char OPT_HELP = 'h';
    static const char OPT_VERBOSELEVEL = 'v';
    static const char OPT_POLLFLAG = 'p';
    static const char OPT_ENDPOINT = 'e';
    static const char OPT_AUTHORIZATIONID = 'i';
    static const char OPT_REQUESTDESCRIPTION = 'd';
    static const char OPT_SPACETOKEN = 't';
    static const char OPT_REQUESTTOKEN = 't';
    static const char OPT_SURL = 's';
    static const char OPT_SURL_2 = 't';
    static const char OPT_DESIRED_TOTALREQUESTTIME = 'a';
    static const char OPT_RS_DESIRED_SIZEOFTOTALSPACE = 'a';
    static const char OPT_RS_DESIRED_SIZEOFGUARANTEEDSPACE = 'b';
    static const char OPT_DESIRED_PINLIFETIME = 'b';
    static const char OPT_BOL_DESIRED_LITETIME = 'b';
    static const char OPT_DESIRED_FILELITETIME = 'c';
    static const char OPT_RS_DESIRED_LIFETIMEOFRESERVEDSPACE = 'c';
    static const char OPT_COPY_DESIRED_TARGETSURLLITETIME = 'c';
    static const char OPT_BOL_DEFERRED_STARTTIME = 'c';
    static const char OPT_RS_ARRAYOFEXPECTEDFILESIZES = 'f';
    static const char OPT_RMDIR_RECURSIVE = 'r';
    static const char OPT_RELEASESPACE_FORCERELEASE = 'f';
    static const char OPT_LS_FULLDETAILEDLIST = 'l';
    static const char OPT_LS_ALLLEVELRECURSIVE = 'r';
    static const char OPT_LS_NUMOFLEVELS = 'n';
    static const char OPT_LS_OFFSET = 'o';
    static const char OPT_LS_COUNT = 'c';
    static const char OPT_RELEASEFILES_DOREMOVE = 'r';
    
    static const char OPT_ARRAYOFANYURI = 's';
    static const char OPT_ARRAYOFANYURI_2 = 'n';
    static const char OPT_TPUTFILEREQUEST = 's';
    static const char OPT_TGETFILEREQUEST = 's';
    static const char OPT_TCOPYFILEREQUEST = 's';
    static const char OPT_TEXTRAINFO = 'S';
    static const char OPT_TEXTRAINFO_2 = 'T';
    static const char OPT_TFILESTORAGETYPE = 'f';
    static const char OPT_TRETENTIONPOLICYINFO = 'r';
    static const char OPT_TOVERWRITEMODE = 'w';
    static const char OPT_TTRANSFERPARAMETERS = 'T';
    static const char OPT_TTRANSFERPARAMETERS_CN = 'N';
    static const char OPT_TTRANSFERPARAMETERS_TP = 'P';
    static const char OPT_TDIROPTION = 'D';
    static const char OPT_ARRAYOFSTRING = 's';
    
    static const bool WITH_OPTION = true;
    static const bool WITHOUT_OPTION = false;
    static const bool NEW_LINE = true;
    
    struct soap _soap;
    string _serviceName;
    string _programName;
    char* _endpoint;
    string _parse_error_explanation;
    struct ns1__TReturnStatus *_request_SRMStatus;
    srm_request_t* _request;
    srm_response_t* _response;
    int _flags;
    int _pollFlag;
    string _verboseLevel;
    bool _verboseLevel_print_NULL;
    bool _verboseLevel_print_Input;
    bool _verboseLevel_print_GlobalOptions;
    bool _verboseLevel_print_Endpoint;
    bool _verboseLevel_print_Output;
    bool _verboseLevel_print_SepLines;
    
    /* Exception classes */
    class InvalidOption {
    private:
        string _explanation;
        char _errorCode;
    public:
    	static const char UNDEFINED = 0;
    	static const char MISSING_ARG = 1;
    	
        InvalidOption(string explanation, char errCode =UNDEFINED) : _explanation(explanation),
        	_errorCode(errCode) { }
        
        InvalidOption(string explanation1, string explanation2, char errCode =UNDEFINED) : _errorCode(errCode)
        {
            _explanation = explanation1 + string(" ") + explanation2;
        }
        
        string getExplanation() { return _explanation; }
        char getErrorCode() { return _errorCode; }
    };
    
    class PrintUsage {};
};

#endif /*SRM_CLIENT_COMMON_HPP_*/
