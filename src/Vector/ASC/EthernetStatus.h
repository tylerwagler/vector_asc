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

/** Ethernet Status */
/* <Time> ETH <Channel> STAT [Link:Link_up|Link_down] [LinkSpeed:<bitrate>Mbit/s] [Physical:IEEE802.3|BroadR-Reach] [Duplex:Full|Half] [MDI:Crossover|Direct] [Connector:RJ45|D-Sub] [BRClockMode:Master|Slave] */
class EthernetStatus : public Event
{
public:
    EthernetStatus();
    virtual ~EthernetStatus();

    /** Time */
    float time;

    /** Channel */
    uint8_t channel;

    /** Link */
    std::string link;

    /** LinkSpeed */
    std::string linkSpeed;

    /** Physical */
    std::string physical;

    /** Duplex */
    std::string duplex;

    /** MDI */
    std::string mdi;

    /** Connector */
    std::string connector;

    /** BRClockMode */
    std::string brClockMode;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static EthernetStatus * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
