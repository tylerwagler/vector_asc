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
#include "MostEcl.h"

namespace Vector {
namespace ASC {

MostEcl::MostEcl() :
    Event(),
    time(0.0),
    channel(0),
    eclMode(0),
    eclState(0)
{
    eventType = EventType::MostEcl;
}

MostEcl::~MostEcl()
{
}

MostEcl * MostEcl::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " M([[:digit:]]+)"
                " Ecl:"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        MostEcl * mostEcl = new MostEcl;
        mostEcl->time = std::stof(match[1]);
        mostEcl->channel = std::stoul(match[2]);
        mostEcl->eclMode = std::stoul(match[3]);
        mostEcl->eclState = std::stoul(match[4]);
        return mostEcl;
    }

    return nullptr;
}

void MostEcl::write(File & file, std::ostream & stream)
{
}

}
}
