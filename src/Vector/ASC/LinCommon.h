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

void writeLinBaudrate(const File & file, std::ostream & stream, const LinBaudrateType & linBaudrate);

void writeLinChannel(const File & file, std::ostream & stream, const LinChannel & linChannel);

void writeLinChecksum(const File & file, std::ostream & stream, const LinChecksum & linChecksum);

void writeLinChecksumModel(const File & file, std::ostream & stream, const LinChecksumModel & linChecksumModel);

#define writeLinData(file, stream, linData) writeData(file, stream, linData)

#define writeLinDir(file, stream, linDir) writeDir(file, stream, linDir)

void writeLinEndOfByte(const File & file, std::ostream & stream, const std::vector<LinT> & linEndOfByte, const LinDlc & linDlc);

void writeLinEndOfFrame(const File & file, std::ostream & stream, const LinEndOfFrame & linEndOfFrame);

void writeLinEndOfHeader(const File & file, std::ostream & stream, const LinEndOfHeader & linEndOfHeader);

void writeLinHeaderBaudrate(const File & file, std::ostream & stream, const LinHeaderBaudrate & linHeaderBaudrate);

void writeLinHeaderTimeLinFullTime(const File & file, std::ostream & stream, const LinHeaderTime & linHeaderTime, const LinFullTime & linFullTime);

void writeLinIsShortErrorLinIsDlcTimeoutLinHasDatabytes(const File & file, std::ostream & stream, const LinIsShortError & linIsShortError, const LinIsDlcTimeout & linIsDlcTimeout, const LinHasDatabytes & linHasDatabytes);

void writeLinOffendingByte(const File & file, std::ostream & stream, const LinOffendingByte & linOffendingByte);

void writeLinResponseBaudrate(const File & file, std::ostream & stream, const LinResponseBaudrate & linResponseBaudrate);

void writeLinSimulated(const File & file, std::ostream & stream, const LinSimulated & linSimulated);

void writeLinSlaveIdLinState(const File & file, std::ostream & stream, const LinSlaveId & linSlaveId, const LinState & linState);

void writeLinStartOfFrame(const File & file, std::ostream & stream, const LinStartOfFrame & linStartOfFrame);

void writeLinStateReason(const File & file, std::ostream & stream, const LinStateReason & linStateReason);

void writeLinStopBitOffsetInHeader(const File & file, std::ostream & stream, const LinStopBitOffsetInHeader & linStopBitOffsetInHeader);

void writeLinStopBitOffsetInResponse(const File & file, std::ostream & stream, const LinStopBitOffsetInResponse & linStopBitOffsetInResponse);

void writeLinSubId(const File & file, std::ostream & stream, const LinNad & linNad, const LinMessageId & linMessageId, const LinSupplierId & linSupplierId);

void writeLinSyncDel(const File & file, std::ostream & stream, const LinSyncDel & linSyncDel);

void writeLinSyncDelimiterTime(const File & file, std::ostream & stream, const LinSyncDelimiterTime & linSyncDelimiterTime);

void writeLinSyncBreak(const File & file, std::ostream & stream, const LinSyncBreak & linSyncBreak);

void writeLinSyncBreakTime(const File & file, std::ostream & stream, const LinSyncBreakTime & linSyncBreakTime);

#define writeLinTime(file, stream, linTime) writeTime(file, stream, linTime)

void writeLinWakeupLengthInfo(const File & file, std::ostream & stream, const LinWakeupLengthInfo & linWakeupLengthInfo);

}
}
