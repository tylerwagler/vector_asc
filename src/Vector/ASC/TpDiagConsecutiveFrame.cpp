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
#include "TpDiagConsecutiveFrame.h"

namespace Vector {
namespace ASC {

TpDiagConsecutiveFrame::TpDiagConsecutiveFrame() :
    Event(),
    sn(0),
    transportedBytes()
{
    eventType = EventType::TpDiagConsecutiveFrame;
}

TpDiagConsecutiveFrame::~TpDiagConsecutiveFrame()
{
}

TpDiagConsecutiveFrame * TpDiagConsecutiveFrame::parse(File & file, std::string & line)
{
    std::regex regex(
                "^CF"
                " Seq\\.Nr\\.: ([[:digit:]]+)"
                " \\[(( [[:xdigit:]]+)*) \\]$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        TpDiagConsecutiveFrame * tpDiagConsecutiveFrame = new TpDiagConsecutiveFrame;
        tpDiagConsecutiveFrame->sn = std::stoul(match[1]);
        std::istringstream iss(match[2]);
        iss >> std::hex;
        for (uint8_t i = 0; !iss.eof(); ++i) {
            unsigned short s;
            iss >> s;
            tpDiagConsecutiveFrame->transportedBytes[i] = s;
        }
        return tpDiagConsecutiveFrame;
    }

    return nullptr;
}

void TpDiagConsecutiveFrame::write(File & file, std::ostream & stream)
{
    stream
            << "CF Seq.Nr.: " << std::dec << sn
            << " [" << std::hex;
    for (uint8_t transportedByte : transportedBytes)
        stream << ' ' << transportedByte;
    stream
            << " ]" << endl;
}

}
}
