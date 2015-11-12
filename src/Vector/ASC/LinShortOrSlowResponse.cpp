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
#include "LinShortOrSlowResponse.h"

namespace Vector {
namespace ASC {

LinShortOrSlowResponse::LinShortOrSlowResponse() :
    Event(),
    time(0.0),
    channel(0),
    id(),
    dlc(0),
    numberOfResponseBytes(0),
    data(),
    isSlowResponse(false),
    responseWasInterruptedByBreak(false),
    startOfFrame(0.0),
    baudrate(0),
    syncBreak(0),
    syncDel(0),
    nad(0),
    messageId(0),
    supplierId(0),
    endOfHeader(0.0),
    endOfByte(),
    headerBaudrate(0.0),
    stopBitOffsetInHeader(0),
    checksumModel()
{
    eventType = EventType::LinShortOrSlowResponse;
}

LinShortOrSlowResponse::~LinShortOrSlowResponse()
{
}

LinShortOrSlowResponse * LinShortOrSlowResponse::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:digit:].]+)"
                " ShortOrSlowResponse:"
                " NumRespBytes = ([[:digit:]]+)(( [[:xdigit:]]+){0,9})?"
                " SlowResponse = ([01])"
                " InterruptedByBreak = ([01])"
                "( SOF = ([[:digit:].]+))?"
                "( BR = ([[:digit:]]+))?"
                "( break = ([[:digit:]]+) ([[:digit:]]+))?"
                "( EOH = ([[:digit:].]+))?"
                "( EOB =(( [[:digit:].]+){0,8}))?"
                "( HBR = ([[:digit:].]+))?"
                "( HSO = ([[:digit:]]+))?"
                "( CSM = (unknown|classic|enhanced|error))?$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinShortOrSlowResponse * linShortOrSlowResponse = new LinShortOrSlowResponse;
        linShortOrSlowResponse->time = std::stod(match[1]);
        linShortOrSlowResponse->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linShortOrSlowResponse->id = match[3];
        linShortOrSlowResponse->dlc = std::stoul(match[4]);
        linShortOrSlowResponse->numberOfResponseBytes = std::stoul(match[5]);
        std::istringstream iss1(match[6]);
        iss1 >> std::hex;
        for (uint8_t i = 0; i < linShortOrSlowResponse->numberOfResponseBytes && i < 9; ++i) {
            unsigned short s;
            iss1 >> s;
            linShortOrSlowResponse->data[i] = s;
        }
        linShortOrSlowResponse->isSlowResponse = (match[8] == '1');
        linShortOrSlowResponse->responseWasInterruptedByBreak = (match[9] == '1');
        linShortOrSlowResponse->startOfFrame = std::stod(match[11]);
        linShortOrSlowResponse->baudrate = std::stoul(match[13]);
        linShortOrSlowResponse->syncBreak = std::stoul(match[15]);
        linShortOrSlowResponse->syncDel = std::stoul(match[16]);
        linShortOrSlowResponse->endOfHeader = std::stod(match[18]);
        std::istringstream iss2(match[20]);
        for (uint8_t i = 0; i < linShortOrSlowResponse->dlc && i < 8; ++i) {
            double s;
            iss2 >> s;
            linShortOrSlowResponse->endOfByte[i] = s;
        }
        linShortOrSlowResponse->headerBaudrate = std::stod(match[23]);
        linShortOrSlowResponse->stopBitOffsetInHeader = std::stoul(match[25]);
        if (match[27] == "unknown")
            linShortOrSlowResponse->checksumModel = LinChecksumModel::Unknown;
        else
        if (match[27] == "classic")
            linShortOrSlowResponse->checksumModel = LinChecksumModel::Classic;
        else
        if (match[27] == "enhanced")
            linShortOrSlowResponse->checksumModel = LinChecksumModel::Enhanced;
        else
        if (match[27] == "error")
            linShortOrSlowResponse->checksumModel = LinChecksumModel::Error;
        return linShortOrSlowResponse;
    }

    return nullptr;
}

void LinShortOrSlowResponse::write(File & file, std::ostream & stream)
{
}

}
}
