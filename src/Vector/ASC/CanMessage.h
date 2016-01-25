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
#include "CanSymbols.h"

namespace Vector {
namespace ASC {

/**
 * CAN Message Event
 *
 * Simple CAN Message received or transmitted on a CAN channel.
 */
class CanMessage : public Event
{
public:
    CanMessage();

    /** @copydoc Time */
    Time time;

    /** @copydoc Channel */
    Channel channel;

    /** @copydoc IdNum */
    IdNum id;

    /** @copydoc Dir */
    Dir dir;

    /** @copydoc Dlc */
    Dlc dlc;

    /** @copydoc Dx */
    std::vector<Dx> data;

    /** @copydoc MessageLength */
    MessageDuration messageDuration;

    /** @copydoc MessageLength */
    MessageLength messageLength;

    /** @copydoc MessageFlags */
    MessageFlags messageFlags;

    /** @copydoc IdNum */
    IdNum messageId;

    /** @copydoc Event::parse() */
    static CanMessage * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
