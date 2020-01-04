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

#include <Vector/ASC/platform.h>

#include <vector>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/FlexRaySymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * FlexRay Message Event (Old Format)
 *
 * FlexRay Message received or transmitted on a FlexRay channel.
 */
struct VECTOR_ASC_EXPORT FlexRayOldMessage final : Event {
    FlexRayOldMessage() : Event(EventType::FlexRayOldMessage) {}

    /** @copydoc FlexRayOldTime */
    FlexRayOldTime time {0.0};

    /** @copydoc FlexRayOldChannel */
    FlexRayOldChannel channel {};

    /** @copydoc FlexRayOldId */
    FlexRayOldId id {0};

    /** @copydoc FlexRayOldCycle */
    FlexRayOldCycle cycle {0};

    /** @copydoc FlexRayOldNm */
    FlexRayOldNm nm {false};

    /** @copydoc FlexRayOldSync */
    FlexRayOldSync sync {false};

    /** @copydoc FlexRayOldHeaderCrc */
    FlexRayOldHeaderCrc headerCrc {0};

    /** @copydoc FlexRayOldSymbolicName */
    FlexRayOldSymbolicName symbolicName {};

    /** @copydoc FlexRayOldDlc */
    FlexRayOldDlc dlc {0};

    /** @copydoc FlexRayOldDx */
    std::vector<FlexRayOldDx> data {};

    /** @copydoc FlexRayOldFrameState */
    FlexRayOldFrameState frameState {0};

    /** @copydoc FlexRayOldHeaderBitMask */
    FlexRayOldHeaderBitMask headerBitMask {0};

    /** @copydoc Event::read() */
    static FlexRayOldMessage * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
