#define BOOST_TEST_MODULE Events
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iterator>
#include <string>

#include <Vector/ASC.h>

static bool isEqual(double a, double b)
{
    return ((a-b) < 0.000001) && ((b-a) < 0.000001);
}

/* File */
BOOST_AUTO_TEST_CASE(FileDate)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileDate.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileDate * fileDate;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);
    fileDate = static_cast<Vector::ASC::FileDate *>(event);
    BOOST_CHECK(fileDate->date.tm_wday == 3);
    BOOST_CHECK(fileDate->date.tm_mon == 5);
    BOOST_CHECK(fileDate->date.tm_mday == 11);
    BOOST_CHECK(fileDate->date.tm_hour == 11);
    BOOST_CHECK(fileDate->date.tm_min == 37);
    BOOST_CHECK(fileDate->date.tm_sec == 33);
    BOOST_CHECK(fileDate->date.tm_year == (2008 - 1900));
    BOOST_CHECK(fileDate->language == Vector::ASC::File::Language::En);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);
    fileDate = static_cast<Vector::ASC::FileDate *>(event);
    BOOST_CHECK(fileDate->date.tm_wday == 2);
    BOOST_CHECK(fileDate->date.tm_mon == 2);
    BOOST_CHECK(fileDate->date.tm_mday == 13);
    BOOST_CHECK(fileDate->date.tm_hour == 11);
    BOOST_CHECK(fileDate->date.tm_min == 58);
    BOOST_CHECK(fileDate->date.tm_sec == 02);
    BOOST_CHECK(fileDate->date.tm_year == (2007 - 1900));
    BOOST_CHECK(fileDate->language == Vector::ASC::File::Language::De);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileBaseTimestamps)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileBaseTimestamps.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileBaseTimestamps * fileBaseTimestamps;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);
    fileBaseTimestamps = static_cast<Vector::ASC::FileBaseTimestamps *>(event);
    BOOST_CHECK(fileBaseTimestamps->base == Vector::ASC::File::Base::Hex);
    BOOST_CHECK(fileBaseTimestamps->timestamps == Vector::ASC::File::Timestamps::Relative);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileInternalEventsLogged)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileInternalEventsLogged.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileInternalEventsLogged * fileInternalEventsLogged;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileInternalEventsLogged);
    fileInternalEventsLogged = static_cast<Vector::ASC::FileInternalEventsLogged *>(event);
    BOOST_CHECK(fileInternalEventsLogged->internalEventsLogged == true);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileInternalEventsLogged);
    fileInternalEventsLogged = static_cast<Vector::ASC::FileInternalEventsLogged *>(event);
    BOOST_CHECK(fileInternalEventsLogged->internalEventsLogged == false);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileVersion)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileVersion.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileVersion * fileVersion;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);
    fileVersion = static_cast<Vector::ASC::FileVersion *>(event);
    BOOST_CHECK(fileVersion->versionMajor == 7);
    BOOST_CHECK(fileVersion->versionMinor == 1);
    BOOST_CHECK(fileVersion->versionPatch == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileSplitInformation)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileSplitInformation.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileSplitInformation * fileSplitInformation;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileSplitInformation);
    fileSplitInformation = static_cast<Vector::ASC::FileSplitInformation *>(event);
    BOOST_CHECK(fileSplitInformation->time == 60.0000);
    BOOST_CHECK(fileSplitInformation->fileName == "Inc_L1.asc");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileComment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileComment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileComment * fileComment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileComment);
    fileComment = static_cast<Vector::ASC::FileComment *>(event);
    BOOST_CHECK(fileComment->comment == " comment");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN Events */
BOOST_AUTO_TEST_CASE(CanMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanMessage * canMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanMessage);
    canMessage = static_cast<Vector::ASC::CanMessage *>(event);
    BOOST_CHECK(isEqual(canMessage->time, 0.003040));
    BOOST_CHECK(canMessage->channel == 1);
    BOOST_CHECK(canMessage->id == 0x123);
    BOOST_CHECK(canMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canMessage->dlc == 2);
    BOOST_REQUIRE(canMessage->data.size() == 2);
    BOOST_CHECK(canMessage->data[0] == 0x00);
    BOOST_CHECK(canMessage->data[1] == 0x00);
    BOOST_CHECK(canMessage->messageDuration == 768000);
    BOOST_CHECK(canMessage->messageLength == 67);
    BOOST_CHECK(canMessage->messageId == 291);
    BOOST_CHECK(canMessage->messageFlags.te == false);
    BOOST_CHECK(canMessage->messageFlags.wu == false);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanMessage);
    canMessage = static_cast<Vector::ASC::CanMessage *>(event);
    BOOST_CHECK(isEqual(canMessage->time, 2.500900));
    BOOST_CHECK(canMessage->channel == 1);
    BOOST_CHECK(canMessage->id == 0x64);
    BOOST_CHECK(canMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canMessage->dlc == 8);
    BOOST_REQUIRE(canMessage->data.size() == 8);
    BOOST_CHECK(canMessage->data[0] == 0x00);
    BOOST_CHECK(canMessage->data[1] == 0x01);
    BOOST_CHECK(canMessage->data[2] == 0x02);
    BOOST_CHECK(canMessage->data[3] == 0x03);
    BOOST_CHECK(canMessage->data[4] == 0x04);
    BOOST_CHECK(canMessage->data[5] == 0x05);
    BOOST_CHECK(canMessage->data[6] == 0x06);
    BOOST_CHECK(canMessage->data[7] == 0x07);
    BOOST_CHECK(canMessage->messageDuration == 0);
    BOOST_CHECK(canMessage->messageLength == 0);
    BOOST_CHECK(canMessage->messageId == 0);
    BOOST_CHECK(canMessage->messageFlags.te == false);
    BOOST_CHECK(canMessage->messageFlags.wu == false);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanMessage);
    canMessage = static_cast<Vector::ASC::CanMessage *>(event);
    BOOST_CHECK(isEqual(canMessage->time, 1.047413));
    BOOST_CHECK(canMessage->channel == 1);
    BOOST_CHECK(canMessage->id == 1792);
    BOOST_CHECK(canMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canMessage->dlc == 8);
    BOOST_REQUIRE(canMessage->data.size() == 8);
    BOOST_CHECK(canMessage->data[0] == 2);
    BOOST_CHECK(canMessage->data[1] == 16);
    BOOST_CHECK(canMessage->data[2] == 0);
    BOOST_CHECK(canMessage->data[3] == 0);
    BOOST_CHECK(canMessage->data[4] == 0);
    BOOST_CHECK(canMessage->data[5] == 0);
    BOOST_CHECK(canMessage->data[6] == 0);
    BOOST_CHECK(canMessage->data[7] == 0);
    BOOST_CHECK(canMessage->messageDuration == 0);
    BOOST_CHECK(canMessage->messageLength == 0);
    BOOST_CHECK(canMessage->messageId == 1792);
    BOOST_CHECK(canMessage->messageFlags.te == false);
    BOOST_CHECK(canMessage->messageFlags.wu == false);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanExtendedMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanExtendedMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanExtendedMessage * canExtendedMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanExtendedMessage);
    canExtendedMessage = static_cast<Vector::ASC::CanExtendedMessage *>(event);
    BOOST_CHECK(isEqual(canExtendedMessage->time, 4.876870));
    BOOST_CHECK(canExtendedMessage->channel == 1);
    BOOST_CHECK(canExtendedMessage->id == 0x54C5638);
    BOOST_CHECK(canExtendedMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canExtendedMessage->dlc == 8);
    BOOST_REQUIRE(canExtendedMessage->data.size() == 8);
    BOOST_CHECK(canExtendedMessage->data[0] == 0x00);
    BOOST_CHECK(canExtendedMessage->data[1] == 0x00);
    BOOST_CHECK(canExtendedMessage->data[2] == 0x00);
    BOOST_CHECK(canExtendedMessage->data[3] == 0x00);
    BOOST_CHECK(canExtendedMessage->data[4] == 0x00);
    BOOST_CHECK(canExtendedMessage->data[5] == 0x00);
    BOOST_CHECK(canExtendedMessage->data[6] == 0x00);
    BOOST_CHECK(canExtendedMessage->data[7] == 0x00);
    BOOST_CHECK(canExtendedMessage->messageDuration == 1704000);
    BOOST_CHECK(canExtendedMessage->messageLength == 145);
    BOOST_CHECK(canExtendedMessage->messageId == 88888888);
    BOOST_CHECK(canExtendedMessage->messageFlags.te == false);
    BOOST_CHECK(canExtendedMessage->messageFlags.wu == false);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanExtendedMessage);
    canExtendedMessage = static_cast<Vector::ASC::CanExtendedMessage *>(event);
    BOOST_CHECK(isEqual(canExtendedMessage->time, 2.501000));
    BOOST_CHECK(canExtendedMessage->channel == 2);
    BOOST_CHECK(canExtendedMessage->id == 0xC8);
    BOOST_CHECK(canExtendedMessage->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(canExtendedMessage->dlc == 8);
    BOOST_REQUIRE(canExtendedMessage->data.size() == 8);
    BOOST_CHECK(canExtendedMessage->data[0] == 0x09);
    BOOST_CHECK(canExtendedMessage->data[1] == 0x08);
    BOOST_CHECK(canExtendedMessage->data[2] == 0x07);
    BOOST_CHECK(canExtendedMessage->data[3] == 0x06);
    BOOST_CHECK(canExtendedMessage->data[4] == 0x05);
    BOOST_CHECK(canExtendedMessage->data[5] == 0x04);
    BOOST_CHECK(canExtendedMessage->data[6] == 0x03);
    BOOST_CHECK(canExtendedMessage->data[7] == 0x02);
    BOOST_CHECK(canExtendedMessage->messageDuration == 0);
    BOOST_CHECK(canExtendedMessage->messageLength == 0);
    BOOST_CHECK(canExtendedMessage->messageId == 0);
    BOOST_CHECK(canExtendedMessage->messageFlags.te == false);
    BOOST_CHECK(canExtendedMessage->messageFlags.wu == false);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanRemoteFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanRemoteFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanRemoteFrame * canRemoteFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanRemoteFrame);
    canRemoteFrame = static_cast<Vector::ASC::CanRemoteFrame *>(event);
    BOOST_CHECK(isEqual(canRemoteFrame->time, 2.501000));
    BOOST_CHECK(canRemoteFrame->channel == 1);
    BOOST_CHECK(canRemoteFrame->id == 0x200);
    BOOST_CHECK(canRemoteFrame->dir == Vector::ASC::Dir::Tx);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanErrorFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanErrorFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanErrorFrame * canErrorFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorFrame);
    canErrorFrame = static_cast<Vector::ASC::CanErrorFrame *>(event);
    BOOST_CHECK(isEqual(canErrorFrame->time, 1.592186));
    BOOST_CHECK(canErrorFrame->channel == 1);
    BOOST_CHECK(canErrorFrame->flags == 0x1);
    BOOST_CHECK(canErrorFrame->code == 0xA2);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorFrame);
    canErrorFrame = static_cast<Vector::ASC::CanErrorFrame *>(event);
    BOOST_CHECK(isEqual(canErrorFrame->time, 1.592186));
    BOOST_CHECK(canErrorFrame->channel == 2);
    BOOST_CHECK(canErrorFrame->flags == 0xe);
    BOOST_CHECK(canErrorFrame->codeExt == 0x20a2);
    BOOST_CHECK(canErrorFrame->code == 0x82);
    BOOST_CHECK(canErrorFrame->id == 0);
    BOOST_CHECK(canErrorFrame->dlc == 0);
    BOOST_CHECK(canErrorFrame->position == 5);
    BOOST_CHECK(canErrorFrame->length == 11300);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorFrame);
    canErrorFrame = static_cast<Vector::ASC::CanErrorFrame *>(event);
    BOOST_CHECK(isEqual(canErrorFrame->time, 2.501000));
    BOOST_CHECK(canErrorFrame->channel == 1);
    BOOST_CHECK(canErrorFrame->flags == 0x0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanBusStatistics)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanBusStatistics.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanBusStatistics * canBusStatistics;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanBusStatistics);
    canBusStatistics = static_cast<Vector::ASC::CanBusStatistics *>(event);
    BOOST_CHECK(isEqual(canBusStatistics->time, 1.010000));
    BOOST_CHECK(canBusStatistics->channel == 1);
    BOOST_CHECK(canBusStatistics->dataFrames == 1000);
    BOOST_CHECK(canBusStatistics->remoteFrames == 15);
    BOOST_CHECK(canBusStatistics->extendedDataFrames == 0);
    BOOST_CHECK(canBusStatistics->extendedRemoteFrames == 0);
    BOOST_CHECK(canBusStatistics->errorFrames == 0);
    BOOST_CHECK(canBusStatistics->overloadFrames == 0);
    BOOST_CHECK(isEqual(canBusStatistics->busload, 0.0));
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanError * canError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanError);
    canError = static_cast<Vector::ASC::CanError *>(event);
    BOOST_CHECK(isEqual(canError->time, 0.000600));
    BOOST_CHECK(canError->channel == 2);
    BOOST_CHECK(canError->error == Vector::ASC::Error::ChipStatusErrorActive);
    BOOST_CHECK(canError->txErr == 0);
    BOOST_CHECK(canError->rxErr == 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanError);
    canError = static_cast<Vector::ASC::CanError *>(event);
    BOOST_CHECK(isEqual(canError->time, 2.501000));
    BOOST_CHECK(canError->channel == 1);
    BOOST_CHECK(canError->error == Vector::ASC::Error::ChipStatusErrorActive);
    BOOST_CHECK(canError->txErr == 0);
    BOOST_CHECK(canError->rxErr == 1);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanOverloadFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanOverloadFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanOverloadFrame * canOverloadFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanOverloadFrame);
    canOverloadFrame = static_cast<Vector::ASC::CanOverloadFrame *>(event);
    BOOST_CHECK(isEqual(canOverloadFrame->time, 2.515800));
    BOOST_CHECK(canOverloadFrame->channel == 1);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN FD Events */
