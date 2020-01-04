/*
 * Copyright (C) 2014-2015 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

/** LIN Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

#define REGEX_LIN_baudrate "([[:digit:]]{1,5})"
#define REGEX_LIN_Channel "L([[:xdigit:]i*]{1,4})"
#define REGEX_LIN_checksum "([[:xdigit:]]{1,3})"
#define REGEX_LIN_checksumModel "(unknown|classic|enhanced|error)"
#define REGEX_LIN_checksumModelInfo "Using (enhanced|classic) checksum"
#define REGEX_LIN_Dir "(Rx|Tx|TxRq)"
#define REGEX_LIN_DLC "([-[:digit:]]{1,2})"
#define REGEX_LIN_NumberOfResponseBytes "([[:digit:]])"
#define REGEX_LIN_Dx "[[:xdigit:]]{1,3}"
#define REGEX_LIN_description "(.+?)"
#define REGEX_LIN_DomSigState "(detected|continuing|finished)"
#define REGEX_LIN_DomSigLength "([[:digit:]]{1,8})"
#define REGEX_LIN_endOfFrame "([[:digit:].]{3,})"
#define REGEX_LIN_ETFName "([[:alnum:]_]+)"
#define REGEX_LIN_endOfHeader "([[:digit:].]{3,})"
#define REGEX_LIN_FullTime "([[:digit:]]+)"
#define REGEX_LIN_fullTime REGEX_LIN_FullTime
#define REGEX_LIN_HasDatabytes "([01])"
#define REGEX_LIN_HeaderTime "([[:digit:]]+)"
#define REGEX_LIN_headerTime REGEX_LIN_HeaderTime
#define REGEX_LIN_headerBaudrate "([[:digit:].]{3,12})"
#define REGEX_LIN_ID "([[:alnum:]_]+)"
#define REGEX_LIN_IsDLCTimeout "([01])"
#define REGEX_LIN_IsShortError "([01])"
#define REGEX_LIN_MessageId "([[:xdigit:]]{1,5})"
#define REGEX_LIN_NAD "([[:xdigit:]]{1,3})"
#define REGEX_LIN_offendingByte "([[:xdigit:]]{1,3})"
#define REGEX_LIN_responseBaudrate "([[:digit:]]{1,5})"
#define REGEX_LIN_simulated "([01])"
#define REGEX_LIN_scheduleTableIndex "([[:digit:]]+)"
#define REGEX_LIN_slaveId "([[:digit:]]{1,2})"
#define REGEX_LIN_SpikeLength "([[:digit:]]{1,6})"
#define REGEX_LIN_startOfFrame "([[:digit:].]{3,})"
#define REGEX_LIN_state "([[:digit:]]{1,3})"
#define REGEX_LIN_StateReason "([[:xdigit:]]{1,3})"
#define REGEX_LIN_stopBitOffsetInHeader "([[:digit:]]{1,8})"
#define REGEX_LIN_stopBitOffsetInResponse "([[:digit:]]{1,8})"
#define REGEX_LIN_SupplierId "([[:xdigit:]]{1,5})"
#define REGEX_LIN_SyncBreak "([[:digit:]]{1,6})"
#define REGEX_LIN_SyncDel "([[:digit:]]{1,6})"
#define REGEX_LIN_syncBreakTime "([[:digit:]]+)" REGEX_ws "us" REGEX_ws "\\(([[:digit:].]+)" REGEX_ws "bits\\)"
#define REGEX_LIN_syncDelimiterTime "([[:digit:]]+)" REGEX_ws "us" REGEX_ws "\\(([[:digit:].]+)" REGEX_ws "bits\\)"
#define REGEX_LIN_T "[[:digit:].]{3,}"
#define REGEX_LIN_Time "([[:digit:].]{3,})"
#define REGEX_LIN_TimeInterval "[[:digit:]]{1,5}"
#define REGEX_LIN_WakeupByte "([[:xdigit:]]{1,3})"
#define REGEX_LIN_WakeupLengthInfo "([012])"
#define REGEX_LIN_IsSlowResponse "([[:digit:]])"
#define REGEX_LIN_ResponseWasInterruptedByBreak "([[:digit:]])"
#define REGEX_LIN_Width "([[:digit:]]{3,4})"
#define REGEX_LIN_DisturbanceType "(dominant|recessive|header|bitstream|variableBitstream)"
#define REGEX_LIN_ByteIndex "([[:digit:]])"
#define REGEX_LIN_BitIndex "([[:digit:]]{1,3})"
#define REGEX_LIN_BitOffsetInSixteenthBits "([[:digit:]]{1,2})"
#define REGEX_LIN_DisturbanceLengthInSixteenthBits "([[:digit:]]{1,2})"
#define REGEX_LIN_IDorFF "([[:xdigit:]]{1,3})"

}
}
