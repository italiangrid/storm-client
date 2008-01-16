#ifndef SRM_CLIENT_ALL_HPP_
#define SRM_CLIENT_ALL_HPP_

// Discovery Functions
#include "SRM_Client_Ping.hpp"
#include "SRM_Client_GetTransferProtocols.hpp"

// Directory Functions
#include "SRM_Client_Mkdir.hpp"
#include "SRM_Client_Rmdir.hpp"
#include "SRM_Client_Rm.hpp"
#include "SRM_Client_Ls.hpp"
#include "SRM_Client_Mv.hpp"

// Data Transfer Functions
#include "SRM_Client_PtP.hpp"
#include "SRM_Client_StatusPtP.hpp"
#include "SRM_Client_PutDone.hpp"
#include "SRM_Client_PtG.hpp"
#include "SRM_Client_StatusPtG.hpp"
#include "SRM_Client_ReleaseFiles.hpp"
#include "SRM_Client_Copy.hpp"
#include "SRM_Client_StatusCopy.hpp"
#include "SRM_Client_BOL.hpp"
#include "SRM_Client_StatusBOL.hpp"
#include "SRM_Client_GetRequestTokens.hpp"
#include "SRM_Client_GetRequestSummary.hpp"
#include "SRM_Client_AbortRequest.hpp"
#include "SRM_Client_AbortFiles.hpp"
#include "SRM_Client_ExtendFileLifeTime.hpp"

// Space Management Functions
#include "SRM_Client_ReserveSpace.hpp"
#include "SRM_Client_GetSpaceMetaData.hpp"
#include "SRM_Client_GetSpaceTokens.hpp"
#include "SRM_Client_ReleaseSpace.hpp"

#endif /*SRM_CLIENT_ALL_HPP_*/
