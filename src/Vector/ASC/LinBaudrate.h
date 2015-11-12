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
#include "Symbols.h"

namespace Vector {
namespace ASC {

/**
 * LIN Baudrate
 *
 * This info event is only displayed when an external Master is configured.
 * This info event is send by the LIN hardware at the start of a measurement and whenever the baud
 * rate changes by more than 0.5 % during a measurement. If this info event is displayed, then the
 *
 * LIN hardware is synchronized with the baud rate of the external Master.
 */
class LinBaudrate : public Event
{
public:
    LinBaudrate();
    virtual ~LinBaudrate();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinBaudrateType */
    LinBaudrateType baudrate;

    /** @copydoc Event::parse() */
    static LinBaudrate * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
