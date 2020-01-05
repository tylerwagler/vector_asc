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

#include <Vector/ASC/DiagRequest.h>
#include <Vector/ASC/TpDiagCommon.h>
#include <Vector/ASC/TpDiagSymbolsRegEx.h>

namespace Vector {
namespace ASC {

DiagRequest * DiagRequest::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_TPDiag_timestamp REGEX_WS "DiagRequest" REGEX_ws
                     "\\[" REGEX_TPDiag_ECUQualifier "\\]" REGEX_ws "(Close|Open|TPon|TPoff|" REGEX_TPDiag_byteSequence ")" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * diagRequest = new DiagRequest;
        diagRequest->time = std::stod(match[1]);
        diagRequest->ecuQualifier = match[2];
        if (match[3] == "Close")
            diagRequest->command = Command::Close;
        else if (match[3] == "Open")
            diagRequest->command = Command::Open;
        else if (match[3] == "TPon")
            diagRequest->command = Command::TpOn;
        else if (match[3] == "TPoff")
            diagRequest->command = Command::TpOff;
        else {
            diagRequest->command = Command::ByteSequence;
            std::istringstream iss(match[3]);
            iss >> std::hex;
            while (!iss.eof()) {
                unsigned short s;
                iss >> s;
                diagRequest->byteSequence.push_back(s);
            }
        }
        return diagRequest;
    }

    return nullptr;
}

void DiagRequest::write(File & file, std::ostream & stream) {
    writeTpDiagTime(file, stream, time);

    /* format: "DiagRequest[%s]" */
    stream << " DiagRequest[" << ecuQualifier << "]";

    switch (command) {
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
        for (TpDiagByteSequence b : byteSequence)
            stream << ' ' << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) b;
    }

    stream << endl;
}

}
}
