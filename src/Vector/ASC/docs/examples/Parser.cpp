#include <iostream>
#include <fstream>

#include "Vector/ASC.h"

void showUnknown(Vector::ASC::Unknown * unknown) {
}

void showFileDate(Vector::ASC::FileDate * fileDate) {
}

void showFileBaseTimestamps(Vector::ASC::FileBaseTimestamps * fileBaseTimestamps) {
}

void showFileInternalEventsLogged(Vector::ASC::FileInternalEventsLogged * fileInternalEventsLogged) {
}

void showFileVersion(Vector::ASC::FileVersion * fileVersion) {
}

void showFileSplitInformation(Vector::ASC::FileSplitInformation * fileSplitInformation) {
}

void showFileComment(Vector::ASC::FileComment * fileComment) {
}

// @todo the further event routines are yet missing...

int main(int argc, char * argv[]) {
    if (argc != 2) {
        std::cout << "Parser <filename.blf>" << std::endl;
        return -1;
    }

    Vector::ASC::File file;
    file.open(argv[1]);

    while (!file.eof()) {
        Vector::ASC::Event * event = file.read();
        if (event == nullptr)
            continue;

        switch (event->eventType) {
        case Vector::ASC::Event::EventType::Default:
            break;

        case Vector::ASC::Event::EventType::Unknown:
            showUnknown(reinterpret_cast<Vector::ASC::Unknown *>(event));
            break;

        case Vector::ASC::Event::EventType::FileDate:
            showFileDate(reinterpret_cast<Vector::ASC::FileDate *>(event));
            break;

        case Vector::ASC::Event::EventType::FileBaseTimestamps:
            showFileBaseTimestamps(reinterpret_cast<Vector::ASC::FileBaseTimestamps *>(event));
            break;

        case Vector::ASC::Event::EventType::FileInternalEventsLogged:
            showFileInternalEventsLogged(reinterpret_cast<Vector::ASC::FileInternalEventsLogged *>(event));
            break;

        case Vector::ASC::Event::EventType::FileVersion:
            showFileVersion(reinterpret_cast<Vector::ASC::FileVersion *>(event));
            break;

        case Vector::ASC::Event::EventType::FileSplitInformation:
            showFileSplitInformation(reinterpret_cast<Vector::ASC::FileSplitInformation *>(event));
            break;

        case Vector::ASC::Event::EventType::FileComment:
            showFileComment(reinterpret_cast<Vector::ASC::FileComment *>(event));
            break;

        case Vector::ASC::Event::EventType::CanMessage:
            break;

        case Vector::ASC::Event::EventType::CanExtendedMessage:
            break;

        case Vector::ASC::Event::EventType::CanRemoteFrame:
            break;

        case Vector::ASC::Event::EventType::CanErrorFrame:
            break;

        case Vector::ASC::Event::EventType::CanBusStatistics:
            break;

        case Vector::ASC::Event::EventType::CanError:
            break;

        case Vector::ASC::Event::EventType::CanOverloadFrame:
            break;

        case Vector::ASC::Event::EventType::CanFdMessage:
            break;

        case Vector::ASC::Event::EventType::CanFdExtendedMessage:
            break;

        case Vector::ASC::Event::EventType::CanFdErrorFrame:
            break;

        // CAN FD Bus Statistics
        // CAN FD Overload Frame

        case Vector::ASC::Event::EventType::LogTrigger:
            break;

        case Vector::ASC::Event::EventType::LogDirectStart:
            break;

        case Vector::ASC::Event::EventType::LogDirectStop:
            break;

        case Vector::ASC::Event::EventType::BeginTriggerblock:
            break;

        case Vector::ASC::Event::EventType::EndTriggerblock:
            break;

        case Vector::ASC::Event::EventType::EnvironmentVariables:
            break;

        case Vector::ASC::Event::EventType::SystemVariables:
            break;

        case Vector::ASC::Event::EventType::MacroSignal:
            break;

        case Vector::ASC::Event::EventType::Gps:
            break;

        case Vector::ASC::Event::EventType::Comment:
            break;

        case Vector::ASC::Event::EventType::GlobalMarker:
            break;

        case Vector::ASC::Event::EventType::EthernetPacket:
            break;

        case Vector::ASC::Event::EventType::EthernetStatus:
            break;

        case Vector::ASC::Event::EventType::EthernetRxError:
            break;

        case Vector::ASC::Event::EventType::AfdxPacket:
            break;

        case Vector::ASC::Event::EventType::FlexRayOldMessage:
            break;

        case Vector::ASC::Event::EventType::FlexRayOldStartCycle:
            break;

        case Vector::ASC::Event::EventType::FlexRayMessage:
            break;

        case Vector::ASC::Event::EventType::FlexRayStartCycle:
            break;

        case Vector::ASC::Event::EventType::FlexRayStatus:
            break;

        case Vector::ASC::Event::EventType::FlexRayError:
            break;

        case Vector::ASC::Event::EventType::KLineByte:
            break;

        case Vector::ASC::Event::EventType::KLineMessage:
            break;

        case Vector::ASC::Event::EventType::LinMessage:
            break;

        case Vector::ASC::Event::EventType::LinTransmissionError:
            break;

        case Vector::ASC::Event::EventType::LinReceiveError:
            break;

        case Vector::ASC::Event::EventType::LinSyncError:
            break;

        case Vector::ASC::Event::EventType::LinChecksumError:
            break;

        case Vector::ASC::Event::EventType::LinSpike:
            break;

        case Vector::ASC::Event::EventType::LinDominantSignal:
            break;

        case Vector::ASC::Event::EventType::LinBaudrate:
            break;

        case Vector::ASC::Event::EventType::LinDlcInfo:
            break;

        case Vector::ASC::Event::EventType::LinChecksumInfo:
            break;

        case Vector::ASC::Event::EventType::LinSchedulerModeChange:
            break;

        case Vector::ASC::Event::EventType::LinSlaveTimeout:
            break;

        case Vector::ASC::Event::EventType::LinEventTriggeredFrameInfo:
            break;

        case Vector::ASC::Event::EventType::LinStatisticInfo:
            break;

        case Vector::ASC::Event::EventType::LinShortOrSlowResponse:
            break;

        case Vector::ASC::Event::EventType::LinDisturbance:
            break;

        case Vector::ASC::Event::EventType::LinSleepMode:
            break;

        case Vector::ASC::Event::EventType::LinWakeupFrame:
            break;

        case Vector::ASC::Event::EventType::LinUnexpectedWakeup:
            break;

        case Vector::ASC::Event::EventType::Most25ControlMessageNodeMode:
            break;

        case Vector::ASC::Event::EventType::Most25ControlMessageSpyMode:
            break;

        case Vector::ASC::Event::EventType::Most25Packet:
            break;

        case Vector::ASC::Event::EventType::MostLightLock:
            break;

        case Vector::ASC::Event::EventType::MostSpecialRegister:
            break;

        case Vector::ASC::Event::EventType::MostCommonRegister:
            break;

        case Vector::ASC::Event::EventType::MostHwMode:
            break;

        case Vector::ASC::Event::EventType::MostNetState:
            break;

        case Vector::ASC::Event::EventType::MostDataLost:
            break;

        case Vector::ASC::Event::EventType::MostTrigger:
            break;

        case Vector::ASC::Event::EventType::MostStatistic:
            break;

        case Vector::ASC::Event::EventType::MostStatisticExtended:
            break;

        case Vector::ASC::Event::EventType::MostTxLight:
            break;

        case Vector::ASC::Event::EventType::MostStress:
            break;

        case Vector::ASC::Event::EventType::Most25AllocTable:
            break;

        case Vector::ASC::Event::EventType::Most150ControlMessage:
            break;

        case Vector::ASC::Event::EventType::Most150ControlMessageFragment:
            break;

        case Vector::ASC::Event::EventType::Most150Packet:
            break;

        case Vector::ASC::Event::EventType::Most150PacketFragment:
            break;

        case Vector::ASC::Event::EventType::MostEthernetPacket:
            break;

        case Vector::ASC::Event::EventType::MostEthernetPacketFragment:
            break;

        case Vector::ASC::Event::EventType::MostSystem:
            break;

        case Vector::ASC::Event::EventType::Most150AllocTable:
            break;

        case Vector::ASC::Event::EventType::Most50ControlMessage:
            break;

        case Vector::ASC::Event::EventType::Most50Packet:
            break;

        case Vector::ASC::Event::EventType::MostEcl:
            break;

        case Vector::ASC::Event::EventType::TpSingleFrame:
            break;

        case Vector::ASC::Event::EventType::TpFirstFrame:
            break;

        case Vector::ASC::Event::EventType::TpConsecutiveFrame:
            break;

        case Vector::ASC::Event::EventType::TpFlowControlFrame:
            break;

        case Vector::ASC::Event::EventType::DiagRequest:
            break;

        case Vector::ASC::Event::EventType::StartOfMeasurement:
            break;
        };

        /* delete event */
        delete event;
    }

    std::cout << "End of file." << std::endl;

    file.close();

    return 0;
}
