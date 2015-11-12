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
#include "EthernetRxError.h"

namespace Vector {
namespace ASC {

EthernetRxError::EthernetRxError() :
    Event(),
    time(0.0),
    channel(0),
    errorCode(0),
    frameChecksum(0),
    dataLen(0),
    data()
{
    eventType = EventType::EthernetRxError;
}

EthernetRxError::~EthernetRxError()
{
}

EthernetRxError * EthernetRxError::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " ETH"
                " ([[:xdigit:]]{1,3})"
                " RxEr"
                " ([[:xdigit:]]{1,2})"
                " ([[:xdigit:]]{8})"
                " ([[:xdigit:]]{1,4}):([[:xdigit:]]*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        EthernetRxError * ethernetRxError = new EthernetRxError;
        ethernetRxError->time = std::stod(match[1]);
        ethernetRxError->channel = std::stoul(match[2], nullptr, file.base);
        ethernetRxError->errorCode = std::stoul(match[3], nullptr, file.base);
        ethernetRxError->frameChecksum = std::stoul(match[4], nullptr, 16);
        ethernetRxError->dataLen = std::stoul(match[5], nullptr, file.base);
        for (int i = 0; i < ethernetRxError->dataLen; ++i) {
            std::string s;
            s.append(match[6], 2*i, 2);
            ethernetRxError->data[i] = std::stoul(s, nullptr, 16);
        }
        return ethernetRxError;
    }

    return nullptr;
}

void EthernetRxError::write(File & file, std::ostream & stream)
{
}

}
}
