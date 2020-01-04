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

#include <Vector/ASC/Event.h>
#include <Vector/ASC/CanSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * CAN Bus Statistics Event
 *
 * CAN Statistic event, which contains statistic information about the CAN channels.
 */
struct VECTOR_ASC_EXPORT CanBusStatistics final : Event {
    CanBusStatistics() : Event(EventType::CanBusStatistics) {}

    /** @copydoc Time */
    Time time {0.0};

    /** @copydoc Channel */
    Channel channel {0};

    /** CAN Data Frames */
    StatNumber dataFrames {0};

    /** CAN Remote Frames */
    StatNumber remoteFrames {0};

    /** CAN Extended Data Frames */
    StatNumber extendedDataFrames {0};

    /** CAN Extended Remote Frames */
    StatNumber extendedRemoteFrames {0};

    /** Error Frames */
    StatNumber errorFrames {0};

    /** Overload Frames */
    StatNumber overloadFrames {0};

    /** Busload */
    StatPercent busload {0.0};

    /** @copydoc Event::read() */
    static CanBusStatistics * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
