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

/* File */
#include "FileDate.h"
#include "FileBaseTimestamps.h"
#include "FileInternalEventsLogged.h"
#include "FileVersion.h"
#include "FileSplitInformation.h"
#include "FileComment.h"

/* CAN Events */
#include "CanMessageEvent.h"
#include "CanExtendedMessageEvent.h"
#include "CanRemoteFrameEvent.h"
#include "CanErrorFrame.h"
#include "CanBusStatisticsEvent.h"
#include "CanErrorEvent.h"
#include "CanOverloadFrameEvent.h"

/* CAN FD Events */
#include "CanFdMessageEvent.h"
#include "CanFdExtendedMessageEvent.h"
#include "CanFdErrorFrame.h"
// CAN FD Bus Statistics Event
// CAN FD Overload Frame

/* Log and Trigger Events */
#include "LogTriggerEvent.h"
#include "LogDirectStartEvent.h"
#include "LogDirectStopEvent.h"
#include "BeginTriggerblockEvent.h"
#include "EndTriggerblockEvent.h"

/* Environment Variables */
#include "EnvironmentVariablesEvent.h"

/* System Variables */
#include "SystemVariablesEvent.h"

/* Macros Signal Events */
#include "MacroSignalEvent.h"

/* GPS events */
#include "GpsEvent.h"

/* Comment events */
#include "CommentEvent.h"

/* Global market events */
#include "GlobalMarkerEvent.h"

/* Ethernet Events */
#include "EthernetPacket.h"
#include "EthernetStatus.h"
#include "EthernetRxError.h"

/* AFDX Events */
#include "AfdxPacket.h"

/* FlexRay Events (Old Format) */
#include "FlexRayOldMessageEvent.h"
#include "FlexRayOldStartCycleEvent.h"

/* FlexRay Events (New Format) */
#include "FlexRayMessageEvent.h"
#include "FlexRayStartCycleEvent.h"
#include "FlexRayStatusEvent.h"
#include "FlexRayErrorEvent.h"

/* K-Line Events */
#include "KLineByteEvent.h"
#include "KLineMessageEvent.h"

/* LIN Events */
#include "LinMessage.h"

/* LIN Error Events */
#include "LinTransmissionError.h"
#include "LinReceiveError.h"
#include "LinSyncError.h"
#include "LinChecksumError.h"
#include "LinSpikeEvent.h"
#include "LinDominantSignal.h"

/* LIN Info Events */
#include "LinBaudrate.h"
#include "LinDlcInfo.h"
#include "LinChecksumInfo.h"
#include "LinSchedulerModeChange.h"
#include "LinSlaveTimeout.h"
#include "LinEventTriggeredFrameInfo.h"
#include "LinStatisticInfo.h"
#include "LinShortOrSlowResponse.h"
#include "LinDisturbanceEvent.h"

/* LIN Sleep/Wakeup Events */
#include "LinSleepMode.h"
#include "LinWakeupFrame.h"
#include "LinUnexpectedWakeup.h"

/* MOST Events */
#include "Most25ControlMessageNodeMode.h"
#include "Most25ControlMessageSpyMode.h"
#include "Most25Packet.h"
#include "MostLightLockEvent.h"
#include "MostSpecialRegisterEvent.h"
#include "MostCommonRegisterEvent.h"
#include "MostHwModeEvent.h"
#include "MostNetStateEvent.h"
#include "MostDataLostEvent.h"
#include "MostTriggerEvent.h"
#include "MostStatisticEvent.h"
#include "MostStatisticExtendedEvent.h"
#include "MostTxLight.h"
#include "MostStressEvent.h"
#include "Most25AllocTable.h"
#include "Most150ControlMessage.h"
#include "Most150ControlMessageFragment.h"
#include "Most150Packet.h"
#include "Most150PacketFragment.h"
#include "MostEthernetPacket.h"
#include "MostEthernetPacketFragment.h"
#include "MostSystemEvent.h"
#include "Most150AllocTable.h"
#include "Most50ControlMessage.h"
#include "Most50Packet.h"
#include "MostEcl.h"

/* TP/Diagnostics Events */
#include "TpDiagPrefix.h"
#include "TpDiagSingleFrame.h"
#include "TpDiagFirstFrame.h"
#include "TpDiagConsecutiveFrame.h"
#include "TpDiagFlowControlFrame.h"
#include "TpDiagRequest.h"
