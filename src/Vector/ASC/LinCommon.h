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

#include <array>
#include <string>
#include "CanCommon.h"
#include "File.h"
#include "LinSymbols.h"

namespace Vector {
namespace ASC {

void writeLinBaudrate(File & file, std::ostream & stream, LinBaudrateType & linBaudrate);

void writeLinChannel(File & file, std::ostream & stream, LinChannel & linChannel);

void writeLinChecksum(File & file, std::ostream & stream, LinChecksum & checksum);

void writeLinChecksumModel(File & file, std::ostream & stream, LinChecksumModel & checksumModel);

#define writeLinDir(file, stream, linDir) writeDir(file, stream, linDir)

void writeLinEndOfByte(File & file, std::ostream & stream, std::array<LinT, 8> & endOfByte, LinDlc & dlc);

void writeLinEndOfFrame(File & file, std::ostream & stream, LinEndOfFrame & endOfFrame);

void writeLinEndOfHeader(File & file, std::ostream & stream, LinEndOfHeader & endOfHeader);

void writeLinHeaderBaudrate(File & file, std::ostream & stream, LinHeaderBaudrate & headerBaudrate);

void writeLinHeaderTimeLinFullTime(File & file, std::ostream & stream, LinHeaderTime & headerTime, LinFullTime & fullTime);

void writeLinResponseBaudrate(File & file, std::ostream & stream, LinResponseBaudrate & responseBaudrate);

void writeLinSimulated(File & file, std::ostream & stream, LinSimulated & simulated);

void writeLinSlaveIdLinState(File & file, std::ostream & stream, LinSlaveId & slaveId, LinState & linState);

void writeLinStartOfFrame(File & file, std::ostream & stream, LinStartOfFrame & startOfFrame);

void writeLinStopBitOffsetInHeader(File & file, std::ostream & stream, LinStopBitOffsetInHeader & stopBitOffsetInHeader);

void writeLinStopBitOffsetInResponse(File & file, std::ostream & stream, LinStopBitOffsetInResponse & stopBitOffsetInResponse);

void writeLinSubId(File & file, std::ostream & stream, LinNad & nad, LinMessageId & messageId, LinSupplierId & supplierId);

void writeLinSyncDel(File & file, std::ostream & stream, LinSyncDel & syncDel);

void writeLinSyncDelimiterTime(File & file, std::ostream & stream, LinSyncDelimiterTime & syncDelimiterTime);

void writeLinSyncBreak(File & file, std::ostream & stream, LinSyncBreak & syncBreak);

void writeLinSyncBreakTime(File & file, std::ostream & stream, LinSyncBreakTime & syncBreakTime);

#define writeLinTime(file, stream, linTime) writeTime(file, stream, linTime)

void writeLinWakeupLengthInfo(File & file, std::ostream & stream, LinWakeupLengthInfo & wakeupLengthInfo);

}
}
