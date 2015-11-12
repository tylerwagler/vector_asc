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
 * LIN Dominant Signal
 *
 * A dominant signal event occurs when a LIN channel remains in the dominant state for a time,
 * which is longer than a valid wakeup frame and not a valid sync break.
 */
class LinDominantSignal : public Event
{
public:
    LinDominantSignal();
    virtual ~LinDominantSignal();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinDomSigState */
    LinDomSigState domSigState;

    /** @copydoc LinDomSigLength */
    LinDomSigLength domSigLength;

    /** @copydoc LinStartOfFrame */
    LinStartOfFrame startOfFrame;

    /** @copydoc LinBaudrateType */
    LinBaudrateType baudrate;

    /** @copydoc Event::parse() */
    static LinDominantSignal * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
