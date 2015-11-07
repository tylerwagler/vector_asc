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

/** MOST50 Packet */
/* <Time> <Channel> Pkt50: <Dir> <SourceAdr> <DestAdr> <State> <AckNack> <TransferType> <RsvdUC> <RsvdUC> <RsvdUC> <CRC2> <RsvdUC> <RsvdUL> <PktLen> <D0> <D1>...<D(PktLen-1)> */
class Most50Packet : public Event
{
public:
    Most50Packet();
    virtual ~Most50Packet();

    /** Time */
    float time;

    /** Channel */
    unsigned short channel;

    /** Dir */
    enum class Dir {
        Rx,
        Tx
    };

    Dir dir;

    /** SourceAdr */
    unsigned short sourceAdr;

    /** DestAdr */
    unsigned short destAdr;

    /** State */
    unsigned short state;

    /** AckNack */
    unsigned short ackNack;

    /** TransferType */
    unsigned short transferType;

    /** RsvdUC */
    unsigned short rsvdUc1;

    /** RsvdUC */
    unsigned short rsvdUc2;

    /** RsvdUC */
    unsigned short rsvdUc3;

    /** CRC2 */
    unsigned short crc2;

    /** RsvdUC */
    unsigned short rsvdUc4;

    /** RsvdUL */
    unsigned short rsvdUl;

    /** PktLen */
    unsigned short pktLen;

    /** Data */
    unsigned short data[8];

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static Most50Packet * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
