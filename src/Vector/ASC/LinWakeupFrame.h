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

#include "platform.h"

#include "Event.h"
#include "LinSymbols.h"

namespace Vector {
namespace ASC {

/**
 * LIN Wakeup Frame
 *
 * A Wakeup-Frame event is displayed when a wakeup request has been detected on a LIN channel.
 */
class LinWakeupFrame : public Event
{
public:
    LinWakeupFrame();

    /** @copydoc LinTime */
    double time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinDir */
    LinDir dir;

    /** @copydoc LinWakeupByte */
    LinWakeupByte wakeupByte;

    /** @copydoc LinStartOfFrame */
    LinStartOfFrame startOfFrame;

    /** @copydoc LinBaudrateType */
    LinBaudrateType baudrate;

    /** @copydoc LinWakeupLengthInfo */
    LinWakeupLengthInfo wakeupLengthInfo;

    /** @copydoc Event::parse() */
    static LinWakeupFrame * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
