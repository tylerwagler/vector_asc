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
#include "MacroSignalEvent.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

MacroSignalEvent::MacroSignalEvent() :
    Event(),
    time(0.0),
    bussystem(Bussystem::Can),
    channel(0),
    node(),
    message(),
    signal(),
    value()
{
    eventType = EventType::MacroSignalEvent;
}

MacroSignalEvent::~MacroSignalEvent()
{
}

MacroSignalEvent * MacroSignalEvent::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "([LF]?)([[:digit:]]+)" REGEX_WS "(.+?)::(.+?)::(.+?)"
                     REGEX_ws "=" REGEX_ws "(.+?)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MacroSignalEvent * macroSignalEvent = new MacroSignalEvent;
        macroSignalEvent->time = std::stod(match[1]);
        if (match[2] == "F")
            macroSignalEvent->bussystem = Vector::ASC::MacroSignalEvent::Bussystem::FlexRay;
        else
        if (match[2] == "L")
            macroSignalEvent->bussystem = Vector::ASC::MacroSignalEvent::Bussystem::Lin;
        else
        if (match[2] == "")
            macroSignalEvent->bussystem = Vector::ASC::MacroSignalEvent::Bussystem::Can;
        macroSignalEvent->channel = std::stoul(match[3]);
        macroSignalEvent->node = match[4];
        macroSignalEvent->message = match[5];
        macroSignalEvent->signal = match[6];
        macroSignalEvent->value = match[7];
        return macroSignalEvent;
    }

    return nullptr;
}

void MacroSignalEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << ' ';
    switch(bussystem) {
    case Bussystem::FlexRay:
        stream << 'F';
        break;
    case Bussystem::Lin:
        stream << 'L';
        break;
    case Bussystem::Can:
    default:
        break;
    }
    stream
            << std::dec << channel
            << ' ' << node
            << "::" << message
            << "::" << signal
            << "=" << value
            << endl;

}

}
}
