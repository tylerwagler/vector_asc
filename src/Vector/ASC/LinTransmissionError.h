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

/** LIN Transmission Error */
/* <Time> <Channel> <ID> TransmErr (slave = <slave id>, state = <state>) header time = <header time>
 * full time = <full time> */
/* <Time> <Channel> <ID> TransmErr (slave = <slave id>, state = <state>) header time = <header time>,
 * full time = <full time> SOF = <start of frame> BR = <baudrate> break = <SyncBreak> <SyncDel>
 * (subId = <NAD> <MessageId> <SupplierId>) EOH = <end of header> */
/* <Time> <Channel> <ID> TransmErr (slave = <slave id>, state = <state>) header time = <header time>,
 * full time = <full time> SOF = <start of frame> BR = <baudrate> break = <SyncBreak> <SyncDel>
 * (subId = <NAD> <MessageId> <SupplierId>) EOH = <end of header> > HBR = <header baudrate> HSO
 * = <stop bit offset in header> */
/* <Time> <Channel> <ID> TransmErr (slave = <slave id>, state = <state>) header time = <header time>,
 * full time = <full time> SOF = <start of frame> BR = <baudrate> break = <SyncBreak> <SyncDel>
 * (subId = <NAD> <MessageId> <SupplierId>) EOH = <end of header> > HBR = <header baudrate> HSO
 * = <stop bit offset in header> CSM = <checksum model> */
class LinTransmissionError : public Event
{
public:
    LinTransmissionError();
    virtual ~LinTransmissionError();

    /** Time */
    float time;

    /** Channel */
    std::string channel;

    /** ID */
    uint16_t id;

    /** slave id */
    uint8_t slaveId;

    /** state */
    uint8_t state;

    /** header time */
    uint8_t headerTime;

    /** full time */
    uint8_t fullTime;


    /** start of frame (SOF) */
    float startOfFrame;

    /** baudrate (BR) */
    uint16_t baudrate;

    /** SyncBreak */
    uint32_t syncBreak;

    /** SyncDel */
    uint32_t syncDel;

    /** subId (NAD) */
    uint16_t subId;

    /** MessageId */
    uint16_t messageId;

    /** SupplierId */
    uint16_t supplierId;

    /** end of header (EOH) */
    float endOfHeader;


    /** header baudrate (HBR) */
    float headerBaudrate;

    /** stop bit offset in header (HSO) */
    uint16_t stopBitOffsetInHeader;


    /** checksum model (CSM) */
    std::string checksumModel;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static LinTransmissionError * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