BOOST_AUTO_TEST_CASE(CanFdMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdMessage * canFdMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdMessage);
    canFdMessage = static_cast<Vector::ASC::CanFdMessage *>(event);
    BOOST_CHECK(isEqual(canFdMessage->time, 8.151536));
    BOOST_CHECK(canFdMessage->channel == 2);
    BOOST_CHECK(canFdMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canFdMessage->id == 0xc9);
    BOOST_CHECK(canFdMessage->symbolicName == "ABSdata_FD_64Byte");
    BOOST_CHECK(canFdMessage->brs == false);
    BOOST_CHECK(canFdMessage->esi == false);
    BOOST_CHECK(canFdMessage->dlc == 9);
    BOOST_CHECK(canFdMessage->dataLength == 12);
    BOOST_REQUIRE(canFdMessage->data.size() == 12);
    BOOST_CHECK(canFdMessage->data[0] == 0x29);
    BOOST_CHECK(canFdMessage->data[1] == 0x00);
    BOOST_CHECK(canFdMessage->data[2] == 0x00);
    BOOST_CHECK(canFdMessage->data[3] == 0x00);
    BOOST_CHECK(canFdMessage->data[4] == 0x0b);
    BOOST_CHECK(canFdMessage->data[5] == 0x2a);
    BOOST_CHECK(canFdMessage->data[6] == 0x00);
    BOOST_CHECK(canFdMessage->data[7] == 0x00);
    BOOST_CHECK(canFdMessage->data[8] == 0x00);
    BOOST_CHECK(canFdMessage->data[9] == 0x00);
    BOOST_CHECK(canFdMessage->data[10] == 0x00);
    BOOST_CHECK(canFdMessage->data[11] == 0x00);
    BOOST_CHECK(canFdMessage->messageDuration == 164000);
    BOOST_CHECK(canFdMessage->messageLength == 167);
    BOOST_CHECK(canFdMessage->flags == 121200);
    BOOST_CHECK(canFdMessage->crc == 0x7ca0);
    BOOST_CHECK(canFdMessage->bitTimingConfArb == 0x500a2041);
    BOOST_CHECK(canFdMessage->bitTimingConfData == 0x460a4841);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanFdExtendedMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdExtendedMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdExtendedMessage * canFdExtendedMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdExtendedMessage);
    canFdExtendedMessage = static_cast<Vector::ASC::CanFdExtendedMessage *>(event);
    BOOST_CHECK(isEqual(canFdExtendedMessage->time, 0.248166));
    BOOST_CHECK(canFdExtendedMessage->channel == 2);
    BOOST_CHECK(canFdExtendedMessage->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(canFdExtendedMessage->id == 0x1fffffff);
    BOOST_CHECK(canFdExtendedMessage->symbolicName == "");
    BOOST_CHECK(canFdExtendedMessage->brs == false);
    BOOST_CHECK(canFdExtendedMessage->esi == false);
    BOOST_CHECK(canFdExtendedMessage->dlc == 0xf);
    BOOST_CHECK(canFdExtendedMessage->dataLength == 64);
    BOOST_REQUIRE(canFdExtendedMessage->data.size() == 64);
    for(int i = 0; i < 64; ++i)
        BOOST_CHECK(canFdExtendedMessage->data[i] == i+1);
    BOOST_CHECK(canFdExtendedMessage->messageDuration == 1238000);
    BOOST_CHECK(canFdExtendedMessage->messageLength == 111);
    BOOST_CHECK(canFdExtendedMessage->flags == 101000);
    BOOST_CHECK(canFdExtendedMessage->crc == 0x46518);
    BOOST_CHECK(canFdExtendedMessage->bitTimingConfArb == 0x46500250);
    BOOST_CHECK(canFdExtendedMessage->bitTimingConfData == 0x46280250);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanFdErrorFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdErrorFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdErrorFrame * canFdErrorFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdErrorFrame);
    canFdErrorFrame = static_cast<Vector::ASC::CanFdErrorFrame *>(event);
    BOOST_CHECK(isEqual(canFdErrorFrame->time, 3.923364));
    BOOST_CHECK(canFdErrorFrame->channel == 2);
    BOOST_CHECK(canFdErrorFrame->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canFdErrorFrame->errorText == "Not Acknowledge error, dominant error flag");
    BOOST_CHECK(canFdErrorFrame->flags1 == 0xfffe);
    BOOST_CHECK(canFdErrorFrame->code == 0xc7);
    BOOST_CHECK(canFdErrorFrame->codeExt == 0x31ca);
    BOOST_CHECK(canFdErrorFrame->phase == Vector::ASC::CanFdErrorFrame::Phase::Data);
    BOOST_CHECK(canFdErrorFrame->position == 45);
    BOOST_CHECK(canFdErrorFrame->id == 0xff);
    BOOST_CHECK(canFdErrorFrame->brs == true);
    BOOST_CHECK(canFdErrorFrame->esi == false);
    BOOST_CHECK(canFdErrorFrame->dlc == 0xf);
    BOOST_CHECK(canFdErrorFrame->dataLength == 64);
    BOOST_REQUIRE(canFdErrorFrame->data.size() == 64);
    for(int i = 0; i < 64; ++i)
        BOOST_CHECK(canFdErrorFrame->data[i] == 0xaa);
    BOOST_CHECK(canFdErrorFrame->messageDuration == 336484);
    BOOST_CHECK(canFdErrorFrame->flags2 == 3);
    BOOST_CHECK(canFdErrorFrame->crc == 0);
    BOOST_CHECK(canFdErrorFrame->bitTimingConfArb == 0x51103250);
    BOOST_CHECK(canFdErrorFrame->bitTimingConfData == 0x460a0250);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

// @todo CanFdBusStatisticsEvent
// @todo CanFdOverloadFrame

/* Log and Trigger Events */
BOOST_AUTO_TEST_CASE(LogTrigger)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogTrigger.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogTrigger * logTrigger;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogTrigger);
    logTrigger = static_cast<Vector::ASC::LogTrigger *>(event);
    BOOST_CHECK(logTrigger->time == 2.000000);
    BOOST_CHECK(logTrigger->information == "");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogTrigger);
    logTrigger = static_cast<Vector::ASC::LogTrigger *>(event);
    BOOST_CHECK(logTrigger->time == 2.700000);
    BOOST_CHECK(logTrigger->information == "(this trigger was in post trigger time of last block)");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LogDirectStart)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogDirectStart.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogDirectStart * logDirectStart;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogDirectStart);
    logDirectStart = static_cast<Vector::ASC::LogDirectStart *>(event);
    BOOST_CHECK(isEqual(logDirectStart->time, 2.110000));
    BOOST_CHECK(logDirectStart->preTrigger == 2000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LogDirectStop)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogDirectStop.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogDirectStop * logDirectStop;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogDirectStop);
    logDirectStop = static_cast<Vector::ASC::LogDirectStop *>(event);
    BOOST_CHECK(isEqual(logDirectStop->time, 2.110000));
    BOOST_CHECK(logDirectStop->postTrigger == 1000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(BeginTriggerblock)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/BeginTriggerblock.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::BeginTriggerblock * beginTriggerblock;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::BeginTriggerblock);
    beginTriggerblock = static_cast<Vector::ASC::BeginTriggerblock *>(event);
    BOOST_CHECK(beginTriggerblock->date.tm_wday == 1);
    BOOST_CHECK(beginTriggerblock->date.tm_mon == 2);
    BOOST_CHECK(beginTriggerblock->date.tm_mday == 7);
    BOOST_CHECK(beginTriggerblock->date.tm_hour == 1+12);
    BOOST_CHECK(beginTriggerblock->date.tm_min == 21);
    BOOST_CHECK(beginTriggerblock->date.tm_sec == 51);
    BOOST_CHECK(beginTriggerblock->date.tm_year == (2005 - 1900));
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(EndTriggerblock)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EndTriggerblock.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    /*Vector::ASC::EndTriggerblock * endTriggerblock;*/

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EndTriggerblock);
    /*endTriggerblock = static_cast<Vector::ASC::EndTriggerblock *>(event);*/
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Environment Variables */
BOOST_AUTO_TEST_CASE(EnvironmentVariables)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EnvironmentVariables.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EnvironmentVariables * environmentVariables;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariables);
    environmentVariables = static_cast<Vector::ASC::EnvironmentVariables *>(event);
    BOOST_CHECK(isEqual(environmentVariables->time, 2.130000));
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariables);
    environmentVariables = static_cast<Vector::ASC::EnvironmentVariables *>(event);
    BOOST_CHECK(isEqual(environmentVariables->time, 2.567000));
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariables);
    environmentVariables = static_cast<Vector::ASC::EnvironmentVariables *>(event);
    BOOST_CHECK(isEqual(environmentVariables->time, 3.830000));
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariables);
    environmentVariables = static_cast<Vector::ASC::EnvironmentVariables *>(event);
    BOOST_CHECK(isEqual(environmentVariables->time, 2.250000));
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* System Variables */
BOOST_AUTO_TEST_CASE(SystemVariables)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/SystemVariables.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::SystemVariables * systemVariables;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK(isEqual(systemVariables->time, 1.200000));
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::Int);
    BOOST_CHECK(systemVariables->path == "::NS1::IntVar");
    BOOST_CHECK(systemVariables->value == "4");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK(isEqual(systemVariables->time, 1.370000));
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::Float);
    BOOST_CHECK(systemVariables->path == "::NS1::FloatVar");
    BOOST_CHECK(systemVariables->value == "4.1");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK(isEqual(systemVariables->time, 1.580000));
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::String);
    BOOST_CHECK(systemVariables->path == "::NS1::StringVar");
    BOOST_CHECK(systemVariables->value == "\"Value: 4\"");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK(isEqual(systemVariables->time, 1.690000));
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::IntArray);
    BOOST_CHECK(systemVariables->path == "::NS1::IntArray");
    BOOST_CHECK(systemVariables->value == "A3 4 5 2");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK(isEqual(systemVariables->time, 2.000000));
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::FloatArray);
    BOOST_CHECK(systemVariables->path == "::NS1::FloatArray");
    BOOST_CHECK(systemVariables->value == "D3 4.1 2.9 6");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Macros Signal Event */
BOOST_AUTO_TEST_CASE(MacroSignal)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MacroSignal.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MacroSignal * macroSignal;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignal);
    macroSignal = static_cast<Vector::ASC::MacroSignal *>(event);
    BOOST_CHECK(isEqual(macroSignal->time, 2.350000));
    BOOST_CHECK(macroSignal->bussystem == Vector::ASC::MacroSignal::Bussystem::Can);
    BOOST_CHECK(macroSignal->channel == 1);
    BOOST_CHECK(macroSignal->node == "Node");
    BOOST_CHECK(macroSignal->message == "aCANMessage");
    BOOST_CHECK(macroSignal->signal == "aBitSignal");
    BOOST_CHECK(macroSignal->value == "1");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignal);
    macroSignal = static_cast<Vector::ASC::MacroSignal *>(event);
    BOOST_CHECK(isEqual(macroSignal->time, 2.350000));
    BOOST_CHECK(macroSignal->bussystem == Vector::ASC::MacroSignal::Bussystem::Can);
    BOOST_CHECK(macroSignal->channel == 1);
    BOOST_CHECK(macroSignal->node == "Node");
    BOOST_CHECK(macroSignal->message == "aCANMessage");
    BOOST_CHECK(macroSignal->signal == "aBitSignal");
    BOOST_CHECK(macroSignal->value == "Eins");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignal);
    macroSignal = static_cast<Vector::ASC::MacroSignal *>(event);
    BOOST_CHECK(isEqual(macroSignal->time, 5.000000));
    BOOST_CHECK(macroSignal->bussystem == Vector::ASC::MacroSignal::Bussystem::Lin);
    BOOST_CHECK(macroSignal->channel == 1);
    BOOST_CHECK(macroSignal->node == "L_Slave");
    BOOST_CHECK(macroSignal->message == "aLINMessage");
    BOOST_CHECK(macroSignal->signal == "aLINBitSignal");
    BOOST_CHECK(macroSignal->value == "0");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignal);
    macroSignal = static_cast<Vector::ASC::MacroSignal *>(event);
    BOOST_CHECK(isEqual(macroSignal->time, 1.110000));
    BOOST_CHECK(macroSignal->bussystem == Vector::ASC::MacroSignal::Bussystem::FlexRay);
    BOOST_CHECK(macroSignal->channel == 1);
    BOOST_CHECK(macroSignal->node == "FR_ECU");
    BOOST_CHECK(macroSignal->message == "aFlexRayMessage");
    BOOST_CHECK(macroSignal->signal == "aFRSignal");
    BOOST_CHECK(macroSignal->value == "3");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* GPS events */
BOOST_AUTO_TEST_CASE(Gps)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Gps.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Gps * gps;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Gps);
    gps = static_cast<Vector::ASC::Gps *>(event);
    BOOST_CHECK(isEqual(gps->time, 2.097603));
    BOOST_CHECK(gps->channel == 1);
    BOOST_CHECK(isEqual(gps->latitude, 48.825100));
    BOOST_CHECK(isEqual(gps->longitude, 9.091267));
    BOOST_CHECK(isEqual(gps->altitude, 325.399994));
    BOOST_CHECK(isEqual(gps->speed, 29.686400));
    BOOST_CHECK(isEqual(gps->course, 87.099998));
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Comment events */
BOOST_AUTO_TEST_CASE(Comment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Comment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Comment * comment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Comment);
    comment = static_cast<Vector::ASC::Comment *>(event);
    BOOST_CHECK(isEqual(comment->time, 1.593770));
    BOOST_CHECK(comment->type == 105);
    BOOST_CHECK(comment->commentText == "testComment");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Global market events */
BOOST_AUTO_TEST_CASE(GlobalMarker)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/GlobalMarker.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::GlobalMarker * globalMarker;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::GlobalMarker);
    globalMarker = static_cast<Vector::ASC::GlobalMarker *>(event);
    BOOST_CHECK(isEqual(globalMarker->time, 2.200804));
    BOOST_CHECK(globalMarker->type == 0);
    BOOST_CHECK(globalMarker->backgroundColor == 16777215);
    BOOST_CHECK(globalMarker->foregroundColor == 0);
    BOOST_CHECK(globalMarker->relocatable == true);
    BOOST_CHECK(globalMarker->groupName == "Marker Group");
    BOOST_CHECK(globalMarker->markerName == "[1]");
    BOOST_CHECK(globalMarker->description == "description");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Ethernet Events */
