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
#include "TpDiagRequest.h"
#include "TpDiagSymbolsRegEx.h"

namespace Vector {
namespace ASC {

TpDiagRequest::TpDiagRequest() :
    Event(),
    time(0.0),
    ecuQualifier(),
    byteSequence()
{
    eventType = EventType::TpDiagRequest;
}

TpDiagRequest * TpDiagRequest::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_TPDiag_timestamp REGEX_WS "DiagRequest" REGEX_ws
                     "\\[" REGEX_TPDiag_ECUQualifier "\\]" REGEX_TPDiag_byteSequence REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        TpDiagRequest * tpDiagRequest = new TpDiagRequest;
        tpDiagRequest->time = std::stod(match[1]);
        tpDiagRequest->ecuQualifier = match[2];
        std::istringstream iss(match[3]);
        iss >> std::hex;
        for (uint8_t i = 0; !iss.eof(); ++i) {
            unsigned short s;
            iss >> s;
            tpDiagRequest->byteSequence[i] = s;
        }
        return tpDiagRequest;
    }

    return nullptr;
}

void TpDiagRequest::write(File & file, std::ostream & stream)
{
    /* format: "%f DiagRequest[%199s] " */
    stream
            << std::fixed << time
            << " DiagRequest[" << ecuQualifier << "] ";

    for (uint8_t byte : byteSequence)
        stream << byte << ' ';

    stream << endl;
}

}
}
