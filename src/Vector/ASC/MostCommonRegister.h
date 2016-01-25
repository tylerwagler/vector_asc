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

#pragma once

#include <vector>
#include "Event.h"
#include "MostSymbols.h"

namespace Vector {
namespace ASC {

/**
 * MOST Common Register Event
 *
 * This event transports a register read or write result (e.g. reading the routing engine of the OS8104).
 * Unlike the special register event this event does not occur spontaneous.
 */
class MostCommonRegister : public Event
{
public:
    MostCommonRegister();

    /** @copydoc MostTime */
    MostTime time;

    /** @copydoc MostChannel */
    MostChannel channel;

    /** @copydoc MostRegSubType */
    MostRegSubType regSubType;

    /** @copydoc MostRegChip */
    MostRegChip regChip;

    /** @copydoc MostRegOffset */
    MostRegOffset regOffset;

    /** @copydoc MostRegDataLen */
    MostRegDataLen regDataLen;

    /** @copydoc MostDx */
    std::vector<MostDx> data;

    /** @copydoc Event::parse() */
    static MostCommonRegister * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
