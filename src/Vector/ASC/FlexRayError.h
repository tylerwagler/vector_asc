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

#include <array>

#include "Event.h"

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/**
 * FlexRay Error Event ("EE")
 *
 * FlexRay Message received or transmitted on a FlexRay channel.
 */
class VECTOR_ASC_EXPORT FlexRayError : public Event
{
public:
    FlexRayError();

    /** Timestamp */
    double time;

    /** Clusternr. */
    uint32_t clusterNr;

    /** Client-ID */
    uint32_t clientId;

    /** Channelnr. */
    uint32_t channelNr;

    /** Channel mask */
    uint32_t channelMask;

    /** CC-Type. */
    uint32_t ccType;

    /** CC-Data[4] */
    std::array<uint32_t, 4> ccData;

    /** @copydoc Event::parse() */
    static FlexRayError * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
