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

/** CAN FD Message Event */
/* <Time> CANFD <Channel> <Dir> <ID> <SymbolicName> <BRS> <ESI> <DLC> <DataLength> <D1> ... <D64> <MessageDuration> <MessageLength> <Flags> <CRC> <BitTimingConfArb> <BitTimingConfData> */
class CanFdMessageEvent : public Event
{
public:
    CanFdMessageEvent();
    virtual ~CanFdMessageEvent();

    /** Time */
    float time;

    /** Channel */
    unsigned int channel;

    /** Dir */
    enum class Dir {
        Rx,
        Tx
    };

    Dir dir;

    /** ID */
    unsigned int id;

    /** SymbolicName */
    std::string symbolicName;

    /** BRS */
    bool brs;

    /** ESI */
    bool esi;

    /** DLC */
    unsigned short dlc;

    /** Data Length */
    unsigned short dataLength;

    /** Data */
    uint8_t data[64];

    /** Message Duration */
    unsigned int messageDuration;

    /** Message Length / Bit Count */
    unsigned int messageLength;

    /** Flags */
    uint32_t flags;

    /** CRC */
    uint32_t crc;

    /** Bit Timing Conf Arb */
    uint32_t bitTimingConfArb;

    /** Bit Timing Conf Data */
    uint32_t bitTimingConfData;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static CanFdMessageEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
