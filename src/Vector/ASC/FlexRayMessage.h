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

#include <vector>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/FlexRaySymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * FlexRay Message Event ("RMSG / PDU")
 *
 * FlexRay Message received or transmitted on a FlexRay channel.
 */
struct VECTOR_ASC_EXPORT FlexRayMessage final : Event {
    FlexRayMessage() : Event(EventType::FlexRayMessage) {}

    /** Timestamp */
    double time {0.0};

    /** Event type */
    enum FlexRayEventType : uint8_t {
        RMSG,
        PDU
    };

    /** Event type */
    FlexRayEventType flexRayEventType {FlexRayEventType::RMSG};

    /** Clusternr. */
    uint32_t clusterNr {0};

    /** Client-ID */
    uint32_t clientId {0};

    /** Channelnr. */
    uint32_t channelNr {0};

    /** Channel mask */
    uint32_t channelMask {0};

    /** Slot ID */
    uint32_t slotId {0};

    /** Cycle no. */
    uint32_t cycleNo {0};

    /** Direction */
    Dir direction {Dir::Rx};

    /** App. param. */
    uint32_t appParam {0};

    /** Flags */
    uint32_t flags {0};

    /** CC-Type. */
    uint32_t ccType {0};

    /** CC-Data */
    uint32_t ccData {0};

    /** Header CRC */
    uint32_t headerCrc {0};

    /** Name */
    std::string name {};

    /** Payload length */
    int32_t payloadLength {0};

    /** Buffer length */
    int32_t bufferLength {0};

    /** Data[n] */
    std::vector<uint8_t> data {};

    /** Frame CRC */
    uint32_t frameCrc {0};

    /** Spy Flag */
    bool spyFlag {false};

    /** Frame Length NS */
    uint32_t frameLengthNs {0};

    /** PDU Offset */
    int32_t pduOffset {0};

    /** @copydoc Event::read() */
    static FlexRayMessage * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;

    /**
     * @copydoc Event::read()
     *
     * specific for FlexRay RMSG
     */
    static FlexRayMessage * readRmsg(File & file, std::string & line);

    /**
     * @copydoc Event::read()
     *
     * specific for FlexRay PDU
     */
    static FlexRayMessage * readPdu(File & file, std::string & line);
};

}
}
