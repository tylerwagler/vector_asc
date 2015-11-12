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
#include "LinDominantSignal.h"

namespace Vector {
namespace ASC {

LinDominantSignal::LinDominantSignal() :
    Event(),
    time(0.0),
    channel(0),
    domSigState(),
    domSigLength(0),
    startOfFrame(0.0),
    baudrate(0)
{
    eventType = EventType::LinDominantSignal;
}

LinDominantSignal::~LinDominantSignal()
{
}

LinDominantSignal * LinDominantSignal::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " Dominant signal (detected|continuing|finished)"
                " ([[:digit:]]+) microseconds"
                "( SOF = ([[:digit:].]+))?"
                "( BR = ([[:digit:]]+))?$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinDominantSignal * linDominantSignal = new LinDominantSignal;
        linDominantSignal->time = std::stod(match[1]);
        linDominantSignal->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        if (match[3] == "detected")
            linDominantSignal->domSigState = LinDomSigState::Detected;
        if (match[3] == "continuing")
            linDominantSignal->domSigState = LinDomSigState::Continuing;
        if (match[3] == "finished")
            linDominantSignal->domSigState = LinDomSigState::Finished;
        linDominantSignal->domSigLength = std::stoul(match[4]);
        linDominantSignal->startOfFrame = std::stod(match[6]);
        linDominantSignal->baudrate = std::stoul(match[8]);
        return linDominantSignal;
    }

    return nullptr;
}

void LinDominantSignal::write(File & file, std::ostream & stream)
{
}

}
}
