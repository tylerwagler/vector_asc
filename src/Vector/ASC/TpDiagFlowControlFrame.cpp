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
#include "TpDiagFlowControlFrame.h"

namespace Vector {
namespace ASC {

TpDiagFlowControlFrame::TpDiagFlowControlFrame() :
    Event(),
    fcType(TpDiagFcType::Cts),
    bs(0),
    stMin(0)
{
    eventType = EventType::TpDiagFlowControlFrame;
}

TpDiagFlowControlFrame::~TpDiagFlowControlFrame()
{
}

TpDiagFlowControlFrame * TpDiagFlowControlFrame::parse(File & file, std::string & line)
{
    std::regex regex(
                "^FC\\.(CTS|WT|OVFLW):"
                " BSmax: 0x([[:xdigit:]]+),"
                " STmin: 0x([[:xdigit:]]+) ms$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        TpDiagFlowControlFrame * tpDiagFlowControlFrame = new TpDiagFlowControlFrame;
        if (match[1] == "CTS")
            tpDiagFlowControlFrame->fcType = TpDiagFcType::Cts;
        else
        if (match[1] == "WT")
            tpDiagFlowControlFrame->fcType = TpDiagFcType::Wt;
        else
        if (match[1] == "OVFLW")
            tpDiagFlowControlFrame->fcType = TpDiagFcType::Ovflw;
        tpDiagFlowControlFrame->bs = std::stoul(match[2], nullptr, 16);
        tpDiagFlowControlFrame->stMin = std::stoul(match[3], nullptr, 16);
        return tpDiagFlowControlFrame;
    }

    return nullptr;
}

void TpDiagFlowControlFrame::write(File & file, std::ostream & stream)
{
    stream << "FC.";
    switch(fcType) {
    case TpDiagFcType::Cts:
        stream << "CTS";
        break;
    case TpDiagFcType::Wt:
        stream << "WT";
        break;
    case TpDiagFcType::Ovflw:
        stream << "OVFLW";
        break;
    }
    stream << ":  BSmax: 0x" << std::hex << bs;
    stream << ", STmin: 0x" << stMin << " ms" << endl;
}

}
}
