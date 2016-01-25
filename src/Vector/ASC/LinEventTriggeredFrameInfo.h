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
#include "LinSymbols.h"

namespace Vector {
namespace ASC {

/**
 * LIN Event Triggered Frame Info
 *
 * This info event is displayed when an event triggered frame is received or transmitted on a LIN
 * channel.
 *
 * IMPORTANT: This event is generated up to CANoe/CANalyzer 5.2 only.
 */
class LinEventTriggeredFrameInfo : public Event
{
public:
    LinEventTriggeredFrameInfo();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinId */
    LinId id;

    /** @copydoc LinEtfName */
    LinEtfName etfName;

    /** @copydoc LinDescription */
    LinDescription description;

    /** @copydoc Event::parse() */
    static LinEventTriggeredFrameInfo * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
