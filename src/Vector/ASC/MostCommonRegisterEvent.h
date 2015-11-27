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
class MostCommonRegisterEvent : public Event
{
public:
    MostCommonRegisterEvent();
    virtual ~MostCommonRegisterEvent();

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
    MostDx data[1024];

    /** @copydoc Event::parse() */
    static MostCommonRegisterEvent * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
