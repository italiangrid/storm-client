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

#include "SRM_Service.hpp"
#include "SRM_Client_All.hpp"
#include "storm_util.hpp"
#include "clients_version.h"

#include "srmSoapBinding.nsmap"

#include <iostream>
#include <stdio.h>
#include <csignal>
#include <string>
#include <cctype>
#include <algorithm>

#define SEP_LINE "============================================================\n"

int stop;

// CTRL-C handler. Used to stop the client when it is polling a request.
void sigint_handler(int sig)
{
    stop = 1;
}

// Used to print a separation line
void printLine(bool ok)
{
	if (ok)
		cout << SEP_LINE;
}

void printUsage(char *programName)
{
    cout << "\nUsage: " << programName << " <requestName> <requestOptions>\n\n";
    cout << "<requestName> can be (it is not case-sensitive):\n";
    cout << "  Discovery functions:\n";
    cout << "                      Ping\n";
    cout << "                      GetTransferProtocols    (or gtp)\n";
    cout << "  Directory functions:\n";
    cout << "                      Mkdir\n";
    cout << "                      Rmdir\n";
    cout << "                      Rm\n";
    cout << "                      Ls\n";
	cout << "                      Mv\n";
    cout << "  Data transfer functions:\n";
	cout << "                      PtP\n";
    cout << "                      PtG\n";
    cout << "                      Copy                    (or cp)\n";                
    cout << "                      StatusPtP               (or sptp)\n";
    cout << "                      StatusPtG               (or sptg)\n";
    cout << "                      StatusCopy              (or scp)\n";
    cout << "                      PutDone                 (or pd)\n";
    cout << "                      ReleaseFiles            (or rf)\n";
    cout << "                      BringOnline             (or bol)\n";
    cout << "                      StatusBringOnline       (or sbol)\n";
    cout << "                      GetRequestTokens        (or grt)\n";
    cout << "                      GetRequestSummary       (or grs)\n";
    cout << "                      AbortRequest            (or ar)\n";
    cout << "                      AbortFiles              (or af)\n";
    cout << "                      ExtendFileLifeTime      (or efl)\n";
    cout << "  Space management functions:\n";
    cout << "                      ReserveSpace            (or rs)\n";
    cout << "                      GetSpaceMetadata        (or gsm)\n";
    cout << "                      ReleaseSpace            (or rsp)\n";
    cout << "                      GetSpaceTokens          (or gst)\n\n";
    cout << "Type \"" << programName << " <requestName> -h\" to get help about <requestName> options\n\n";
    cout << "Global options:\n";
    cout << "    -h, --help            Print this help message\n";
    cout << "    -v, --version         Print version information\n\n";
}

// Returns an instance of the request SRM service
SRM_Service* get_SRM_service(string serviceName)
{
	// Discovery Functions
    if (serviceName.compare("ping") == 0)
        return new SRM_Client_Ping();
    else if ((serviceName.compare("gettransferprotocols") == 0) || (serviceName.compare("gtp") == 0))
        return new SRM_Client_GetTransferProtocols();
    
    // Directory Functions
    else if (serviceName.compare("mkdir") == 0)
        return new SRM_Client_Mkdir();
    else if (serviceName.compare("rmdir") == 0)
        return new SRM_Client_Rmdir();
    else if (serviceName.compare("rm") == 0)
        return new SRM_Client_Rm();
    else if (serviceName.compare("ls") == 0)
        return new SRM_Client_Ls();
    else if (serviceName.compare("mv") == 0)
        return new SRM_Client_Mv();
    
    // Data Transfer Functions
    else if (serviceName.compare("ptp") == 0)
        return new SRM_Client_PtP();
    else if ((serviceName.compare("putdone") == 0) || (serviceName.compare("pd") == 0))
        return new SRM_Client_PutDone();
    else if ((serviceName.compare("statusptp") == 0) || (serviceName.compare("sptp") == 0))
        return new SRM_Client_StatusPtP();
    else if (serviceName.compare("ptg") == 0)
        return new SRM_Client_PtG();
    else if ((serviceName.compare("statusptg") == 0) || (serviceName.compare("sptg") == 0))
        return new SRM_Client_StatusPtG();
    else if ((serviceName.compare("releasefiles") == 0) || (serviceName.compare("rf") == 0))
        return new SRM_Client_ReleaseFiles();
    else if ((serviceName.compare("bringonline") == 0) || (serviceName.compare("bol") == 0))
        return new SRM_Client_BOL();
    else if ((serviceName.compare("statusbringonline") == 0) ||
    		 (serviceName.compare("statusbol") == 0) ||
    		 (serviceName.compare("sbol") == 0))
        return new SRM_Client_StatusBOL();
    else if ((serviceName.compare("copy") == 0) || (serviceName.compare("cp") == 0))
        return new SRM_Client_Copy();
    else if ((serviceName.compare("statuscopy") == 0) || (serviceName.compare("scp") == 0))
        return new SRM_Client_StatusCopy();
    else if ((serviceName.compare("getrequesttokens") == 0) || (serviceName.compare("grt") == 0))
        return new SRM_Client_GetRequestTokens();
    else if ((serviceName.compare("getrequestsummary") == 0) || (serviceName.compare("grs") == 0))
        return new SRM_Client_GetRequestSummary();
    else if ((serviceName.compare("abortrequest") == 0) || (serviceName.compare("ar") == 0))
        return new SRM_Client_AbortRequest();
    else if ((serviceName.compare("abortfiles") == 0) || (serviceName.compare("af") == 0))
        return new SRM_Client_AbortFiles();
    else if ((serviceName.compare("extendfilelifetime") == 0) || (serviceName.compare("efl") == 0))
        return new SRM_Client_ExtendFileLifeTime();
        
    // Space Management Functions
    else if ((serviceName.compare("reservespace") == 0) || (serviceName.compare("rs") == 0))
        return new SRM_Client_ReserveSpace();
    else if ((serviceName.compare("getspacemetadata") == 0) || (serviceName.compare("gsm") == 0))
        return new SRM_Client_GetSpaceMetaData();
    else if ((serviceName.compare("getspacetokens") == 0) || (serviceName.compare("gst") == 0))
        return new SRM_Client_GetSpaceTokens();
    else if ((serviceName.compare("releasespace") == 0) || (serviceName.compare("rsp") == 0))
        return new SRM_Client_ReleaseSpace();
        
    // SRM service not found, return not supported.
    return NULL;
}

