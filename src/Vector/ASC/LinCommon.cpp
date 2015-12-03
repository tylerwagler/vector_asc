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

#include <iomanip>
#include "LinCommon.h"

namespace Vector {
namespace ASC {

void writeLinBaudrate(File & file, std::ostream & stream, LinBaudrateType & linBaudrate)
{
    /* format: "  BR = %-5u" */
    stream << "  BR = " << std::left << std::setw(5) << std::dec << (uint32_t) linBaudrate;
}

void writeLinChannel(File & file, std::ostream & stream, LinChannel & linChannel)
{
    stream << "L";
    if (linChannel == 1)
        stream << 'i';
    else
        stream << std::setw(0) << std::dec << (uint16_t) linChannel;
}

void writeLinChecksum(File & file, std::ostream & stream, LinChecksum & checksum)
{
    /* format: "  checksum = %3u" */
    /* format: "  checksum = %2.2x" */
    stream << "  checksum = ";
    switch(file.base) {
    case 10:
        stream << std::setw(3) << std::dec;
        break;
    case 16:
        stream << std::setw(2) << std::setprecision(2) << std::hex;
        break;
    }
    stream << (uint16_t) checksum;
}

void writeLinChecksumModel(File & file, std::ostream & stream, LinChecksumModel & checksumModel)
{
    /* format: "  CSM = %s" */
    stream << "  CSM = ";
    switch(checksumModel) {
    case LinChecksumModel::Unknown:
        stream << "unknown";
        break;
    case LinChecksumModel::Classic:
        stream << "classic";
        break;
    case LinChecksumModel::Enhanced:
        stream << "enhanced";
        break;
    case LinChecksumModel::Error:
        stream << "error";
        break;
    }
}

void writeLinData(File & file, std::ostream & stream, std::vector<LinDx> & data)
{
    for (LinDx d: data) {
        switch(file.base) {
        case 10:
            stream << ' ' << std::right
                   << std::setfill(' ') << std::setw(3)
                   << std::dec << (uint16_t) d;
            break;
        case 16:
            stream << ' ' << std::right
                   << std::setfill('0') << std::setw(2)
                   << std::hex << (uint16_t) d;
            break;
        }
    }
}

void writeLinEndOfByte(File & file, std::ostream & stream, std::vector<LinT> & endOfByte, LinDlc & dlc)
{
    /* format: "   EOB = " */
    stream << "   EOB = ";

    for (LinT t: endOfByte)
        stream << ' ' << std::setw(0) << std::setprecision(6) << std::fixed << t;
}

void writeLinEndOfFrame(File & file, std::ostream & stream, LinEndOfFrame & endOfFrame)
{
    /* format: "   EOF = " */
    stream << "   EOF = ";

    stream << std::setw(0) << std::setprecision(6) << std::fixed << endOfFrame;
}

void writeLinEndOfHeader(File & file, std::ostream & stream, LinEndOfHeader & endOfHeader)
{
    /* format: "   EOH = " */
    stream << "   EOH = ";

    stream << std::setw(0) << std::setprecision(6) << std::fixed << endOfHeader;
}

void writeLinHeaderBaudrate(File & file, std::ostream & stream, LinHeaderBaudrate & headerBaudrate)
{
    /* format: "  HBR = %-5.6f" */
    stream << "  HBR = " << std::left << std::setw(5) << std::setprecision(6) << std::fixed << headerBaudrate;
}

void writeLinHeaderTimeLinFullTime(File & file, std::ostream & stream, LinHeaderTime & headerTime, LinFullTime & fullTime)
{
    stream << std::setfill(' ');

    /* format: "   header time = %3u, full time = %3u" */
    stream
            << "   header time = "
            << std::right << std::setw(3) << std::dec << (uint16_t) headerTime
            << ", full time = "
            << std::right << std::setw(3) << std::dec << (uint16_t) fullTime;
}

void writeLinIsShortErrorLinIsDlcTimeoutLinHasDatabytes(File & file, std::ostream & stream, LinIsShortError & isShortError, LinIsDlcTimeout & isDlcTimeout, LinHasDatabytes & hasDatabytes)
{
    /* format: "  ShortError = %d  DlcTimeout = %d  HasDatabytes = %d" */
    stream
            << "  ShortError = " << (isShortError ? '1': '0')
            << "  DlcTimeout = " << (isDlcTimeout ? '1': '0')
            << "  HasDatabytes = " << (hasDatabytes ? '1': '0');
}

void writeLinOffendingByte(File & file, std::ostream & stream, LinOffendingByte & offendingByte)
{
    /* format: "char = %3d" */
    /* format: "char = %2.2x" */
    stream << "char = ";
    switch(file.base) {
    case 10:
        stream << std::setw(3) << std::dec << (uint16_t) offendingByte;
        break;
    case 16:
        stream << std::setw(2) << std::hex << (uint16_t) offendingByte;
        break;
    }

}

void writeLinResponseBaudrate(File & file, std::ostream & stream, LinResponseBaudrate & responseBaudrate)
{
    /* format: "  RBR = %-5u" */
    stream << "  RBR = " << std::left << std::setw(5) << std::dec << (uint16_t) responseBaudrate;
}

void writeLinSimulated(File & file, std::ostream & stream, LinSimulated & simulated)
{
    /* format: "  sim = %d " */
    stream << "  sim = " << (simulated ? '1' : '0') << ' ';
}

void writeLinSlaveIdLinState(File & file, std::ostream & stream, LinSlaveId & slaveId, LinState & linState)
{
    /* format: "  slave = %2u, state = %3u," */
    /* format: "slave = %2u, state = %3u " */
    /* format: "slave = %2u, state = %3u" */
    stream
            << "  slave = "
            << std::right << std::setw(2) << std::dec << (uint16_t) slaveId
            << ", state = "
            << std::right << std::setw(3) << std::dec << (uint16_t) linState;
}

void writeLinStartOfFrame(File & file, std::ostream & stream, LinStartOfFrame & startOfFrame)
{
    if(file.version < File::Version::Ver_6_1) {
        /* format: ", start of frame = %s" */
        stream
                << ", start of frame = "
                << std::setw(0) << std::setprecision(6) << std::fixed << startOfFrame;
    } else {
        /* format: "  SOF = " */
        stream << "  SOF = ";

        stream << std::right << std::setfill(' ') << std::setw(0) << std::setprecision(6) << std::fixed << startOfFrame;
    }
}

void writeLinStateReason(File & file, std::ostream & stream, LinStateReason & stateReason)
{
    /* format: "  StateReason = %-3d */
    /* format: "  StateReason = %2.2x" */
    stream << "  StateReason = ";
    switch(file.base) {
    case 10:
        stream << std::left << std::setw(3) << std::dec << (uint16_t) stateReason;
        break;
    case 16:
        stream << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) stateReason;
        break;
    }
}

void writeLinStopBitOffsetInHeader(File & file, std::ostream & stream, LinStopBitOffsetInHeader & stopBitOffsetInHeader)
{
    /* format: "  HSO = %-8u" */
    stream << "  HSO = " << std::left << std::setw(8) << std::dec << (uint32_t) stopBitOffsetInHeader;
}

void writeLinStopBitOffsetInResponse(File & file, std::ostream & stream, LinStopBitOffsetInResponse & stopBitOffsetInResponse)
{
    /* format: "  RSO = %-8u" */
    stream << "  RSO = " << std::left << std::setw(8) << std::dec << (uint32_t) stopBitOffsetInResponse;
}

void writeLinSubId(File & file, std::ostream & stream, LinNad & nad, LinMessageId & messageId, LinSupplierId & supplierId)
{
    /* format: "  subId = %-3u %-5u %-5u" */
    /* format: "  subId = %2.2x %4.4x %4.4x" */
    stream << "  subId = ";
    switch(file.base) {
    case 10:
        stream
                << std::left << std::setw(3) << std::dec << (uint16_t) nad << ' '
                << std::left << std::setw(5) << std::dec << (uint16_t) messageId << ' '
                << std::left << std::setw(5) << std::dec << (uint16_t) supplierId;
        break;
    case 16:
        stream
                << std::setw(2) << std::setprecision(2) << std::hex << (uint16_t) nad << ' '
                << std::setw(2) << std::setprecision(2) << std::hex << (uint16_t) messageId << ' '
                << std::setw(2) << std::setprecision(2) << std::hex << (uint16_t) supplierId;
        break;
    }
}

void writeLinSyncDel(File & file, std::ostream & stream, LinSyncDel & syncDel)
{
    /* format: " %-6u" */
    stream << ' ' << std::left << std::setw(6) << (uint32_t) syncDel;
}

void writeLinSyncDelimiterTime(File & file, std::ostream & stream, LinSyncDelimiterTime & syncDelimiterTime)
{
    /* format: ", sync delimiter = %3u us " */
    stream
            << ", sync delimiter = "
            << std::setw(3) << std::dec << (uint16_t) syncDelimiterTime.us
            << ' ';

    /* format: "(%f bits)" */
    stream << '(' << std::fixed << syncDelimiterTime.bitTimes << " bits)";
}

void writeLinSyncBreak(File & file, std::ostream & stream, LinSyncBreak & syncBreak)
{
    /* format: "  break = %-6u" */
    stream << "  break = " << std::left << std::setw(6) << (uint32_t) syncBreak;
}

void writeLinSyncBreakTime(File & file, std::ostream & stream, LinSyncBreakTime & syncBreakTime)
{
    /* format: ", sync break = %3u us " */
    stream
            << ", sync break = "
            << std::setw(3) << std::dec << (uint16_t) syncBreakTime.us
            << ' ';

    /* format: "(%f bits)" */
    stream << '(' << std::fixed << syncBreakTime.bitTimes << " bits)";
}

void writeLinWakeupLengthInfo(File & file, std::ostream & stream, LinWakeupLengthInfo & wakeupLengthInfo)
{
    /* format: "  LengthCode = %d" */
    stream << "  LengthCode = " << std::dec << (int16_t) wakeupLengthInfo;
}

}
}