BOOST_AUTO_TEST_CASE(EthernetPacket)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetPacket * ethernetPacket;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetPacket);
    ethernetPacket = static_cast<Vector::ASC::EthernetPacket *>(event);
    BOOST_CHECK(isEqual(ethernetPacket->time, 0.000000));
    BOOST_CHECK(ethernetPacket->channel == 2);
    BOOST_CHECK(ethernetPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(ethernetPacket->dataLen == 0x3c);
    BOOST_REQUIRE(ethernetPacket->data.size() == 0x3c);
    BOOST_CHECK(ethernetPacket->data[0x00] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x01] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x02] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x03] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x04] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x05] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x06] == 0x40);
    BOOST_CHECK(ethernetPacket->data[0x07] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x08] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x09] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x0a] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x0b] == 0x04);
    BOOST_CHECK(ethernetPacket->data[0x0c] == 0x08);
    BOOST_CHECK(ethernetPacket->data[0x0d] == 0x06);
    BOOST_CHECK(ethernetPacket->data[0x0e] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x0f] == 0x01);
    BOOST_CHECK(ethernetPacket->data[0x10] == 0x08);
    BOOST_CHECK(ethernetPacket->data[0x11] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x12] == 0x06);
    BOOST_CHECK(ethernetPacket->data[0x13] == 0x04);
    BOOST_CHECK(ethernetPacket->data[0x14] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x15] == 0x01);
    BOOST_CHECK(ethernetPacket->data[0x16] == 0x40);
    BOOST_CHECK(ethernetPacket->data[0x17] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x18] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x19] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x1a] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x1b] == 0x04);
    BOOST_CHECK(ethernetPacket->data[0x1c] == 0xC0);
    BOOST_CHECK(ethernetPacket->data[0x1d] == 0xA8);
    BOOST_CHECK(ethernetPacket->data[0x1e] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x1f] == 0x01);
    BOOST_CHECK(ethernetPacket->data[0x20] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x21] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x22] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x23] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x24] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x25] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x26] == 0xC0);
    BOOST_CHECK(ethernetPacket->data[0x27] == 0xA8);
    BOOST_CHECK(ethernetPacket->data[0x28] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x29] == 0x01);
    BOOST_CHECK(ethernetPacket->data[0x2a] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2b] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2c] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2d] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2e] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2f] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x30] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x31] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x32] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x33] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x34] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x35] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x36] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x37] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x38] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x39] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x3a] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x3b] == 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(EthernetStatus)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetStatus.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetStatus * ethernetStatus;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetStatus);
    ethernetStatus = static_cast<Vector::ASC::EthernetStatus *>(event);
    BOOST_CHECK(isEqual(ethernetStatus->time, 0.002404));
    BOOST_CHECK(ethernetStatus->channel == 1);
    BOOST_CHECK(ethernetStatus->link == Vector::ASC::EthernetStatus::Link::Up);
    BOOST_CHECK(ethernetStatus->linkSpeed == 100);
    BOOST_CHECK(ethernetStatus->physical == Vector::ASC::EthernetStatus::Physical::Ieee802_3);
    BOOST_CHECK(ethernetStatus->duplex == Vector::ASC::EthernetStatus::Duplex::Full);
    BOOST_CHECK(ethernetStatus->mdi == Vector::ASC::EthernetStatus::Mdi::Crossover);
    BOOST_CHECK(ethernetStatus->connector == Vector::ASC::EthernetStatus::Connector::Rj45);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(EthernetRxError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetRxError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetRxError * ethernetRxError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetRxError);
    ethernetRxError = static_cast<Vector::ASC::EthernetRxError *>(event);
    BOOST_CHECK(isEqual(ethernetRxError->time, 1.465409));
    BOOST_CHECK(ethernetRxError->channel == 2);
    BOOST_CHECK(ethernetRxError->errorCode == 0x02);
    BOOST_CHECK(ethernetRxError->frameChecksum == 0x00001234);
    BOOST_CHECK(ethernetRxError->dataLen == 0x3c);
    BOOST_REQUIRE(ethernetRxError->data.size() == 0x3c);
    BOOST_CHECK(ethernetRxError->data[0x00] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x01] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x02] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x03] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x04] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x05] == 0x01);
    BOOST_CHECK(ethernetRxError->data[0x06] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x07] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x08] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x09] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x0a] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x0b] == 0x02);
    BOOST_CHECK(ethernetRxError->data[0x0c] == 0xFF);
    BOOST_CHECK(ethernetRxError->data[0x0d] == 0x01);
    BOOST_CHECK(ethernetRxError->data[0x0e] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x0f] == 0x01);
    BOOST_CHECK(ethernetRxError->data[0x10] == 0x02);
    BOOST_CHECK(ethernetRxError->data[0x11] == 0x03);
    BOOST_CHECK(ethernetRxError->data[0x12] == 0x04);
    BOOST_CHECK(ethernetRxError->data[0x13] == 0x05);
    BOOST_CHECK(ethernetRxError->data[0x14] == 0x06);
    BOOST_CHECK(ethernetRxError->data[0x15] == 0x07);
    BOOST_CHECK(ethernetRxError->data[0x16] == 0x08);
    BOOST_CHECK(ethernetRxError->data[0x17] == 0x09);
    BOOST_CHECK(ethernetRxError->data[0x18] == 0x0A);
    BOOST_CHECK(ethernetRxError->data[0x19] == 0x0B);
    BOOST_CHECK(ethernetRxError->data[0x1a] == 0x0C);
    BOOST_CHECK(ethernetRxError->data[0x1b] == 0x0D);
    BOOST_CHECK(ethernetRxError->data[0x1c] == 0x0E);
    BOOST_CHECK(ethernetRxError->data[0x1d] == 0x0F);
    BOOST_CHECK(ethernetRxError->data[0x1e] == 0x10);
    BOOST_CHECK(ethernetRxError->data[0x1f] == 0x11);
    BOOST_CHECK(ethernetRxError->data[0x20] == 0x12);
    BOOST_CHECK(ethernetRxError->data[0x21] == 0x13);
    BOOST_CHECK(ethernetRxError->data[0x22] == 0x14);
    BOOST_CHECK(ethernetRxError->data[0x23] == 0x15);
    BOOST_CHECK(ethernetRxError->data[0x24] == 0x16);
    BOOST_CHECK(ethernetRxError->data[0x25] == 0x17);
    BOOST_CHECK(ethernetRxError->data[0x26] == 0x18);
    BOOST_CHECK(ethernetRxError->data[0x27] == 0x19);
    BOOST_CHECK(ethernetRxError->data[0x28] == 0x1A);
    BOOST_CHECK(ethernetRxError->data[0x29] == 0x1B);
    BOOST_CHECK(ethernetRxError->data[0x2a] == 0x1C);
    BOOST_CHECK(ethernetRxError->data[0x2b] == 0x1D);
    BOOST_CHECK(ethernetRxError->data[0x2c] == 0x1E);
    BOOST_CHECK(ethernetRxError->data[0x2d] == 0x1F);
    BOOST_CHECK(ethernetRxError->data[0x2e] == 0x20);
    BOOST_CHECK(ethernetRxError->data[0x2f] == 0x21);
    BOOST_CHECK(ethernetRxError->data[0x30] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x31] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x32] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x33] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x34] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x35] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x36] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x37] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x38] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x39] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x3a] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x3b] == 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* AFDX Events */
BOOST_AUTO_TEST_CASE(AfdxPacket)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AfdxPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::AfdxPacket * afdxPacket;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::AfdxPacket);
    afdxPacket = static_cast<Vector::ASC::AfdxPacket *>(event);
    BOOST_CHECK(isEqual(afdxPacket->time, 0.000000));
    BOOST_CHECK(afdxPacket->channel == 1);
    BOOST_CHECK(afdxPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(afdxPacket->ethChannel == 1);
    BOOST_CHECK(afdxPacket->flags == 0x64);
    BOOST_CHECK(afdxPacket->bag == 0);
    BOOST_CHECK(afdxPacket->dataLen == 0x3c);
    BOOST_REQUIRE(afdxPacket->data.size() == 0x3c);
    BOOST_CHECK(afdxPacket->data[0x00] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x01] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x02] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x03] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x04] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x05] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x06] == 0x40);
    BOOST_CHECK(afdxPacket->data[0x07] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x08] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x09] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x0a] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x0b] == 0x04);
    BOOST_CHECK(afdxPacket->data[0x0c] == 0x08);
    BOOST_CHECK(afdxPacket->data[0x0d] == 0x06);
    BOOST_CHECK(afdxPacket->data[0x0e] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x0f] == 0x01);
    BOOST_CHECK(afdxPacket->data[0x10] == 0x08);
    BOOST_CHECK(afdxPacket->data[0x11] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x12] == 0x06);
    BOOST_CHECK(afdxPacket->data[0x13] == 0x04);
    BOOST_CHECK(afdxPacket->data[0x14] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x15] == 0x01);
    BOOST_CHECK(afdxPacket->data[0x16] == 0x40);
    BOOST_CHECK(afdxPacket->data[0x17] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x18] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x19] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x1a] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x1b] == 0x04);
    BOOST_CHECK(afdxPacket->data[0x1c] == 0xC0);
    BOOST_CHECK(afdxPacket->data[0x1d] == 0xA8);
    BOOST_CHECK(afdxPacket->data[0x1e] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x1f] == 0x01);
    BOOST_CHECK(afdxPacket->data[0x20] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x21] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x22] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x23] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x24] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x25] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x26] == 0xC0);
    BOOST_CHECK(afdxPacket->data[0x27] == 0xA8);
    BOOST_CHECK(afdxPacket->data[0x28] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x29] == 0x01);
    BOOST_CHECK(afdxPacket->data[0x2a] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2b] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2c] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2d] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2e] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2f] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x30] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x31] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x32] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x33] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x34] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x35] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x36] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x37] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x38] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x39] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x3a] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x3b] == 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* FlexRay Events (Old Format) */
