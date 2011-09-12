#ifndef SRM_CLIENT_ALL_HPP_
#define SRM_CLIENT_ALL_HPP_
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
