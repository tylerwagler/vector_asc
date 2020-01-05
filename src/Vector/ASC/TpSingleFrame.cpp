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
#include <sstream>

#include <Vector/ASC/TpDiagCommon.h>
#include <Vector/ASC/TpDiagSymbolsRegEx.h>
#include <Vector/ASC/TpSingleFrame.h>

namespace Vector {
namespace ASC {

TpSingleFrame * TpSingleFrame::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL "//" REGEX_ws REGEX_TPDiag_CANChannel REGEX_WS "OTP\\(" REGEX_TPDiag_connectionId "\\)"
                     REGEX_WS REGEX_TPDiag_type REGEX_WS REGEX_TPDiag_source "->" REGEX_TPDiag_destination ":"
                     REGEX_ws "SF" REGEX_WS "Length:" REGEX_ws REGEX_TPDiag_length
                     REGEX_ws "\\[" REGEX_TPDiag_transportedBytes REGEX_WS "\\]" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * tpSingleFrame = new TpSingleFrame;
        tpSingleFrame->canChannel = std::stoul(match[1]);
        tpSingleFrame->connectionId = std::stoul(match[2], nullptr, 16);
        if (match[3] == "Info")
            tpSingleFrame->type = TpDiagType::Info;
        else if (match[3] == "Warn")
            tpSingleFrame->type = TpDiagType::Warn;
        else if (match[3] == "Error")
            tpSingleFrame->type = TpDiagType::Error;
        else if (match[3] == "Atom")
            tpSingleFrame->type = TpDiagType::Atom;
        else if (match[3] == "Data")
            tpSingleFrame->type = TpDiagType::Data;
        tpSingleFrame->source = match[4];
        tpSingleFrame->destination = match[5];
        tpSingleFrame->length = std::stoul(match[6], nullptr, 16);
        std::istringstream iss(match[7]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            tpSingleFrame->transportedBytes.push_back(s);
        }
        return tpSingleFrame;
    }

    return nullptr;
}

void TpSingleFrame::write(File & /*file*/, std::ostream & stream) {
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

    /* format: "SF Length: "*/
    stream << "SF Length: ";

    stream << std::setfill('0') << std::setw(2) << std::hex << length << " [" << std::hex;
    for (TpDiagTransportedBytes transportedByte : transportedBytes)
        stream << ' ' << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) transportedByte;
    stream << " ]";

    stream << endl;
}

}
}
