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
 * LIN Checksum Info
 *
 * This info event is displayed when the LIN hardware successfully detected the checksum model of
 * an unknown frame. This checksum model is set as the expected checksum model for this frame.
 * An error is displayed if the same frame is received with a different checksum model.
 */
class LinChecksumInfo : public Event
{
public:
    LinChecksumInfo();
    virtual ~LinChecksumInfo();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinId */
    LinId id;

    /** @copydoc LinChecksumModelInfo */
    LinChecksumModelInfo checksumModelInfo;

    /** @copydoc Event::parse() */
    static LinChecksumInfo * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
