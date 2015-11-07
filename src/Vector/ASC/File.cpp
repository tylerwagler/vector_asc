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

#include <cstring>
#include <iostream>

#include "AllEvents.h"
#include "File.h"

namespace Vector {
namespace ASC {

File::File() :
    openMode(OpenMode::Read),
    file()
{
}

File::~File()
{
}

void File::open(const char * filename)
{
    switch(openMode) {
    case OpenMode::Read:
        file.open(filename, std::ios_base::in);
        break;
    case OpenMode::Write:
        file.open(filename, std::ios_base::out);
        break;
    }
}

void File::open(const std::string & filename)
{
    open(filename.c_str());
}

bool File::is_open() const
{
    return file.is_open();
}

void File::close()
{
    file.close();
}

bool File::eof()
{
    return file.eof();
}

Event * File::read()
{
    /** @todo here we need some intelligence to test only likely Events */

    /* read line */
    std::string line;
    (void) std::getline(file, line);

    /* remove windows line ending */
    if (line.back() == '\r')
        line.pop_back();

    /* File */
    FileDate * fileData = FileDate::parse(*this, line);
    if (fileData)
        return fileData;
    FileBaseTimestamps * fileBaseTimestamps = FileBaseTimestamps::parse(*this, line);
    if (fileBaseTimestamps)
        return fileBaseTimestamps;
    FileInternalEventsLogged * fileInternalEventsLogged = FileInternalEventsLogged::parse(*this, line);
    if (fileInternalEventsLogged)
        return fileInternalEventsLogged;
    FileVersion * fileVersion = FileVersion::parse(*this, line);
    if (fileVersion)
        return fileVersion;
    FileSplitInformation * fileSplitInformation = FileSplitInformation::parse(*this, line);
    if (fileSplitInformation)
        return fileSplitInformation;
    // fileComment is non-greedy, hence tested below

    /* CAN Events */
    CanMessageEvent * canMessageEvent = CanMessageEvent::parse(*this, line);
    if (canMessageEvent)
        return canMessageEvent;
    CanExtendedMessageEvent * canExtendedMessageEvent = CanExtendedMessageEvent::parse(*this, line);
    if (canExtendedMessageEvent)
        return canExtendedMessageEvent;
    CanRemoteFrameEvent * canRemoteFrameEvent = CanRemoteFrameEvent::parse(*this, line);
    if (canRemoteFrameEvent)
        return canRemoteFrameEvent;
    CanErrorFrame * canErrorFrame = CanErrorFrame::parse(*this, line);
    if (canErrorFrame)
        return canErrorFrame;
    CanBusStatisticsEvent * canBusStatisticsEvent = CanBusStatisticsEvent::parse(*this, line);
    if (canBusStatisticsEvent)
        return canBusStatisticsEvent;
    CanErrorEvent * canErrorEvent = CanErrorEvent::parse(*this, line);
    if (canErrorEvent)
        return canErrorEvent;
    CanOverloadFrameEvent * canOverloadFrameEvent = CanOverloadFrameEvent::parse(*this, line);
    if (canOverloadFrameEvent)
        return canOverloadFrameEvent;

    /* CAN FD Events */
    CanFdMessageEvent * canFdMessageEvent = CanFdMessageEvent::parse(*this, line);
    if (canFdMessageEvent)
        return canFdMessageEvent;
    CanFdExtendedMessageEvent * canFdExtendedMessageEvent = CanFdExtendedMessageEvent::parse(*this, line);
    if (canFdExtendedMessageEvent)
        return canFdExtendedMessageEvent;
    CanFdErrorFrame * canFdErrorFrame = CanFdErrorFrame::parse(*this, line);
    if (canFdErrorFrame)
        return canFdErrorFrame;
    // @todo CAN FD Bus Statistics Event
    // @todo CAN FD Overload Frame

    /* Log and Trigger Events */
    LogTriggerEvent * logTriggerEvent = LogTriggerEvent::parse(*this, line);
    if (logTriggerEvent)
        return logTriggerEvent;
    LogDirectStartEvent * logDirectStartEvent = LogDirectStartEvent::parse(*this, line);
    if (logDirectStartEvent)
        return logDirectStartEvent;
    LogDirectStopEvent * logDirectStopEvent = LogDirectStopEvent::parse(*this, line);
    if (logDirectStopEvent)
        return logDirectStopEvent;
    BeginTriggerblockEvent * beginTriggerblockEvent = BeginTriggerblockEvent::parse(*this, line);
    if (beginTriggerblockEvent)
        return beginTriggerblockEvent;
    EndTriggerblockEvent * endTriggerblockEvent = EndTriggerblockEvent::parse(*this, line);
    if (endTriggerblockEvent)
        return endTriggerblockEvent;

    /* Environment Variables */
    EnvironmentVariablesEvent * environmentVariablesEvent = EnvironmentVariablesEvent::parse(*this, line);
    if (environmentVariablesEvent)
        return environmentVariablesEvent;

    /* System Variables */
    SystemVariablesEvent * systemVariablesEvent = SystemVariablesEvent::parse(*this, line);
    if (systemVariablesEvent)
        return systemVariablesEvent;

    /* Macros Signal Events */
    MacroSignalEvent * macroSignalEvent = MacroSignalEvent::parse(*this, line);
    if (macroSignalEvent)
        return macroSignalEvent;

    /* GPS events */
    GpsEvent * gpsEvent = GpsEvent::parse(*this, line);
    if (gpsEvent)
        return gpsEvent;

    /* Comment events */
    CommentEvent * commentEvent = CommentEvent::parse(*this, line);
    if (commentEvent)
        return commentEvent;

    /* Global market events */
    GlobalMarkerEvent * globalMarkerEvent = GlobalMarkerEvent::parse(*this, line);
    if (globalMarkerEvent)
        return globalMarkerEvent;

    /* Ethernet Events */
    EthernetPacket * ethernetPacket = EthernetPacket::parse(*this, line);
    if (ethernetPacket)
        return ethernetPacket;
    EthernetStatus * ethernetStatus = EthernetStatus::parse(*this, line);
    if (ethernetStatus)
        return ethernetStatus;
    EthernetRxError * ethernetRxError = EthernetRxError::parse(*this, line);
    if (ethernetRxError)
        return ethernetRxError;

    /* AFDX Events */
    AfdxPacket * afdxPacket = AfdxPacket::parse(*this, line);
    if (afdxPacket)
        return afdxPacket;

    /* FlexRay Events (Old Format) */
    FlexRayOldMessageEvent * flexRayOldMessageEvent = FlexRayOldMessageEvent::parse(*this, line);
    if (flexRayOldMessageEvent)
        return flexRayOldMessageEvent;
    FlexRayOldStartCycleEvent * flexRayOldStartCycleEvent = FlexRayOldStartCycleEvent::parse(*this, line);
    if (flexRayOldStartCycleEvent)
        return flexRayOldStartCycleEvent;

    /* FlexRay Events (New Format) */
    FlexRayMessageEvent * flexRayMessageEvent = FlexRayMessageEvent::parse(*this, line);
    if (flexRayMessageEvent)
        return flexRayMessageEvent;
    FlexRayStartCycleEvent * flexRayStartCycleEvent = FlexRayStartCycleEvent::parse(*this, line);
    if (flexRayStartCycleEvent)
        return flexRayStartCycleEvent;
    FlexRayStatusEvent * flexRayStatusEvent = FlexRayStatusEvent::parse(*this, line);
    if (flexRayStatusEvent)
        return flexRayStatusEvent;
    FlexRayErrorEvent * flexRayErrorEvent = FlexRayErrorEvent::parse(*this, line);
    if (flexRayErrorEvent)
        return flexRayErrorEvent;

    /* K-Line Events */
    KLineByteEvent * kLineByteEvent = KLineByteEvent::parse(*this, line);
    if (kLineByteEvent)
        return kLineByteEvent;
    KLineMessageEvent * kLineMessageEvent = KLineMessageEvent::parse(*this, line);
    if (kLineMessageEvent)
        return kLineMessageEvent;

    /* LIN Events */
    LinMessage * linMessage = LinMessage::parse(*this, line);
    if (linMessage)
        return linMessage;

    /* LIN Error Events */
    LinTransmissionError * linTransmissionError = LinTransmissionError::parse(*this, line);
    if (linTransmissionError)
        return linTransmissionError;
    LinReceiveError * linReceiveError = LinReceiveError::parse(*this, line);
    if (linReceiveError)
        return linReceiveError;
    LinSyncError * linSyncError = LinSyncError::parse(*this, line);
    if (linSyncError)
        return linSyncError;
    LinChecksumError * linChecksumError = LinChecksumError::parse(*this, line);
    if (linChecksumError)
        return linChecksumError;
    LinSpikeEvent * linSpikeEvent = LinSpikeEvent::parse(*this, line);
    if (linSpikeEvent)
        return linSpikeEvent;
    LinDominantSignal * linDominantSignal = LinDominantSignal::parse(*this, line);
    if (linDominantSignal)
        return linDominantSignal;

    /* LIN Info Events */
    LinBaudrate * linBaudrate = LinBaudrate::parse(*this, line);
    if (linBaudrate)
        return linBaudrate;
    LinDlcInfo * linDlcInfo = LinDlcInfo::parse(*this, line);
    if (linDlcInfo)
        return linDlcInfo;
    LinChecksumInfo * linChecksumInfo = LinChecksumInfo::parse(*this, line);
    if (linChecksumInfo)
        return linChecksumInfo;
    LinSchedulerModeChange * linSchedulerModeChange = LinSchedulerModeChange::parse(*this, line);
    if (linSchedulerModeChange)
        return linSchedulerModeChange;
    LinSlaveTimeout * linSlaveTimeout = LinSlaveTimeout::parse(*this, line);
    if (linSlaveTimeout)
        return linSlaveTimeout;
    LinEventTriggeredFrameInfo * linEventTriggeredFrameInfo = LinEventTriggeredFrameInfo::parse(*this, line);
    if (linEventTriggeredFrameInfo)
        return linEventTriggeredFrameInfo;
    LinStatisticInfo * linStatisticInfo = LinStatisticInfo::parse(*this, line);
    if (linStatisticInfo)
        return linStatisticInfo;
    LinShortOrSlowResponse * linShortOrSlowResponse = LinShortOrSlowResponse::parse(*this, line);
    if (linShortOrSlowResponse)
        return linShortOrSlowResponse;
    LinDisturbanceEvent * linDisturbanceEvent = LinDisturbanceEvent::parse(*this, line);
    if (linDisturbanceEvent)
        return linDisturbanceEvent;

    /* LIN Sleep/Wakeup Events */
    LinSleepMode * linSleepMode = LinSleepMode::parse(*this, line);
    if (linSleepMode)
        return linSleepMode;
    LinWakeupFrame * linWakeupFrame = LinWakeupFrame::parse(*this, line);
    if (linWakeupFrame)
        return linWakeupFrame;
    LinUnexpectedWakeup * linUnexpectedWakeup = LinUnexpectedWakeup::parse(*this, line);
    if (linUnexpectedWakeup)
        return linUnexpectedWakeup;

    /* MOST Events */
    Most25ControlMessageNodeMode * most25ControlMessageNodeMode = Most25ControlMessageNodeMode::parse(*this, line);
    if (most25ControlMessageNodeMode)
        return most25ControlMessageNodeMode;
    Most25ControlMessageSpyMode * most25ControlMessageSpyMode = Most25ControlMessageSpyMode::parse(*this, line);
    if (most25ControlMessageSpyMode)
        return most25ControlMessageSpyMode;
    Most25Packet * most25Packet = Most25Packet::parse(*this, line);
    if (most25Packet)
        return most25Packet;
    MostLightLockEvent * mostLightLockEvent = MostLightLockEvent::parse(*this, line);
    if (mostLightLockEvent)
        return mostLightLockEvent;
    MostSpecialRegisterEvent * mostSpecialRegisterEvent = MostSpecialRegisterEvent::parse(*this, line);
    if (mostSpecialRegisterEvent)
        return mostSpecialRegisterEvent;
    MostCommonRegisterEvent * mostCommonRegisterEvent = MostCommonRegisterEvent::parse(*this, line);
    if (mostCommonRegisterEvent)
        return mostCommonRegisterEvent;
    MostHwModeEvent * mostHwModeEvent = MostHwModeEvent::parse(*this, line);
    if (mostHwModeEvent)
        return mostHwModeEvent;
    MostNetStateEvent * mostNetStateEvent = MostNetStateEvent::parse(*this, line);
    if (mostNetStateEvent)
        return mostNetStateEvent;
    MostDataLostEvent * mostDataLostEvent = MostDataLostEvent::parse(*this, line);
    if (mostDataLostEvent)
        return mostDataLostEvent;
    MostTriggerEvent * mostTriggerEvent = MostTriggerEvent::parse(*this, line);
    if (mostTriggerEvent)
        return mostTriggerEvent;
    MostStatisticEvent * mostStatisticEvent = MostStatisticEvent::parse(*this, line);
    if (mostStatisticEvent)
        return mostStatisticEvent;
    MostStatisticExtendedEvent * mostStatisticExtendedEvent = MostStatisticExtendedEvent::parse(*this, line);
    if (mostStatisticExtendedEvent)
        return mostStatisticExtendedEvent;
    MostTxLight * mostTxLight = MostTxLight::parse(*this, line);
    if (mostTxLight)
        return mostTxLight;
    MostStressEvent * mostStressEvent = MostStressEvent::parse(*this, line);
    if (mostStressEvent)
        return mostStressEvent;
    Most25AllocTable * most25AllocTable = Most25AllocTable::parse(*this, line);
    if (most25AllocTable)
        return most25AllocTable;
    Most150ControlMessage * most150ControlMessage = Most150ControlMessage::parse(*this, line);
    if (most150ControlMessage)
        return most150ControlMessage;
    Most150ControlMessageFragment * most150ControlMessageFragment = Most150ControlMessageFragment::parse(*this, line);
    if (most150ControlMessageFragment)
        return most150ControlMessageFragment;
    Most150Packet * most150Packet = Most150Packet::parse(*this, line);
    if (most150Packet)
        return most150Packet;
    Most150PacketFragment * most150PacketFragment = Most150PacketFragment::parse(*this, line);
    if (most150PacketFragment)
        return most150PacketFragment;
    MostEthernetPacket * mostEthernetPacket = MostEthernetPacket::parse(*this, line);
    if (mostEthernetPacket)
        return mostEthernetPacket;
    MostEthernetPacketFragment * mostEthernetPacketFragment = MostEthernetPacketFragment::parse(*this, line);
    if (mostEthernetPacketFragment)
        return mostEthernetPacketFragment;
    MostSystemEvent * mostSystemEvent = MostSystemEvent::parse(*this, line);
    if (mostSystemEvent)
        return mostSystemEvent;
    Most150AllocTable * most150AllocTable = Most150AllocTable::parse(*this, line);
    if (most150AllocTable)
        return most150AllocTable;
    Most50ControlMessage * most50ControlMessage = Most50ControlMessage::parse(*this, line);
    if (most50ControlMessage)
        return most50ControlMessage;
    Most50Packet * most50Packet = Most50Packet::parse(*this, line);
    if (most50Packet)
        return most50Packet;
    MostEcl * mostEcl = MostEcl::parse(*this, line);
    if (mostEcl)
        return mostEcl;

    /* TP/Diagnostics Events */
    TpDiagPrefix * tpDiagPrefix = TpDiagPrefix::parse(*this, line);
    if (tpDiagPrefix)
        return tpDiagPrefix;
    TpDiagSingleFrame * tpDiagSingleFrame = TpDiagSingleFrame::parse(*this, line);
    if (tpDiagSingleFrame)
        return tpDiagSingleFrame;
    TpDiagFirstFrame * tpDiagFirstFrame = TpDiagFirstFrame::parse(*this, line);
    if (tpDiagFirstFrame)
        return tpDiagFirstFrame;
    TpDiagConsecutiveFrame * tpDiagConsecutiveFrame = TpDiagConsecutiveFrame::parse(*this, line);
    if (tpDiagConsecutiveFrame)
        return tpDiagConsecutiveFrame;
    TpDiagFlowControlFrame * tpDiagFlowControlFrame = TpDiagFlowControlFrame::parse(*this, line);
    if (tpDiagFlowControlFrame)
        return tpDiagFlowControlFrame;
    TpDiagRequest * tpDiagRequest = TpDiagRequest::parse(*this, line);
    if (tpDiagRequest)
        return tpDiagRequest;

    FileComment * fileComment = FileComment::parse(*this, line);
    if (fileComment)
        return fileComment;

    return nullptr;
}

}
}