BOOST_AUTO_TEST_CASE(FlexRayOldMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayOldMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayOldMessage * flexRayOldMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldMessage);
    flexRayOldMessage = static_cast<Vector::ASC::FlexRayOldMessage *>(event);
    BOOST_CHECK(isEqual(flexRayOldMessage->time, 0.042000));
    BOOST_CHECK(flexRayOldMessage->channel == '1');
    BOOST_CHECK(flexRayOldMessage->id == 4);
    BOOST_CHECK(flexRayOldMessage->cycle == 25);
    BOOST_CHECK(flexRayOldMessage->nm == false);
    BOOST_CHECK(flexRayOldMessage->sync == true);
    BOOST_CHECK(flexRayOldMessage->headerCrc == 151);
    BOOST_CHECK(flexRayOldMessage->symbolicName == "Ident_04_Rnd_0");
    BOOST_CHECK(flexRayOldMessage->dlc == 4);
    BOOST_REQUIRE(flexRayOldMessage->data.size() == 4);
    BOOST_CHECK(flexRayOldMessage->data[0] == 21);
    BOOST_CHECK(flexRayOldMessage->data[1] == 87);
    BOOST_CHECK(flexRayOldMessage->data[2] == 22);
    BOOST_CHECK(flexRayOldMessage->data[3] == 148);
    BOOST_CHECK(flexRayOldMessage->frameState == 0x00d0);
    BOOST_CHECK(flexRayOldMessage->headerBitMask == 0x9a);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldMessage);
    flexRayOldMessage = static_cast<Vector::ASC::FlexRayOldMessage *>(event);
    BOOST_CHECK(isEqual(flexRayOldMessage->time, 0.042600));
    BOOST_CHECK(flexRayOldMessage->channel == '2');
    BOOST_CHECK(flexRayOldMessage->id == 13);
    BOOST_CHECK(flexRayOldMessage->cycle == 25);
    BOOST_CHECK(flexRayOldMessage->nm == false);
    BOOST_CHECK(flexRayOldMessage->sync == false);
    BOOST_CHECK(flexRayOldMessage->headerCrc == 620);
    BOOST_CHECK(flexRayOldMessage->symbolicName == "x");
    BOOST_CHECK(flexRayOldMessage->dlc == 4);
    BOOST_REQUIRE(flexRayOldMessage->data.size() == 4);
    BOOST_CHECK(flexRayOldMessage->data[0] == 2);
    BOOST_CHECK(flexRayOldMessage->data[1] == 89);
    BOOST_CHECK(flexRayOldMessage->data[2] == 0);
    BOOST_CHECK(flexRayOldMessage->data[3] == 13);
    BOOST_CHECK(flexRayOldMessage->frameState == 0x0180);
    BOOST_CHECK(flexRayOldMessage->headerBitMask == 0x88);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayOldStartCycle)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayOldStartCycle.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayOldStartCycle * flexRayOldStartCycle;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldStartCycle);
    flexRayOldStartCycle = static_cast<Vector::ASC::FlexRayOldStartCycle *>(event);
    BOOST_CHECK(isEqual(flexRayOldStartCycle->time, 0.041700));
    BOOST_CHECK(flexRayOldStartCycle->channel == '*');
    BOOST_CHECK(flexRayOldStartCycle->dlc == 2);
    BOOST_REQUIRE(flexRayOldStartCycle->data.size() == 2);
    BOOST_CHECK(flexRayOldStartCycle->data[0] == 0);
    BOOST_CHECK(flexRayOldStartCycle->data[1] == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* FlexRay Events (New Format) */
BOOST_AUTO_TEST_CASE(FlexRayMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayMessage * flexRayMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessage);
    flexRayMessage = static_cast<Vector::ASC::FlexRayMessage *>(event);
    BOOST_CHECK(isEqual(flexRayMessage->time, 0.039255));
    BOOST_CHECK(flexRayMessage->flexRayEventType == Vector::ASC::FlexRayMessage::FlexRayEventType::RMSG);
    BOOST_CHECK(flexRayMessage->clusterNr == 0);
    BOOST_CHECK(flexRayMessage->clientId == 0);
    BOOST_CHECK(flexRayMessage->channelNr == 1);
    BOOST_CHECK(flexRayMessage->channelMask == 1);
    BOOST_CHECK(flexRayMessage->slotId == 4);
    BOOST_CHECK(flexRayMessage->cycleNo == 7);
    BOOST_CHECK(flexRayMessage->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK(flexRayMessage->appParam == 0);
    BOOST_CHECK(flexRayMessage->flags == 14);
    BOOST_CHECK(flexRayMessage->ccType == 5);
    BOOST_CHECK(flexRayMessage->ccData == 32);
    BOOST_CHECK(flexRayMessage->headerCrc == 151);
    BOOST_CHECK(flexRayMessage->name == "Message_2");
    BOOST_CHECK(flexRayMessage->payloadLength == 4);
    BOOST_CHECK(flexRayMessage->bufferLength == 4);
    BOOST_REQUIRE(flexRayMessage->data.size() == 4);
    BOOST_CHECK(flexRayMessage->data[0] == 27);
    BOOST_CHECK(flexRayMessage->data[1] == 24);
    BOOST_CHECK(flexRayMessage->data[2] == 29);
    BOOST_CHECK(flexRayMessage->data[3] == 241);
    BOOST_CHECK(flexRayMessage->frameCrc == 0);
    BOOST_CHECK(flexRayMessage->spyFlag == 0);
    BOOST_CHECK(flexRayMessage->frameLengthNs == 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessage);
    flexRayMessage = static_cast<Vector::ASC::FlexRayMessage *>(event);
    BOOST_CHECK(isEqual(flexRayMessage->time, 0.047906));
    BOOST_CHECK(flexRayMessage->flexRayEventType == Vector::ASC::FlexRayMessage::FlexRayEventType::PDU);
    BOOST_CHECK(flexRayMessage->clusterNr == 0);
    BOOST_CHECK(flexRayMessage->clientId == 2);
    BOOST_CHECK(flexRayMessage->channelNr == 1);
    BOOST_CHECK(flexRayMessage->channelMask == 1);
    BOOST_CHECK(flexRayMessage->slotId == 3);
    BOOST_CHECK(flexRayMessage->cycleNo == 7);
    BOOST_CHECK(flexRayMessage->direction == Vector::ASC::Dir::Tx);
    BOOST_CHECK(flexRayMessage->appParam == 0);
    BOOST_CHECK(flexRayMessage->flags == 2313218);
    BOOST_CHECK(flexRayMessage->ccType == 5);
    BOOST_CHECK(flexRayMessage->ccData == 32);
    BOOST_CHECK(flexRayMessage->headerCrc == 559);
    BOOST_CHECK(flexRayMessage->name == "PDU_DEMO_1");
    BOOST_CHECK(flexRayMessage->payloadLength == 1);
    BOOST_CHECK(flexRayMessage->bufferLength == 1);
    BOOST_REQUIRE(flexRayMessage->data.size() == 1);
    BOOST_CHECK(flexRayMessage->data[0] == 0);
    BOOST_CHECK(flexRayMessage->frameCrc == 0);
    BOOST_CHECK(flexRayMessage->spyFlag == 0);
    BOOST_CHECK(flexRayMessage->frameLengthNs == 0);
    BOOST_CHECK(flexRayMessage->pduOffset == 40);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessage);
    flexRayMessage = static_cast<Vector::ASC::FlexRayMessage *>(event);
    BOOST_CHECK(isEqual(flexRayMessage->time, 0.047906));
    BOOST_CHECK(flexRayMessage->flexRayEventType == Vector::ASC::FlexRayMessage::FlexRayEventType::RMSG);
    BOOST_CHECK(flexRayMessage->clusterNr == 0);
    BOOST_CHECK(flexRayMessage->clientId == 2);
    BOOST_CHECK(flexRayMessage->channelNr == 1);
    BOOST_CHECK(flexRayMessage->channelMask == 1);
    BOOST_CHECK(flexRayMessage->slotId == 3);
    BOOST_CHECK(flexRayMessage->cycleNo == 7);
    BOOST_CHECK(flexRayMessage->direction == Vector::ASC::Dir::Tx);
    BOOST_CHECK(flexRayMessage->appParam == 0);
    BOOST_CHECK(flexRayMessage->flags == 2640898);
    BOOST_CHECK(flexRayMessage->ccType == 5);
    BOOST_CHECK(flexRayMessage->ccData == 32);
    BOOST_CHECK(flexRayMessage->headerCrc == 559);
    BOOST_CHECK(flexRayMessage->name == "FlexRay_Frame_[3|0|1]");
    BOOST_CHECK(flexRayMessage->payloadLength == 42);
    BOOST_CHECK(flexRayMessage->bufferLength == 42);
    BOOST_REQUIRE(flexRayMessage->data.size() == 42);
    BOOST_CHECK(flexRayMessage->data[ 0] == 0);
    BOOST_CHECK(flexRayMessage->data[ 1] == 0);
    BOOST_CHECK(flexRayMessage->data[ 2] == 0);
    BOOST_CHECK(flexRayMessage->data[ 3] == 0);
    BOOST_CHECK(flexRayMessage->data[ 4] == 0);
    BOOST_CHECK(flexRayMessage->data[ 5] == 0);
    BOOST_CHECK(flexRayMessage->data[ 6] == 0);
    BOOST_CHECK(flexRayMessage->data[ 7] == 0);
    BOOST_CHECK(flexRayMessage->data[ 8] == 0);
    BOOST_CHECK(flexRayMessage->data[ 9] == 0);
    BOOST_CHECK(flexRayMessage->data[10] == 0);
    BOOST_CHECK(flexRayMessage->data[11] == 0);
    BOOST_CHECK(flexRayMessage->data[12] == 0);
    BOOST_CHECK(flexRayMessage->data[13] == 0);
    BOOST_CHECK(flexRayMessage->data[14] == 0);
    BOOST_CHECK(flexRayMessage->data[15] == 0);
    BOOST_CHECK(flexRayMessage->data[16] == 0);
    BOOST_CHECK(flexRayMessage->data[17] == 0);
    BOOST_CHECK(flexRayMessage->data[18] == 0);
    BOOST_CHECK(flexRayMessage->data[19] == 0);
    BOOST_CHECK(flexRayMessage->data[20] == 0);
    BOOST_CHECK(flexRayMessage->data[21] == 0);
    BOOST_CHECK(flexRayMessage->data[22] == 0);
    BOOST_CHECK(flexRayMessage->data[23] == 128);
    BOOST_CHECK(flexRayMessage->data[24] == 0);
    BOOST_CHECK(flexRayMessage->data[25] == 128);
    BOOST_CHECK(flexRayMessage->data[26] == 0);
    BOOST_CHECK(flexRayMessage->data[27] == 128);
    BOOST_CHECK(flexRayMessage->data[28] == 0);
    BOOST_CHECK(flexRayMessage->data[29] == 0);
    BOOST_CHECK(flexRayMessage->data[30] == 0);
    BOOST_CHECK(flexRayMessage->data[31] == 0);
    BOOST_CHECK(flexRayMessage->data[32] == 0);
    BOOST_CHECK(flexRayMessage->data[33] == 128);
    BOOST_CHECK(flexRayMessage->data[34] == 0);
    BOOST_CHECK(flexRayMessage->data[35] == 128);
    BOOST_CHECK(flexRayMessage->data[36] == 0);
    BOOST_CHECK(flexRayMessage->data[37] == 128);
    BOOST_CHECK(flexRayMessage->data[38] == 0);
    BOOST_CHECK(flexRayMessage->data[39] == 0);
    BOOST_CHECK(flexRayMessage->data[40] == 0);
    BOOST_CHECK(flexRayMessage->data[41] == 56);
    BOOST_CHECK(flexRayMessage->frameCrc == 0);
    BOOST_CHECK(flexRayMessage->spyFlag == 0);
    BOOST_CHECK(flexRayMessage->frameLengthNs == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayStartCycle)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayStartCycle.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayStartCycle * flexRayStartCycle;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayStartCycle);
    flexRayStartCycle = static_cast<Vector::ASC::FlexRayStartCycle *>(event);
    BOOST_CHECK(isEqual(flexRayStartCycle->time, 0.044115));
    BOOST_CHECK(flexRayStartCycle->clusterNr == 0);
    BOOST_CHECK(flexRayStartCycle->clientId == 0);
    BOOST_CHECK(flexRayStartCycle->channelNr == 1);
    BOOST_CHECK(flexRayStartCycle->channelMask == 3);
    BOOST_CHECK(flexRayStartCycle->cycleNo == 8);
    BOOST_CHECK(flexRayStartCycle->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK(flexRayStartCycle->ccType == 5);
    BOOST_CHECK(flexRayStartCycle->ccData[0] == 0);
    BOOST_CHECK(flexRayStartCycle->ccData[1] == 4);
    BOOST_CHECK(flexRayStartCycle->ccData[2] == 0);
    BOOST_CHECK(flexRayStartCycle->ccData[3] == 0);
    BOOST_CHECK(flexRayStartCycle->ccData[4] == 0);
    BOOST_CHECK(flexRayStartCycle->nmVectL == 0);
    BOOST_REQUIRE(flexRayStartCycle->nmVect.size() == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayStatus)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayStatus.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayStatus * flexRayStatus;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayStatus);
    flexRayStatus = static_cast<Vector::ASC::FlexRayStatus *>(event);
    BOOST_CHECK(isEqual(flexRayStatus->time, 0.003022));
    BOOST_CHECK(flexRayStatus->clusterNr == 0);
    BOOST_CHECK(flexRayStatus->clientId == 0);
    BOOST_CHECK(flexRayStatus->channelNr == 1);
    BOOST_CHECK(flexRayStatus->channelMask == 3);
    BOOST_CHECK(flexRayStatus->cycleNo == 255);
    BOOST_CHECK(flexRayStatus->ccType == 5);
    BOOST_CHECK(flexRayStatus->syncState == 2);
    BOOST_CHECK(flexRayStatus->ccData[0] == 15);
    BOOST_CHECK(flexRayStatus->ccData[1] == 0);
    BOOST_CHECK(flexRayStatus->symbol == 0);
    BOOST_CHECK(flexRayStatus->wakeUpState == 0);
    BOOST_CHECK(flexRayStatus->spyFlag == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayError * flexRayError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayError);
    flexRayError = static_cast<Vector::ASC::FlexRayError *>(event);
    BOOST_CHECK(isEqual(flexRayError->time, 7.344250));
    BOOST_CHECK(flexRayError->clusterNr == 0);
    BOOST_CHECK(flexRayError->clientId == 0);
    BOOST_CHECK(flexRayError->channelNr == 1);
    BOOST_CHECK(flexRayError->channelMask == 2);
    BOOST_CHECK(flexRayError->ccType == 5);
    BOOST_CHECK(flexRayError->ccData[0] == 5);
    BOOST_CHECK(flexRayError->ccData[1] == 65536);
    BOOST_CHECK(flexRayError->ccData[2] == 0);
    BOOST_CHECK(flexRayError->ccData[3] == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* K-Line Events */
BOOST_AUTO_TEST_CASE(KLineByte)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/KLineByte.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::KLineByte * kLineByte;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::KLineByte);
    kLineByte = static_cast<Vector::ASC::KLineByte *>(event);
    BOOST_CHECK(isEqual(kLineByte->time, 12.315000));
    BOOST_CHECK(kLineByte->port == "COM2");
    BOOST_CHECK(kLineByte->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK(kLineByte->baudrate == 10400);
    BOOST_CHECK(kLineByte->length == 7);
    BOOST_REQUIRE(kLineByte->data.size() == 7);
    BOOST_CHECK(kLineByte->data[0] == 0x83);
    BOOST_CHECK(kLineByte->data[1] == 0x11);
    BOOST_CHECK(kLineByte->data[2] == 0x61);
    BOOST_CHECK(kLineByte->data[3] == 0x7F);
    BOOST_CHECK(kLineByte->data[4] == 0x1A);
    BOOST_CHECK(kLineByte->data[5] == 0x78);
    BOOST_CHECK(kLineByte->data[6] == 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(KLineMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/KLineMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::KLineMessage * kLineMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::KLineMessage);
    kLineMessage = static_cast<Vector::ASC::KLineMessage *>(event);
    BOOST_CHECK(isEqual(kLineMessage->time, 12.315000));
    BOOST_CHECK(kLineMessage->port == "COM2");
    BOOST_CHECK(kLineMessage->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK(kLineMessage->baudrate == 10400);
    BOOST_CHECK(kLineMessage->source == "61");
    BOOST_CHECK(kLineMessage->destination == "11");
    BOOST_CHECK(kLineMessage->length == 7);
    BOOST_REQUIRE(kLineMessage->data.size() == 7);
    BOOST_CHECK(kLineMessage->data[0] == 0x83);
    BOOST_CHECK(kLineMessage->data[1] == 0x11);
    BOOST_CHECK(kLineMessage->data[2] == 0x61);
    BOOST_CHECK(kLineMessage->data[3] == 0x7F);
    BOOST_CHECK(kLineMessage->data[4] == 0x1A);
    BOOST_CHECK(kLineMessage->data[5] == 0x78);
    BOOST_CHECK(kLineMessage->data[6] == 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN Events */
BOOST_AUTO_TEST_CASE(LinMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinMessage * linMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinMessage);
    linMessage = static_cast<Vector::ASC::LinMessage *>(event);
    BOOST_CHECK(isEqual(linMessage->time, 0.073973));
    BOOST_CHECK(linMessage->channel == 1);
    BOOST_CHECK(linMessage->id == "2d");
    BOOST_CHECK(linMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(linMessage->dlc == 8);
    BOOST_REQUIRE(linMessage->data.size() == 8);
    BOOST_CHECK(linMessage->data[0] == 0x00);
    BOOST_CHECK(linMessage->data[1] == 0xf0);
    BOOST_CHECK(linMessage->data[2] == 0xf0);
    BOOST_CHECK(linMessage->data[3] == 0xff);
    BOOST_CHECK(linMessage->data[4] == 0xff);
    BOOST_CHECK(linMessage->data[5] == 0xff);
    BOOST_CHECK(linMessage->data[6] == 0xff);
    BOOST_CHECK(linMessage->data[7] == 0xff);
    BOOST_CHECK(linMessage->checksum = 70);
    BOOST_CHECK(linMessage->headerTime == 40);
    BOOST_CHECK(linMessage->fullTime == 130);
    BOOST_CHECK(isEqual(linMessage->startOfFrame, 0.067195));
    BOOST_CHECK(linMessage->baudrate == 19230);
    BOOST_CHECK(linMessage->syncBreak == 937125);
    BOOST_CHECK(linMessage->syncDel == 114062);
    BOOST_CHECK(isEqual(linMessage->endOfHeader, 0.069266));
    BOOST_REQUIRE(linMessage->endOfByte.size() == 8);
    BOOST_CHECK(isEqual(linMessage->endOfByte[0], 0.069789));
    BOOST_CHECK(isEqual(linMessage->endOfByte[1], 0.070312));
    BOOST_CHECK(isEqual(linMessage->endOfByte[2], 0.070835));
    BOOST_CHECK(isEqual(linMessage->endOfByte[3], 0.071358));
    BOOST_CHECK(isEqual(linMessage->endOfByte[4], 0.071881));
    BOOST_CHECK(isEqual(linMessage->endOfByte[5], 0.072404));
    BOOST_CHECK(isEqual(linMessage->endOfByte[6], 0.072927));
    BOOST_CHECK(isEqual(linMessage->endOfByte[7], 0.073450));
    BOOST_CHECK(linMessage->simulated == true);
    BOOST_CHECK(isEqual(linMessage->endOfFrame, 0.073973));
    BOOST_CHECK(linMessage->responseBaudrate == 19231);
    BOOST_CHECK(isEqual(linMessage->headerBaudrate, 19230.769231));
    BOOST_CHECK(linMessage->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linMessage->stopBitOffsetInResponse == 26000);
    BOOST_CHECK(linMessage->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN Error Events */
BOOST_AUTO_TEST_CASE(LinTransmissionError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinTransmissionError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinTransmissionError * linTransmissionError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinTransmissionError);
    linTransmissionError = static_cast<Vector::ASC::LinTransmissionError *>(event);
    BOOST_CHECK(isEqual(linTransmissionError->time, 0.424674));
    BOOST_CHECK(linTransmissionError->channel == 1);
    BOOST_CHECK(linTransmissionError->id == "33");
    BOOST_CHECK(linTransmissionError->headerTime == 40);
    BOOST_CHECK(linTransmissionError->fullTime == 166);
    BOOST_CHECK(isEqual(linTransmissionError->startOfFrame, 0.416054));
    BOOST_CHECK(linTransmissionError->baudrate == 19230);
    BOOST_CHECK(linTransmissionError->syncBreak == 937187);
    BOOST_CHECK(linTransmissionError->syncDel == 113250);
    BOOST_CHECK(isEqual(linTransmissionError->endOfHeader, 0.418122));
    BOOST_CHECK(isEqual(linTransmissionError->headerBaudrate, 19230.769231));
    BOOST_CHECK(linTransmissionError->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linTransmissionError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinReceiveError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinReceiveError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinReceiveError * linReceiveError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinReceiveError);
    linReceiveError = static_cast<Vector::ASC::LinReceiveError *>(event);
    BOOST_CHECK(isEqual(linReceiveError->time, 0.554673));
    BOOST_CHECK(linReceiveError->channel == 1);
    BOOST_CHECK(linReceiveError->id == "33");
    BOOST_CHECK(linReceiveError->dlc == 8);
    BOOST_CHECK(linReceiveError->description == "timeout while waiting for checksum field");
    BOOST_CHECK(linReceiveError->stateReason == 0x0c);
    BOOST_CHECK(linReceiveError->isShortError == false);
    BOOST_CHECK(linReceiveError->isDlcTimeout == false);
    BOOST_CHECK(linReceiveError->hasDataBytes == true);
    BOOST_REQUIRE(linReceiveError->data.size() == 8);
    BOOST_CHECK(linReceiveError->data[0] == 0x05);
    BOOST_CHECK(linReceiveError->data[1] == 0x00);
    BOOST_CHECK(linReceiveError->data[2] == 0x00);
    BOOST_CHECK(linReceiveError->data[3] == 0x00);
    BOOST_CHECK(linReceiveError->data[4] == 0x00);
    BOOST_CHECK(linReceiveError->data[5] == 0xff);
    BOOST_CHECK(linReceiveError->data[6] == 0xff);
    BOOST_CHECK(linReceiveError->data[7] == 0xff);
    BOOST_CHECK(isEqual(linReceiveError->startOfFrame, 0.546052));
    BOOST_CHECK(linReceiveError->baudrate == 19230);
    BOOST_CHECK(linReceiveError->syncBreak == 937187);
    BOOST_CHECK(linReceiveError->syncDel == 112437);
    BOOST_CHECK(isEqual(linReceiveError->endOfHeader, 0.548121));
    BOOST_REQUIRE(linReceiveError->endOfByte.size() == 8);
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[0], 0.548644));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[1], 0.549167));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[2], 0.549690));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[3], 0.550213));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[4], 0.550736));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[5], 0.551259));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[6], 0.551782));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[7], 0.552305));
    BOOST_CHECK(linReceiveError->responseBaudrate == 19231);
    BOOST_CHECK(linReceiveError->stopBitOffsetInResponse == 26000);
    BOOST_CHECK(isEqual(linReceiveError->headerBaudrate, 19230.769231));
    BOOST_CHECK(linReceiveError->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linReceiveError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinSyncError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSyncError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSyncError * linSyncError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSyncError);
    linSyncError = static_cast<Vector::ASC::LinSyncError *>(event);
    BOOST_CHECK(isEqual(linSyncError->time, 2.022336));
    BOOST_CHECK(linSyncError->channel == 2);
    BOOST_CHECK(linSyncError->timeInterval[0] == 208);
    BOOST_CHECK(linSyncError->timeInterval[1] == 0);
    BOOST_CHECK(linSyncError->timeInterval[2] == 0);
    BOOST_CHECK(linSyncError->timeInterval[3] == 0);
    BOOST_CHECK(isEqual(linSyncError->startOfFrame, 2.021077));
    BOOST_CHECK(linSyncError->baudrate == 19230);
    BOOST_CHECK(linSyncError->syncBreak == 937125);
    BOOST_CHECK(linSyncError->syncDel == 113312);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinChecksumError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinChecksumError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinChecksumError * linChecksumError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinChecksumError);
    linChecksumError = static_cast<Vector::ASC::LinChecksumError *>(event);
    BOOST_CHECK(isEqual(linChecksumError->time, 0.462829));
    BOOST_CHECK(linChecksumError->channel == 1);
    BOOST_CHECK(linChecksumError->id == "33");
    BOOST_CHECK(linChecksumError->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(linChecksumError->dlc == 8);
    BOOST_REQUIRE(linChecksumError->data.size() == 8);
    BOOST_CHECK(linChecksumError->data[0] == 0x05);
    BOOST_CHECK(linChecksumError->data[1] == 0x00);
    BOOST_CHECK(linChecksumError->data[2] == 0x00);
    BOOST_CHECK(linChecksumError->data[3] == 0x00);
    BOOST_CHECK(linChecksumError->data[4] == 0x00);
    BOOST_CHECK(linChecksumError->data[5] == 0xff);
    BOOST_CHECK(linChecksumError->data[6] == 0xff);
    BOOST_CHECK(linChecksumError->data[7] == 0xff);
    BOOST_CHECK(linChecksumError->checksum == 0x86);
    BOOST_CHECK(linChecksumError->headerTime == 40);
    BOOST_CHECK(linChecksumError->fullTime == 130);
    BOOST_CHECK(isEqual(linChecksumError->startOfFrame, 0.456050));
    BOOST_CHECK(linChecksumError->baudrate == 19230);
    BOOST_CHECK(linChecksumError->syncBreak == 937187);
    BOOST_CHECK(linChecksumError->syncDel == 114875);
    BOOST_CHECK(isEqual(linChecksumError->endOfHeader, 0.458122));
    BOOST_REQUIRE(linChecksumError->endOfByte.size() == 8);
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[0], 0.458645));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[1], 0.459168));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[2], 0.459691));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[3], 0.460214));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[4], 0.460737));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[5], 0.461260));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[6], 0.461783));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[7], 0.462306));
    BOOST_CHECK(linChecksumError->simulated == true);
    BOOST_CHECK(isEqual(linChecksumError->endOfFrame, 0.462829));
    BOOST_CHECK(linChecksumError->responseBaudrate == 19231);
    BOOST_CHECK(isEqual(linChecksumError->headerBaudrate, 19230.769231));
    BOOST_CHECK(linChecksumError->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linChecksumError->stopBitOffsetInResponse == 26000);
    BOOST_CHECK(linChecksumError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinSpike)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSpike.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSpike * linSpike;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSpike);
    linSpike = static_cast<Vector::ASC::LinSpike *>(event);
    BOOST_CHECK(isEqual(linSpike->time, 5.990958));
    BOOST_CHECK(linSpike->channel == 2);
    BOOST_CHECK(linSpike->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(linSpike->spikeLength == 56);
    BOOST_CHECK(isEqual(linSpike->startOfFrame, 5.990902));
    BOOST_CHECK(linSpike->baudrate == 9615);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinDominantSignal)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDominantSignal.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDominantSignal * linDominantSignal;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDominantSignal);
    linDominantSignal = static_cast<Vector::ASC::LinDominantSignal *>(event);
    BOOST_CHECK(isEqual(linDominantSignal->time, 8.976802));
    BOOST_CHECK(linDominantSignal->channel == 1);
    BOOST_CHECK(linDominantSignal->domSigState == Vector::ASC::LinDomSigState::Detected);
    BOOST_CHECK(linDominantSignal->domSigLength == 5003);
    BOOST_CHECK(isEqual(linDominantSignal->startOfFrame, 8.971798));
    BOOST_CHECK(linDominantSignal->baudrate == 9615);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDominantSignal);
    linDominantSignal = static_cast<Vector::ASC::LinDominantSignal *>(event);
    BOOST_CHECK(isEqual(linDominantSignal->time, 8.977000));
    BOOST_CHECK(linDominantSignal->channel == 1);
    BOOST_CHECK(linDominantSignal->domSigState == Vector::ASC::LinDomSigState::Finished);
    BOOST_CHECK(linDominantSignal->domSigLength == 5201);
    BOOST_CHECK(isEqual(linDominantSignal->startOfFrame, 8.971798));
    BOOST_CHECK(linDominantSignal->baudrate == 9615);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN Info Events */
