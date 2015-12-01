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
#include "FlexRayCommon.h"
#include "FlexRayMessage.h"
#include "FlexRaySymbolsRegEx.h"

namespace Vector {
namespace ASC {

FlexRayMessage::FlexRayMessage() :
    Event(),
    time(0.0),
    flexRayEventType(FlexRayEventType::RMSG),
    clusterNr(0),
    clientId(0),
    channelNr(0),
    channelMask(0),
    slotId(0),
    cycleNo(0),
    direction(),
    appParam(0),
    flags(0),
    ccType(0),
    ccData(0),
    headerCrc(0),
    name(),
    payloadLength(0),
    bufferLength(0),
    data(),
    frameCrc(0),
    spyFlag(0),
    frameLengthNs(0),
    pduOffset(0)
{
    eventType = EventType::FlexRayMessage;
}

FlexRayMessage::~FlexRayMessage()
{
}

FlexRayMessage * FlexRayMessage::parseRmsg(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "RMSG"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_FlexRay_Dir REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:alnum:]_\\[\\|\\]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     "((" REGEX_WS "[[:xdigit:]]+){0,254})" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([01])" REGEX_WS "([[:digit:]]+)"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayMessage * flexRayMessage = new FlexRayMessage;
        flexRayMessage->time = std::stod(match[1]);
        flexRayMessage->flexRayEventType = FlexRayEventType::RMSG;
        flexRayMessage->clusterNr = std::stoul(match[2]);
        flexRayMessage->clientId = std::stoul(match[3]);
        flexRayMessage->channelNr = std::stoul(match[4]);
        flexRayMessage->channelMask = std::stoul(match[5]);
        flexRayMessage->slotId = std::stoul(match[6]);
        flexRayMessage->cycleNo = std::stoul(match[7]);
        flexRayMessage->direction = match[8];
        flexRayMessage->appParam = std::stoul(match[9]);
        flexRayMessage->flags = std::stoul(match[10]);
        flexRayMessage->ccType = std::stoul(match[11]);
        flexRayMessage->ccData = std::stoul(match[12]);
        flexRayMessage->headerCrc = std::stoul(match[13]);
        flexRayMessage->name = match[14];
        flexRayMessage->payloadLength = std::stoul(match[15]);
        flexRayMessage->bufferLength = std::stoul(match[16]);
        std::istringstream iss(match[17]);
        for (uint8_t i = 0; i < flexRayMessage->bufferLength; ++i) {
            unsigned short s;
            iss >> s;
            flexRayMessage->data[i] = s;
        }
        flexRayMessage->frameCrc = std::stoul(match[19]);
        flexRayMessage->spyFlag = (match[20] == '1');
        flexRayMessage->frameLengthNs = std::stoul(match[21]);
        return flexRayMessage;
    }

    return nullptr;
}

FlexRayMessage * FlexRayMessage::parsePdu(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "PDU"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_FlexRay_Dir REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:alnum:]_\\[\\|\\]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     "((" REGEX_WS "[[:xdigit:]]+){0,254})" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([01])" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayMessage * flexRayMessage = new FlexRayMessage;
        flexRayMessage->time = std::stod(match[1]);
        flexRayMessage->flexRayEventType = FlexRayEventType::PDU;
        flexRayMessage->clusterNr = std::stoul(match[2]);
        flexRayMessage->clientId = std::stoul(match[3]);
        flexRayMessage->channelNr = std::stoul(match[4]);
        flexRayMessage->channelMask = std::stoul(match[5]);
        flexRayMessage->slotId = std::stoul(match[6]);
        flexRayMessage->cycleNo = std::stoul(match[7]);
        flexRayMessage->direction = match[8];
        flexRayMessage->appParam = std::stoul(match[9]);
        flexRayMessage->flags = std::stoul(match[10]);
        flexRayMessage->ccType = std::stoul(match[11]);
        flexRayMessage->ccData = std::stoul(match[12]);
        flexRayMessage->headerCrc = std::stoul(match[13]);
        flexRayMessage->name = match[14];
        flexRayMessage->payloadLength = std::stoul(match[15]);
        flexRayMessage->bufferLength = std::stoul(match[16]);
        std::istringstream iss(match[17]);
        for (uint8_t i = 0; i < flexRayMessage->bufferLength; ++i) {
            unsigned short s;
            iss >> s;
            flexRayMessage->data[i] = s;
        }
        flexRayMessage->frameCrc = std::stoul(match[19]);
        flexRayMessage->spyFlag = (match[20] == '1');
        flexRayMessage->frameLengthNs = std::stoul(match[21]);
        flexRayMessage->pduOffset = std::stoul(match[22]);
        return flexRayMessage;
    }

    return nullptr;
}

FlexRayMessage * FlexRayMessage::parse(File & file, std::string & line)
{
    FlexRayMessage * flexRayMessage;

    flexRayMessage = parseRmsg(file, line);
    if (flexRayMessage != nullptr)
        return flexRayMessage;

    flexRayMessage = parsePdu(file, line);
    if (flexRayMessage != nullptr)
        return flexRayMessage;

    return nullptr;
}

void FlexRayMessage::write(File & file, std::ostream & stream)
{
    stream << endl;
}

}
}
