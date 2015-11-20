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
#include "FlexRayMessageEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

FlexRayMessageEvent::FlexRayMessageEvent() :
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
    eventType = EventType::FlexRayMessageEvent;
}

FlexRayMessageEvent::~FlexRayMessageEvent()
{
}

FlexRayMessageEvent * FlexRayMessageEvent::parseRmsg(File & file, std::string & line)
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
        FlexRayMessageEvent * flexRayMessageEvent = new FlexRayMessageEvent;
        flexRayMessageEvent->time = std::stod(match[1]);
        flexRayMessageEvent->flexRayEventType = FlexRayEventType::RMSG;
        flexRayMessageEvent->clusterNr = std::stoul(match[2]);
        flexRayMessageEvent->clientId = std::stoul(match[3]);
        flexRayMessageEvent->channelNr = std::stoul(match[4]);
        flexRayMessageEvent->channelMask = std::stoul(match[5]);
        flexRayMessageEvent->slotId = std::stoul(match[6]);
        flexRayMessageEvent->cycleNo = std::stoul(match[7]);
        flexRayMessageEvent->direction = match[8];
        flexRayMessageEvent->appParam = std::stoul(match[9]);
        flexRayMessageEvent->flags = std::stoul(match[10]);
        flexRayMessageEvent->ccType = std::stoul(match[11]);
        flexRayMessageEvent->ccData = std::stoul(match[12]);
        flexRayMessageEvent->headerCrc = std::stoul(match[13]);
        flexRayMessageEvent->name = match[14];
        flexRayMessageEvent->payloadLength = std::stoul(match[15]);
        flexRayMessageEvent->bufferLength = std::stoul(match[16]);
        std::istringstream iss(match[17]);
        for (uint8_t i = 0; i < flexRayMessageEvent->bufferLength; ++i) {
            unsigned short s;
            iss >> s;
            flexRayMessageEvent->data[i] = s;
        }
        flexRayMessageEvent->frameCrc = std::stoul(match[19]);
        flexRayMessageEvent->spyFlag = (match[20] == '1');
        flexRayMessageEvent->frameLengthNs = std::stoul(match[21]);
        return flexRayMessageEvent;
    }

    return nullptr;
}

FlexRayMessageEvent * FlexRayMessageEvent::parsePdu(File & file, std::string & line)
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
        FlexRayMessageEvent * flexRayMessageEvent = new FlexRayMessageEvent;
        flexRayMessageEvent->time = std::stod(match[1]);
        flexRayMessageEvent->flexRayEventType = FlexRayEventType::PDU;
        flexRayMessageEvent->clusterNr = std::stoul(match[2]);
        flexRayMessageEvent->clientId = std::stoul(match[3]);
        flexRayMessageEvent->channelNr = std::stoul(match[4]);
        flexRayMessageEvent->channelMask = std::stoul(match[5]);
        flexRayMessageEvent->slotId = std::stoul(match[6]);
        flexRayMessageEvent->cycleNo = std::stoul(match[7]);
        flexRayMessageEvent->direction = match[8];
        flexRayMessageEvent->appParam = std::stoul(match[9]);
        flexRayMessageEvent->flags = std::stoul(match[10]);
        flexRayMessageEvent->ccType = std::stoul(match[11]);
        flexRayMessageEvent->ccData = std::stoul(match[12]);
        flexRayMessageEvent->headerCrc = std::stoul(match[13]);
        flexRayMessageEvent->name = match[14];
        flexRayMessageEvent->payloadLength = std::stoul(match[15]);
        flexRayMessageEvent->bufferLength = std::stoul(match[16]);
        std::istringstream iss(match[17]);
        for (uint8_t i = 0; i < flexRayMessageEvent->bufferLength; ++i) {
            unsigned short s;
            iss >> s;
            flexRayMessageEvent->data[i] = s;
        }
        flexRayMessageEvent->frameCrc = std::stoul(match[19]);
        flexRayMessageEvent->spyFlag = (match[20] == '1');
        flexRayMessageEvent->frameLengthNs = std::stoul(match[21]);
        flexRayMessageEvent->pduOffset = std::stoul(match[22]);
        return flexRayMessageEvent;
    }

    return nullptr;
}

FlexRayMessageEvent * FlexRayMessageEvent::parse(File & file, std::string & line)
{
    FlexRayMessageEvent * flexRayMessageEvent;

    flexRayMessageEvent = parseRmsg(file, line);
    if (flexRayMessageEvent != nullptr)
        return flexRayMessageEvent;

    flexRayMessageEvent = parsePdu(file, line);
    if (flexRayMessageEvent != nullptr)
        return flexRayMessageEvent;

    return nullptr;
}

void FlexRayMessageEvent::write(File & file, std::ostream & stream)
{
}

}
}
