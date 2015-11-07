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

/** MOST Statistic Event */
/* <Time> <Channel> MostStatistic: Fr: <StatVal> Lt: <StatValue> Bl: <StatVal> Pk: <StatValue> */
class MostStatisticEvent : public Event
{
public:
    MostStatisticEvent();
    virtual ~MostStatisticEvent();

    /** Time */
    float time;

    /** Channel */
    unsigned short channel;

    /** Fr */
    unsigned short fr;

    /** Lt */
    unsigned short lt;

    /** Bl */
    unsigned short bl;

    /** Pk */
    unsigned short pk;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static MostStatisticEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
