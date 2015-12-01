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
#include "TpDiagRequest.h"
#include "TpDiagSymbolsRegEx.h"

namespace Vector {
namespace ASC {

TpDiagRequest::TpDiagRequest() :
    Event(),
    time(0.0),
    ecuQualifier(),
    command(Command::ByteSequence),
    byteSequence()
{
    eventType = EventType::TpDiagRequest;
}

TpDiagRequest * TpDiagRequest::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_TPDiag_timestamp REGEX_WS "DiagRequest" REGEX_ws
                     "\\[" REGEX_TPDiag_ECUQualifier "\\]" REGEX_ws "(Close|Open|TPon|TPoff|" REGEX_TPDiag_byteSequence ")" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        TpDiagRequest * tpDiagRequest = new TpDiagRequest;
        tpDiagRequest->time = std::stod(match[1]);
        tpDiagRequest->ecuQualifier = match[2];
        if (match[3] == "Close")
            tpDiagRequest->command = Command::Close;
        else
        if (match[3] == "Open")
            tpDiagRequest->command = Command::Open;
        else
        if (match[3] == "TPon")
            tpDiagRequest->command = Command::TpOn;
        else
        if (match[3] == "TPoff")
            tpDiagRequest->command = Command::TpOff;
        else
        {
            tpDiagRequest->command = Command::ByteSequence;
            std::istringstream iss(match[3]);
            iss >> std::hex;
            for (int i = 0; !iss.eof(); ++i) {
                unsigned short s;
                iss >> s;
                tpDiagRequest->byteSequence.push_back(s);
            }
        }
        return tpDiagRequest;
    }

    return nullptr;
}

void TpDiagRequest::write(File & file, std::ostream & stream)
{
    /* format: "%f DiagRequest[%199s] " */
    stream
            << std::right << std::setfill(' ') << std::setw(9) << std::setprecision(4) << std::fixed << time
            << " DiagRequest[" << ecuQualifier << "] ";

    switch(command) {
    case Command::Close:
        /** format: " Close" */
        stream << " Close";
        break;
    case Command::Open:
        /** format: " Open" */
        stream << " Open";
        break;
    case Command::TpOn:
            /** format: " TPon" */
        stream << " TPon";
        break;
    case Command::TpOff:
        /** format: " TPoff" */
        stream << " TPoff";
        break;
    case Command::ByteSequence:
        /* format: " %02X" */
        for (uint8_t b: byteSequence)
            stream << ' ' << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) b;
    }

    stream << endl;
}

}
}
