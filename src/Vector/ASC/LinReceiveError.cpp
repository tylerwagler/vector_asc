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
#include <regex>
#include <sstream>

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinReceiveError.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinReceiveError * LinReceiveError::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel
                     "(" REGEX_WS REGEX_LIN_ID REGEX_WS REGEX_LIN_DLC ")?"
                     REGEX_WS "RcvError:" REGEX_ws REGEX_LIN_description
                     "(" REGEX_WS "char" REGEX_ws "=" REGEX_ws REGEX_LIN_offendingByte ")?"
                     "(" REGEX_WS "slave" REGEX_ws "=" REGEX_ws REGEX_LIN_slaveId "," REGEX_ws "state" REGEX_ws "=" REGEX_ws REGEX_LIN_state ")?"
                     "(" REGEX_WS "StateReason" REGEX_ws "=" REGEX_ws REGEX_LIN_StateReason
                     REGEX_WS "ShortError" REGEX_ws "=" REGEX_ws REGEX_LIN_IsShortError
                     REGEX_WS "DlcTimeout" REGEX_ws "=" REGEX_ws REGEX_LIN_IsDLCTimeout
                     REGEX_WS "HasDatabytes" REGEX_ws "=" REGEX_ws REGEX_LIN_HasDatabytes "((" REGEX_WS REGEX_LIN_Dx"){0,8})"
                     REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate
                     REGEX_WS "break" REGEX_ws "=" REGEX_ws REGEX_LIN_SyncBreak REGEX_WS REGEX_LIN_SyncDel
                     "(" REGEX_WS "subId" REGEX_ws "=" REGEX_ws REGEX_LIN_NAD REGEX_WS REGEX_LIN_MessageId REGEX_WS REGEX_LIN_SupplierId ")?"
                     "(" REGEX_WS "EOH" REGEX_ws "=" REGEX_ws REGEX_LIN_endOfHeader ")?"
                     "(" REGEX_WS "EOB" REGEX_ws "=" REGEX_ws "((" REGEX_WS REGEX_LIN_T "){0,8}))?"
                     "(" REGEX_WS "RBR" REGEX_ws "=" REGEX_ws REGEX_LIN_responseBaudrate
                     "(" REGEX_WS "HBR" REGEX_ws "=" REGEX_ws REGEX_LIN_headerBaudrate
                     REGEX_WS "HSO" REGEX_ws "=" REGEX_ws REGEX_LIN_stopBitOffsetInHeader
                     REGEX_WS "RSO" REGEX_ws "=" REGEX_ws REGEX_LIN_stopBitOffsetInResponse
                     "(" REGEX_WS "CSM" REGEX_ws "=" REGEX_ws REGEX_LIN_checksumModel ")?)?)?)?" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linReceiveError = new LinReceiveError;
        linReceiveError->time = std::stod(match[1]);
        linReceiveError->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        if (match[3] != "") {
            linReceiveError->id = match[4];
            linReceiveError->dlc = std::stoul(match[5]);
        }
        linReceiveError->description = match[6];
        if (match[7] != "")
            linReceiveError->offendingByte = std::stoul(match[8], nullptr, file.base);
        if (match[9] != "") {
            linReceiveError->slaveId = std::stoul(match[10]);
            linReceiveError->state = std::stoul(match[11]);
        }
        if (match[12] != "") {
            linReceiveError->stateReason = std::stoul(match[13], nullptr, file.base);
            linReceiveError->isShortError = (match[14] == '1');
            linReceiveError->isDlcTimeout = (match[15] == '1');
            linReceiveError->hasDataBytes = (match[16] == '1');
            std::istringstream iss1(match[17]);
            switch (file.base) {
            case 10:
                iss1 >> std::dec;
                break;
            case 16:
                iss1 >> std::hex;
                break;
            }
            while (!iss1.eof()) {
                unsigned short s;
                iss1 >> s;
                linReceiveError->data.push_back(s);
            }
            linReceiveError->startOfFrame = std::stod(match[19]);
            linReceiveError->baudrate = std::stoul(match[20]);
            linReceiveError->syncBreak = std::stoul(match[21]);
            linReceiveError->syncDel = std::stoul(match[22]);
            if (match[23] != "") {
                linReceiveError->nad = std::stoul(match[24], nullptr, file.base);
                linReceiveError->messageId = std::stoul(match[25], nullptr, file.base);
                linReceiveError->supplierId = std::stoul(match[26], nullptr, file.base);
            }
            if (match[27] != "")
                linReceiveError->endOfHeader = std::stod(match[28]);
            if (match[29] != "") {
                std::istringstream iss2(match[30]);
                while (!iss2.eof()) {
                    double s;
                    iss2 >> s;
                    linReceiveError->endOfByte.push_back(s);
                }
            }
            if (match[32] != "") {
                linReceiveError->responseBaudrate = std::stoul(match[33]);
                if (match[34] != "") {
                    linReceiveError->headerBaudrate = std::stod(match[35]);
                    linReceiveError->stopBitOffsetInResponse = std::stoul(match[36]);
                    linReceiveError->stopBitOffsetInHeader = std::stoul(match[37]);
                    if (match[38] != "") {
                        if (match[39] == "unknown")
                            linReceiveError->checksumModel = LinChecksumModel::Unknown;
                        else if (match[39] == "classic")
                            linReceiveError->checksumModel = LinChecksumModel::Classic;
                        else if (match[39] == "enhanced")
                            linReceiveError->checksumModel = LinChecksumModel::Enhanced;
                        else if (match[39] == "error")
                            linReceiveError->checksumModel = LinChecksumModel::Error;
                    }
                }
            }
        }
        return linReceiveError;
    }

    return nullptr;
}

