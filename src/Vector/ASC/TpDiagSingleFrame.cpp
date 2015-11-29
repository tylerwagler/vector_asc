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

#include <iomanip>
#include <regex>
#include "TpDiagCommon.h"
#include "TpDiagSingleFrame.h"
#include "TpDiagSymbolsRegEx.h"

namespace Vector {
namespace ASC {

TpDiagSingleFrame::TpDiagSingleFrame() :
    Event(),
    length(0),
    transportedBytes()
{
    eventType = EventType::TpDiagSingleFrame;
}

TpDiagSingleFrame::~TpDiagSingleFrame()
{
}

TpDiagSingleFrame * TpDiagSingleFrame::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL "SF" REGEX_WS "Length:" REGEX_ws REGEX_TPDiag_length
                     REGEX_ws "\\[" REGEX_TPDiag_transportedBytes REGEX_WS "\\]" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        TpDiagSingleFrame * tpDiagSingleFrame = new TpDiagSingleFrame;
        tpDiagSingleFrame->length = std::stoul(match[1], nullptr, 16);
        std::istringstream iss(match[2]);
        iss >> std::hex;
        for (uint8_t i = 0; i < tpDiagSingleFrame->length; ++i) {
            unsigned short s;
            iss >> s;
            tpDiagSingleFrame->transportedBytes[i] = s;
        }
        return tpDiagSingleFrame;
    }

    return nullptr;
}

void TpDiagSingleFrame::write(File & file, std::ostream & stream)
{
    /* format: "SF Length: "*/
    stream << "SF Length: ";

    stream << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) length << " [" << std::hex;
    for (uint8_t transportedByte : transportedBytes)
        stream << ' ' << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) transportedByte;
    stream << " ]";

    stream << endl;
}

}
}
