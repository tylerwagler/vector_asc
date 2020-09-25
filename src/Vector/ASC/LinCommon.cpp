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

#include <Vector/ASC/LinCommon.h>

namespace Vector {
namespace ASC {

void writeLinBaudrate(const File & /*file*/, std::ostream & stream, const LinBaudrateType & linBaudrate) {
    /* format: "  BR = %-5u" */
    stream << "  BR = " << std::left << std::setw(5) << std::dec << linBaudrate;
}

void writeLinChannel(const File & /*file*/, std::ostream & stream, const LinChannel & linChannel) {
    stream << "L";
    if (linChannel == 1)
        stream << 'i';
    else
        stream << std::setw(0) << std::dec << linChannel;
}

void writeLinChecksum(const File & file, std::ostream & stream, const LinChecksum & linChecksum) {
    /* format: "  checksum = %3u" */
    /* format: "  checksum = %2.2x" */
    stream << "  checksum = ";
    switch (file.base) {
    case 10:
        stream << std::setw(3) << std::dec;
        break;
    case 16:
        stream << std::setw(2) << std::setprecision(2) << std::hex;
        break;
    }
    stream << (uint16_t) linChecksum;
}

void writeLinChecksumModel(const File & /*file*/, std::ostream & stream, const LinChecksumModel & linChecksumModel) {
    /* format: "  CSM = %s" */
    stream << "  CSM = ";
    switch (linChecksumModel) {
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

void writeLinEndOfByte(const File & /*file*/, std::ostream & stream, const std::vector<LinT> & linEndOfByte, const LinDlc & /*linDlc*/) {
    /* format: "   EOB = " */
    stream << "   EOB = ";

    for (LinT t : linEndOfByte)
        stream << ' ' << std::setw(0) << std::setprecision(6) << std::fixed << t;
}

void writeLinEndOfFrame(const File & /*file*/, std::ostream & stream, const LinEndOfFrame & linEndOfFrame) {
    /* format: "   EOF = " */
    stream << "   EOF = ";

    stream << std::setw(0) << std::setprecision(6) << std::fixed << linEndOfFrame;
}

void writeLinEndOfHeader(const File & /*file*/, std::ostream & stream, const LinEndOfHeader & linEndOfHeader) {
    /* format: "   EOH = " */
    stream << "   EOH = ";

    stream << std::setw(0) << std::setprecision(6) << std::fixed << linEndOfHeader;
}

void writeLinHeaderBaudrate(const File & /*file*/, std::ostream & stream, const LinHeaderBaudrate & linHeaderBaudrate) {
    /* format: "  HBR = %-5.6f" */
    stream << "  HBR = " << std::left << std::setw(5) << std::setprecision(6) << std::fixed << linHeaderBaudrate;
}

void writeLinHeaderTimeLinFullTime(const File & /*file*/, std::ostream & stream, const LinHeaderTime & linHeaderTime, const LinFullTime & linFullTime) {
    stream << std::setfill(' ');

    /* format: "   header time = %3u, full time = %3u" */
    stream
            << "   header time = "
            << std::right << std::setw(3) << std::dec << linHeaderTime
            << ", full time = "
            << std::right << std::setw(3) << std::dec << linFullTime;
}

void writeLinIsShortErrorLinIsDlcTimeoutLinHasDatabytes(const File & /*file*/, std::ostream & stream, const LinIsShortError & linIsShortError, const LinIsDlcTimeout & linIsDlcTimeout, const LinHasDatabytes & linHasDatabytes) {
    /* format: "  ShortError = %d  DlcTimeout = %d  HasDatabytes = %d" */
    stream
            << "  ShortError = " << (linIsShortError ? '1' : '0')
            << "  DlcTimeout = " << (linIsDlcTimeout ? '1' : '0')
            << "  HasDatabytes = " << (linHasDatabytes ? '1' : '0');
}

void writeLinOffendingByte(const File & file, std::ostream & stream, const LinOffendingByte & linOffendingByte) {
    /* format: "char = %3d" */
    /* format: "char = %2.2x" */
    stream << "char = ";
    switch (file.base) {
    case 10:
        stream << std::setw(3) << std::dec << (uint16_t) linOffendingByte;
        break;
    case 16:
        stream << std::setw(2) << std::hex << (uint16_t) linOffendingByte;
        break;
    }

}

void writeLinResponseBaudrate(const File & /*file*/, std::ostream & stream, const LinResponseBaudrate & linResponseBaudrate) {
    /* format: "  RBR = %-5u" */
    stream << "  RBR = " << std::left << std::setw(5) << std::dec << linResponseBaudrate;
}

void writeLinSimulated(const File & /*file*/, std::ostream & stream, const LinSimulated & linSimulated) {
    /* format: "  sim = %d " */
    stream << "  sim = " << (linSimulated ? '1' : '0') << ' ';
}

void writeLinSlaveIdLinState(const File & /*file*/, std::ostream & stream, const LinSlaveId & linSlaveId, const LinState & linState) {
    /* format: "  slave = %2u, state = %3u," */
    /* format: "slave = %2u, state = %3u " */
    /* format: "slave = %2u, state = %3u" */
    stream
            << "  slave = "
            << std::right << std::setw(2) << std::dec << (uint16_t) linSlaveId
            << ", state = "
            << std::right << std::setw(3) << std::dec << (uint16_t) linState;
}

void writeLinStartOfFrame(const File & file, std::ostream & stream, const LinStartOfFrame & linStartOfFrame) {
    if (file.version < File::Version::Ver_6_1) {
        /* format: ", start of frame = %s" */
        stream
                << ", start of frame = "
                << std::setw(0) << std::setprecision(6) << std::fixed << linStartOfFrame;
    } else {
        /* format: "  SOF = " */
        stream << "  SOF = ";

        stream << std::right << std::setfill(' ') << std::setw(0) << std::setprecision(6) << std::fixed << linStartOfFrame;
    }
}

void writeLinStateReason(const File & file, std::ostream & stream, const LinStateReason & linStateReason) {
    /* format: "  StateReason = %-3d */
    /* format: "  StateReason = %2.2x" */
    stream << "  StateReason = ";
    switch (file.base) {
    case 10:
        stream << std::left << std::setw(3) << std::dec << (uint16_t) linStateReason;
        break;
    case 16:
        stream << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) linStateReason;
        break;
    }
}

void writeLinStopBitOffsetInHeader(const File & /*file*/, std::ostream & stream, const LinStopBitOffsetInHeader & linStopBitOffsetInHeader) {
    /* format: "  HSO = %-8u" */
    stream << "  HSO = " << std::left << std::setw(8) << std::dec << linStopBitOffsetInHeader;
}

void writeLinStopBitOffsetInResponse(const File & /*file*/, std::ostream & stream, const LinStopBitOffsetInResponse & linStopBitOffsetInResponse) {
    /* format: "  RSO = %-8u" */
    stream << "  RSO = " << std::left << std::setw(8) << std::dec << linStopBitOffsetInResponse;
}

void writeLinSubId(const File & file, std::ostream & stream, const LinNad & linNad, const LinMessageId & linMessageId, const LinSupplierId & linSupplierId) {
    /* format: "  subId = %-3u %-5u %-5u" */
    /* format: "  subId = %2.2x %4.4x %4.4x" */
    stream << "  subId = ";
    switch (file.base) {
    case 10:
        stream
                << std::left << std::setw(3) << std::dec << (uint16_t) linNad
                << ' ' << std::left << std::setw(5) << std::dec << linMessageId
                << ' ' << std::left << std::setw(5) << std::dec << linSupplierId;
        break;
    case 16:
        stream
                << std::setw(2) << std::setprecision(2) << std::hex << (uint16_t) linNad
                << ' ' << std::setw(2) << std::setprecision(2) << std::hex << linMessageId
                << ' ' << std::setw(2) << std::setprecision(2) << std::hex << linSupplierId;
        break;
    }
}

void writeLinSyncDel(const File & /*file*/, std::ostream & stream, const LinSyncDel & linSyncDel) {
    /* format: " %-6u" */
    stream << ' ' << std::left << std::setw(6) << linSyncDel;
}

void writeLinSyncDelimiterTime(const File & /*file*/, std::ostream & stream, const LinSyncDelimiterTime & linSyncDelimiterTime) {
    /* format: ", sync delimiter = %3u us " */
    stream
            << ", sync delimiter = "
            << std::setw(3) << std::dec << linSyncDelimiterTime.us
            << ' ';

    /* format: "(%f bits)" */
    stream << '(' << std::fixed << linSyncDelimiterTime.bitTimes << " bits)";
}

void writeLinSyncBreak(const File & /*file*/, std::ostream & stream, const LinSyncBreak & linSyncBreak) {
    /* format: "  break = %-6u" */
    stream << "  break = " << std::left << std::setw(6) << linSyncBreak;
}

void writeLinSyncBreakTime(const File & /*file*/, std::ostream & stream, const LinSyncBreakTime & linSyncBreakTime) {
    /* format: ", sync break = %3u us " */
    stream
            << ", sync break = "
            << std::setw(3) << std::dec << linSyncBreakTime.us
            << ' ';

    /* format: "(%f bits)" */
    stream << '(' << std::fixed << linSyncBreakTime.bitTimes << " bits)";
}

void writeLinWakeupLengthInfo(const File & /*file*/, std::ostream & stream, const LinWakeupLengthInfo & linWakeupLengthInfo) {
    /* format: "  LengthCode = %d" */
    stream << "  LengthCode = " << std::dec << (int16_t) linWakeupLengthInfo;
}

}
}
