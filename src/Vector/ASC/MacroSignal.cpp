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

#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/CanSymbolsRegEx.h>
#include <Vector/ASC/MacroSignal.h>

namespace Vector {
namespace ASC {

MacroSignal * MacroSignal::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "([LF]?)([[:digit:]]+)" REGEX_WS "(.+?)::(.+?)::(.+?)"
                     REGEX_ws "=" REGEX_ws "(.+?)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * macroSignal = new MacroSignal;
        macroSignal->time = std::stod(match[1]);
        if (match[2] == "F")
            macroSignal->bussystem = Vector::ASC::MacroSignal::Bussystem::FlexRay;
        else if (match[2] == "L")
            macroSignal->bussystem = Vector::ASC::MacroSignal::Bussystem::Lin;
        else if (match[2] == "")
            macroSignal->bussystem = Vector::ASC::MacroSignal::Bussystem::Can;
        macroSignal->channel = std::stoul(match[3]);
        macroSignal->node = match[4];
        macroSignal->message = match[5];
        macroSignal->signal = match[6];
        macroSignal->value = match[7];
        return macroSignal;
    }

    return nullptr;
}

void MacroSignal::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << ' ';

    switch (bussystem) {
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
            << " = " << value;

    stream << endl;
}

}
}
