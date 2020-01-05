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

#include <Vector/ASC/LinChecksumError.h>
#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinChecksumError * LinChecksumError::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS REGEX_LIN_ID REGEX_WS "CSErr"
                     REGEX_WS REGEX_LIN_Dir REGEX_WS REGEX_LIN_DLC
                     "((" REGEX_WS "[[:xdigit:]]+){0,8})"
                     "(" REGEX_WS "slave" REGEX_ws "=" REGEX_ws REGEX_LIN_slaveId "," REGEX_ws "state" REGEX_ws "=" REGEX_ws REGEX_LIN_state ")?"
                     REGEX_WS "checksum" REGEX_ws "=" REGEX_ws REGEX_LIN_checksum
                     REGEX_WS "header time" REGEX_ws "=" REGEX_ws REGEX_LIN_headerTime ","
                     REGEX_ws "full time" REGEX_ws "=" REGEX_ws REGEX_LIN_fullTime
                     "(" REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate
                     REGEX_WS "break" REGEX_ws "=" REGEX_ws REGEX_LIN_SyncBreak REGEX_WS REGEX_LIN_SyncDel
                     "(" REGEX_WS "subId" REGEX_ws "=" REGEX_ws REGEX_LIN_NAD REGEX_WS REGEX_LIN_MessageId REGEX_WS REGEX_LIN_SupplierId ")?"
                     REGEX_WS "EOH" REGEX_ws "=" REGEX_ws REGEX_LIN_endOfFrame
                     REGEX_WS "EOB" REGEX_ws "=((" REGEX_WS REGEX_LIN_T "){0,8})"
                     REGEX_WS "sim" REGEX_ws "=" REGEX_ws REGEX_LIN_simulated
                     "(" REGEX_WS "EOF" REGEX_ws "=" REGEX_ws REGEX_LIN_endOfFrame
                     "(" REGEX_WS "RBR" REGEX_ws "=" REGEX_ws REGEX_LIN_responseBaudrate
                     "(" REGEX_WS "HBR" REGEX_ws "=" REGEX_ws REGEX_LIN_headerBaudrate
                     REGEX_WS "HSO" REGEX_ws "=" REGEX_ws REGEX_LIN_stopBitOffsetInHeader
                     REGEX_WS "RSO" REGEX_ws "=" REGEX_ws REGEX_LIN_stopBitOffsetInResponse
                     "(" REGEX_WS "CSM" REGEX_ws "=" REGEX_ws REGEX_LIN_checksumModel ")?)?)?)?)?" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linChecksumError = new LinChecksumError;
        linChecksumError->time = std::stod(match[1]);
        linChecksumError->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linChecksumError->id = match[3];
        if (match[4] == "Rx")
            linChecksumError->dir = Dir::Rx;
        else if (match[4] == "Tx")
            linChecksumError->dir = Dir::Tx;
        linChecksumError->dlc = std::stoul(match[5], nullptr, file.base);
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
            linChecksumError->data.push_back(s);
        }
        if (match[8] != "") {
            linChecksumError->slaveId = std::stoul(match[9]);
            linChecksumError->state = std::stoul(match[10]);
        }
        linChecksumError->checksum = std::stoul(match[11], nullptr, file.base);
        linChecksumError->headerTime = std::stoul(match[12]);
        linChecksumError->fullTime = std::stoul(match[13]);
        if (match[14] != "") {
            linChecksumError->startOfFrame = std::stod(match[15]);
            linChecksumError->baudrate = std::stoul(match[16]);
            linChecksumError->syncBreak = std::stoul(match[17]);
            linChecksumError->syncDel = std::stoul(match[18]);
            if (match[19] != "") {
                linChecksumError->nad = std::stoul(match[20]);
                linChecksumError->messageId = std::stoul(match[21]);
                linChecksumError->supplierId = std::stoul(match[22]);
            }
            linChecksumError->endOfHeader = std::stod(match[23]);
            std::istringstream iss2(match[24]);
            while (!iss2.eof()) {
                double s;
                iss2 >> s;
                linChecksumError->endOfByte.push_back(s);
            }
            linChecksumError->simulated = (match[26] == '1');
            if (match[27] != "") {
                linChecksumError->endOfFrame = std::stod(match[28]);
                if (match[29] != "") {
                    linChecksumError->responseBaudrate = std::stoul(match[30]);
                    if (match[31] != "") {
                        linChecksumError->headerBaudrate = std::stod(match[32]);
                        linChecksumError->stopBitOffsetInHeader = std::stoul(match[33]);
                        linChecksumError->stopBitOffsetInResponse = std::stoul(match[34]);
                        if (match[35] != "") {
                            if (match[36] == "unknown")
                                linChecksumError->checksumModel = LinChecksumModel::Unknown;
                            else if (match[36] == "classic")
                                linChecksumError->checksumModel = LinChecksumModel::Classic;
                            else if (match[36] == "enhanced")
                                linChecksumError->checksumModel = LinChecksumModel::Enhanced;
                            else if (match[36] == "error")
                                linChecksumError->checksumModel = LinChecksumModel::Error;
                        }
                    }
                }
            }
        }
        return linChecksumError;
    }

    return nullptr;
}

void LinChecksumError::write(File & file, std::ostream & stream) {
    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s %-12.1x CSErr %s  %d" */
    /* format: "%s %-12.1d CSErr %s  %d" */
    /* format: "%s %s CSErr %s  %d" */
    writeLinChannel(file, stream, channel);
    stream << ' ';
    stream << id; // @todo other formats
    stream << " CSErr ";
    writeLinDir(file, stream, dir);
    stream << "  ";
    stream << std::dec << (uint16_t) dlc;

    writeLinData(file, stream, data);
    if ((slaveId != 0) || (state != 0))
        writeLinSlaveIdLinState(file, stream, slaveId, state);
    writeLinChecksum(file, stream, checksum);
    writeLinHeaderTimeLinFullTime(file, stream, headerTime, fullTime);
    if (file.version >= File::Version::Ver_6_1) {
        writeLinStartOfFrame(file, stream, startOfFrame);
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