void LinReceiveError::write(File & file, std::ostream & stream) {
    writeLinTime(file, stream, time);
    stream << ' ';

    writeLinChannel(file, stream, channel);
    stream << ' ';

    /* format: "%-12.1x %d RcvError: " */
    /* format: "%-12.1d %d RcvError: " */
    /* format: "%s %d RcvError: " */
    stream
            << std::left << std::setw(12) << id
            << ' '
            << std::right << std::setw(0) << std::dec << (uint16_t) dlc
            << " RcvError: ";

    stream << description;
    // writeLinOffendingByte(file, stream, offendingByte); // @todo actually opt.
    if ((slaveId != 0) || (state != 0))
        writeLinSlaveIdLinState(file, stream, slaveId, state);
    if (file.version >= File::Version::Ver_6_1) {
        writeLinStateReason(file, stream, stateReason);
        writeLinIsShortErrorLinIsDlcTimeoutLinHasDatabytes(file, stream, isShortError, isDlcTimeout, hasDataBytes);
        writeLinData(file, stream, data);
        writeLinStartOfFrame(file, stream, startOfFrame);
        writeLinBaudrate(file, stream, baudrate);
        writeLinSyncBreak(file, stream, syncBreak);
        writeLinSyncDel(file, stream, syncDel);
        if ((nad != 0) || (messageId != 0) || (supplierId != 0))
            writeLinSubId(file, stream, nad, messageId, supplierId);
        writeLinEndOfHeader(file, stream, endOfHeader); // @todo actually opt.
        writeLinEndOfByte(file, stream, endOfByte, dlc); // @todo actually opt.
        if (file.version >= File::Version::Ver_7_1_SP3) {
            writeLinResponseBaudrate(file, stream, responseBaudrate); // @todo actually opt. in 7.1 SP3
            if (file.version >= File::Version::Ver_7_2) {
                writeLinHeaderBaudrate(file, stream, headerBaudrate);
                writeLinStopBitOffsetInHeader(file, stream, stopBitOffsetInHeader);
                writeLinStopBitOffsetInResponse(file, stream, stopBitOffsetInResponse);
                if (file.version >= File::Version::Ver_7_2_SP3)
                    writeLinChecksumModel(file, stream, checksumModel);
            }
        }
    }

    stream << endl;
}

}
}
