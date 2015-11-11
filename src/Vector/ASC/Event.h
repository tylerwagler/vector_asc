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

#include <iostream>
#include <string>
#include "File.h"

namespace Vector {
namespace ASC {

/**
 * Base class for all events
 */
class Event
{
public:
    Event();
    virtual ~Event();

    /**
     * Event Type
     */
    enum EventType : int {
        Default = 0,
        Unknown = 1,

        /* File */
        FileDate = 10,
        FileBaseTimestamps,
        FileInternalEventsLogged,
        FileVersion,
        FileSplitInformation,
        FileComment,

        /* CAN Events */
        CanMessageEvent = 20,
        CanExtendedMessageEvent,
        CanRemoteFrameEvent,
        CanErrorFrame,
        CanBusStatisticsEvent,
        CanErrorEvent,
        CanOverloadFrameEvent,

        /* CAN FD Events */
        CanFdMessageEvent = 30,
        CanFdExtendedMessageEvent,
        CanFdErrorFrame,
        // CAN FD Bus Statistics Event
        // CAN FD Overload Frame

        /* Log and Trigger Events */
        LogTriggerEvent = 40,
        LogDirectStartEvent,
        LogDirectStopEvent,
        BeginTriggerblockEvent,
        EndTriggerblockEvent,

        /* Environment Variables */
        EnvironmentVariablesEvent = 50,

        /* System Variables */
        SystemVariablesEvent = 60,

        /* Macros Signal Events */
        MacroSignalEvent = 70,

        /* GPS events */
        GpsEvent = 80,

        /* Comment events */
        CommentEvent = 90,

        /* Global market events */
        GlobalMarkerEvent = 100,

        /* Ethernet Events */
        EthernetPacket = 110,
        EthernetStatus,
        EthernetRxError,

        /* AFDX Events */
        AfdxPacket = 120,

        /* FlexRay Events (Old Format) */
        FlexRayOldMessageEvent = 130,
        FlexRayOldStartCycleEvent,

        /* FlexRay Events (New Format) */
        FlexRayMessageEvent = 140,
        FlexRayStartCycleEvent,
        FlexRayStatusEvent,
        FlexRayErrorEvent,

        /* K-Line Events */
        KLineByteEvent = 150,
        KLineMessageEvent,

        /* LIN Events */
        LinMessage = 160,

        /* LIN Error Events */
        LinTransmissionError = 170,
        LinReceiveError,
        LinSyncError,
        LinChecksumError,
        LinSpikeEvent,
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
        LinDisturbanceEvent,

        /* LIN Sleep/Wakeup Events */
        LinSleepMode = 190,
        LinWakeupFrame,
        LinUnexpectedWakeup,

        /* MOST Events */
        Most25ControlMessageNodeMode = 200,
        Most25ControlMessageSpyMode,
        Most25Packet,
        MostLightLockEvent,
        MostSpecialRegisterEvent,
        MostCommonRegisterEvent,
        MostHwModeEvent,
        MostNetStateEvent,
        MostDataLostEvent,
        MostTriggerEvent,
        MostStatisticEvent,
        MostStatisticExtendedEvent,
        MostTxLight,
        MostStressEvent,
        Most25AllocTable,
        Most150ControlMessage,
        Most150ControlMessageFragment,
        Most150Packet,
        Most150PacketFragment,
        MostEthernetPacket,
        MostEthernetPacketFragment,
        MostSystemEvent,
        Most150AllocTable,
        Most50ControlMessage,
        Most50Packet,
        MostEcl,

        /* TP/Diagnostics Events */
        TpDiagPrefix = 230,
        TpDiagSingleFrame,
        TpDiagFirstFrame,
        TpDiagConsecutiveFrame,
        TpDiagFlowControlFrame,
        TpDiagRequest
    };

    EventType eventType;

    /**
     * Parse function
     *
     * @param file File for number base
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static Event * parse(File & file, std::string & line);

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
