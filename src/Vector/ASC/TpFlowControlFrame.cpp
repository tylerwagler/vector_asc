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

#include <Vector/ASC/TpDiagCommon.h>
#include <Vector/ASC/TpDiagSymbolsRegEx.h>
#include <Vector/ASC/TpFlowControlFrame.h>

namespace Vector {
namespace ASC {

TpFlowControlFrame * TpFlowControlFrame::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL "//" REGEX_ws REGEX_TPDiag_CANChannel REGEX_WS "OTP\\(" REGEX_TPDiag_connectionId "\\)"
                     REGEX_WS REGEX_TPDiag_type REGEX_WS REGEX_TPDiag_source "->" REGEX_TPDiag_destination ":"
                     REGEX_ws "FC." REGEX_TPDiag_FCType ":" REGEX_ws "BSmax:" REGEX_ws "0x" REGEX_TPDiag_BS ","
                     REGEX_ws "STmin:" REGEX_ws "0x" REGEX_TPDiag_STmin REGEX_ws "ms" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * tpFlowControlFrame = new TpFlowControlFrame;
        tpFlowControlFrame->canChannel = std::stoul(match[1]);
        tpFlowControlFrame->connectionId = std::stoul(match[2], nullptr, 16);
        if (match[3] == "Info")
            tpFlowControlFrame->type = TpDiagType::Info;
        else if (match[3] == "Warn")
            tpFlowControlFrame->type = TpDiagType::Warn;
        else if (match[3] == "Error")
            tpFlowControlFrame->type = TpDiagType::Error;
        else if (match[3] == "Atom")
            tpFlowControlFrame->type = TpDiagType::Atom;
        else if (match[3] == "Data")
            tpFlowControlFrame->type = TpDiagType::Data;
        tpFlowControlFrame->source = match[4];
        tpFlowControlFrame->destination = match[5];
        if (match[6] == "CTS")
            tpFlowControlFrame->fcType = TpDiagFcType::Cts;
        else if (match[6] == "WT")
            tpFlowControlFrame->fcType = TpDiagFcType::Wt;
        else if (match[6] == "OVFLW")
            tpFlowControlFrame->fcType = TpDiagFcType::Ovflw;
        tpFlowControlFrame->bs = std::stoul(match[7], nullptr, 16);
        tpFlowControlFrame->stMin = std::stoul(match[8], nullptr, 16);
        return tpFlowControlFrame;
    }

    return nullptr;
}

void TpFlowControlFrame::write(File & /*file*/, std::ostream & stream) {
    stream << "// " << std::dec << (uint16_t) canChannel;

    /* format: "  OTP(" */
    stream << "  OTP(";

    stream << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) connectionId << ") ";
    switch (type) {
    case TpDiagType::Info:
        stream << "Info";
        break;
    case TpDiagType::Warn:
        stream << "Warn";
        break;
    case TpDiagType::Error:
        stream << "Error";
        break;
    case TpDiagType::Atom:
        stream << "Atom";
        break;
    case TpDiagType::Data:
        stream << "Data";
        break;
    }
    stream << " " << source << "->" << destination << ": ";

    switch (fcType) {
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

    /* format: "BSmax: " */
    stream << "BSmax: ";

    stream << "0x" << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) bs;

    /* format: ", Stmin: "*/
    stream << ", STmin: ";

    stream << "0x" << std::setfill('0') << std::setw(2) << std::hex << (uint16_t) stMin << " ms";

    stream << endl;
}

}
}
