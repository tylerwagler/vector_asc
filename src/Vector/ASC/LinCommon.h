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

#pragma once

#include <Vector/ASC/platform.h>

#include <ostream>
#include <vector>

#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/File.h>
#include <Vector/ASC/LinSymbols.h>

namespace Vector {
namespace ASC {

void writeLinBaudrate(File & file, std::ostream & stream, LinBaudrateType & linBaudrate);

void writeLinChannel(File & file, std::ostream & stream, LinChannel & linChannel);

void writeLinChecksum(File & file, std::ostream & stream, LinChecksum & linChecksum);

void writeLinChecksumModel(File & file, std::ostream & stream, LinChecksumModel & linChecksumModel);

#define writeLinData(file, stream, linData) writeData(file, stream, linData)

#define writeLinDir(file, stream, linDir) writeDir(file, stream, linDir)

void writeLinEndOfByte(File & file, std::ostream & stream, std::vector<LinT> & linEndOfByte, LinDlc & linDlc);

void writeLinEndOfFrame(File & file, std::ostream & stream, LinEndOfFrame & linEndOfFrame);

void writeLinEndOfHeader(File & file, std::ostream & stream, LinEndOfHeader & linEndOfHeader);

void writeLinHeaderBaudrate(File & file, std::ostream & stream, LinHeaderBaudrate & linHeaderBaudrate);

void writeLinHeaderTimeLinFullTime(File & file, std::ostream & stream, LinHeaderTime & linHeaderTime, LinFullTime & linFullTime);

void writeLinIsShortErrorLinIsDlcTimeoutLinHasDatabytes(File & file, std::ostream & stream, LinIsShortError & linIsShortError, LinIsDlcTimeout & linIsDlcTimeout, LinHasDatabytes & linHasDatabytes);

void writeLinOffendingByte(File & file, std::ostream & stream, LinOffendingByte & linOffendingByte);

void writeLinResponseBaudrate(File & file, std::ostream & stream, LinResponseBaudrate & linResponseBaudrate);

void writeLinSimulated(File & file, std::ostream & stream, LinSimulated & linSimulated);

void writeLinSlaveIdLinState(File & file, std::ostream & stream, LinSlaveId & linSlaveId, LinState & linState);

void writeLinStartOfFrame(File & file, std::ostream & stream, LinStartOfFrame & linStartOfFrame);

void writeLinStateReason(File & file, std::ostream & stream, LinStateReason & linStateReason);

void writeLinStopBitOffsetInHeader(File & file, std::ostream & stream, LinStopBitOffsetInHeader & linStopBitOffsetInHeader);

void writeLinStopBitOffsetInResponse(File & file, std::ostream & stream, LinStopBitOffsetInResponse & linStopBitOffsetInResponse);

void writeLinSubId(File & file, std::ostream & stream, LinNad & linNad, LinMessageId & linMessageId, LinSupplierId & linSupplierId);

void writeLinSyncDel(File & file, std::ostream & stream, LinSyncDel & linSyncDel);

void writeLinSyncDelimiterTime(File & file, std::ostream & stream, LinSyncDelimiterTime & linSyncDelimiterTime);

void writeLinSyncBreak(File & file, std::ostream & stream, LinSyncBreak & linSyncBreak);

void writeLinSyncBreakTime(File & file, std::ostream & stream, LinSyncBreakTime & linSyncBreakTime);

#define writeLinTime(file, stream, linTime) writeTime(file, stream, linTime)

void writeLinWakeupLengthInfo(File & file, std::ostream & stream, LinWakeupLengthInfo & linWakeupLengthInfo);

}
}
