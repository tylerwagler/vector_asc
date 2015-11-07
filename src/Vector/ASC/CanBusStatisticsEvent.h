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

namespace Vector {
namespace ASC {

/** CAN Bus Statistics Event */
/* <Time> <Channel> Statistic: D <StatNumber> R <StatNumber> XD <StatNumber> XR <StatNumber> E <StatNumber> O <StatNumber> B <StatPercent>% */
class CanBusStatisticsEvent : public Event
{
public:
    CanBusStatisticsEvent();
    virtual ~CanBusStatisticsEvent();

    /** Time */
    float time;

    /** Channel */
    uint16_t channel;

    /** CAN Data Frames */
    uint32_t dataFrames;

    /** CAN Remote Frames */
    uint32_t remoteFrames;

    /** CAN Extended Data Frames */
    uint32_t extendedDataFrames;

    /** CAN Extended Remote Frames */
    uint32_t extendedRemoteFrames;

    /** Error Frames */
    uint32_t errorFrames;

    /** Overload Frames */
    uint32_t overloadFrames;

    /** Busload */
    float busload;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static CanBusStatisticsEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