BOOST_AUTO_TEST_CASE(LinBaudrate)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinBaudrate.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinBaudrate * linBaudrate;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinBaudrate);
    linBaudrate = static_cast<Vector::ASC::LinBaudrate *>(event);
    BOOST_CHECK(isEqual(linBaudrate->time, 0.018800));
    BOOST_CHECK(linBaudrate->channel == 1);
    BOOST_CHECK(linBaudrate->baudrate == 9615);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinDlcInfo)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDlcInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDlcInfo * linDlcInfo;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDlcInfo);
    linDlcInfo = static_cast<Vector::ASC::LinDlcInfo *>(event);
    BOOST_CHECK(isEqual(linDlcInfo->time, 12.637500));
    BOOST_CHECK(linDlcInfo->channel == 1);
    BOOST_CHECK(linDlcInfo->id == "20");
    BOOST_CHECK(linDlcInfo->dlc == 4);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinChecksumInfo)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinChecksumInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinChecksumInfo * linChecksumInfo;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinChecksumInfo);
    linChecksumInfo = static_cast<Vector::ASC::LinChecksumInfo *>(event);
    BOOST_CHECK(isEqual(linChecksumInfo->time, 0.020100));
    BOOST_CHECK(linChecksumInfo->channel == 1);
    BOOST_CHECK(linChecksumInfo->id == "22");
    BOOST_CHECK(linChecksumInfo->checksumModelInfo == Vector::ASC::LinChecksumModelInfo::Classic);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinSchedulerModeChange)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSchedulerModeChange.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSchedulerModeChange * linSchedulerModeChange;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSchedulerModeChange);
    linSchedulerModeChange = static_cast<Vector::ASC::LinSchedulerModeChange *>(event);
    BOOST_CHECK(isEqual(linSchedulerModeChange->time, 0.100000));
    BOOST_CHECK(linSchedulerModeChange->channel == 1);
    BOOST_CHECK(linSchedulerModeChange->priorSchedulerMode == 2);
    BOOST_CHECK(linSchedulerModeChange->nextSchedulerMode == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinSlaveTimeout)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSlaveTimeout.asc");
    BOOST_REQUIRE(file.is_open());


    Vector::ASC::Event * event;
    Vector::ASC::LinSlaveTimeout * linSlaveTimeout;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSlaveTimeout);
    linSlaveTimeout = static_cast<Vector::ASC::LinSlaveTimeout *>(event);
    BOOST_CHECK(isEqual(linSlaveTimeout->time, 1.001200));
    BOOST_CHECK(linSlaveTimeout->channel == 1);
    BOOST_CHECK(linSlaveTimeout->slaveId == 0);
    BOOST_CHECK(linSlaveTimeout->currentState == 0);
    BOOST_CHECK(linSlaveTimeout->followingState == 1);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinEventTriggeredFrameInfo)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinEventTriggeredFrameInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinEventTriggeredFrameInfo * linEventTriggeredFrameInfo;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinEventTriggeredFrameInfo);
    linEventTriggeredFrameInfo = static_cast<Vector::ASC::LinEventTriggeredFrameInfo *>(event);
    BOOST_CHECK(isEqual(linEventTriggeredFrameInfo->time, 1.909165));
    BOOST_CHECK(linEventTriggeredFrameInfo->channel == 1);
    BOOST_CHECK(linEventTriggeredFrameInfo->id == "3a");
    BOOST_CHECK(linEventTriggeredFrameInfo->etfName == "ETF_MotorStates");
    BOOST_CHECK(linEventTriggeredFrameInfo->description == "No response");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinStatisticInfo)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinStatisticInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinStatisticInfo * linStatisticInfo;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinStatisticInfo);
    linStatisticInfo = static_cast<Vector::ASC::LinStatisticInfo *>(event);
    BOOST_CHECK(isEqual(linStatisticInfo->time, 1.999580));
    BOOST_CHECK(linStatisticInfo->channel == 1);
    BOOST_CHECK(linStatisticInfo->channelNum == 1);
    BOOST_CHECK(isEqual(linStatisticInfo->busLoad, 0.903601));
    BOOST_CHECK(linStatisticInfo->burstsTotal == 0);
    BOOST_CHECK(linStatisticInfo->burstsOverrun == 0);
    BOOST_CHECK(linStatisticInfo->framesSent == 0);
    BOOST_CHECK(linStatisticInfo->framesReceived == 73);
    BOOST_CHECK(linStatisticInfo->framesUnanswered == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinShortOrSlowResponse)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinShortOrSlowResponse.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinShortOrSlowResponse * linShortOrSlowResponse;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinShortOrSlowResponse);
    linShortOrSlowResponse = static_cast<Vector::ASC::LinShortOrSlowResponse *>(event);
    BOOST_CHECK(isEqual(linShortOrSlowResponse->time, 1.298765));
    BOOST_CHECK(linShortOrSlowResponse->channel == 1);
    BOOST_CHECK(linShortOrSlowResponse->id == "1");
    BOOST_CHECK(linShortOrSlowResponse->dlc == 8);
    BOOST_CHECK(linShortOrSlowResponse->numberOfResponseBytes == 9);
    BOOST_REQUIRE(linShortOrSlowResponse->data.size() == 9);
    BOOST_CHECK(linShortOrSlowResponse->data[0] == 0x11);
    BOOST_CHECK(linShortOrSlowResponse->data[1] == 0x12);
    BOOST_CHECK(linShortOrSlowResponse->data[2] == 0x13);
    BOOST_CHECK(linShortOrSlowResponse->data[3] == 0x14);
    BOOST_CHECK(linShortOrSlowResponse->data[4] == 0x15);
    BOOST_CHECK(linShortOrSlowResponse->data[5] == 0x16);
    BOOST_CHECK(linShortOrSlowResponse->data[6] == 0x17);
    BOOST_CHECK(linShortOrSlowResponse->data[7] == 0x18);
    BOOST_CHECK(linShortOrSlowResponse->data[8] == 0x99);
    BOOST_CHECK(linShortOrSlowResponse->isSlowResponse == true);
    BOOST_CHECK(linShortOrSlowResponse->responseWasInterruptedByBreak == false);
    BOOST_CHECK(isEqual(linShortOrSlowResponse->startOfFrame, 1.279516));
    BOOST_CHECK(linShortOrSlowResponse->baudrate == 19230);
    BOOST_CHECK(linShortOrSlowResponse->syncBreak == 937250);
    BOOST_CHECK(linShortOrSlowResponse->syncDel == 102625);
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfHeader, 1.281570));
    BOOST_REQUIRE(linShortOrSlowResponse->endOfByte.size() == 8);
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[0], 1.283679));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[1], 1.285759));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[2], 1.287839));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[3], 1.289927));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[4], 1.292007));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[5], 1.294087));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[6], 1.296167));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[7], 1.298244));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->headerBaudrate, 19230.769231));
    BOOST_CHECK(linShortOrSlowResponse->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linShortOrSlowResponse->checksumModel == Vector::ASC::LinChecksumModel::Unknown);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinDisturbance)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDisturbance.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDisturbance * linDisturbance;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDisturbance);
    linDisturbance = static_cast<Vector::ASC::LinDisturbance *>(event);
    BOOST_CHECK(isEqual(linDisturbance->time, 1.323661));
    BOOST_CHECK(linDisturbance->channel == 1);
    BOOST_CHECK(linDisturbance->disturbanceType == Vector::ASC::LinDisturbanceType::Dominant);
    BOOST_CHECK(linDisturbance->byteIndex == 1);
    BOOST_CHECK(linDisturbance->bitIndex == 6);
    BOOST_CHECK(linDisturbance->bitOffset == 0);
    BOOST_CHECK(linDisturbance->length == 16);
    BOOST_CHECK(linDisturbance->header == 0x2D);
    BOOST_CHECK(linDisturbance->disturbingHeader == 0xFF);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN Sleep/Wakeup Events */
