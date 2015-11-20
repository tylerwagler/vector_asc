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
#include "CanErrorFrame.h"
#include "SymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanErrorFrame::CanErrorFrame() :
    Event(),
    time(0.0),
    channel(0),
    flags(0),
    codeExt(0),
    code(0),
    id(0),
    dlc(0),
    position(0),
    length(0)
{
    eventType = EventType::CanErrorFrame;
}

CanErrorFrame::~CanErrorFrame()
{
}

CanErrorFrame * CanErrorFrame::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS REGEX_Channel REGEX_WS "ErrorFrame"
                     "(" REGEX_WS "ECC:" REGEX_ws "([01]+))?"
                     "(" REGEX_WS "Flags" REGEX_ws "=" REGEX_ws "0x([[:xdigit:]]+))?"
                     "(" REGEX_WS "CodeExt" REGEX_ws "=" REGEX_ws "0x([[:xdigit:]]+))?"
                     "(" REGEX_WS "Code" REGEX_ws "=" REGEX_ws "0x([[:xdigit:]]+))?"
                     "(" REGEX_WS "ID" REGEX_ws "=" REGEX_ws "([[:digit:]]+))?"
                     "(" REGEX_WS "DLC" REGEX_ws "=" REGEX_ws "([[:xdigit:]]{1,2}))?"
                     "(" REGEX_WS "Position" REGEX_ws "=" REGEX_ws "([[:digit:]]+))?"
                     "(" REGEX_WS "Length" REGEX_ws "=" REGEX_ws "([[:digit:]]+))?"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanErrorFrame * canErrorFrame = new CanErrorFrame;
        canErrorFrame->time = std::stod(match[1]);
        canErrorFrame->channel = std::stoul(match[2]);
        if (match[3] != "")
            canErrorFrame->code = std::stoul(match[4], nullptr, 2);
        if (match[5] != "")
            canErrorFrame->flags = std::stoul(match[6], nullptr, 16);
        if (match[7] != "")
            canErrorFrame->codeExt = std::stoul(match[8], nullptr, 16);
        if (match[9] != "")
            canErrorFrame->code = std::stoul(match[10], nullptr, 16);
        if (match[11] != "")
            canErrorFrame->id = std::stoul(match[12]);
        if (match[13] != "")
            canErrorFrame->dlc = std::stoul(match[14], nullptr, file.base);
        if (match[15] != "")
            canErrorFrame->position = std::stoul(match[16]);
        if (match[17] != "")
            canErrorFrame->length = std::stoul(match[18]);
        return canErrorFrame;
    }

    return nullptr;
}

void CanErrorFrame::write(File & file, std::ostream & stream)
{
#if 0
    stream << getTimeStamp(eventTime);
    stream << ' ' << channel;
    stream << " ErrorFrame";

    if (version >= Version::Ver_7_5) {
        if (sja1000) {
            stream << " ECC:";
            stream << ((ecc >> 7) & 1);
            stream << ((ecc >> 6) & 1);
            stream << ((ecc >> 5) & 1);
            stream << ((ecc >> 4) & 1);
            stream << ((ecc >> 3) & 1);
            stream << ((ecc >> 2) & 1);
            stream << ((ecc >> 1) & 1);
            stream << ((ecc >> 0) & 1);
        }
        if (canCore) {
            stream << " Flags = 0x" << std::hex << flags;
            stream << " CodeExt = 0x" << std::hex << codeExt;
            stream << " Code = 0x" << std::hex << code;
            stream << " ID = " << std::hex << id;
            if (extended) {
                stream << "x";
            }
            stream << " DLC = " << std::hex << dlc << std::dec;
            stream << " Position = " << position;
            stream << " Length = " << length;
        }
    }

    *this << endl;
#endif
}

}
}
