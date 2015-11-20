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

#include <regex>
#include "LinTransmissionError.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

LinTransmissionError::LinTransmissionError() :
    Event(),
    time(0.0),
    channel(0),
    id(),
    slaveId(0),
    state(0),
    headerTime(0),
    fullTime(0),
    startOfFrame(0.0),
    baudrate(0),
    syncBreak(0),
    syncDel(0),
    nad(0),
    messageId(0),
    supplierId(0),
    endOfHeader(0.0),
    headerBaudrate(0.0),
    stopBitOffsetInHeader(0),
    checksumModel()
{
    eventType = EventType::LinTransmissionError;
}

LinTransmissionError::~LinTransmissionError()
{
}

LinTransmissionError * LinTransmissionError::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS REGEX_LIN_ID REGEX_WS "TransmErr"
                     "(" REGEX_WS "slave" REGEX_ws "=" REGEX_ws REGEX_LIN_slaveId ","
                     REGEX_ws "state" REGEX_ws "=" REGEX_ws REGEX_LIN_state ")?"
                     REGEX_WS "header time" REGEX_ws "=" REGEX_ws REGEX_LIN_headerTime ","
                     REGEX_ws "full time" REGEX_ws "=" REGEX_ws REGEX_LIN_fullTime
                     "(" REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate
                     REGEX_WS "break" REGEX_ws "=" REGEX_ws REGEX_LIN_SyncBreak REGEX_WS REGEX_LIN_SyncDel
                     "(subId" REGEX_ws "=" REGEX_ws REGEX_LIN_NAD REGEX_WS REGEX_LIN_MessageId REGEX_WS REGEX_LIN_SupplierId ")?"
                     REGEX_WS "EOH" REGEX_ws "=" REGEX_ws REGEX_LIN_endOfHeader
                     "(" REGEX_WS "HBR" REGEX_ws "=" REGEX_ws REGEX_LIN_headerBaudrate
                     REGEX_WS "HSO" REGEX_ws "=" REGEX_ws REGEX_LIN_stopBitOffsetInHeader
                     "(" REGEX_WS "CSM" REGEX_ws "=" REGEX_ws REGEX_LIN_checksumModel ")?)?)?" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinTransmissionError * linTransmissionError = new LinTransmissionError;
        linTransmissionError->time = std::stod(match[1]);
        linTransmissionError->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linTransmissionError->id = match[3];
        if (match[4] != "") {
            linTransmissionError->slaveId = std::stoul(match[5]);
            linTransmissionError->state = std::stoul(match[6]);
        }
        linTransmissionError->headerTime = std::stoul(match[7]);
        linTransmissionError->fullTime = std::stoul(match[8]);
        if (match[9] != "") {
            linTransmissionError->startOfFrame = std::stod(match[10]);
            linTransmissionError->baudrate = std::stoul(match[11]);
            linTransmissionError->syncBreak = std::stoul(match[12]);
            linTransmissionError->syncDel = std::stoul(match[13]);
            if (match[14] != "") {
                linTransmissionError->nad = std::stoul(match[15]);
                linTransmissionError->messageId = std::stoul(match[16]);
                linTransmissionError->supplierId = std::stoul(match[17]);
            }
            linTransmissionError->endOfHeader = std::stod(match[18]);
            if (match[19] != "")
                linTransmissionError->headerBaudrate = std::stod(match[20]);
            linTransmissionError->stopBitOffsetInHeader = std::stoul(match[21]);
            if (match[22] != "") {
                if (match[23] == "unknown")
                    linTransmissionError->checksumModel = LinChecksumModel::Unknown;
                else
                if (match[23] == "classic")
                    linTransmissionError->checksumModel = LinChecksumModel::Classic;
                else
                if (match[23] == "enhanced")
                    linTransmissionError->checksumModel = LinChecksumModel::Enhanced;
                else
                if (match[23] == "error")
                    linTransmissionError->checksumModel = LinChecksumModel::Error;
            }
        }
        return linTransmissionError;
    }

    return nullptr;
}

void LinTransmissionError::write(File & file, std::ostream & stream)
{
}

}
}