BOOST_AUTO_TEST_CASE(LinSleepMode)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSleepMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSleepMode * linSleepMode;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSleepMode);
    linSleepMode = static_cast<Vector::ASC::LinSleepMode *>(event);
    BOOST_CHECK(isEqual(linSleepMode->time, 0.7772));
    BOOST_CHECK(linSleepMode->channel == 1);
    BOOST_CHECK(linSleepMode->simulated == false);
    BOOST_CHECK(linSleepMode->description == "entering sleep mode due to sleep mode frame");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinWakeupFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinWakeupFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinWakeupFrame * linWakeupFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinWakeupFrame);
    linWakeupFrame = static_cast<Vector::ASC::LinWakeupFrame *>(event);
    BOOST_CHECK(isEqual(linWakeupFrame->time, 2.318672));
    BOOST_CHECK(linWakeupFrame->channel == 1);
    BOOST_CHECK(linWakeupFrame->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(linWakeupFrame->wakeupByte == 0);
    BOOST_CHECK(isEqual(linWakeupFrame->startOfFrame, 2.317671));
    BOOST_CHECK(linWakeupFrame->baudrate == 19230);
    BOOST_CHECK(linWakeupFrame->wakeupLengthInfo == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinUnexpectedWakeup)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinUnexpectedWakeup.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinUnexpectedWakeup * linUnexpectedWakeup;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinUnexpectedWakeup);
    linUnexpectedWakeup = static_cast<Vector::ASC::LinUnexpectedWakeup *>(event);
    BOOST_CHECK(isEqual(linUnexpectedWakeup->time, 0.892363));
    BOOST_CHECK(linUnexpectedWakeup->channel == 1);
    BOOST_CHECK(linUnexpectedWakeup->width == 260);
    BOOST_CHECK(isEqual(linUnexpectedWakeup->startOfFrame, 0.891843));
    BOOST_CHECK(linUnexpectedWakeup->baudrate == 19230);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST Events */
