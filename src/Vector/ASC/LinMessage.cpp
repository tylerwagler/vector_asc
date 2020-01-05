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
#include <Vector/ASC/LinMessage.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinMessage * LinMessage::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS REGEX_LIN_ID REGEX_WS REGEX_LIN_Dir
                     REGEX_WS REGEX_LIN_DLC "((" REGEX_WS REGEX_LIN_Dx "){0,8})"
                     "(" REGEX_WS "slave" REGEX_ws "=" REGEX_ws REGEX_LIN_slaveId "," REGEX_ws "state" REGEX_ws "=" REGEX_ws REGEX_LIN_state ")?"
                     REGEX_WS "checksum" REGEX_ws "=" REGEX_ws REGEX_LIN_checksum
                     REGEX_WS "header time" REGEX_ws "=" REGEX_ws REGEX_LIN_headerTime ","
                     REGEX_ws "full time" REGEX_ws "=" REGEX_ws REGEX_LIN_fullTime
                     "(("
                     REGEX_WS "start of frame" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame ","
                     REGEX_ws "sync break" REGEX_ws "=" REGEX_ws REGEX_LIN_syncBreakTime ","
                     REGEX_ws "sync delimiter" REGEX_ws "=" REGEX_ws REGEX_LIN_syncDelimiterTime
                     ")|("
                     REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate
                     REGEX_WS "break" REGEX_ws "=" REGEX_ws REGEX_LIN_SyncBreak REGEX_WS REGEX_LIN_SyncDel
                     "(" REGEX_WS "subId" REGEX_ws "=" REGEX_ws REGEX_LIN_NAD REGEX_WS REGEX_LIN_MessageId REGEX_WS REGEX_LIN_SupplierId ")?"
                     REGEX_WS "EOH" REGEX_ws "=" REGEX_ws REGEX_LIN_endOfHeader
                     REGEX_WS "EOB" REGEX_ws "=((" REGEX_ws REGEX_LIN_T "){0,8})"
                     REGEX_WS "sim" REGEX_ws "=" REGEX_ws REGEX_LIN_simulated
                     "(" REGEX_WS "EOF" REGEX_ws "=" REGEX_ws REGEX_LIN_endOfFrame
                     "(" REGEX_WS "RBR" REGEX_ws "=" REGEX_ws REGEX_LIN_responseBaudrate
                     "(" REGEX_WS "HBR" REGEX_ws "=" REGEX_ws REGEX_LIN_headerBaudrate
                     REGEX_WS "HSO" REGEX_ws "=" REGEX_ws REGEX_LIN_stopBitOffsetInHeader
                     REGEX_WS "RSO" REGEX_ws "=" REGEX_ws REGEX_LIN_stopBitOffsetInResponse
                     "(" REGEX_WS "CSM" REGEX_ws "=" REGEX_ws REGEX_LIN_checksumModel
                     ")?)?)?)?))" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linMessage = new LinMessage;
        linMessage->time = std::stod(match[1]);
        linMessage->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linMessage->id = match[3];
        if (match[4] == "Rx")
            linMessage->dir = Dir::Rx;
        else if (match[4] == "Tx")
            linMessage->dir = Dir::Tx;
        linMessage->dlc = std::stoul(match[5]);
        std::istringstream iss1(match[6]);
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
            linMessage->data.push_back(s);
        }
        if (match[8] != "") {
            linMessage->slaveId = std::stoul(match[9]);
            linMessage->state = std::stoul(match[10]);
        }
        linMessage->checksum = std::stoul(match[11], nullptr, file.base);
        linMessage->headerTime = std::stoul(match[12]);
        linMessage->fullTime = std::stoul(match[13]);
        if (match[14] != "") {
            if (match[15] != "") {
                linMessage->startOfFrame = std::stod(match[16]);
                linMessage->syncBreakTime.us = std::stoul(match[17]);
                linMessage->syncBreakTime.bitTimes = std::stod(match[18]);
                linMessage->syncDelimiterTime.us = std::stoul(match[19]);
                linMessage->syncDelimiterTime.bitTimes = std::stod(match[20]);
            }
            if (match[21] != "") {
                linMessage->startOfFrame = std::stod(match[22]);
                linMessage->baudrate = std::stoul(match[23]);
                linMessage->syncBreak = std::stoul(match[24]);
                linMessage->syncDel = std::stoul(match[25]);
                if (match[26] != "") {
                    linMessage->nad = std::stoul(match[27], nullptr, file.base);
                    linMessage->messageId = std::stoul(match[28], nullptr, file.base);
                    linMessage->supplierId = std::stoul(match[29], nullptr, file.base);
                }
                linMessage->endOfHeader = std::stod(match[30]);
                std::istringstream iss2(match[31]);
                while (!iss2.eof()) {
                    double s;
                    iss2 >> s;
                    linMessage->endOfByte.push_back(s);
                }
                linMessage->simulated = (match[33] == '1');
                if (match[34] != "")
                    linMessage->endOfFrame = std::stod(match[35]);
                if (match[36] != "")
                    linMessage->responseBaudrate = std::stoul(match[37]);
                if (match[38] != "")
                    linMessage->headerBaudrate = std::stod(match[39]);
                linMessage->stopBitOffsetInHeader = std::stoul(match[40]);
                linMessage->stopBitOffsetInResponse = std::stoul(match[41]);
                if (match[42] != "") {
                    if (match[43] == "unknown")
                        linMessage->checksumModel = LinChecksumModel::Unknown;
                    else if (match[43] == "classic")
                        linMessage->checksumModel = LinChecksumModel::Classic;
                    else if (match[43] == "enhanced")
                        linMessage->checksumModel = LinChecksumModel::Enhanced;
                    else if (match[43] == "error")
                        linMessage->checksumModel = LinChecksumModel::Error;
                }
            }
        }
        return linMessage;
    }

    return nullptr;
}

