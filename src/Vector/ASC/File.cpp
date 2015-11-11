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
    version(Version::Ver_7_5),
    base(16),
    file(),
    scanner(nullptr)
{
}

File::~File()
{
    delete scanner;
    scanner = nullptr;
}

void File::open(const char * filename)
{
    switch(openMode) {
    case OpenMode::Read:
        /* open file for reading */
        file.open(filename, std::ios_base::in);

        /* create scanner */
        delete scanner;
        try {
            scanner = new ascFlexLexer(&file);
        }
        catch(std::bad_alloc & ba)
        {
            std::cerr << "Failed to allocate scanner: " << ba.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        break;
    case OpenMode::Write:
        /* open file for writing */
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
    /* delete scanner */
    delete scanner;
    scanner = nullptr;

    /* close file */
    file.close();
}

bool File::eof()
{
    return file.eof();
}

Event * File::read()
{
    /* scan line */
    int eventType = scanner->yylex();
    std::string line = scanner->YYText();

    /* remove windows line ending */
    if (line.back() == '\r')
        line.pop_back();

    switch(eventType) {
    case Event::EventType::Unknown:
        std::cerr << line << std::endl;
        break;

    /* File */
    case Event::EventType::FileDate:
        return FileDate::parse(*this, line);
    case Event::EventType::FileBaseTimestamps:
        {
            FileBaseTimestamps * fileBaseTimestamps = FileBaseTimestamps::parse(*this, line);
            if (fileBaseTimestamps) {
                base = static_cast<uint8_t>(fileBaseTimestamps->base);
            }
            return fileBaseTimestamps;
        }
    case Event::EventType::FileInternalEventsLogged:
        return FileInternalEventsLogged::parse(*this, line);
    case Event::EventType::FileVersion:
        {
            FileVersion * fileVersion = FileVersion::parse(*this, line);
            if (fileVersion) {
                version = (fileVersion->versionMajor << 8) | (fileVersion->versionMinor);
            }
            return fileVersion;
        }
    case Event::EventType::FileSplitInformation:
        return FileSplitInformation::parse(*this, line);
    case Event::EventType::FileComment:
        return FileComment::parse(*this, line);

    /* CAN Events */
    case Event::EventType::CanMessageEvent:
        return CanMessageEvent::parse(*this, line);
    case Event::EventType::CanExtendedMessageEvent:
        return CanExtendedMessageEvent::parse(*this, line);
    case Event::EventType::CanRemoteFrameEvent:
        return CanRemoteFrameEvent::parse(*this, line);
    case Event::EventType::CanErrorFrame:
        return CanErrorFrame::parse(*this, line);
    case Event::EventType::CanBusStatisticsEvent:
        return CanBusStatisticsEvent::parse(*this, line);
    case Event::EventType::CanErrorEvent:
        return CanErrorEvent::parse(*this, line);
    case Event::EventType::CanOverloadFrameEvent:
        return CanOverloadFrameEvent::parse(*this, line);

    /* CAN FD Events */
    case Event::EventType::CanFdMessageEvent:
        return CanFdMessageEvent::parse(*this, line);
    case Event::EventType::CanFdExtendedMessageEvent:
        return CanFdExtendedMessageEvent::parse(*this, line);
    case Event::EventType::CanFdErrorFrame:
        return CanFdErrorFrame::parse(*this, line);
    // CAN FD Bus Statistics Event
    // CAN FD Overload Frame

    /* Log and Trigger Events */
    case Event::EventType::LogTriggerEvent:
        return LogTriggerEvent::parse(*this, line);
    case Event::EventType::LogDirectStartEvent:
        return LogDirectStartEvent::parse(*this, line);
    case Event::EventType::LogDirectStopEvent:
        return LogDirectStopEvent::parse(*this, line);
    case Event::EventType::BeginTriggerblockEvent:
        return BeginTriggerblockEvent::parse(*this, line);
    case Event::EventType::EndTriggerblockEvent:
        return EndTriggerblockEvent::parse(*this, line);

    /* Environment Variables */
    case Event::EventType::EnvironmentVariablesEvent:
        return EnvironmentVariablesEvent::parse(*this, line);

    /* System Variables */
    case Event::EventType::SystemVariablesEvent:
        return SystemVariablesEvent::parse(*this, line);

    /* Macros Signal Events */
    case Event::EventType::MacroSignalEvent:
        return MacroSignalEvent::parse(*this, line);

    /* GPS events */
    case Event::EventType::GpsEvent:
        return GpsEvent::parse(*this, line);

    /* Comment events */
    case Event::EventType::CommentEvent:
        return CommentEvent::parse(*this, line);

    /* Global market events */
    case Event::EventType::GlobalMarkerEvent:
        return GlobalMarkerEvent::parse(*this, line);

    /* Ethernet Events */
    case Event::EventType::EthernetPacket:
        return EthernetPacket::parse(*this, line);
    case Event::EventType::EthernetStatus:
        return EthernetStatus::parse(*this, line);
    case Event::EventType::EthernetRxError:
        return EthernetRxError::parse(*this, line);

    /* AFDX Events */
    case Event::EventType::AfdxPacket:
        return AfdxPacket::parse(*this, line);

    /* FlexRay Events (Old Format) */
    case Event::EventType::FlexRayOldMessageEvent:
        return FlexRayOldMessageEvent::parse(*this, line);
    case Event::EventType::FlexRayOldStartCycleEvent:
        return FlexRayOldStartCycleEvent::parse(*this, line);

    /* FlexRay Events (New Format) */
    case Event::EventType::FlexRayMessageEvent:
        return FlexRayMessageEvent::parse(*this, line);
    case Event::EventType::FlexRayStartCycleEvent:
        return FlexRayStartCycleEvent::parse(*this, line);
    case Event::EventType::FlexRayStatusEvent:
        return FlexRayStatusEvent::parse(*this, line);
    case Event::EventType::FlexRayErrorEvent:
        return FlexRayErrorEvent::parse(*this, line);

    /* K-Line Events */
    case Event::EventType::KLineByteEvent:
        return KLineByteEvent::parse(*this, line);
    case Event::EventType::KLineMessageEvent:
        return KLineMessageEvent::parse(*this, line);

    /* LIN Events */
    case Event::EventType::LinMessage:
        return LinMessage::parse(*this, line);

    /* LIN Error Events */
    case Event::EventType::LinTransmissionError:
        return LinTransmissionError::parse(*this, line);
    case Event::EventType::LinReceiveError:
        return LinReceiveError::parse(*this, line);
    case Event::EventType::LinSyncError:
        return LinSyncError::parse(*this, line);
    case Event::EventType::LinChecksumError:
        return LinChecksumError::parse(*this, line);
    case Event::EventType::LinSpikeEvent:
        return LinSpikeEvent::parse(*this, line);
    case Event::EventType::LinDominantSignal:
        return LinDominantSignal::parse(*this, line);

    /* LIN Info Events */
    case Event::EventType::LinBaudrate:
        return LinBaudrate::parse(*this, line);
    case Event::EventType::LinDlcInfo:
        return LinDlcInfo::parse(*this, line);
    case Event::EventType::LinChecksumInfo:
        return LinChecksumInfo::parse(*this, line);
    case Event::EventType::LinSchedulerModeChange:
        return LinSchedulerModeChange::parse(*this, line);
    case Event::EventType::LinSlaveTimeout:
        return LinSlaveTimeout::parse(*this, line);
    case Event::EventType::LinEventTriggeredFrameInfo:
        return LinEventTriggeredFrameInfo::parse(*this, line);
    case Event::EventType::LinStatisticInfo:
        return LinStatisticInfo::parse(*this, line);
    case Event::EventType::LinShortOrSlowResponse:
        return LinShortOrSlowResponse::parse(*this, line);
    case Event::EventType::LinDisturbanceEvent:
        return LinDisturbanceEvent::parse(*this, line);

    /* LIN Sleep/Wakeup Events */
    case Event::EventType::LinSleepMode:
        return LinSleepMode::parse(*this, line);
    case Event::EventType::LinWakeupFrame:
        return LinWakeupFrame::parse(*this, line);
    case Event::EventType::LinUnexpectedWakeup:
        return LinUnexpectedWakeup::parse(*this, line);

    /* MOST Events */
    case Event::EventType::Most25ControlMessageNodeMode:
        return Most25ControlMessageNodeMode::parse(*this, line);
    case Event::EventType::Most25ControlMessageSpyMode:
        return Most25ControlMessageSpyMode::parse(*this, line);
    case Event::EventType::Most25Packet:
        return Most25Packet::parse(*this, line);
    case Event::EventType::MostLightLockEvent:
        return MostLightLockEvent::parse(*this, line);
    case Event::EventType::MostSpecialRegisterEvent:
        return MostSpecialRegisterEvent::parse(*this, line);
    case Event::EventType::MostCommonRegisterEvent:
        return MostCommonRegisterEvent::parse(*this, line);
    case Event::EventType::MostHwModeEvent:
        return MostHwModeEvent::parse(*this, line);
    case Event::EventType::MostNetStateEvent:
        return MostNetStateEvent::parse(*this, line);
    case Event::EventType::MostDataLostEvent:
        return MostDataLostEvent::parse(*this, line);
    case Event::EventType::MostTriggerEvent:
        return MostTriggerEvent::parse(*this, line);
    case Event::EventType::MostStatisticEvent:
        return MostStatisticEvent::parse(*this, line);
    case Event::EventType::MostStatisticExtendedEvent:
        return MostStatisticExtendedEvent::parse(*this, line);
    case Event::EventType::MostTxLight:
        return MostTxLight::parse(*this, line);
    case Event::EventType::MostStressEvent:
        return MostStressEvent::parse(*this, line);
    case Event::EventType::Most25AllocTable:
        return Most25AllocTable::parse(*this, line);
    case Event::EventType::Most150ControlMessage:
        return Most150ControlMessage::parse(*this, line);
    case Event::EventType::Most150ControlMessageFragment:
        return Most150ControlMessageFragment::parse(*this, line);
    case Event::EventType::Most150Packet:
        return Most150Packet::parse(*this, line);
    case Event::EventType::Most150PacketFragment:
        return Most150PacketFragment::parse(*this, line);
    case Event::EventType::MostEthernetPacket:
        return MostEthernetPacket::parse(*this, line);
    case Event::EventType::MostEthernetPacketFragment:
        return MostEthernetPacketFragment::parse(*this, line);
    case Event::EventType::MostSystemEvent:
        return MostSystemEvent::parse(*this, line);
    case Event::EventType::Most150AllocTable:
        return Most150AllocTable::parse(*this, line);
    case Event::EventType::Most50ControlMessage:
        return Most50ControlMessage::parse(*this, line);
    case Event::EventType::Most50Packet:
        return Most50Packet::parse(*this, line);
    case Event::EventType::MostEcl:
        return MostEcl::parse(*this, line);

    /* TP/Diagnostics Events */
    case Event::EventType::TpDiagPrefix:
        return TpDiagPrefix::parse(*this, line);
    case Event::EventType::TpDiagSingleFrame:
        return TpDiagSingleFrame::parse(*this, line);
    case Event::EventType::TpDiagFirstFrame:
        return TpDiagFirstFrame::parse(*this, line);
    case Event::EventType::TpDiagConsecutiveFrame:
        return TpDiagConsecutiveFrame::parse(*this, line);
    case Event::EventType::TpDiagFlowControlFrame:
        return TpDiagFlowControlFrame::parse(*this, line);
    case Event::EventType::TpDiagRequest:
        return TpDiagRequest::parse(*this, line);

    case Event::EventType::Default:
    default:
        std::cerr << line << std::endl;
        break;
    }

    return nullptr;
}

}
}
