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
#include <Vector/ASC/CanErrorFrame.h>
#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

CanErrorFrame * CanErrorFrame::read(File & file, std::string & line) {
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
        auto * canErrorFrame = new CanErrorFrame;
        canErrorFrame->time = std::stod(match[1]);
        canErrorFrame->channel = std::stoul(match[2]);
        if (match[3] != "") {
            canErrorFrame->code = std::stoul(match[4], nullptr, 2);
            canErrorFrame->flags |= (1 << 0); // SJA 1000 ECC is valid
        }
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

void CanErrorFrame::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << ' ' << std::dec << (uint16_t) channel << "  ";

    /* format: "ErrorFrame" */
    stream << "ErrorFrame";

    /* SJA 1000 */
    if (flags & 0x1) {
        stream << '\t';
        /* format: "ECC: " */
        stream << "ECC: ";
        stream << (uint16_t) ((code >> 7) & 1);
        stream << (uint16_t) ((code >> 6) & 1);
        stream << (uint16_t) ((code >> 5) & 1);
        stream << (uint16_t) ((code >> 4) & 1);
        stream << (uint16_t) ((code >> 3) & 1);
        stream << (uint16_t) ((code >> 2) & 1);
        stream << (uint16_t) ((code >> 1) & 1);
        stream << (uint16_t) ((code >> 0) & 1);
    }

    /* CAN Core */
    if (flags & 0xe) {
        /* format: "Flags = " */
        stream << " Flags = ";
        stream << "0x" << std::hex << (uint16_t) flags;

        /* format: "CodeExt = " */
        stream << " CodeExt = ";
        stream << "0x" << std::hex << codeExt;

        /* format: "Code = " */
        stream << " Code = ";
        stream << "0x" << std::hex << (uint16_t) code;

        /* format: "ID = " */
        stream << " ID = ";
        stream << std::hex << id;
        if (extendedId)
            stream << 'x';

        /* format: "DLC = " */
        stream << " DLC = ";
        stream << std::hex << (uint16_t) dlc;

        /* format: "Position = " */
        stream << " Position = ";
        stream << std::dec << position;

        /* format: "Length = " */
        stream << " Length = ";
        stream << std::dec << length;
    }

    stream << endl;
}

}
}