void LinMessage::write(File & file, std::ostream & stream) {
    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s %-12.12s    %s     %d" */
    /* format: "%s %-12.1d    %s     %d" */
    /* format: "%s %-12.1x    %s     %d" */
    writeLinChannel(file, stream, channel);
    stream
            << ' '
            << std::left << std::setw(12) << id
            << "    ";
    writeLinDir(file, stream, dir);
    stream
            << "     "
            << std::right << std::setw(0) << std::dec << (uint16_t) dlc;

    writeLinData(file, stream, data);
    stream << ' ';
    if ((slaveId != 0) || (state != 0))
        writeLinSlaveIdLinState(file, stream, slaveId, state);
    else
        stream << "                           ";
    writeLinChecksum(file, stream, checksum);
    writeLinHeaderTimeLinFullTime(file, stream, headerTime, fullTime);
    writeLinStartOfFrame(file, stream, startOfFrame);
    if (file.version < File::Version::Ver_6_1) {
        writeLinSyncBreakTime(file, stream, syncBreakTime);
        writeLinSyncDelimiterTime(file, stream, syncDelimiterTime);
    } else {
        writeLinBaudrate(file, stream, baudrate);
        writeLinSyncBreak(file, stream, syncBreak);
        writeLinSyncDel(file, stream, syncDel);
        if ((nad != 0) || (messageId != 0) || (supplierId != 0))
            writeLinSubId(file, stream, nad, messageId, supplierId);
        writeLinEndOfHeader(file, stream, endOfHeader);
        writeLinEndOfByte(file, stream, endOfByte, dlc);
        writeLinSimulated(file, stream, simulated);
        if (file.version >= File::Version::Ver_7_0) {
            writeLinEndOfFrame(file, stream, endOfFrame);
            if (file.version >= File::Version::Ver_7_1_SP3) {
                writeLinResponseBaudrate(file, stream, responseBaudrate);
                if (file.version >= File::Version::Ver_7_2) {
                    writeLinHeaderBaudrate(file, stream, headerBaudrate);
                    writeLinStopBitOffsetInHeader(file, stream, stopBitOffsetInHeader);
                    writeLinStopBitOffsetInResponse(file, stream, stopBitOffsetInResponse);
                    if (file.version >= File::Version::Ver_7_2_SP3)
                        writeLinChecksumModel(file, stream, checksumModel);
                }
            }
        }
    }

    stream << endl;
}

}
}
