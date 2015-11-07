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

/** CAN FD Error Frame */
/* <Time> CANFD <Channel> <Dir> ErrorFrame <ErrorText> <flags> <code> <codeExt> <Phase> <Position> <ID> <BRS> <ESI> <DLC> <DataLength> <D1> ... <D64> <MessageDuration> <Flags> <CRC> <BitTimingConfArb> <BitTimingConfData> */
class CanFdErrorFrame : public Event
{
public:
    CanFdErrorFrame();
    virtual ~CanFdErrorFrame();

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

    /** Error Text */
    std::string errorText;

    /** flags */
    uint32_t flags1;

    /** code */
    uint32_t code;

    /** codeExt */
    uint32_t codeExt;

    /** Phase */
    enum class Phase {
        Data
    };

    /** Phase */
    Phase phase;

    /** Position */
    uint32_t position;

    /** ID */
    uint32_t id;

    /** BRS */
    bool brs;

    /** ESI */
    bool esi;

    /** DLC */
    uint8_t dlc;

    /** Data Length */
    uint8_t dataLength;

    /** Data */
    uint8_t data[64];

    /** Message Duration */
    uint32_t messageDuration;

    /** Flags */
    uint32_t flags2;

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
    static CanFdErrorFrame * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