int main(int argc, char** argv)
{
    SRM_Service *srmRequest;
    int error;
    char *endpoint;
    
    if (argc < 2) {
        printUsage(argv[0]);
        exit(1);
    }
    // If the first argument starts with '-' it is interpreted as HELP    
    string first_arg(argv[1]);
    if ((first_arg == "-v") || (first_arg == "--version")) {
        cout << "StoRM SRM v2.2 clients version " << clients_version << endl << endl;
        exit(0);
    } else if ((first_arg == "-h") || (first_arg == "--help")) {
        printUsage(argv[0]);
        exit(0);
    } else if (*argv[1] == '-') {
        cout << "Invalid option: " << argv[1] << endl << endl;
        exit(1);
    }

    // The first argument is the request type
    string serviceName(argv[1]);
    // Convert serviceName to lowercase letters
	transform(serviceName.begin(), serviceName.end(), serviceName.begin(), (int(*)(int)) tolower);
	
    // Get the SRM service instance
    srmRequest = get_SRM_service(serviceName);
    if (srmRequest == NULL) {
    	cout << endl << serviceName << ": not supported\n\n";
        exit(1);
    }
    
    // Parse the request input data from the command line
    error = srmRequest->parseFromCommandLine(2, argc, argv);
    switch (error) {
        case SRM_Service::PRINT_USAGE:
            srmRequest->printUsage();
            delete srmRequest;
            exit(1);
        case SRM_Service::PARSE_FAILURE:
            srmRequest->printRequestStatus();
            delete srmRequest;
            exit(2);
            break;
    }
    
    // Get verbose level of separation lines
    bool vl = srmRequest->getVerboseLevel_SepLines();
    
    // Print global options values (if requested by the verbose level)
    if (srmRequest->getVerboseLevel_GlobalOptions()) {
	    printLine(vl);
        string verboseLevel = srmRequest->getVerboseLevel();
	    cout << "Behavior:\n";
	    cout << "poll: " << srmRequest->getPollflag() << endl;
	    cout << "verbose level: ";
        if (verboseLevel.empty())
            cout << "default\n";
        else
            cout << verboseLevel << endl;
    }
    
    // Print request input data (if requested by the verbose level)
    if (srmRequest->getVerboseLevel_Input()) {
    	printLine(vl);
	    cout << "Input data:\n";
	    srmRequest->printRequestInputdata();
    }
    
    endpoint = srmRequest->getEndpoint();
    if (endpoint == NULL) {
        cout << "Cannot execute request: endpoint not specified\n\n";
        exit(1);
    }
    
    // Print endpoint (if requested by the verbose level)
    if (srmRequest->getVerboseLevel_Endpoint()) {
	    printLine(vl);
	    cout << "Sending " << srmRequest->getServiceName() << " request to: " << endpoint << endl;
    }
    
    // Execute the request
    cout << "Before execute:\n";
    srmRequest->execute();
    cout << "Afer execute:\n";

    cout << "Request Status Code " << srmRequest->getRequestStatusCode() << endl;
    cout << "Poll Flag " << srmRequest->getPollflag() << endl;

    // Poll the status of the request
    if ((srmRequest->getRequestStatusCode()>=0) && (srmRequest->getPollflag())) {
        int stat, prev_stat;
        // Stop with Ctrl+c
        signal(SIGINT, sigint_handler);
        stop = 0;
        prev_stat = stat = srmRequest->getRequestStatusCode();
        printLine(vl);
        cout << "Polling request status:\n";
        cout << "Current status: " << reconvertStatusCode(stat) << " (Ctrl+c to stop polling)" << flush;
        while ((stop==0) && ((stat==17) || (stat==18))) {
            if (prev_stat != stat) {
                prev_stat = stat;
                cout << "\nCurrent status: " << reconvertStatusCode(stat) << " (Ctrl+c to stop polling)" << flush;
            }
            sleep(1);
            srmRequest->poll();
            stat = srmRequest->getRequestStatusCode();
            cout << "." << flush; 
        }
        cout << endl << flush;
    }
    
    // Print the response 
    printLine(vl);
    srmRequest->printRequestStatus();
    
    // Print output data (if requested by the verbose level)
    int stat = srmRequest->getRequestStatusCode();
    if (stat >= 0) {
    	if (srmRequest->getVerboseLevel_Output()) {
	    	printLine(vl);
	        cout << "SRM Response:\n";
	        srmRequest->printRequestOutputdata();
    	}
    }
    
    printLine(vl);
    
    delete srmRequest;
    
    return 0;
}