BOOST_AUTO_TEST_CASE(Most25ControlMessageNodeMode)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25ControlMessageNodeMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25ControlMessageNodeMode * most25ControlMessageNodeMode;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25ControlMessageNodeMode);
    most25ControlMessageNodeMode = static_cast<Vector::ASC::Most25ControlMessageNodeMode *>(event);
    BOOST_CHECK(isEqual(most25ControlMessageNodeMode->time, 0.111757));
    BOOST_CHECK(most25ControlMessageNodeMode->channel == 1);
    BOOST_CHECK(most25ControlMessageNodeMode->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(most25ControlMessageNodeMode->sourceAdr == 0x0100);
    BOOST_CHECK(most25ControlMessageNodeMode->destAdr == 0x0401);
    BOOST_CHECK(most25ControlMessageNodeMode->rType == 0x00);
    BOOST_REQUIRE(most25ControlMessageNodeMode->data.size() == 17);
    BOOST_CHECK(most25ControlMessageNodeMode->data[0] == 0x01);
    BOOST_CHECK(most25ControlMessageNodeMode->data[1] == 0x01);
    BOOST_CHECK(most25ControlMessageNodeMode->data[2] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[3] == 0x01);
    BOOST_CHECK(most25ControlMessageNodeMode->data[4] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[5] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[6] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[7] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[8] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[9] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[10] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[11] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[12] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[13] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[14] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[15] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[16] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->state2 == 0x1250);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most25ControlMessageSpyMode)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25ControlMessageSpyMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25ControlMessageSpyMode * most25ControlMessageSpyMode;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25ControlMessageSpyMode);
    most25ControlMessageSpyMode = static_cast<Vector::ASC::Most25ControlMessageSpyMode *>(event);
    BOOST_CHECK(isEqual(most25ControlMessageSpyMode->time, 0.113526));
    BOOST_CHECK(most25ControlMessageSpyMode->channel == 1);
    BOOST_CHECK(most25ControlMessageSpyMode->sourceAdr == 0xFFFF);
    BOOST_CHECK(most25ControlMessageSpyMode->destAdr == 0x0100);
    BOOST_CHECK(most25ControlMessageSpyMode->rType == 0x00);
    BOOST_REQUIRE(most25ControlMessageSpyMode->data.size() == 17);
    BOOST_CHECK(most25ControlMessageSpyMode->data[0] == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->data[1] == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->data[2] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[3] == 0x0C);
    BOOST_CHECK(most25ControlMessageSpyMode->data[4] == 0x04);
    BOOST_CHECK(most25ControlMessageSpyMode->data[5] == 0x31);
    BOOST_CHECK(most25ControlMessageSpyMode->data[6] == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->data[7] == 0x52);
    BOOST_CHECK(most25ControlMessageSpyMode->data[8] == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->data[9] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[10] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[11] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[12] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[13] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[14] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[15] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[16] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->state == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->ackNack == 0x12);
    BOOST_CHECK(most25ControlMessageSpyMode->crc == 0xAA33);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most25Packet)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25Packet * most25Packet;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25Packet);
    most25Packet = static_cast<Vector::ASC::Most25Packet *>(event);
    BOOST_CHECK(isEqual(most25Packet->time, 4.445080));
    BOOST_CHECK(most25Packet->channel == 1);
    BOOST_CHECK(most25Packet->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(most25Packet->sourceAdr == 0x0101);
    BOOST_CHECK(most25Packet->destAdr == 0x0100);
    BOOST_CHECK(most25Packet->pktState == 0x00);
    BOOST_CHECK(most25Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(most25Packet->pktPrio == 0);
    BOOST_CHECK(most25Packet->pktArbitr == 0x03);
    BOOST_CHECK(most25Packet->crc2 == 0x0000);
    BOOST_CHECK(most25Packet->pktLen == 0x00A);
    BOOST_REQUIRE(most25Packet->data.size() == 0x00A);
    BOOST_CHECK(most25Packet->data[0] == 0x52);
    BOOST_CHECK(most25Packet->data[1] == 0x01);
    BOOST_CHECK(most25Packet->data[2] == 0xE0);
    BOOST_CHECK(most25Packet->data[3] == 0x3C);
    BOOST_CHECK(most25Packet->data[4] == 0x90);
    BOOST_CHECK(most25Packet->data[5] == 0x01);
    BOOST_CHECK(most25Packet->data[6] == 0xFD);
    BOOST_CHECK(most25Packet->data[7] == 0x00);
    BOOST_CHECK(most25Packet->data[8] == 0x00);
    BOOST_CHECK(most25Packet->data[9] == 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostLightLock)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostLightLock.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostLightLock * mostLightLock;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostLightLock);
    mostLightLock = static_cast<Vector::ASC::MostLightLock *>(event);
    BOOST_CHECK(isEqual(mostLightLock->time, 0.008638));
    BOOST_CHECK(mostLightLock->channel == 1);
    BOOST_CHECK(mostLightLock->llState == 1);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostSpecialRegister)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostSpecialRegister.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostSpecialRegister * mostSpecialRegister;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostSpecialRegister);
    mostSpecialRegister = static_cast<Vector::ASC::MostSpecialRegister *>(event);
    BOOST_CHECK(isEqual(mostSpecialRegister->time, 1.471300));
    BOOST_CHECK(mostSpecialRegister->channel == 1);
    BOOST_CHECK(mostSpecialRegister->regSubType == Vector::ASC::MostRegSubType::Notify);
    BOOST_CHECK(mostSpecialRegister->regId == 0x8A);
    BOOST_CHECK(mostSpecialRegister->regValue == 0x0172);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostCommonRegister)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostCommonRegister.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostCommonRegister * mostCommonRegister;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostCommonRegister);
    mostCommonRegister = static_cast<Vector::ASC::MostCommonRegister *>(event);
    BOOST_CHECK(isEqual(mostCommonRegister->time, 9.050000));
    BOOST_CHECK(mostCommonRegister->channel == 1);
    BOOST_CHECK(mostCommonRegister->regSubType == Vector::ASC::MostRegSubType::Unspecified);
    BOOST_CHECK(mostCommonRegister->regChip == 0x01);
    BOOST_CHECK(mostCommonRegister->regOffset == 0x0000);
    BOOST_CHECK(mostCommonRegister->regDataLen == 0x10);
    BOOST_REQUIRE(mostCommonRegister->data.size() == 0x10);
    BOOST_CHECK(mostCommonRegister->data[0] == 0x00);
    BOOST_CHECK(mostCommonRegister->data[1] == 0x01);
    BOOST_CHECK(mostCommonRegister->data[2] == 0x02);
    BOOST_CHECK(mostCommonRegister->data[3] == 0x03);
    BOOST_CHECK(mostCommonRegister->data[4] == 0x04);
    BOOST_CHECK(mostCommonRegister->data[5] == 0x05);
    BOOST_CHECK(mostCommonRegister->data[6] == 0x06);
    BOOST_CHECK(mostCommonRegister->data[7] == 0x07);
    BOOST_CHECK(mostCommonRegister->data[8] == 0x08);
    BOOST_CHECK(mostCommonRegister->data[9] == 0x09);
    BOOST_CHECK(mostCommonRegister->data[10] == 0x0A);
    BOOST_CHECK(mostCommonRegister->data[11] == 0x0B);
    BOOST_CHECK(mostCommonRegister->data[12] == 0x0C);
    BOOST_CHECK(mostCommonRegister->data[13] == 0x0D);
    BOOST_CHECK(mostCommonRegister->data[14] == 0x0E);
    BOOST_CHECK(mostCommonRegister->data[15] == 0x0F);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostHwMode)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostHwMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostHwMode * mostHwMode;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostHwMode);
    mostHwMode = static_cast<Vector::ASC::MostHwMode *>(event);
    BOOST_CHECK(isEqual(mostHwMode->time, 3.560000));
    BOOST_CHECK(mostHwMode->channel == 1);
    BOOST_CHECK(mostHwMode->hwMode == 0x01);
    BOOST_CHECK(mostHwMode->hwModeMask == 0x01);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostNetState)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostNetState.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostNetState * mostNetState;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostNetState);
    mostNetState = static_cast<Vector::ASC::MostNetState *>(event);
    BOOST_CHECK(isEqual(mostNetState->time, 1.027900));
    BOOST_CHECK(mostNetState->channel == 1);
    BOOST_CHECK(mostNetState->netStateOld == 2);
    BOOST_CHECK(mostNetState->netStateNew == 3);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostDataLost)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostDataLost.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostDataLost * mostDataLost;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostDataLost);
    mostDataLost = static_cast<Vector::ASC::MostDataLost *>(event);
    BOOST_CHECK(isEqual(mostDataLost->time, 1.303700));
    BOOST_CHECK(mostDataLost->channel == 1);
    BOOST_CHECK(mostDataLost->dlInfo == 0x00000005);
    BOOST_CHECK(mostDataLost->dlCtrl == 0x003F);
    BOOST_CHECK(mostDataLost->dlAsync == 0x000D);
    BOOST_CHECK(isEqual(mostDataLost->dlTime[0], 101.30369));
    BOOST_CHECK(isEqual(mostDataLost->dlTime[1], 2223.52592));
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostTrigger)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostTrigger.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostTrigger * mostTrigger;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostTrigger);
    mostTrigger = static_cast<Vector::ASC::MostTrigger *>(event);
    BOOST_CHECK(isEqual(mostTrigger->time, 1.303700));
    BOOST_CHECK(mostTrigger->channel == 1);
    BOOST_CHECK(mostTrigger->trigMode == Vector::ASC::MostTrigMode::SynchronizationSlave);
    BOOST_CHECK(mostTrigger->trigHw == 4);
    BOOST_CHECK(mostTrigger->trigValue[0] == 0x00000001);
    BOOST_CHECK(mostTrigger->trigValue[1] == 0x00000000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostStatistic)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStatistic.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStatistic * mostStatistic;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStatistic);
    mostStatistic = static_cast<Vector::ASC::MostStatistic *>(event);
    BOOST_CHECK(isEqual(mostStatistic->time, 2.030000));
    BOOST_CHECK(mostStatistic->channel == 1);
    BOOST_CHECK(mostStatistic->fr == 0);
    BOOST_CHECK(mostStatistic->lt == 4);
    BOOST_CHECK(mostStatistic->bl == 0);
    BOOST_CHECK(mostStatistic->pk == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostStatisticExtended)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStatisticExtended.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStatisticExtended * mostStatisticExtended;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStatisticExtended);
    mostStatisticExtended = static_cast<Vector::ASC::MostStatisticExtended *>(event);
    BOOST_CHECK(isEqual(mostStatisticExtended->time, 2.024742));
    BOOST_CHECK(mostStatisticExtended->channel == 2);
    BOOST_CHECK(mostStatisticExtended->codingErrors == 0x000006);
    BOOST_CHECK(mostStatisticExtended->frameCounter == 0x00A395);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostTxLight)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostTxLight.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostTxLight * mostTxLight;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostTxLight);
    mostTxLight = static_cast<Vector::ASC::MostTxLight *>(event);
    BOOST_CHECK(isEqual(mostTxLight->time, 0.008638));
    BOOST_CHECK(mostTxLight->channel == 1);
    BOOST_CHECK(mostTxLight->txLightState == Vector::ASC::MostTxLightState::Enabled);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostStress)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStress.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStress * mostStress;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStress);
    mostStress = static_cast<Vector::ASC::MostStress *>(event);
    BOOST_CHECK(isEqual(mostStress->time, 1.793083));
    BOOST_CHECK(mostStress->channel == 1);
    BOOST_CHECK(mostStress->stressMode == 2);
    BOOST_CHECK(mostStress->stressState == Vector::ASC::MostStressState::Started);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most25AllocTable)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25AllocTable.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25AllocTable * most25AllocTable;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25AllocTable);
    most25AllocTable = static_cast<Vector::ASC::Most25AllocTable *>(event);
    BOOST_CHECK(isEqual(most25AllocTable->time, 0.032775));
    BOOST_CHECK(most25AllocTable->channel == 2);
    BOOST_CHECK(most25AllocTable->allocTableSize == 0x003C);
    BOOST_REQUIRE(most25AllocTable->data.size() == 0x003C);
    BOOST_CHECK(most25AllocTable->data[0x00] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x01] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x02] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x03] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x04] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x05] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x06] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x07] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x08] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x09] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0a] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0b] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0c] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0d] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0e] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0f] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x10] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x11] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x12] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x13] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x14] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x15] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x16] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x17] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x18] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x19] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1a] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1b] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1c] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1d] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1e] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1f] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x20] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x21] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x22] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x23] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x24] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x25] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x26] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x27] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x28] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x29] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2a] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2b] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2c] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2d] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2e] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2f] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x30] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x31] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x32] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x33] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x34] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x35] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x36] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x37] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x38] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x39] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x3a] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x3b] == 0x70);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150ControlMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150ControlMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150ControlMessage * most150ControlMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150ControlMessage);
    most150ControlMessage = static_cast<Vector::ASC::Most150ControlMessage *>(event);
    BOOST_CHECK(isEqual(most150ControlMessage->time, 5.708800));
    BOOST_CHECK(most150ControlMessage->channel == 1);
    BOOST_CHECK(most150ControlMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(most150ControlMessage->sourceAdr == 0x0172);
    BOOST_CHECK(most150ControlMessage->destAdr == 0x03C8);
    BOOST_CHECK(most150ControlMessage->state == 0x02);
    BOOST_CHECK(most150ControlMessage->ackNack == 0x11);
    BOOST_CHECK(most150ControlMessage->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(most150ControlMessage->pAck == 0x22);
    BOOST_CHECK(most150ControlMessage->priority == 0x01);
    BOOST_CHECK(most150ControlMessage->pIndex == 0x33);
    BOOST_CHECK(most150ControlMessage->crc2 == 0xAABB);
    BOOST_CHECK(most150ControlMessage->cAck == 0x44);
    BOOST_CHECK(most150ControlMessage->rsvdUl == 0x00);
    BOOST_CHECK(most150ControlMessage->msg150Len == 0x08);
    BOOST_REQUIRE(most150ControlMessage->data.size() == 0x08);
    BOOST_CHECK(most150ControlMessage->data[0] == 0x11);
    BOOST_CHECK(most150ControlMessage->data[1] == 0x22);
    BOOST_CHECK(most150ControlMessage->data[2] == 0x33);
    BOOST_CHECK(most150ControlMessage->data[3] == 0x34);
    BOOST_CHECK(most150ControlMessage->data[4] == 0x00);
    BOOST_CHECK(most150ControlMessage->data[5] == 0x02);
    BOOST_CHECK(most150ControlMessage->data[6] == 0x11);
    BOOST_CHECK(most150ControlMessage->data[7] == 0x22);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150ControlMessageFragment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150ControlMessageFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150ControlMessageFragment * most150ControlMessageFragment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150ControlMessageFragment);
    most150ControlMessageFragment = static_cast<Vector::ASC::Most150ControlMessageFragment *>(event);
    BOOST_CHECK(isEqual(most150ControlMessageFragment->time, 5.708800));
    BOOST_CHECK(most150ControlMessageFragment->channel == 1);
    BOOST_CHECK(most150ControlMessageFragment->frgMask == 0x01020304);
    BOOST_CHECK(most150ControlMessageFragment->sourceAdr == 0x0172);
    BOOST_CHECK(most150ControlMessageFragment->destAdr == 0x03C8);
    BOOST_CHECK(most150ControlMessageFragment->ackNack == 0x11);
    BOOST_CHECK(most150ControlMessageFragment->pAck == 0x22);
    BOOST_CHECK(most150ControlMessageFragment->priority == 0x01);
    BOOST_CHECK(most150ControlMessageFragment->pIndex == 0x33);
    BOOST_CHECK(most150ControlMessageFragment->crc2 == 0xAABB);
    BOOST_CHECK(most150ControlMessageFragment->cAck == 0x44);
    BOOST_CHECK(most150ControlMessageFragment->rsvdUl == 0x00);
    BOOST_CHECK(most150ControlMessageFragment->frgDataLen == 0x0006);
    BOOST_CHECK(most150ControlMessageFragment->frgDataLenAnnounced == 0x0210);
    BOOST_CHECK(most150ControlMessageFragment->firstDataLen == 0x06);
    BOOST_REQUIRE(most150ControlMessageFragment->data.size() == 0x06);
    BOOST_CHECK(most150ControlMessageFragment->data[0] == 0x01);
    BOOST_CHECK(most150ControlMessageFragment->data[1] == 0x02);
    BOOST_CHECK(most150ControlMessageFragment->data[2] == 0x03);
    BOOST_CHECK(most150ControlMessageFragment->data[3] == 0x04);
    BOOST_CHECK(most150ControlMessageFragment->data[4] == 0x05);
    BOOST_CHECK(most150ControlMessageFragment->data[5] == 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150Packet)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150Packet * most150Packet;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150Packet);
    most150Packet = static_cast<Vector::ASC::Most150Packet *>(event);
    BOOST_CHECK(isEqual(most150Packet->time, 5.708800));
    BOOST_CHECK(most150Packet->channel == 1);
    BOOST_CHECK(most150Packet->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(most150Packet->sourceAdr == 0x0172);
    BOOST_CHECK(most150Packet->destAdr == 0x03C8);
    BOOST_CHECK(most150Packet->state == 0x02);
    BOOST_CHECK(most150Packet->ackNack == 0x11);
    BOOST_CHECK(most150Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(most150Packet->pAck == 0x00);
    BOOST_CHECK(most150Packet->rsvdUc == 0x00);
    BOOST_CHECK(most150Packet->pIndex == 0x33);
    BOOST_CHECK(most150Packet->crc2 == 0xAABB);
    BOOST_CHECK(most150Packet->cAck == 0x44);
    BOOST_CHECK(most150Packet->rsvdUl == 0x00);
    BOOST_CHECK(most150Packet->pkt150Len == 0x08);
    BOOST_REQUIRE(most150Packet->data.size() == 0x08);
    BOOST_CHECK(most150Packet->data[0] == 0x11);
    BOOST_CHECK(most150Packet->data[1] == 0x22);
    BOOST_CHECK(most150Packet->data[2] == 0x33);
    BOOST_CHECK(most150Packet->data[3] == 0x34);
    BOOST_CHECK(most150Packet->data[4] == 0x00);
    BOOST_CHECK(most150Packet->data[5] == 0x02);
    BOOST_CHECK(most150Packet->data[6] == 0x11);
    BOOST_CHECK(most150Packet->data[7] == 0x22);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150PacketFragment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150PacketFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150PacketFragment * most150PacketFragment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150PacketFragment);
    most150PacketFragment = static_cast<Vector::ASC::Most150PacketFragment *>(event);
    BOOST_CHECK(isEqual(most150PacketFragment->time, 5.708800));
    BOOST_CHECK(most150PacketFragment->channel == 1);
    BOOST_CHECK(most150PacketFragment->frgMask == 0x01020304);
    BOOST_CHECK(most150PacketFragment->sourceAdr == 0x0172);
    BOOST_CHECK(most150PacketFragment->destAdr == 0x03C8);
    BOOST_CHECK(most150PacketFragment->ackNack == 0x11);
    BOOST_CHECK(most150PacketFragment->pAck == 0x22);
    BOOST_CHECK(most150PacketFragment->rsvdUc == 0x01);
    BOOST_CHECK(most150PacketFragment->pIndex == 0x33);
    BOOST_CHECK(most150PacketFragment->crc2 == 0xAABB);
    BOOST_CHECK(most150PacketFragment->cAck == 0x44);
    BOOST_CHECK(most150PacketFragment->rsvdUl == 0x00);
    BOOST_CHECK(most150PacketFragment->frgDataLen == 0x0006);
    BOOST_CHECK(most150PacketFragment->frgDataLenAnnounced == 0x0210);
    BOOST_CHECK(most150PacketFragment->firstDataLen == 0x06);
    BOOST_REQUIRE(most150PacketFragment->data.size() == 0x06);
    BOOST_CHECK(most150PacketFragment->data[0] == 0x01);
    BOOST_CHECK(most150PacketFragment->data[1] == 0x02);
    BOOST_CHECK(most150PacketFragment->data[2] == 0x03);
    BOOST_CHECK(most150PacketFragment->data[3] == 0x04);
    BOOST_CHECK(most150PacketFragment->data[4] == 0x05);
    BOOST_CHECK(most150PacketFragment->data[5] == 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostEthernetPacket)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEthernetPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEthernetPacket * mostEthernetPacket;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEthernetPacket);
    mostEthernetPacket = static_cast<Vector::ASC::MostEthernetPacket *>(event);
    BOOST_CHECK(isEqual(mostEthernetPacket->time, 5.708800));
    BOOST_CHECK(mostEthernetPacket->channel == 1);
    BOOST_CHECK(mostEthernetPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(mostEthernetPacket->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPacket->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPacket->state == 0x02);
    BOOST_CHECK(mostEthernetPacket->ackNack == 0x11);
    BOOST_CHECK(mostEthernetPacket->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(mostEthernetPacket->pAck == 0x22);
    BOOST_CHECK(mostEthernetPacket->crc4 == 0xAABBCCDD);
    BOOST_CHECK(mostEthernetPacket->cAck == 0x44);
    BOOST_CHECK(mostEthernetPacket->rsvdUl == 0x00);
    BOOST_CHECK(mostEthernetPacket->pktEthLen == 0x08);
    BOOST_REQUIRE(mostEthernetPacket->data.size() == 0x08);
    BOOST_CHECK(mostEthernetPacket->data[0] == 0x11);
    BOOST_CHECK(mostEthernetPacket->data[1] == 0x22);
    BOOST_CHECK(mostEthernetPacket->data[2] == 0x33);
    BOOST_CHECK(mostEthernetPacket->data[3] == 0x34);
    BOOST_CHECK(mostEthernetPacket->data[4] == 0x00);
    BOOST_CHECK(mostEthernetPacket->data[5] == 0x02);
    BOOST_CHECK(mostEthernetPacket->data[6] == 0x11);
    BOOST_CHECK(mostEthernetPacket->data[7] == 0x22);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostEthernetPacketFragment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEthernetPacketFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEthernetPacketFragment * mostEthernetPacketFragment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEthernetPacketFragment);
    mostEthernetPacketFragment = static_cast<Vector::ASC::MostEthernetPacketFragment *>(event);
    BOOST_CHECK(isEqual(mostEthernetPacketFragment->time, 5.708800));
    BOOST_CHECK(mostEthernetPacketFragment->channel == 1);
    BOOST_CHECK(mostEthernetPacketFragment->frgMask == 0x01020304);
    BOOST_CHECK(mostEthernetPacketFragment->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPacketFragment->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPacketFragment->ackNack == 0x11);
    BOOST_CHECK(mostEthernetPacketFragment->pAck == 0x01);
    BOOST_CHECK(mostEthernetPacketFragment->crc4 == 0xAABBCCDD);
    BOOST_CHECK(mostEthernetPacketFragment->cAck == 0x44);
    BOOST_CHECK(mostEthernetPacketFragment->rsvdUl == 0x00);
    BOOST_CHECK(mostEthernetPacketFragment->frgDataLen == 0x0006);
    BOOST_CHECK(mostEthernetPacketFragment->frgDataLenAnnounced == 0x0210);
    BOOST_CHECK(mostEthernetPacketFragment->firstDataLen == 0x06);
    BOOST_REQUIRE(mostEthernetPacketFragment->data.size() == 0x06);
    BOOST_CHECK(mostEthernetPacketFragment->data[0] == 0x01);
    BOOST_CHECK(mostEthernetPacketFragment->data[1] == 0x02);
    BOOST_CHECK(mostEthernetPacketFragment->data[2] == 0x03);
    BOOST_CHECK(mostEthernetPacketFragment->data[3] == 0x04);
    BOOST_CHECK(mostEthernetPacketFragment->data[4] == 0x05);
    BOOST_CHECK(mostEthernetPacketFragment->data[5] == 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostSystem)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostSystem.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostSystem * mostSystem;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostSystem);
    mostSystem = static_cast<Vector::ASC::MostSystem *>(event);
    BOOST_CHECK(isEqual(mostSystem->time, 1.027900));
    BOOST_CHECK(mostSystem->channel == 1);
    BOOST_CHECK(mostSystem->sysId == Vector::ASC::MostSysId::SystemLock);
    BOOST_CHECK(mostSystem->sysValue == 0x0001);
    BOOST_CHECK(mostSystem->sysValueOld == 0x0000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150AllocTable)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150AllocTable.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150AllocTable * most150AllocTable;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150AllocTable);
    most150AllocTable = static_cast<Vector::ASC::Most150AllocTable *>(event);
    BOOST_CHECK(isEqual(most150AllocTable->time, 44.814398));
    BOOST_CHECK(most150AllocTable->channel == 1);
    BOOST_CHECK(most150AllocTable->at150EventModeFlags == 0x00);
    BOOST_CHECK(most150AllocTable->freeBytes == 0x002E);
    BOOST_CHECK(most150AllocTable->at150Size == 0x0004);
    BOOST_REQUIRE(most150AllocTable->wordData.size() == 0x0004);
    BOOST_CHECK(most150AllocTable->wordData[0] == 0x010B);
    BOOST_CHECK(most150AllocTable->wordData[1] == 0x0004);
    BOOST_CHECK(most150AllocTable->wordData[2] == 0x4151);
    BOOST_CHECK(most150AllocTable->wordData[3] == 0x0046);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150AllocTable);
    most150AllocTable = static_cast<Vector::ASC::Most150AllocTable *>(event);
    BOOST_CHECK(isEqual(most150AllocTable->time, 50.126855));
    BOOST_CHECK(most150AllocTable->channel == 1);
    BOOST_CHECK(most150AllocTable->at150EventModeFlags == 0x00);
    BOOST_CHECK(most150AllocTable->freeBytes == 0x0074);
    BOOST_CHECK(most150AllocTable->at150Size == 0x0004);
    BOOST_REQUIRE(most150AllocTable->wordData.size() == 0x0004);
    BOOST_CHECK(most150AllocTable->wordData[0] == 0x010B);
    BOOST_CHECK(most150AllocTable->wordData[1] == 0x0004);
    BOOST_CHECK(most150AllocTable->wordData[2] == 0x8151);
    BOOST_CHECK(most150AllocTable->wordData[3] == 0x0046);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most50ControlMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most50ControlMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most50ControlMessage * most50ControlMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most50ControlMessage);
    most50ControlMessage = static_cast<Vector::ASC::Most50ControlMessage *>(event);
    BOOST_CHECK(isEqual(most50ControlMessage->time, 0.200000));
    BOOST_CHECK(most50ControlMessage->channel == 1);
    BOOST_CHECK(most50ControlMessage->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(most50ControlMessage->sourceAdr == 0xEF00);
    BOOST_CHECK(most50ControlMessage->destAdr == 0x0101);
    BOOST_CHECK(most50ControlMessage->state == 0x01);
    BOOST_CHECK(most50ControlMessage->ackNack == 0x00);
    BOOST_CHECK(most50ControlMessage->transferType == Vector::ASC::MostTransferType::Spy);
    BOOST_CHECK(most50ControlMessage->rsvdUc1 == 0x00);
    BOOST_CHECK(most50ControlMessage->priority == 0x00);
    BOOST_CHECK(most50ControlMessage->rsvdUc2 == 0x00);
    BOOST_CHECK(most50ControlMessage->crc2 == 0x5678);
    BOOST_CHECK(most50ControlMessage->rsvdUc3 == 0x00);
    BOOST_CHECK(most50ControlMessage->rsvdUl == 0x00);
    BOOST_CHECK(most50ControlMessage->msg50Len == 0x09);
    BOOST_REQUIRE(most50ControlMessage->data.size() == 0x09);
    BOOST_CHECK(most50ControlMessage->data[0] == 0x11);
    BOOST_CHECK(most50ControlMessage->data[1] == 0x01);
    BOOST_CHECK(most50ControlMessage->data[2] == 0x22);
    BOOST_CHECK(most50ControlMessage->data[3] == 0x23);
    BOOST_CHECK(most50ControlMessage->data[4] == 0x04);
    BOOST_CHECK(most50ControlMessage->data[5] == 0x11);
    BOOST_CHECK(most50ControlMessage->data[6] == 0x22);
    BOOST_CHECK(most50ControlMessage->data[7] == 0x33);
    BOOST_CHECK(most50ControlMessage->data[8] == 0x44);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most50Packet)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most50Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most50Packet * most50Packet;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most50Packet);
    most50Packet = static_cast<Vector::ASC::Most50Packet *>(event);
    BOOST_CHECK(isEqual(most50Packet->time, 5.708800));
    BOOST_CHECK(most50Packet->channel == 1);
    BOOST_CHECK(most50Packet->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(most50Packet->sourceAdr == 0x0172);
    BOOST_CHECK(most50Packet->destAdr == 0x03C8);
    BOOST_CHECK(most50Packet->state == 0x02);
    BOOST_CHECK(most50Packet->ackNack == 0x11);
    BOOST_CHECK(most50Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(most50Packet->rsvdUc1 == 0x00);
    BOOST_CHECK(most50Packet->rsvdUc2 == 0x00);
    BOOST_CHECK(most50Packet->rsvdUc3 == 0x00);
    BOOST_CHECK(most50Packet->crc2 == 0xAABB);
    BOOST_CHECK(most50Packet->rsvdUc4 == 0x00);
    BOOST_CHECK(most50Packet->rsvdUl == 0x00);
    BOOST_CHECK(most50Packet->pktLen == 0x08);
    BOOST_REQUIRE(most50Packet->data.size() == 0x08);
    BOOST_CHECK(most50Packet->data[0] == 0x11);
    BOOST_CHECK(most50Packet->data[1] == 0x22);
    BOOST_CHECK(most50Packet->data[2] == 0x33);
    BOOST_CHECK(most50Packet->data[3] == 0x34);
    BOOST_CHECK(most50Packet->data[4] == 0x00);
    BOOST_CHECK(most50Packet->data[5] == 0x02);
    BOOST_CHECK(most50Packet->data[6] == 0x11);
    BOOST_CHECK(most50Packet->data[7] == 0x22);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostEcl)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEcl.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEcl * mostEcl;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEcl);
    mostEcl = static_cast<Vector::ASC::MostEcl *>(event);
    BOOST_CHECK(isEqual(mostEcl->time, 0.009068));
    BOOST_CHECK(mostEcl->eclMode == Vector::ASC::MostEclMode::Discrete);
    BOOST_CHECK(mostEcl->eclState == Vector::ASC::MostEclState::LineHigh);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* TP/Diagnostics Events */
