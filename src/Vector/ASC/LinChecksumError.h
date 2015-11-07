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

/** LIN ChecksumError */
/* <Time> <Channel> <ID> CSErr <Dir> <DLC> <D0>...<D7> (slave = <slave id>, state = <state>) check-
 * sum = <checksum> header time = <header time>, full time = <full time> */
/* <Time> <Channel> <ID> CSErr <Dir> <DLC> <D0>...<D7> (slave = <slave id>, state = <state>)
 * checksum = <checksum> header time = <header time>, full time = <full time> SOF = <start of frame>
 * BR = <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) EOH
 * = <end of header> EOB = <T0> ... <T7> sim = <simulated> */
/* <Time> <Channel> <ID> CSErr <Dir> <DLC> <D0>...<D7> (slave = <slave id>, state = <state>)
 * checksum = <checksum> header time = <header time>, full time = <full time> SOF = <start of frame>
 * BR = <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) EOH
 * = <end of header> EOB = <T0> ... <T7> sim = <simulated> EOF = <end of frame> */
/* <Time> <Channel> <ID> CSErr <Dir> <DLC> <D0>...<D7> (slave = <slave id>, state = <state>)
 * checksum = <checksum> header time = <header time>, full time = <full time> SOF = <start of frame>
 * BR = <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) EOH
 * = <end of header> EOB = <T0> ... <T7> sim = <simulated> EOF = <end of frame> RBR = <response
 * baudrate> */
/* <Time> <Channel> <ID> CSErr <Dir> <DLC> <D0>...<D7> (slave = <slave id>, state = <state>)
 * checksum = <checksum> header time = <header time>, full time = <full time> SOF = <start of frame>
 * BR = <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) EOH
 * = <end of header> EOB = <T0> ... <T7> sim = <simulated> EOF = <end of frame> RBR = <response
 * baudrate> HBR = <header baudrate> HSO = <stop bit offset in header> RSO = <stop bit offset in re-
 * sponse> */
/* <Time> <Channel> <ID> CSErr <Dir> <DLC> <D0>...<D7> (slave = <slave id>, state = <state>)
 * checksum = <checksum> header time = <header time>, full time = <full time> SOF = <start of frame>
 * BR = <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) EOH
 * = <end of header> EOB = <T0> ... <T7> sim = <simulated> EOF = <end of frame> RBR = <response
 * baudrate> HBR = <header baudrate> HSO = <stop bit offset in header> RSO = <stop bit offset in re-
 * sponse> CSM = <unknown|classic|enhanced|error> */
class LinChecksumError : public Event
{
public:
    LinChecksumError();
    virtual ~LinChecksumError();

    /** Time */
    float time;

    /** Channel */
    std::string channel;

    /** ID */
    uint16_t id;

    /** Dir */
    enum class Dir {
        Rx,
        Tx
    };

    Dir dir;

    /** DLC */
    uint8_t dlc;

    /** Data */
    uint8_t data[8];

    /** slave id */
    uint8_t slaveId;

    /** state */
    uint8_t state;

    /** checksum */
    uint8_t checksum;

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
    uint8_t subId;

    /** MessageId */
    uint16_t messageId;

    /** SupplierId */
    uint16_t supplierId;

    /** end of header (EOH) */
    float endOfHeader;

    /** end of byte (EOB) */
    float endOfByte[8];

    /** simulated */
    bool simulated;


    /** end of frame (EOF) */
    float endOfFrame;


    /** response baudrate (RBR) */
    uint16_t responseBaudrate;


    /** header baudrate (HBR) */
    float headerBaudrate;

    /** stop bit offset in header (HSO) */
    uint32_t stopBitOffsetInHeader;

    /** stop bit offset in response (RSO) */
    uint32_t stopBitOffsetInResponse;

    /** unknown|classic|enhanced|error (CSM) */
    std::string checksumModel;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static LinChecksumError * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
