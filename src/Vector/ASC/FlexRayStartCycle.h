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

#include <array>
#include <vector>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/FlexRaySymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * FlexRay Start Cycle Event ("SCE")
 *
 * FlexRay Message received or transmitted on a FlexRay channel.
 */
struct VECTOR_ASC_EXPORT FlexRayStartCycle final : Event {
    FlexRayStartCycle() : Event(EventType::FlexRayStartCycle) {}

    /** Timestamp */
    double time {0.0};

    /** Clusternr. */
    uint32_t clusterNr {0};

    /** Client-ID */
    uint32_t clientId {0};

    /** Channelnr. */
    uint32_t channelNr {0};

    /** Channel mask */
    uint32_t channelMask {0};

    /** Cycle no. */
    uint32_t cycleNo {0};

    /** Direction */
    Dir direction {Dir::Rx};

    /** CC-Type. */
    uint32_t ccType {0};

    /** CC-Data[5] */
    std::array<uint32_t, 5> ccData {};

    /** NM_Vect_L */
    uint32_t nmVectL {0};

    /** NM_Vect[n] */
    std::vector<uint8_t> nmVect {};

    /** @copydoc Event::read() */
    static FlexRayStartCycle * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
