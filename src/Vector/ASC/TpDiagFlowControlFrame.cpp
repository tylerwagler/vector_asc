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
#include "TpDiagCommon.h"
#include "TpDiagFlowControlFrame.h"
#include "TpDiagSymbolsRegEx.h"

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
    std::regex regex(REGEX_STOL "FC." REGEX_TPDiag_FCType ":" REGEX_ws "BSmax:" REGEX_ws "0x" REGEX_TPDiag_BS ","
                     REGEX_ws "STmin:" REGEX_ws "0x" REGEX_TPDiag_STmin REGEX_ws "ms" REGEX_ENDL);
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
    switch(fcType) {
    case TpDiagFcType::Cts:
        /* format: "FC.CTS:  " */
        stream << "FC.CTS:  ";
        break;
    case TpDiagFcType::Wt:
        /* format: "FC.WT:   " */
        stream << "FC.WT:   ";
        break;
    case TpDiagFcType::Ovflw:
        /* format: "FC.OVFLW:" */
        stream << "FC.OVFLW:";
        break;
    case TpDiagFcType::IllegalFlowStatus:
        /* format: "FC.Illegal Flow Status= 0x" */
        stream << "FC.Illegal Flow Status= 0x";
        break;
    }

    stream << ' ';

    /* format: "Bsmax: " */
    stream << "Bsmax: ";

    stream << "0x" << std::hex << bs;

    /* format: ", Stmin: "*/
    stream << ", STmin: ";

    stream << "0x" << stMin << " ms";

    stream << endl;
}

}
}
