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
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " ([[:xdigit:]]+)"
                " TransmErr"
                " header time = ([[:digit:]]+), full time = ([[:digit:]]+)"
                "( SOF = ([[:digit:].]+))?"
                "( BR = ([[:digit:]]+))?"
                "( break = ([[:digit:]]+) ([[:digit:]]+))?"
                "( EOH = ([[:digit:].]+))?"
                "( HBR = ([[:digit:].]+))?"
                "( HSO = ([[:digit:]]+))?"
                "( CSM = (unknown|classic|enhanced|error))?$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinTransmissionError * linTransmissionError = new LinTransmissionError;
        linTransmissionError->time = std::stod(match[1]);
        linTransmissionError->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linTransmissionError->id = match[3];
        linTransmissionError->headerTime = std::stoul(match[4]);
        linTransmissionError->fullTime = std::stoul(match[5]);
        linTransmissionError->startOfFrame = std::stod(match[7]);
        linTransmissionError->baudrate = std::stoul(match[9]);
        linTransmissionError->syncBreak = std::stoul(match[11]);
        linTransmissionError->syncDel = std::stoul(match[12]);
        linTransmissionError->endOfHeader = std::stod(match[14]);
        linTransmissionError->headerBaudrate = std::stod(match[16]);
        linTransmissionError->stopBitOffsetInHeader = std::stoul(match[18]);
        if (match[20] == "unknown")
            linTransmissionError->checksumModel = LinChecksumModel::Unknown;
        else
        if (match[20] == "classic")
            linTransmissionError->checksumModel = LinChecksumModel::Classic;
        else
        if (match[20] == "enhanced")
            linTransmissionError->checksumModel = LinChecksumModel::Enhanced;
        else
        if (match[20] == "error")
            linTransmissionError->checksumModel = LinChecksumModel::Error;
        return linTransmissionError;
    }

    return nullptr;
}

void LinTransmissionError::write(File & file, std::ostream & stream)
{
}

}
}
