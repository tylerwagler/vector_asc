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

#include <iostream>
#include <string>

#include <Vector/ASC/File.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/* forward declaration */
class File;

/**
 * Base class for all events
 */
struct VECTOR_ASC_EXPORT Event {
    /**
     * Event Type
     */
    enum EventType : int {
        /** Default and End-Of-File */
        Default = 0,

        /** Unknown Event */
        Unknown = 1,

        /* File */
        FileDate = 10,
        FileBaseTimestamps,
        FileInternalEventsLogged,
        FileVersion,
        FileSplitInformation,
        FileComment,

        /* CAN Events */
        CanMessage = 20,
        CanExtendedMessage,
        CanRemoteFrame,
        CanErrorFrame,
        CanBusStatistics,
        CanError,
        CanOverloadFrame,

        /* CAN FD Events */
        CanFdMessage = 30,
        CanFdExtendedMessage,
        CanFdErrorFrame,
        // CAN FD Bus Statistics
        // CAN FD Overload Frame

        /* Log and Trigger Events */
        LogTrigger = 40,
        LogDirectStart,
        LogDirectStop,
        BeginTriggerblock,
        EndTriggerblock,

        /* Environment Variables */
        EnvironmentVariables = 50,

        /* System Variables */
        SystemVariables = 60,

        /* Macros Signal Events */
        MacroSignal = 70,

        /* GPS events */
        Gps = 80,

        /* Comment events */
        Comment = 90,

        /* Global market events */
        GlobalMarker = 100,

        /* Ethernet Events */
        EthernetPacket = 110,
        EthernetStatus,
        EthernetRxError,

        /* AFDX Events */
        AfdxPacket = 120,

        /* FlexRay Events (Old Format) */
        FlexRayOldMessage = 130,
        FlexRayOldStartCycle,

        /* FlexRay Events (New Format) */
        FlexRayMessage = 140,
        FlexRayStartCycle,
        FlexRayStatus,
        FlexRayError,

        /* K-Line Events */
        KLineByte = 150,
        KLineMessage,

        /* LIN Events */
        LinMessage = 160,

        /* LIN Error Events */
        LinTransmissionError = 170,
        LinReceiveError,
        LinSyncError,
        LinChecksumError,
        LinSpike,
        LinDominantSignal,

        /* LIN Info Events */
        LinBaudrate = 180,
        LinDlcInfo,
        LinChecksumInfo,
        LinSchedulerModeChange,
        LinSlaveTimeout,
        LinEventTriggeredFrameInfo,
        LinStatisticInfo,
        LinShortOrSlowResponse,
        LinDisturbance,

        /* LIN Sleep/Wakeup Events */
        LinSleepMode = 190,
        LinWakeupFrame,
        LinUnexpectedWakeup,

        /* MOST Events */
        Most25ControlMessageNodeMode = 200,
        Most25ControlMessageSpyMode,
        Most25Packet,
        MostLightLock,
        MostSpecialRegister,
        MostCommonRegister,
        MostHwMode,
        MostNetState,
        MostDataLost,
        MostTrigger,
        MostStatistic,
        MostStatisticExtended,
        MostTxLight,
        MostStress,
        Most25AllocTable,
        Most150ControlMessage,
        Most150ControlMessageFragment,
        Most150Packet,
        Most150PacketFragment,
        MostEthernetPacket,
        MostEthernetPacketFragment,
        MostSystem,
        Most150AllocTable,
        Most50ControlMessage,
        Most50Packet,
        MostEcl,

        /* TP/Diagnostics Events */
        TpSingleFrame = 230,
        TpFirstFrame,
        TpConsecutiveFrame,
        TpFlowControlFrame,
        DiagRequest,

        /* undocumented events */
        StartOfMeasurement = 240
    };

    Event(EventType eventType) :
        eventType(eventType) {}
    virtual ~Event() = default;

    /** @copydoc EventType */
    EventType eventType {EventType::Default};

    /**
     * Parse function
     *
     * @param file File for number base
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static Event * read(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param file File for number base
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
