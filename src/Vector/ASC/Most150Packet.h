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

/** MOST150 Packet */
/* <Time> <Channel> Pkt150: <Dir> <SourceAdr> <DestAdr> <State> <AckNack> <TransferType> <Pack> <RsvdUC> <Pindex> <CRC2> <Cack> <RsvdUL> <Pkt150Len> <D0> <D1>...<D(PktLen-1)> */
class Most150Packet : public Event
{
public:
    Most150Packet();
    virtual ~Most150Packet();

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

    /** Pack */
    unsigned short pAck;

    /** RsvdUC */
    unsigned short rsvdUc;

    /** Pindex */
    unsigned short pIndex;

    /** CRC2 */
    unsigned short crc2;

    /** Cack */
    unsigned short cAck;

    /** RsvdUL */
    unsigned short rsvdUl;

    /** Pkt150Len */
    unsigned short pkt150Len;

    /** Data */
    unsigned short data[1024];

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static Most150Packet * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