BOOST_AUTO_TEST_CASE(TpSingleFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpSingleFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpSingleFrame * tpDiagSingleFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpSingleFrame);
    tpDiagSingleFrame = static_cast<Vector::ASC::TpSingleFrame *>(event);
    BOOST_CHECK(tpDiagSingleFrame->canChannel == 1);
    BOOST_CHECK(tpDiagSingleFrame->connectionId == 0x05);
    BOOST_CHECK(tpDiagSingleFrame->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK(tpDiagSingleFrame->source == "<tester>");
    BOOST_CHECK(tpDiagSingleFrame->destination == "Any_ECU_example");
    BOOST_CHECK(tpDiagSingleFrame->length == 0x02);
    BOOST_REQUIRE(tpDiagSingleFrame->transportedBytes.size() == 0x02);
    BOOST_CHECK(tpDiagSingleFrame->transportedBytes[0] == 0x1A);
    BOOST_CHECK(tpDiagSingleFrame->transportedBytes[1] == 0x90);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(TpDiagFirstFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpFirstFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpFirstFrame * tpFirstFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpFirstFrame);
    tpFirstFrame = static_cast<Vector::ASC::TpFirstFrame *>(event);
    BOOST_CHECK(tpFirstFrame->canChannel == 1);
    BOOST_CHECK(tpFirstFrame->connectionId == 0x07);
    BOOST_CHECK(tpFirstFrame->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK(tpFirstFrame->source == "Any_ECU_example");
    BOOST_CHECK(tpFirstFrame->destination == "<tester>");
    BOOST_CHECK(tpFirstFrame->length == 0x000C);
    BOOST_REQUIRE(tpFirstFrame->transportedBytes.size() == 6);
    BOOST_CHECK(tpFirstFrame->transportedBytes[0] == 0x5A);
    BOOST_CHECK(tpFirstFrame->transportedBytes[1] == 0x90);
    BOOST_CHECK(tpFirstFrame->transportedBytes[2] == 0x98);
    BOOST_CHECK(tpFirstFrame->transportedBytes[3] == 0x76);
    BOOST_CHECK(tpFirstFrame->transportedBytes[4] == 0x54);
    BOOST_CHECK(tpFirstFrame->transportedBytes[5] == 0x32);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(TpConsecutiveFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpConsecutiveFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpConsecutiveFrame * tpConsecutiveFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpConsecutiveFrame);
    tpConsecutiveFrame = static_cast<Vector::ASC::TpConsecutiveFrame *>(event);
    BOOST_CHECK(tpConsecutiveFrame->canChannel == 1);
    BOOST_CHECK(tpConsecutiveFrame->connectionId == 0x07);
    BOOST_CHECK(tpConsecutiveFrame->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK(tpConsecutiveFrame->source == "Any_ECU_example");
    BOOST_CHECK(tpConsecutiveFrame->destination == "<tester>");
    BOOST_CHECK(tpConsecutiveFrame->sn == 1);
    BOOST_REQUIRE(tpConsecutiveFrame->transportedBytes.size() == 7);
    BOOST_CHECK(tpConsecutiveFrame->transportedBytes[0] == 0x10);
    BOOST_CHECK(tpConsecutiveFrame->transportedBytes[1] == 0x00);
    BOOST_CHECK(tpConsecutiveFrame->transportedBytes[2] == 0x99);
    BOOST_CHECK(tpConsecutiveFrame->transportedBytes[3] == 0x99);
    BOOST_CHECK(tpConsecutiveFrame->transportedBytes[4] == 0x00);
    BOOST_CHECK(tpConsecutiveFrame->transportedBytes[5] == 0x01);
    BOOST_CHECK(tpConsecutiveFrame->transportedBytes[6] == 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(TpFlowControlFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpFlowControlFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpFlowControlFrame * tpFlowControlFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpFlowControlFrame);
    tpFlowControlFrame = static_cast<Vector::ASC::TpFlowControlFrame *>(event);
    BOOST_CHECK(tpFlowControlFrame->canChannel == 1);
    BOOST_CHECK(tpFlowControlFrame->connectionId == 0x07);
    BOOST_CHECK(tpFlowControlFrame->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK(tpFlowControlFrame->source == "<tester>");
    BOOST_CHECK(tpFlowControlFrame->destination == "Any_ECU_example");
    BOOST_CHECK(tpFlowControlFrame->fcType == Vector::ASC::TpDiagFcType::Cts);
    BOOST_CHECK(tpFlowControlFrame->bs == 0x00);
    BOOST_CHECK(tpFlowControlFrame->stMin == 0x14);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(DiagRequest)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/DiagRequest.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::DiagRequest * diagRequest;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK(isEqual(diagRequest->time, 1.765500));
    BOOST_CHECK(diagRequest->ecuQualifier == "Any_ECU_example");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::ByteSequence);
    BOOST_REQUIRE(diagRequest->byteSequence.size() == 2);
    BOOST_CHECK(diagRequest->byteSequence[0] == 0x1A);
    BOOST_CHECK(diagRequest->byteSequence[1] == 0x90);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK(isEqual(diagRequest->time, 1.000000));
    BOOST_CHECK(diagRequest->ecuQualifier == "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::Open);
    BOOST_CHECK(diagRequest->byteSequence.size() == 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK(isEqual(diagRequest->time, 1.000000));
    BOOST_CHECK(diagRequest->ecuQualifier == "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::ByteSequence);
    BOOST_REQUIRE(diagRequest->byteSequence.size() == 1);
    BOOST_CHECK(diagRequest->byteSequence[0] == 0x20);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK(isEqual(diagRequest->time, 1.000000));
    BOOST_CHECK(diagRequest->ecuQualifier == "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::Close);
    BOOST_CHECK(diagRequest->byteSequence.size() == 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK(isEqual(diagRequest->time, 1.000000));
    BOOST_CHECK(diagRequest->ecuQualifier == "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::TpOn);
    BOOST_CHECK(diagRequest->byteSequence.size() == 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK(isEqual(diagRequest->time, 1.000000));
    BOOST_CHECK(diagRequest->ecuQualifier == "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::TpOff);
    BOOST_CHECK(diagRequest->byteSequence.size() == 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(StartOfMeasurement)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/StartOfMeasurement.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::StartOfMeasurement * startOfMeasurement;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::StartOfMeasurement);
    startOfMeasurement = static_cast<Vector::ASC::StartOfMeasurement *>(event);
    BOOST_CHECK(isEqual(startOfMeasurement->time, 0.000000));
    BOOST_CHECK(startOfMeasurement->language == Vector::ASC::File::Language::De);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::StartOfMeasurement);
    startOfMeasurement = static_cast<Vector::ASC::StartOfMeasurement *>(event);
    BOOST_CHECK(isEqual(startOfMeasurement->time, 1.000000));
    BOOST_CHECK(startOfMeasurement->language == Vector::ASC::File::Language::En);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
