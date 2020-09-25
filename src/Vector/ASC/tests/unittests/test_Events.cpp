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

/* File */
BOOST_AUTO_TEST_CASE(FileDate) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileDate.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileDate * fileDate;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);
    fileDate = static_cast<Vector::ASC::FileDate *>(event);
    BOOST_CHECK_EQUAL(fileDate->date.tm_wday, 3);
    BOOST_CHECK_EQUAL(fileDate->date.tm_mon, 5);
    BOOST_CHECK_EQUAL(fileDate->date.tm_mday, 11);
    BOOST_CHECK_EQUAL(fileDate->date.tm_hour, 11);
    BOOST_CHECK_EQUAL(fileDate->date.tm_min, 37);
    BOOST_CHECK_EQUAL(fileDate->date.tm_sec, 33);
    BOOST_CHECK_EQUAL(fileDate->date.tm_year, (2008 - 1900));
    BOOST_CHECK(fileDate->language == Vector::ASC::File::Language::En);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);
    fileDate = static_cast<Vector::ASC::FileDate *>(event);
    BOOST_CHECK_EQUAL(fileDate->date.tm_wday, 2);
    BOOST_CHECK_EQUAL(fileDate->date.tm_mon, 2);
    BOOST_CHECK_EQUAL(fileDate->date.tm_mday, 13);
    BOOST_CHECK_EQUAL(fileDate->date.tm_hour, 11);
    BOOST_CHECK_EQUAL(fileDate->date.tm_min, 58);
    BOOST_CHECK_EQUAL(fileDate->date.tm_sec, 02);
    BOOST_CHECK_EQUAL(fileDate->date.tm_year, (2007 - 1900));
    BOOST_CHECK(fileDate->language == Vector::ASC::File::Language::De);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileBaseTimestamps) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileBaseTimestamps.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileBaseTimestamps * fileBaseTimestamps;

    event = file.read();
    BOOST_REQUIRE(event);
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

BOOST_AUTO_TEST_CASE(FileInternalEventsLogged) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileInternalEventsLogged.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileInternalEventsLogged * fileInternalEventsLogged;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileInternalEventsLogged);
    fileInternalEventsLogged = static_cast<Vector::ASC::FileInternalEventsLogged *>(event);
    BOOST_CHECK_EQUAL(fileInternalEventsLogged->internalEventsLogged, true);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileInternalEventsLogged);
    fileInternalEventsLogged = static_cast<Vector::ASC::FileInternalEventsLogged *>(event);
    BOOST_CHECK_EQUAL(fileInternalEventsLogged->internalEventsLogged, false);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileVersion) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileVersion.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileVersion * fileVersion;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);
    fileVersion = static_cast<Vector::ASC::FileVersion *>(event);
    BOOST_CHECK_EQUAL(fileVersion->versionMajor, 7);
    BOOST_CHECK_EQUAL(fileVersion->versionMinor, 1);
    BOOST_CHECK_EQUAL(fileVersion->versionPatch, 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileSplitInformation) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileSplitInformation.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileSplitInformation * fileSplitInformation;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileSplitInformation);
    fileSplitInformation = static_cast<Vector::ASC::FileSplitInformation *>(event);
    BOOST_CHECK_EQUAL(fileSplitInformation->time, 60.0000);
    BOOST_CHECK_EQUAL(fileSplitInformation->fileName, "Inc_L1.asc");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FileComment) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileComment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileComment * fileComment;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileComment);
    fileComment = static_cast<Vector::ASC::FileComment *>(event);
    BOOST_CHECK_EQUAL(fileComment->comment, " comment");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN Events */
BOOST_AUTO_TEST_CASE(CanMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanMessage * canMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanMessage);
    canMessage = static_cast<Vector::ASC::CanMessage *>(event);
    BOOST_CHECK_EQUAL(canMessage->time, 0.003040);
    BOOST_CHECK_EQUAL(canMessage->channel, 1);
    BOOST_CHECK_EQUAL(canMessage->id, 0x123);
    BOOST_CHECK(canMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(canMessage->dlc, 2);
    BOOST_REQUIRE_EQUAL(canMessage->data.size(), 2);
    BOOST_CHECK_EQUAL(canMessage->data[0], 0x00);
    BOOST_CHECK_EQUAL(canMessage->data[1], 0x00);
    BOOST_CHECK_EQUAL(canMessage->messageDuration, 768000);
    BOOST_CHECK_EQUAL(canMessage->messageLength, 67);
    BOOST_CHECK_EQUAL(canMessage->messageId, 291);
    BOOST_CHECK_EQUAL(canMessage->messageFlags.te, false);
    BOOST_CHECK_EQUAL(canMessage->messageFlags.wu, false);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanMessage);
    canMessage = static_cast<Vector::ASC::CanMessage *>(event);
    BOOST_CHECK_EQUAL(canMessage->time, 2.500900);
    BOOST_CHECK_EQUAL(canMessage->channel, 1);
    BOOST_CHECK_EQUAL(canMessage->id, 0x64);
    BOOST_CHECK(canMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(canMessage->dlc, 8);
    BOOST_REQUIRE_EQUAL(canMessage->data.size(), 8);
    BOOST_CHECK_EQUAL(canMessage->data[0], 0x00);
    BOOST_CHECK_EQUAL(canMessage->data[1], 0x01);
    BOOST_CHECK_EQUAL(canMessage->data[2], 0x02);
    BOOST_CHECK_EQUAL(canMessage->data[3], 0x03);
    BOOST_CHECK_EQUAL(canMessage->data[4], 0x04);
    BOOST_CHECK_EQUAL(canMessage->data[5], 0x05);
    BOOST_CHECK_EQUAL(canMessage->data[6], 0x06);
    BOOST_CHECK_EQUAL(canMessage->data[7], 0x07);
    BOOST_CHECK_EQUAL(canMessage->messageDuration, 0);
    BOOST_CHECK_EQUAL(canMessage->messageLength, 0);
    BOOST_CHECK_EQUAL(canMessage->messageId, 0);
    BOOST_CHECK_EQUAL(canMessage->messageFlags.te, false);
    BOOST_CHECK_EQUAL(canMessage->messageFlags.wu, false);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanMessage);
    canMessage = static_cast<Vector::ASC::CanMessage *>(event);
    BOOST_CHECK_EQUAL(canMessage->time, 1.047413);
    BOOST_CHECK_EQUAL(canMessage->channel, 1);
    BOOST_CHECK_EQUAL(canMessage->id, 1792);
    BOOST_CHECK(canMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(canMessage->dlc, 8);
    BOOST_REQUIRE_EQUAL(canMessage->data.size(), 8);
    BOOST_CHECK_EQUAL(canMessage->data[0], 2);
    BOOST_CHECK_EQUAL(canMessage->data[1], 16);
    BOOST_CHECK_EQUAL(canMessage->data[2], 0);
    BOOST_CHECK_EQUAL(canMessage->data[3], 0);
    BOOST_CHECK_EQUAL(canMessage->data[4], 0);
    BOOST_CHECK_EQUAL(canMessage->data[5], 0);
    BOOST_CHECK_EQUAL(canMessage->data[6], 0);
    BOOST_CHECK_EQUAL(canMessage->data[7], 0);
    BOOST_CHECK_EQUAL(canMessage->messageDuration, 0);
    BOOST_CHECK_EQUAL(canMessage->messageLength, 0);
    BOOST_CHECK_EQUAL(canMessage->messageId, 1792);
    BOOST_CHECK_EQUAL(canMessage->messageFlags.te, false);
    BOOST_CHECK_EQUAL(canMessage->messageFlags.wu, false);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanExtendedMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanExtendedMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanExtendedMessage * canExtendedMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanExtendedMessage);
    canExtendedMessage = static_cast<Vector::ASC::CanExtendedMessage *>(event);
    BOOST_CHECK_EQUAL(canExtendedMessage->time, 4.876870);
    BOOST_CHECK_EQUAL(canExtendedMessage->channel, 1);
    BOOST_CHECK_EQUAL(canExtendedMessage->id, 0x54C5638);
    BOOST_CHECK(canExtendedMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(canExtendedMessage->dlc, 8);
    BOOST_REQUIRE_EQUAL(canExtendedMessage->data.size(), 8);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[0], 0x00);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[1], 0x00);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[2], 0x00);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[3], 0x00);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[4], 0x00);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[5], 0x00);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[6], 0x00);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[7], 0x00);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageDuration, 1704000);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageLength, 145);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageId, 88888888);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageFlags.te, false);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageFlags.wu, false);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanExtendedMessage);
    canExtendedMessage = static_cast<Vector::ASC::CanExtendedMessage *>(event);
    BOOST_CHECK_EQUAL(canExtendedMessage->time, 2.501000);
    BOOST_CHECK_EQUAL(canExtendedMessage->channel, 2);
    BOOST_CHECK_EQUAL(canExtendedMessage->id, 0xC8);
    BOOST_CHECK(canExtendedMessage->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(canExtendedMessage->dlc, 8);
    BOOST_REQUIRE_EQUAL(canExtendedMessage->data.size(), 8);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[0], 0x09);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[1], 0x08);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[2], 0x07);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[3], 0x06);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[4], 0x05);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[5], 0x04);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[6], 0x03);
    BOOST_CHECK_EQUAL(canExtendedMessage->data[7], 0x02);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageDuration, 0);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageLength, 0);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageId, 0);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageFlags.te, false);
    BOOST_CHECK_EQUAL(canExtendedMessage->messageFlags.wu, false);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanRemoteFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanRemoteFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanRemoteFrame * canRemoteFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanRemoteFrame);
    canRemoteFrame = static_cast<Vector::ASC::CanRemoteFrame *>(event);
    BOOST_CHECK_EQUAL(canRemoteFrame->time, 2.501000);
    BOOST_CHECK_EQUAL(canRemoteFrame->channel, 1);
    BOOST_CHECK_EQUAL(canRemoteFrame->id, 0x200);
    BOOST_CHECK(canRemoteFrame->dir == Vector::ASC::Dir::Tx);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanErrorFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanErrorFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanErrorFrame * canErrorFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorFrame);
    canErrorFrame = static_cast<Vector::ASC::CanErrorFrame *>(event);
    BOOST_CHECK_EQUAL(canErrorFrame->time, 1.592186);
    BOOST_CHECK_EQUAL(canErrorFrame->channel, 1);
    BOOST_CHECK_EQUAL(canErrorFrame->flags, 0x1);
    BOOST_CHECK_EQUAL(canErrorFrame->code, 0xA2);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorFrame);
    canErrorFrame = static_cast<Vector::ASC::CanErrorFrame *>(event);
    BOOST_CHECK_EQUAL(canErrorFrame->time, 1.592186);
    BOOST_CHECK_EQUAL(canErrorFrame->channel, 2);
    BOOST_CHECK_EQUAL(canErrorFrame->flags, 0xe);
    BOOST_CHECK_EQUAL(canErrorFrame->codeExt, 0x20a2);
    BOOST_CHECK_EQUAL(canErrorFrame->code, 0x82);
    BOOST_CHECK_EQUAL(canErrorFrame->id, 0);
    BOOST_CHECK_EQUAL(canErrorFrame->dlc, 0);
    BOOST_CHECK_EQUAL(canErrorFrame->position, 5);
    BOOST_CHECK_EQUAL(canErrorFrame->length, 11300);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorFrame);
    canErrorFrame = static_cast<Vector::ASC::CanErrorFrame *>(event);
    BOOST_CHECK_EQUAL(canErrorFrame->time, 2.501000);
    BOOST_CHECK_EQUAL(canErrorFrame->channel, 1);
    BOOST_CHECK_EQUAL(canErrorFrame->flags, 0x0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanBusStatistics) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanBusStatistics.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanBusStatistics * canBusStatistics;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanBusStatistics);
    canBusStatistics = static_cast<Vector::ASC::CanBusStatistics *>(event);
    BOOST_CHECK_EQUAL(canBusStatistics->time, 1.010000);
    BOOST_CHECK_EQUAL(canBusStatistics->channel, 1);
    BOOST_CHECK_EQUAL(canBusStatistics->dataFrames, 1000);
    BOOST_CHECK_EQUAL(canBusStatistics->remoteFrames, 15);
    BOOST_CHECK_EQUAL(canBusStatistics->extendedDataFrames, 0);
    BOOST_CHECK_EQUAL(canBusStatistics->extendedRemoteFrames, 0);
    BOOST_CHECK_EQUAL(canBusStatistics->errorFrames, 0);
    BOOST_CHECK_EQUAL(canBusStatistics->overloadFrames, 0);
    BOOST_CHECK_EQUAL(canBusStatistics->busload, 0.0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanError) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanError * canError;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanError);
    canError = static_cast<Vector::ASC::CanError *>(event);
    BOOST_CHECK_EQUAL(canError->time, 0.000600);
    BOOST_CHECK_EQUAL(canError->channel, 2);
    BOOST_CHECK(canError->error == Vector::ASC::Error::ChipStatusErrorActive);
    BOOST_CHECK_EQUAL(canError->txErr, 0);
    BOOST_CHECK_EQUAL(canError->rxErr, 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanError);
    canError = static_cast<Vector::ASC::CanError *>(event);
    BOOST_CHECK_EQUAL(canError->time, 2.501000);
    BOOST_CHECK_EQUAL(canError->channel, 1);
    BOOST_CHECK(canError->error == Vector::ASC::Error::ChipStatusErrorActive);
    BOOST_CHECK_EQUAL(canError->txErr, 0);
    BOOST_CHECK_EQUAL(canError->rxErr, 1);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanOverloadFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanOverloadFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanOverloadFrame * canOverloadFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanOverloadFrame);
    canOverloadFrame = static_cast<Vector::ASC::CanOverloadFrame *>(event);
    BOOST_CHECK_EQUAL(canOverloadFrame->time, 2.515800);
    BOOST_CHECK_EQUAL(canOverloadFrame->channel, 1);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* CAN FD Events */
BOOST_AUTO_TEST_CASE(CanFdMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdMessage * canFdMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdMessage);
    canFdMessage = static_cast<Vector::ASC::CanFdMessage *>(event);
    BOOST_CHECK_EQUAL(canFdMessage->time, 8.151536);
    BOOST_CHECK_EQUAL(canFdMessage->channel, 2);
    BOOST_CHECK(canFdMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(canFdMessage->id, 0xc9);
    BOOST_CHECK_EQUAL(canFdMessage->symbolicName, "ABSdata_FD_64Byte");
    BOOST_CHECK_EQUAL(canFdMessage->brs, false);
    BOOST_CHECK_EQUAL(canFdMessage->esi, false);
    BOOST_CHECK_EQUAL(canFdMessage->dlc, 9);
    BOOST_CHECK_EQUAL(canFdMessage->dataLength, 12);
    BOOST_REQUIRE_EQUAL(canFdMessage->data.size(), 12);
    BOOST_CHECK_EQUAL(canFdMessage->data[0], 0x29);
    BOOST_CHECK_EQUAL(canFdMessage->data[1], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->data[2], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->data[3], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->data[4], 0x0b);
    BOOST_CHECK_EQUAL(canFdMessage->data[5], 0x2a);
    BOOST_CHECK_EQUAL(canFdMessage->data[6], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->data[7], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->data[8], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->data[9], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->data[10], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->data[11], 0x00);
    BOOST_CHECK_EQUAL(canFdMessage->messageDuration, 164000);
    BOOST_CHECK_EQUAL(canFdMessage->messageLength, 167);
    BOOST_CHECK_EQUAL(canFdMessage->flags, 121200);
    BOOST_CHECK_EQUAL(canFdMessage->crc, 0x7ca0);
    BOOST_CHECK_EQUAL(canFdMessage->bitTimingConfArb, 0x500a2041);
    BOOST_CHECK_EQUAL(canFdMessage->bitTimingConfData, 0x460a4841);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanFdExtendedMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdExtendedMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdExtendedMessage * canFdExtendedMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdExtendedMessage);
    canFdExtendedMessage = static_cast<Vector::ASC::CanFdExtendedMessage *>(event);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->time, 0.248166);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->channel, 2);
    BOOST_CHECK(canFdExtendedMessage->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->id, 0x1fffffff);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->symbolicName, "");
    BOOST_CHECK_EQUAL(canFdExtendedMessage->brs, false);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->esi, false);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->dlc, 0xf);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->dataLength, 64);
    BOOST_REQUIRE_EQUAL(canFdExtendedMessage->data.size(), 64);
    for (int i = 0; i < 64; ++i)
        BOOST_CHECK_EQUAL(canFdExtendedMessage->data[i], i + 1);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->messageDuration, 1238000);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->messageLength, 111);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->flags, 101000);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->crc, 0x46518);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->bitTimingConfArb, 0x46500250);
    BOOST_CHECK_EQUAL(canFdExtendedMessage->bitTimingConfData, 0x46280250);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(CanFdErrorFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdErrorFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdErrorFrame * canFdErrorFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdErrorFrame);
    canFdErrorFrame = static_cast<Vector::ASC::CanFdErrorFrame *>(event);
    BOOST_CHECK_EQUAL(canFdErrorFrame->time, 3.923364);
    BOOST_CHECK_EQUAL(canFdErrorFrame->channel, 2);
    BOOST_CHECK(canFdErrorFrame->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(canFdErrorFrame->errorText, "Not Acknowledge error, dominant error flag");
    BOOST_CHECK_EQUAL(canFdErrorFrame->flags1, 0xfffe);
    BOOST_CHECK_EQUAL(canFdErrorFrame->code, 0xc7);
    BOOST_CHECK_EQUAL(canFdErrorFrame->codeExt, 0x31ca);
    BOOST_CHECK(canFdErrorFrame->phase == Vector::ASC::CanFdErrorFrame::Phase::Data);
    BOOST_CHECK_EQUAL(canFdErrorFrame->position, 45);
    BOOST_CHECK_EQUAL(canFdErrorFrame->id, 0xff);
    BOOST_CHECK_EQUAL(canFdErrorFrame->brs, true);
    BOOST_CHECK_EQUAL(canFdErrorFrame->esi, false);
    BOOST_CHECK_EQUAL(canFdErrorFrame->dlc, 0xf);
    BOOST_CHECK_EQUAL(canFdErrorFrame->dataLength, 64);
    BOOST_REQUIRE_EQUAL(canFdErrorFrame->data.size(), 64);
    for (int i = 0; i < 64; ++i)
        BOOST_CHECK_EQUAL(canFdErrorFrame->data[i], 0xaa);
    BOOST_CHECK_EQUAL(canFdErrorFrame->messageDuration, 336484);
    BOOST_CHECK_EQUAL(canFdErrorFrame->flags2, 3);
    BOOST_CHECK_EQUAL(canFdErrorFrame->crc, 0);
    BOOST_CHECK_EQUAL(canFdErrorFrame->bitTimingConfArb, 0x51103250);
    BOOST_CHECK_EQUAL(canFdErrorFrame->bitTimingConfData, 0x460a0250);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

// @todo CanFdBusStatisticsEvent
// @todo CanFdOverloadFrame

/* Log and Trigger Events */
BOOST_AUTO_TEST_CASE(LogTrigger) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogTrigger.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogTrigger * logTrigger;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogTrigger);
    logTrigger = static_cast<Vector::ASC::LogTrigger *>(event);
    BOOST_CHECK_EQUAL(logTrigger->time, 2.000000);
    BOOST_CHECK_EQUAL(logTrigger->information, "");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogTrigger);
    logTrigger = static_cast<Vector::ASC::LogTrigger *>(event);
    BOOST_CHECK_EQUAL(logTrigger->time, 2.700000);
    BOOST_CHECK_EQUAL(logTrigger->information, "(this trigger was in post trigger time of last block)");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LogDirectStart) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogDirectStart.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogDirectStart * logDirectStart;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogDirectStart);
    logDirectStart = static_cast<Vector::ASC::LogDirectStart *>(event);
    BOOST_CHECK_EQUAL(logDirectStart->time, 2.110000);
    BOOST_CHECK_EQUAL(logDirectStart->preTrigger, 2000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LogDirectStop) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogDirectStop.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogDirectStop * logDirectStop;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogDirectStop);
    logDirectStop = static_cast<Vector::ASC::LogDirectStop *>(event);
    BOOST_CHECK_EQUAL(logDirectStop->time, 2.110000);
    BOOST_CHECK_EQUAL(logDirectStop->postTrigger, 1000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(BeginTriggerblock) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/BeginTriggerblock.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::BeginTriggerblock * beginTriggerblock;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::BeginTriggerblock);
    beginTriggerblock = static_cast<Vector::ASC::BeginTriggerblock *>(event);
    BOOST_CHECK_EQUAL(beginTriggerblock->date.tm_wday, 1);
    BOOST_CHECK_EQUAL(beginTriggerblock->date.tm_mon, 2);
    BOOST_CHECK_EQUAL(beginTriggerblock->date.tm_mday, 7);
    BOOST_CHECK_EQUAL(beginTriggerblock->date.tm_hour, 1 + 12);
    BOOST_CHECK_EQUAL(beginTriggerblock->date.tm_min, 21);
    BOOST_CHECK_EQUAL(beginTriggerblock->date.tm_sec, 51);
    BOOST_CHECK_EQUAL(beginTriggerblock->date.tm_year, (2005 - 1900));
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(EndTriggerblock) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EndTriggerblock.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    /*Vector::ASC::EndTriggerblock * endTriggerblock;*/

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EndTriggerblock);
    /*endTriggerblock = static_cast<Vector::ASC::EndTriggerblock *>(event);*/
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Environment Variables */
BOOST_AUTO_TEST_CASE(EnvironmentVariables) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EnvironmentVariables.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EnvironmentVariables * environmentVariables;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariables);
    environmentVariables = static_cast<Vector::ASC::EnvironmentVariables *>(event);
    BOOST_CHECK_EQUAL(environmentVariables->time, 2.130000);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariables);
    environmentVariables = static_cast<Vector::ASC::EnvironmentVariables *>(event);
    BOOST_CHECK_EQUAL(environmentVariables->time, 2.567000);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariables);
    environmentVariables = static_cast<Vector::ASC::EnvironmentVariables *>(event);
    BOOST_CHECK_EQUAL(environmentVariables->time, 3.830000);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariables);
    environmentVariables = static_cast<Vector::ASC::EnvironmentVariables *>(event);
    BOOST_CHECK_EQUAL(environmentVariables->time, 2.250000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* System Variables */
BOOST_AUTO_TEST_CASE(SystemVariables) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/SystemVariables.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::SystemVariables * systemVariables;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK_EQUAL(systemVariables->time, 1.200000);
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::Int);
    BOOST_CHECK_EQUAL(systemVariables->path, "::NS1::IntVar");
    BOOST_CHECK_EQUAL(systemVariables->value, "4");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK_EQUAL(systemVariables->time, 1.370000);
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::Float);
    BOOST_CHECK_EQUAL(systemVariables->path, "::NS1::FloatVar");
    BOOST_CHECK_EQUAL(systemVariables->value, "4.1");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK_EQUAL(systemVariables->time, 1.580000);
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::String);
    BOOST_CHECK_EQUAL(systemVariables->path, "::NS1::StringVar");
    BOOST_CHECK_EQUAL(systemVariables->value, "\"Value: 4\"");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK_EQUAL(systemVariables->time, 1.690000);
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::IntArray);
    BOOST_CHECK_EQUAL(systemVariables->path, "::NS1::IntArray");
    BOOST_CHECK_EQUAL(systemVariables->value, "A3 4 5 2");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariables);
    systemVariables = static_cast<Vector::ASC::SystemVariables *>(event);
    BOOST_CHECK_EQUAL(systemVariables->time, 2.000000);
    BOOST_CHECK(systemVariables->svtype == Vector::ASC::Svtype::FloatArray);
    BOOST_CHECK_EQUAL(systemVariables->path, "::NS1::FloatArray");
    BOOST_CHECK_EQUAL(systemVariables->value, "D3 4.1 2.9 6");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Macros Signal Event */
BOOST_AUTO_TEST_CASE(MacroSignal) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MacroSignal.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MacroSignal * macroSignal;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignal);
    macroSignal = static_cast<Vector::ASC::MacroSignal *>(event);
    BOOST_CHECK_EQUAL(macroSignal->time, 2.350000);
    BOOST_CHECK(macroSignal->bussystem == Vector::ASC::MacroSignal::Bussystem::Can);
    BOOST_CHECK_EQUAL(macroSignal->channel, 1);
    BOOST_CHECK_EQUAL(macroSignal->node, "Node");
    BOOST_CHECK_EQUAL(macroSignal->message, "aCANMessage");
    BOOST_CHECK_EQUAL(macroSignal->signal, "aBitSignal");
    BOOST_CHECK_EQUAL(macroSignal->value, "1");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignal);
    macroSignal = static_cast<Vector::ASC::MacroSignal *>(event);
    BOOST_CHECK_EQUAL(macroSignal->time, 2.350000);
    BOOST_CHECK(macroSignal->bussystem == Vector::ASC::MacroSignal::Bussystem::Can);
    BOOST_CHECK_EQUAL(macroSignal->channel, 1);
    BOOST_CHECK_EQUAL(macroSignal->node, "Node");
    BOOST_CHECK_EQUAL(macroSignal->message, "aCANMessage");
    BOOST_CHECK_EQUAL(macroSignal->signal, "aBitSignal");
    BOOST_CHECK_EQUAL(macroSignal->value, "Eins");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignal);
    macroSignal = static_cast<Vector::ASC::MacroSignal *>(event);
    BOOST_CHECK_EQUAL(macroSignal->time, 5.000000);
    BOOST_CHECK(macroSignal->bussystem == Vector::ASC::MacroSignal::Bussystem::Lin);
    BOOST_CHECK_EQUAL(macroSignal->channel, 1);
    BOOST_CHECK_EQUAL(macroSignal->node, "L_Slave");
    BOOST_CHECK_EQUAL(macroSignal->message, "aLINMessage");
    BOOST_CHECK_EQUAL(macroSignal->signal, "aLINBitSignal");
    BOOST_CHECK_EQUAL(macroSignal->value, "0");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignal);
    macroSignal = static_cast<Vector::ASC::MacroSignal *>(event);
    BOOST_CHECK_EQUAL(macroSignal->time, 1.110000);
    BOOST_CHECK(macroSignal->bussystem == Vector::ASC::MacroSignal::Bussystem::FlexRay);
    BOOST_CHECK_EQUAL(macroSignal->channel, 1);
    BOOST_CHECK_EQUAL(macroSignal->node, "FR_ECU");
    BOOST_CHECK_EQUAL(macroSignal->message, "aFlexRayMessage");
    BOOST_CHECK_EQUAL(macroSignal->signal, "aFRSignal");
    BOOST_CHECK_EQUAL(macroSignal->value, "3");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* GPS events */
BOOST_AUTO_TEST_CASE(Gps) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Gps.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Gps * gps;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Gps);
    gps = static_cast<Vector::ASC::Gps *>(event);
    BOOST_CHECK_EQUAL(gps->time, 2.097603);
    BOOST_CHECK_EQUAL(gps->channel, 1);
    BOOST_CHECK_EQUAL(gps->latitude, 48.825100);
    BOOST_CHECK_EQUAL(gps->longitude, 9.091267);
    BOOST_CHECK_EQUAL(gps->altitude, 325.399994);
    BOOST_CHECK_EQUAL(gps->speed, 29.686400);
    BOOST_CHECK_EQUAL(gps->course, 87.099998);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Comment events */
BOOST_AUTO_TEST_CASE(Comment) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Comment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Comment * comment;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Comment);
    comment = static_cast<Vector::ASC::Comment *>(event);
    BOOST_CHECK_EQUAL(comment->time, 1.593770);
    BOOST_CHECK_EQUAL(comment->type, 105);
    BOOST_CHECK_EQUAL(comment->commentText, "testComment");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Global market events */
BOOST_AUTO_TEST_CASE(GlobalMarker) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/GlobalMarker.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::GlobalMarker * globalMarker;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::GlobalMarker);
    globalMarker = static_cast<Vector::ASC::GlobalMarker *>(event);
    BOOST_CHECK_EQUAL(globalMarker->time, 2.200804);
    BOOST_CHECK_EQUAL(globalMarker->type, 0);
    BOOST_CHECK_EQUAL(globalMarker->backgroundColor, 16777215);
    BOOST_CHECK_EQUAL(globalMarker->foregroundColor, 0);
    BOOST_CHECK_EQUAL(globalMarker->relocatable, true);
    BOOST_CHECK_EQUAL(globalMarker->groupName, "Marker Group");
    BOOST_CHECK_EQUAL(globalMarker->markerName, "[1]");
    BOOST_CHECK_EQUAL(globalMarker->description, "description");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* Ethernet Events */
BOOST_AUTO_TEST_CASE(EthernetPacket) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetPacket * ethernetPacket;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetPacket);
    ethernetPacket = static_cast<Vector::ASC::EthernetPacket *>(event);
    BOOST_CHECK_EQUAL(ethernetPacket->time, 0.000000);
    BOOST_CHECK_EQUAL(ethernetPacket->channel, 2);
    BOOST_CHECK(ethernetPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(ethernetPacket->dataLen, 0x3c);
    BOOST_REQUIRE_EQUAL(ethernetPacket->data.size(), 0x3c);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x00], 0xFF);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x01], 0xFF);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x02], 0xFF);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x03], 0xFF);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x04], 0xFF);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x05], 0xFF);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x06], 0x40);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x07], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x08], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x09], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x0a], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x0b], 0x04);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x0c], 0x08);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x0d], 0x06);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x0e], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x0f], 0x01);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x10], 0x08);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x11], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x12], 0x06);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x13], 0x04);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x14], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x15], 0x01);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x16], 0x40);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x17], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x18], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x19], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x1a], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x1b], 0x04);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x1c], 0xC0);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x1d], 0xA8);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x1e], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x1f], 0x01);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x20], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x21], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x22], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x23], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x24], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x25], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x26], 0xC0);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x27], 0xA8);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x28], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x29], 0x01);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x2a], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x2b], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x2c], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x2d], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x2e], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x2f], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x30], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x31], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x32], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x33], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x34], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x35], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x36], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x37], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x38], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x39], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x3a], 0x00);
    BOOST_CHECK_EQUAL(ethernetPacket->data[0x3b], 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(EthernetStatus) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetStatus.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetStatus * ethernetStatus;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetStatus);
    ethernetStatus = static_cast<Vector::ASC::EthernetStatus *>(event);
    BOOST_CHECK_EQUAL(ethernetStatus->time, 0.002404);
    BOOST_CHECK_EQUAL(ethernetStatus->channel, 1);
    BOOST_CHECK(ethernetStatus->link == Vector::ASC::EthernetStatus::Link::Up);
    BOOST_CHECK_EQUAL(ethernetStatus->linkSpeed, 100);
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

BOOST_AUTO_TEST_CASE(EthernetRxError) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetRxError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetRxError * ethernetRxError;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetRxError);
    ethernetRxError = static_cast<Vector::ASC::EthernetRxError *>(event);
    BOOST_CHECK_EQUAL(ethernetRxError->time, 1.465409);
    BOOST_CHECK_EQUAL(ethernetRxError->channel, 2);
    BOOST_CHECK_EQUAL(ethernetRxError->errorCode, 0x02);
    BOOST_CHECK_EQUAL(ethernetRxError->frameChecksum, 0x00001234);
    BOOST_CHECK_EQUAL(ethernetRxError->dataLen, 0x3c);
    BOOST_REQUIRE_EQUAL(ethernetRxError->data.size(), 0x3c);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x00], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x01], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x02], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x03], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x04], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x05], 0x01);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x06], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x07], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x08], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x09], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x0a], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x0b], 0x02);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x0c], 0xFF);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x0d], 0x01);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x0e], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x0f], 0x01);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x10], 0x02);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x11], 0x03);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x12], 0x04);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x13], 0x05);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x14], 0x06);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x15], 0x07);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x16], 0x08);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x17], 0x09);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x18], 0x0A);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x19], 0x0B);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x1a], 0x0C);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x1b], 0x0D);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x1c], 0x0E);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x1d], 0x0F);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x1e], 0x10);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x1f], 0x11);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x20], 0x12);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x21], 0x13);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x22], 0x14);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x23], 0x15);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x24], 0x16);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x25], 0x17);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x26], 0x18);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x27], 0x19);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x28], 0x1A);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x29], 0x1B);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x2a], 0x1C);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x2b], 0x1D);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x2c], 0x1E);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x2d], 0x1F);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x2e], 0x20);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x2f], 0x21);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x30], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x31], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x32], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x33], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x34], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x35], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x36], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x37], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x38], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x39], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x3a], 0x00);
    BOOST_CHECK_EQUAL(ethernetRxError->data[0x3b], 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* AFDX Events */
BOOST_AUTO_TEST_CASE(AfdxPacket) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AfdxPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::AfdxPacket * afdxPacket;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::AfdxPacket);
    afdxPacket = static_cast<Vector::ASC::AfdxPacket *>(event);
    BOOST_CHECK_EQUAL(afdxPacket->time, 0.000000);
    BOOST_CHECK_EQUAL(afdxPacket->channel, 1);
    BOOST_CHECK(afdxPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(afdxPacket->ethChannel, 1);
    BOOST_CHECK_EQUAL(afdxPacket->flags, 0x64);
    BOOST_CHECK_EQUAL(afdxPacket->bag, 0);
    BOOST_CHECK_EQUAL(afdxPacket->dataLen, 0x3c);
    BOOST_REQUIRE_EQUAL(afdxPacket->data.size(), 0x3c);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x00], 0xFF);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x01], 0xFF);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x02], 0xFF);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x03], 0xFF);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x04], 0xFF);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x05], 0xFF);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x06], 0x40);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x07], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x08], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x09], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x0a], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x0b], 0x04);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x0c], 0x08);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x0d], 0x06);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x0e], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x0f], 0x01);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x10], 0x08);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x11], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x12], 0x06);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x13], 0x04);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x14], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x15], 0x01);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x16], 0x40);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x17], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x18], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x19], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x1a], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x1b], 0x04);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x1c], 0xC0);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x1d], 0xA8);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x1e], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x1f], 0x01);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x20], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x21], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x22], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x23], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x24], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x25], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x26], 0xC0);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x27], 0xA8);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x28], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x29], 0x01);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x2a], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x2b], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x2c], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x2d], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x2e], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x2f], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x30], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x31], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x32], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x33], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x34], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x35], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x36], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x37], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x38], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x39], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x3a], 0x00);
    BOOST_CHECK_EQUAL(afdxPacket->data[0x3b], 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* FlexRay Events (Old Format) */
BOOST_AUTO_TEST_CASE(FlexRayOldMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayOldMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayOldMessage * flexRayOldMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldMessage);
    flexRayOldMessage = static_cast<Vector::ASC::FlexRayOldMessage *>(event);
    BOOST_CHECK_EQUAL(flexRayOldMessage->time, 0.042000);
    BOOST_CHECK_EQUAL(flexRayOldMessage->channel, '1');
    BOOST_CHECK_EQUAL(flexRayOldMessage->id, 4);
    BOOST_CHECK_EQUAL(flexRayOldMessage->cycle, 25);
    BOOST_CHECK_EQUAL(flexRayOldMessage->nm, false);
    BOOST_CHECK_EQUAL(flexRayOldMessage->sync, true);
    BOOST_CHECK_EQUAL(flexRayOldMessage->headerCrc, 151);
    BOOST_CHECK_EQUAL(flexRayOldMessage->symbolicName, "Ident_04_Rnd_0");
    BOOST_CHECK_EQUAL(flexRayOldMessage->dlc, 4);
    BOOST_REQUIRE_EQUAL(flexRayOldMessage->data.size(), 4);
    BOOST_CHECK_EQUAL(flexRayOldMessage->data[0], 21);
    BOOST_CHECK_EQUAL(flexRayOldMessage->data[1], 87);
    BOOST_CHECK_EQUAL(flexRayOldMessage->data[2], 22);
    BOOST_CHECK_EQUAL(flexRayOldMessage->data[3], 148);
    BOOST_CHECK_EQUAL(flexRayOldMessage->frameState, 0x00d0);
    BOOST_CHECK_EQUAL(flexRayOldMessage->headerBitMask, 0x9a);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldMessage);
    flexRayOldMessage = static_cast<Vector::ASC::FlexRayOldMessage *>(event);
    BOOST_CHECK_EQUAL(flexRayOldMessage->time, 0.042600);
    BOOST_CHECK_EQUAL(flexRayOldMessage->channel, '2');
    BOOST_CHECK_EQUAL(flexRayOldMessage->id, 13);
    BOOST_CHECK_EQUAL(flexRayOldMessage->cycle, 25);
    BOOST_CHECK_EQUAL(flexRayOldMessage->nm, false);
    BOOST_CHECK_EQUAL(flexRayOldMessage->sync, false);
    BOOST_CHECK_EQUAL(flexRayOldMessage->headerCrc, 620);
    BOOST_CHECK_EQUAL(flexRayOldMessage->symbolicName, "x");
    BOOST_CHECK_EQUAL(flexRayOldMessage->dlc, 4);
    BOOST_REQUIRE_EQUAL(flexRayOldMessage->data.size(), 4);
    BOOST_CHECK_EQUAL(flexRayOldMessage->data[0], 2);
    BOOST_CHECK_EQUAL(flexRayOldMessage->data[1], 89);
    BOOST_CHECK_EQUAL(flexRayOldMessage->data[2], 0);
    BOOST_CHECK_EQUAL(flexRayOldMessage->data[3], 13);
    BOOST_CHECK_EQUAL(flexRayOldMessage->frameState, 0x0180);
    BOOST_CHECK_EQUAL(flexRayOldMessage->headerBitMask, 0x88);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayOldStartCycle) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayOldStartCycle.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayOldStartCycle * flexRayOldStartCycle;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldStartCycle);
    flexRayOldStartCycle = static_cast<Vector::ASC::FlexRayOldStartCycle *>(event);
    BOOST_CHECK_EQUAL(flexRayOldStartCycle->time, 0.041700);
    BOOST_CHECK_EQUAL(flexRayOldStartCycle->channel, '*');
    BOOST_CHECK_EQUAL(flexRayOldStartCycle->dlc, 2);
    BOOST_REQUIRE_EQUAL(flexRayOldStartCycle->data.size(), 2);
    BOOST_CHECK_EQUAL(flexRayOldStartCycle->data[0], 0);
    BOOST_CHECK_EQUAL(flexRayOldStartCycle->data[1], 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* FlexRay Events (New Format) */
BOOST_AUTO_TEST_CASE(FlexRayMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayMessage * flexRayMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessage);
    flexRayMessage = static_cast<Vector::ASC::FlexRayMessage *>(event);
    BOOST_CHECK_EQUAL(flexRayMessage->time, 0.039255);
    BOOST_CHECK(flexRayMessage->flexRayEventType == Vector::ASC::FlexRayMessage::FlexRayEventType::RMSG);
    BOOST_CHECK_EQUAL(flexRayMessage->clusterNr, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->clientId, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->channelNr, 1);
    BOOST_CHECK_EQUAL(flexRayMessage->channelMask, 1);
    BOOST_CHECK_EQUAL(flexRayMessage->slotId, 4);
    BOOST_CHECK_EQUAL(flexRayMessage->cycleNo, 7);
    BOOST_CHECK(flexRayMessage->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(flexRayMessage->appParam, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->flags, 14);
    BOOST_CHECK_EQUAL(flexRayMessage->ccType, 5);
    BOOST_CHECK_EQUAL(flexRayMessage->ccData, 32);
    BOOST_CHECK_EQUAL(flexRayMessage->headerCrc, 151);
    BOOST_CHECK_EQUAL(flexRayMessage->name, "Message_2");
    BOOST_CHECK_EQUAL(flexRayMessage->payloadLength, 4);
    BOOST_CHECK_EQUAL(flexRayMessage->bufferLength, 4);
    BOOST_REQUIRE_EQUAL(flexRayMessage->data.size(), 4);
    BOOST_CHECK_EQUAL(flexRayMessage->data[0], 27);
    BOOST_CHECK_EQUAL(flexRayMessage->data[1], 24);
    BOOST_CHECK_EQUAL(flexRayMessage->data[2], 29);
    BOOST_CHECK_EQUAL(flexRayMessage->data[3], 241);
    BOOST_CHECK_EQUAL(flexRayMessage->frameCrc, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->spyFlag, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->frameLengthNs, 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessage);
    flexRayMessage = static_cast<Vector::ASC::FlexRayMessage *>(event);
    BOOST_CHECK_EQUAL(flexRayMessage->time, 0.047906);
    BOOST_CHECK(flexRayMessage->flexRayEventType == Vector::ASC::FlexRayMessage::FlexRayEventType::PDU);
    BOOST_CHECK_EQUAL(flexRayMessage->clusterNr, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->clientId, 2);
    BOOST_CHECK_EQUAL(flexRayMessage->channelNr, 1);
    BOOST_CHECK_EQUAL(flexRayMessage->channelMask, 1);
    BOOST_CHECK_EQUAL(flexRayMessage->slotId, 3);
    BOOST_CHECK_EQUAL(flexRayMessage->cycleNo, 7);
    BOOST_CHECK(flexRayMessage->direction == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(flexRayMessage->appParam, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->flags, 2313218);
    BOOST_CHECK_EQUAL(flexRayMessage->ccType, 5);
    BOOST_CHECK_EQUAL(flexRayMessage->ccData, 32);
    BOOST_CHECK_EQUAL(flexRayMessage->headerCrc, 559);
    BOOST_CHECK_EQUAL(flexRayMessage->name, "PDU_DEMO_1");
    BOOST_CHECK_EQUAL(flexRayMessage->payloadLength, 1);
    BOOST_CHECK_EQUAL(flexRayMessage->bufferLength, 1);
    BOOST_REQUIRE_EQUAL(flexRayMessage->data.size(), 1);
    BOOST_CHECK_EQUAL(flexRayMessage->data[0], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->frameCrc, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->spyFlag, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->frameLengthNs, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->pduOffset, 40);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessage);
    flexRayMessage = static_cast<Vector::ASC::FlexRayMessage *>(event);
    BOOST_CHECK_EQUAL(flexRayMessage->time, 0.047906);
    BOOST_CHECK(flexRayMessage->flexRayEventType == Vector::ASC::FlexRayMessage::FlexRayEventType::RMSG);
    BOOST_CHECK_EQUAL(flexRayMessage->clusterNr, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->clientId, 2);
    BOOST_CHECK_EQUAL(flexRayMessage->channelNr, 1);
    BOOST_CHECK_EQUAL(flexRayMessage->channelMask, 1);
    BOOST_CHECK_EQUAL(flexRayMessage->slotId, 3);
    BOOST_CHECK_EQUAL(flexRayMessage->cycleNo, 7);
    BOOST_CHECK(flexRayMessage->direction == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(flexRayMessage->appParam, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->flags, 2640898);
    BOOST_CHECK_EQUAL(flexRayMessage->ccType, 5);
    BOOST_CHECK_EQUAL(flexRayMessage->ccData, 32);
    BOOST_CHECK_EQUAL(flexRayMessage->headerCrc, 559);
    BOOST_CHECK_EQUAL(flexRayMessage->name, "FlexRay_Frame_[3|0|1]");
    BOOST_CHECK_EQUAL(flexRayMessage->payloadLength, 42);
    BOOST_CHECK_EQUAL(flexRayMessage->bufferLength, 42);
    BOOST_REQUIRE_EQUAL(flexRayMessage->data.size(), 42);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 0], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 1], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 2], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 3], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 4], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 5], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 6], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 7], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 8], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[ 9], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[10], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[11], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[12], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[13], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[14], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[15], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[16], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[17], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[18], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[19], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[20], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[21], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[22], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[23], 128);
    BOOST_CHECK_EQUAL(flexRayMessage->data[24], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[25], 128);
    BOOST_CHECK_EQUAL(flexRayMessage->data[26], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[27], 128);
    BOOST_CHECK_EQUAL(flexRayMessage->data[28], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[29], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[30], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[31], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[32], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[33], 128);
    BOOST_CHECK_EQUAL(flexRayMessage->data[34], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[35], 128);
    BOOST_CHECK_EQUAL(flexRayMessage->data[36], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[37], 128);
    BOOST_CHECK_EQUAL(flexRayMessage->data[38], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[39], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[40], 0);
    BOOST_CHECK_EQUAL(flexRayMessage->data[41], 56);
    BOOST_CHECK_EQUAL(flexRayMessage->frameCrc, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->spyFlag, 0);
    BOOST_CHECK_EQUAL(flexRayMessage->frameLengthNs, 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayStartCycle) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayStartCycle.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayStartCycle * flexRayStartCycle;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayStartCycle);
    flexRayStartCycle = static_cast<Vector::ASC::FlexRayStartCycle *>(event);
    BOOST_CHECK_EQUAL(flexRayStartCycle->time, 0.044115);
    BOOST_CHECK_EQUAL(flexRayStartCycle->clusterNr, 0);
    BOOST_CHECK_EQUAL(flexRayStartCycle->clientId, 0);
    BOOST_CHECK_EQUAL(flexRayStartCycle->channelNr, 1);
    BOOST_CHECK_EQUAL(flexRayStartCycle->channelMask, 3);
    BOOST_CHECK_EQUAL(flexRayStartCycle->cycleNo, 8);
    BOOST_CHECK(flexRayStartCycle->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(flexRayStartCycle->ccType, 5);
    BOOST_CHECK_EQUAL(flexRayStartCycle->ccData[0], 0);
    BOOST_CHECK_EQUAL(flexRayStartCycle->ccData[1], 4);
    BOOST_CHECK_EQUAL(flexRayStartCycle->ccData[2], 0);
    BOOST_CHECK_EQUAL(flexRayStartCycle->ccData[3], 0);
    BOOST_CHECK_EQUAL(flexRayStartCycle->ccData[4], 0);
    BOOST_CHECK_EQUAL(flexRayStartCycle->nmVectL, 0);
    BOOST_REQUIRE_EQUAL(flexRayStartCycle->nmVect.size(), 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayStatus) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayStatus.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayStatus * flexRayStatus;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayStatus);
    flexRayStatus = static_cast<Vector::ASC::FlexRayStatus *>(event);
    BOOST_CHECK_EQUAL(flexRayStatus->time, 0.003022);
    BOOST_CHECK_EQUAL(flexRayStatus->clusterNr, 0);
    BOOST_CHECK_EQUAL(flexRayStatus->clientId, 0);
    BOOST_CHECK_EQUAL(flexRayStatus->channelNr, 1);
    BOOST_CHECK_EQUAL(flexRayStatus->channelMask, 3);
    BOOST_CHECK_EQUAL(flexRayStatus->cycleNo, 255);
    BOOST_CHECK_EQUAL(flexRayStatus->ccType, 5);
    BOOST_CHECK_EQUAL(flexRayStatus->syncState, 2);
    BOOST_CHECK_EQUAL(flexRayStatus->ccData[0], 15);
    BOOST_CHECK_EQUAL(flexRayStatus->ccData[1], 0);
    BOOST_CHECK_EQUAL(flexRayStatus->symbol, 0);
    BOOST_CHECK_EQUAL(flexRayStatus->wakeUpState, 0);
    BOOST_CHECK_EQUAL(flexRayStatus->spyFlag, 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayError) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayError * flexRayError;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayError);
    flexRayError = static_cast<Vector::ASC::FlexRayError *>(event);
    BOOST_CHECK_EQUAL(flexRayError->time, 7.344250);
    BOOST_CHECK_EQUAL(flexRayError->clusterNr, 0);
    BOOST_CHECK_EQUAL(flexRayError->clientId, 0);
    BOOST_CHECK_EQUAL(flexRayError->channelNr, 1);
    BOOST_CHECK_EQUAL(flexRayError->channelMask, 2);
    BOOST_CHECK_EQUAL(flexRayError->ccType, 5);
    BOOST_CHECK_EQUAL(flexRayError->ccData[0], 5);
    BOOST_CHECK_EQUAL(flexRayError->ccData[1], 65536);
    BOOST_CHECK_EQUAL(flexRayError->ccData[2], 0);
    BOOST_CHECK_EQUAL(flexRayError->ccData[3], 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* K-Line Events */
BOOST_AUTO_TEST_CASE(KLineByte) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/KLineByte.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::KLineByte * kLineByte;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::KLineByte);
    kLineByte = static_cast<Vector::ASC::KLineByte *>(event);
    BOOST_CHECK_EQUAL(kLineByte->time, 12.315000);
    BOOST_CHECK_EQUAL(kLineByte->port, "COM2");
    BOOST_CHECK(kLineByte->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(kLineByte->baudrate, 10400);
    BOOST_CHECK_EQUAL(kLineByte->length, 7);
    BOOST_REQUIRE_EQUAL(kLineByte->data.size(), 7);
    BOOST_CHECK_EQUAL(kLineByte->data[0], 0x83);
    BOOST_CHECK_EQUAL(kLineByte->data[1], 0x11);
    BOOST_CHECK_EQUAL(kLineByte->data[2], 0x61);
    BOOST_CHECK_EQUAL(kLineByte->data[3], 0x7F);
    BOOST_CHECK_EQUAL(kLineByte->data[4], 0x1A);
    BOOST_CHECK_EQUAL(kLineByte->data[5], 0x78);
    BOOST_CHECK_EQUAL(kLineByte->data[6], 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(KLineMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/KLineMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::KLineMessage * kLineMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::KLineMessage);
    kLineMessage = static_cast<Vector::ASC::KLineMessage *>(event);
    BOOST_CHECK_EQUAL(kLineMessage->time, 12.315000);
    BOOST_CHECK_EQUAL(kLineMessage->port, "COM2");
    BOOST_CHECK(kLineMessage->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(kLineMessage->baudrate, 10400);
    BOOST_CHECK_EQUAL(kLineMessage->source, "61");
    BOOST_CHECK_EQUAL(kLineMessage->destination, "11");
    BOOST_CHECK_EQUAL(kLineMessage->length, 7);
    BOOST_REQUIRE_EQUAL(kLineMessage->data.size(), 7);
    BOOST_CHECK_EQUAL(kLineMessage->data[0], 0x83);
    BOOST_CHECK_EQUAL(kLineMessage->data[1], 0x11);
    BOOST_CHECK_EQUAL(kLineMessage->data[2], 0x61);
    BOOST_CHECK_EQUAL(kLineMessage->data[3], 0x7F);
    BOOST_CHECK_EQUAL(kLineMessage->data[4], 0x1A);
    BOOST_CHECK_EQUAL(kLineMessage->data[5], 0x78);
    BOOST_CHECK_EQUAL(kLineMessage->data[6], 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN Events */
BOOST_AUTO_TEST_CASE(LinMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinMessage * linMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinMessage);
    linMessage = static_cast<Vector::ASC::LinMessage *>(event);
    BOOST_CHECK_EQUAL(linMessage->time, 0.073973);
    BOOST_CHECK_EQUAL(linMessage->channel, 1);
    BOOST_CHECK_EQUAL(linMessage->id, "2d");
    BOOST_CHECK(linMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(linMessage->dlc, 8);
    BOOST_REQUIRE_EQUAL(linMessage->data.size(), 8);
    BOOST_CHECK_EQUAL(linMessage->data[0], 0x00);
    BOOST_CHECK_EQUAL(linMessage->data[1], 0xf0);
    BOOST_CHECK_EQUAL(linMessage->data[2], 0xf0);
    BOOST_CHECK_EQUAL(linMessage->data[3], 0xff);
    BOOST_CHECK_EQUAL(linMessage->data[4], 0xff);
    BOOST_CHECK_EQUAL(linMessage->data[5], 0xff);
    BOOST_CHECK_EQUAL(linMessage->data[6], 0xff);
    BOOST_CHECK_EQUAL(linMessage->data[7], 0xff);
    BOOST_CHECK(linMessage->checksum = 70);
    BOOST_CHECK_EQUAL(linMessage->headerTime, 40);
    BOOST_CHECK_EQUAL(linMessage->fullTime, 130);
    BOOST_CHECK_EQUAL(linMessage->startOfFrame, 0.067195);
    BOOST_CHECK_EQUAL(linMessage->baudrate, 19230);
    BOOST_CHECK_EQUAL(linMessage->syncBreak, 937125);
    BOOST_CHECK_EQUAL(linMessage->syncDel, 114062);
    BOOST_CHECK_EQUAL(linMessage->endOfHeader, 0.069266);
    BOOST_REQUIRE_EQUAL(linMessage->endOfByte.size(), 8);
    BOOST_CHECK_EQUAL(linMessage->endOfByte[0], 0.069789);
    BOOST_CHECK_EQUAL(linMessage->endOfByte[1], 0.070312);
    BOOST_CHECK_EQUAL(linMessage->endOfByte[2], 0.070835);
    BOOST_CHECK_EQUAL(linMessage->endOfByte[3], 0.071358);
    BOOST_CHECK_EQUAL(linMessage->endOfByte[4], 0.071881);
    BOOST_CHECK_EQUAL(linMessage->endOfByte[5], 0.072404);
    BOOST_CHECK_EQUAL(linMessage->endOfByte[6], 0.072927);
    BOOST_CHECK_EQUAL(linMessage->endOfByte[7], 0.073450);
    BOOST_CHECK_EQUAL(linMessage->simulated, true);
    BOOST_CHECK_EQUAL(linMessage->endOfFrame, 0.073973);
    BOOST_CHECK_EQUAL(linMessage->responseBaudrate, 19231);
    BOOST_CHECK_EQUAL(linMessage->headerBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(linMessage->stopBitOffsetInHeader, 26000);
    BOOST_CHECK_EQUAL(linMessage->stopBitOffsetInResponse, 26000);
    BOOST_CHECK(linMessage->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN Error Events */
BOOST_AUTO_TEST_CASE(LinTransmissionError) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinTransmissionError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinTransmissionError * linTransmissionError;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinTransmissionError);
    linTransmissionError = static_cast<Vector::ASC::LinTransmissionError *>(event);
    BOOST_CHECK_EQUAL(linTransmissionError->time, 0.424674);
    BOOST_CHECK_EQUAL(linTransmissionError->channel, 1);
    BOOST_CHECK_EQUAL(linTransmissionError->id, "33");
    BOOST_CHECK_EQUAL(linTransmissionError->headerTime, 40);
    BOOST_CHECK_EQUAL(linTransmissionError->fullTime, 166);
    BOOST_CHECK_EQUAL(linTransmissionError->startOfFrame, 0.416054);
    BOOST_CHECK_EQUAL(linTransmissionError->baudrate, 19230);
    BOOST_CHECK_EQUAL(linTransmissionError->syncBreak, 937187);
    BOOST_CHECK_EQUAL(linTransmissionError->syncDel, 113250);
    BOOST_CHECK_EQUAL(linTransmissionError->endOfHeader, 0.418122);
    BOOST_CHECK_EQUAL(linTransmissionError->headerBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(linTransmissionError->stopBitOffsetInHeader, 26000);
    BOOST_CHECK(linTransmissionError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinReceiveError) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinReceiveError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinReceiveError * linReceiveError;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinReceiveError);
    linReceiveError = static_cast<Vector::ASC::LinReceiveError *>(event);
    BOOST_CHECK_EQUAL(linReceiveError->time, 0.554673);
    BOOST_CHECK_EQUAL(linReceiveError->channel, 1);
    BOOST_CHECK_EQUAL(linReceiveError->id, "33");
    BOOST_CHECK_EQUAL(linReceiveError->dlc, 8);
    BOOST_CHECK_EQUAL(linReceiveError->description, "timeout while waiting for checksum field");
    BOOST_CHECK_EQUAL(linReceiveError->stateReason, 0x0c);
    BOOST_CHECK_EQUAL(linReceiveError->isShortError, false);
    BOOST_CHECK_EQUAL(linReceiveError->isDlcTimeout, false);
    BOOST_CHECK_EQUAL(linReceiveError->hasDataBytes, true);
    BOOST_REQUIRE_EQUAL(linReceiveError->data.size(), 8);
    BOOST_CHECK_EQUAL(linReceiveError->data[0], 0x05);
    BOOST_CHECK_EQUAL(linReceiveError->data[1], 0x00);
    BOOST_CHECK_EQUAL(linReceiveError->data[2], 0x00);
    BOOST_CHECK_EQUAL(linReceiveError->data[3], 0x00);
    BOOST_CHECK_EQUAL(linReceiveError->data[4], 0x00);
    BOOST_CHECK_EQUAL(linReceiveError->data[5], 0xff);
    BOOST_CHECK_EQUAL(linReceiveError->data[6], 0xff);
    BOOST_CHECK_EQUAL(linReceiveError->data[7], 0xff);
    BOOST_CHECK_EQUAL(linReceiveError->startOfFrame, 0.546052);
    BOOST_CHECK_EQUAL(linReceiveError->baudrate, 19230);
    BOOST_CHECK_EQUAL(linReceiveError->syncBreak, 937187);
    BOOST_CHECK_EQUAL(linReceiveError->syncDel, 112437);
    BOOST_CHECK_EQUAL(linReceiveError->endOfHeader, 0.548121);
    BOOST_REQUIRE_EQUAL(linReceiveError->endOfByte.size(), 8);
    BOOST_CHECK_EQUAL(linReceiveError->endOfByte[0], 0.548644);
    BOOST_CHECK_EQUAL(linReceiveError->endOfByte[1], 0.549167);
    BOOST_CHECK_EQUAL(linReceiveError->endOfByte[2], 0.549690);
    BOOST_CHECK_EQUAL(linReceiveError->endOfByte[3], 0.550213);
    BOOST_CHECK_EQUAL(linReceiveError->endOfByte[4], 0.550736);
    BOOST_CHECK_EQUAL(linReceiveError->endOfByte[5], 0.551259);
    BOOST_CHECK_EQUAL(linReceiveError->endOfByte[6], 0.551782);
    BOOST_CHECK_EQUAL(linReceiveError->endOfByte[7], 0.552305);
    BOOST_CHECK_EQUAL(linReceiveError->responseBaudrate, 19231);
    BOOST_CHECK_EQUAL(linReceiveError->stopBitOffsetInResponse, 26000);
    BOOST_CHECK_EQUAL(linReceiveError->headerBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(linReceiveError->stopBitOffsetInHeader, 26000);
    BOOST_CHECK(linReceiveError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinSyncError) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSyncError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSyncError * linSyncError;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSyncError);
    linSyncError = static_cast<Vector::ASC::LinSyncError *>(event);
    BOOST_CHECK_EQUAL(linSyncError->time, 2.022336);
    BOOST_CHECK_EQUAL(linSyncError->channel, 2);
    BOOST_CHECK_EQUAL(linSyncError->timeInterval[0], 208);
    BOOST_CHECK_EQUAL(linSyncError->timeInterval[1], 0);
    BOOST_CHECK_EQUAL(linSyncError->timeInterval[2], 0);
    BOOST_CHECK_EQUAL(linSyncError->timeInterval[3], 0);
    BOOST_CHECK_EQUAL(linSyncError->startOfFrame, 2.021077);
    BOOST_CHECK_EQUAL(linSyncError->baudrate, 19230);
    BOOST_CHECK_EQUAL(linSyncError->syncBreak, 937125);
    BOOST_CHECK_EQUAL(linSyncError->syncDel, 113312);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinChecksumError) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinChecksumError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinChecksumError * linChecksumError;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinChecksumError);
    linChecksumError = static_cast<Vector::ASC::LinChecksumError *>(event);
    BOOST_CHECK_EQUAL(linChecksumError->time, 0.462829);
    BOOST_CHECK_EQUAL(linChecksumError->channel, 1);
    BOOST_CHECK_EQUAL(linChecksumError->id, "33");
    BOOST_CHECK(linChecksumError->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(linChecksumError->dlc, 8);
    BOOST_REQUIRE_EQUAL(linChecksumError->data.size(), 8);
    BOOST_CHECK_EQUAL(linChecksumError->data[0], 0x05);
    BOOST_CHECK_EQUAL(linChecksumError->data[1], 0x00);
    BOOST_CHECK_EQUAL(linChecksumError->data[2], 0x00);
    BOOST_CHECK_EQUAL(linChecksumError->data[3], 0x00);
    BOOST_CHECK_EQUAL(linChecksumError->data[4], 0x00);
    BOOST_CHECK_EQUAL(linChecksumError->data[5], 0xff);
    BOOST_CHECK_EQUAL(linChecksumError->data[6], 0xff);
    BOOST_CHECK_EQUAL(linChecksumError->data[7], 0xff);
    BOOST_CHECK_EQUAL(linChecksumError->checksum, 0x86);
    BOOST_CHECK_EQUAL(linChecksumError->headerTime, 40);
    BOOST_CHECK_EQUAL(linChecksumError->fullTime, 130);
    BOOST_CHECK_EQUAL(linChecksumError->startOfFrame, 0.456050);
    BOOST_CHECK_EQUAL(linChecksumError->baudrate, 19230);
    BOOST_CHECK_EQUAL(linChecksumError->syncBreak, 937187);
    BOOST_CHECK_EQUAL(linChecksumError->syncDel, 114875);
    BOOST_CHECK_EQUAL(linChecksumError->endOfHeader, 0.458122);
    BOOST_REQUIRE_EQUAL(linChecksumError->endOfByte.size(), 8);
    BOOST_CHECK_EQUAL(linChecksumError->endOfByte[0], 0.458645);
    BOOST_CHECK_EQUAL(linChecksumError->endOfByte[1], 0.459168);
    BOOST_CHECK_EQUAL(linChecksumError->endOfByte[2], 0.459691);
    BOOST_CHECK_EQUAL(linChecksumError->endOfByte[3], 0.460214);
    BOOST_CHECK_EQUAL(linChecksumError->endOfByte[4], 0.460737);
    BOOST_CHECK_EQUAL(linChecksumError->endOfByte[5], 0.461260);
    BOOST_CHECK_EQUAL(linChecksumError->endOfByte[6], 0.461783);
    BOOST_CHECK_EQUAL(linChecksumError->endOfByte[7], 0.462306);
    BOOST_CHECK_EQUAL(linChecksumError->simulated, true);
    BOOST_CHECK_EQUAL(linChecksumError->endOfFrame, 0.462829);
    BOOST_CHECK_EQUAL(linChecksumError->responseBaudrate, 19231);
    BOOST_CHECK_EQUAL(linChecksumError->headerBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(linChecksumError->stopBitOffsetInHeader, 26000);
    BOOST_CHECK_EQUAL(linChecksumError->stopBitOffsetInResponse, 26000);
    BOOST_CHECK(linChecksumError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinSpike) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSpike.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSpike * linSpike;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSpike);
    linSpike = static_cast<Vector::ASC::LinSpike *>(event);
    BOOST_CHECK_EQUAL(linSpike->time, 5.990958);
    BOOST_CHECK_EQUAL(linSpike->channel, 2);
    BOOST_CHECK(linSpike->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(linSpike->spikeLength, 56);
    BOOST_CHECK_EQUAL(linSpike->startOfFrame, 5.990902);
    BOOST_CHECK_EQUAL(linSpike->baudrate, 9615);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinDominantSignal) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDominantSignal.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDominantSignal * linDominantSignal;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDominantSignal);
    linDominantSignal = static_cast<Vector::ASC::LinDominantSignal *>(event);
    BOOST_CHECK_EQUAL(linDominantSignal->time, 8.976802);
    BOOST_CHECK_EQUAL(linDominantSignal->channel, 1);
    BOOST_CHECK(linDominantSignal->domSigState == Vector::ASC::LinDomSigState::Detected);
    BOOST_CHECK_EQUAL(linDominantSignal->domSigLength, 5003);
    BOOST_CHECK_EQUAL(linDominantSignal->startOfFrame, 8.971798);
    BOOST_CHECK_EQUAL(linDominantSignal->baudrate, 9615);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDominantSignal);
    linDominantSignal = static_cast<Vector::ASC::LinDominantSignal *>(event);
    BOOST_CHECK_EQUAL(linDominantSignal->time, 8.977000);
    BOOST_CHECK_EQUAL(linDominantSignal->channel, 1);
    BOOST_CHECK(linDominantSignal->domSigState == Vector::ASC::LinDomSigState::Finished);
    BOOST_CHECK_EQUAL(linDominantSignal->domSigLength, 5201);
    BOOST_CHECK_EQUAL(linDominantSignal->startOfFrame, 8.971798);
    BOOST_CHECK_EQUAL(linDominantSignal->baudrate, 9615);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN Info Events */
BOOST_AUTO_TEST_CASE(LinBaudrate) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinBaudrate.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinBaudrate * linBaudrate;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinBaudrate);
    linBaudrate = static_cast<Vector::ASC::LinBaudrate *>(event);
    BOOST_CHECK_EQUAL(linBaudrate->time, 0.018800);
    BOOST_CHECK_EQUAL(linBaudrate->channel, 1);
    BOOST_CHECK_EQUAL(linBaudrate->baudrate, 9615);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinDlcInfo) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDlcInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDlcInfo * linDlcInfo;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDlcInfo);
    linDlcInfo = static_cast<Vector::ASC::LinDlcInfo *>(event);
    BOOST_CHECK_EQUAL(linDlcInfo->time, 12.637500);
    BOOST_CHECK_EQUAL(linDlcInfo->channel, 1);
    BOOST_CHECK_EQUAL(linDlcInfo->id, "20");
    BOOST_CHECK_EQUAL(linDlcInfo->dlc, 4);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinChecksumInfo) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinChecksumInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinChecksumInfo * linChecksumInfo;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinChecksumInfo);
    linChecksumInfo = static_cast<Vector::ASC::LinChecksumInfo *>(event);
    BOOST_CHECK_EQUAL(linChecksumInfo->time, 0.020100);
    BOOST_CHECK_EQUAL(linChecksumInfo->channel, 1);
    BOOST_CHECK_EQUAL(linChecksumInfo->id, "22");
    BOOST_CHECK(linChecksumInfo->checksumModelInfo == Vector::ASC::LinChecksumModelInfo::Classic);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinSchedulerModeChange) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSchedulerModeChange.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSchedulerModeChange * linSchedulerModeChange;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSchedulerModeChange);
    linSchedulerModeChange = static_cast<Vector::ASC::LinSchedulerModeChange *>(event);
    BOOST_CHECK_EQUAL(linSchedulerModeChange->time, 0.100000);
    BOOST_CHECK_EQUAL(linSchedulerModeChange->channel, 1);
    BOOST_CHECK_EQUAL(linSchedulerModeChange->priorSchedulerMode, 2);
    BOOST_CHECK_EQUAL(linSchedulerModeChange->nextSchedulerMode, 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinSlaveTimeout) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSlaveTimeout.asc");
    BOOST_REQUIRE(file.is_open());


    Vector::ASC::Event * event;
    Vector::ASC::LinSlaveTimeout * linSlaveTimeout;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSlaveTimeout);
    linSlaveTimeout = static_cast<Vector::ASC::LinSlaveTimeout *>(event);
    BOOST_CHECK_EQUAL(linSlaveTimeout->time, 1.001200);
    BOOST_CHECK_EQUAL(linSlaveTimeout->channel, 1);
    BOOST_CHECK_EQUAL(linSlaveTimeout->slaveId, 0);
    BOOST_CHECK_EQUAL(linSlaveTimeout->currentState, 0);
    BOOST_CHECK_EQUAL(linSlaveTimeout->followingState, 1);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinEventTriggeredFrameInfo) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinEventTriggeredFrameInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinEventTriggeredFrameInfo * linEventTriggeredFrameInfo;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinEventTriggeredFrameInfo);
    linEventTriggeredFrameInfo = static_cast<Vector::ASC::LinEventTriggeredFrameInfo *>(event);
    BOOST_CHECK_EQUAL(linEventTriggeredFrameInfo->time, 1.909165);
    BOOST_CHECK_EQUAL(linEventTriggeredFrameInfo->channel, 1);
    BOOST_CHECK_EQUAL(linEventTriggeredFrameInfo->id, "3a");
    BOOST_CHECK_EQUAL(linEventTriggeredFrameInfo->etfName, "ETF_MotorStates");
    BOOST_CHECK_EQUAL(linEventTriggeredFrameInfo->description, "No response");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinStatisticInfo) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinStatisticInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinStatisticInfo * linStatisticInfo;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinStatisticInfo);
    linStatisticInfo = static_cast<Vector::ASC::LinStatisticInfo *>(event);
    BOOST_CHECK_EQUAL(linStatisticInfo->time, 1.999580);
    BOOST_CHECK_EQUAL(linStatisticInfo->channel, 1);
    BOOST_CHECK_EQUAL(linStatisticInfo->channelNum, 1);
    BOOST_CHECK_EQUAL(linStatisticInfo->busLoad, 0.903601);
    BOOST_CHECK_EQUAL(linStatisticInfo->burstsTotal, 0);
    BOOST_CHECK_EQUAL(linStatisticInfo->burstsOverrun, 0);
    BOOST_CHECK_EQUAL(linStatisticInfo->framesSent, 0);
    BOOST_CHECK_EQUAL(linStatisticInfo->framesReceived, 73);
    BOOST_CHECK_EQUAL(linStatisticInfo->framesUnanswered, 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinShortOrSlowResponse) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinShortOrSlowResponse.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinShortOrSlowResponse * linShortOrSlowResponse;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinShortOrSlowResponse);
    linShortOrSlowResponse = static_cast<Vector::ASC::LinShortOrSlowResponse *>(event);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->time, 1.298765);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->channel, 1);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->id, "1");
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->dlc, 8);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->numberOfResponseBytes, 9);
    BOOST_REQUIRE_EQUAL(linShortOrSlowResponse->data.size(), 9);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[0], 0x11);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[1], 0x12);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[2], 0x13);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[3], 0x14);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[4], 0x15);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[5], 0x16);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[6], 0x17);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[7], 0x18);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->data[8], 0x99);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->isSlowResponse, true);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->responseWasInterruptedByBreak, false);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->startOfFrame, 1.279516);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->baudrate, 19230);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->syncBreak, 937250);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->syncDel, 102625);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfHeader, 1.281570);
    BOOST_REQUIRE_EQUAL(linShortOrSlowResponse->endOfByte.size(), 8);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfByte[0], 1.283679);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfByte[1], 1.285759);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfByte[2], 1.287839);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfByte[3], 1.289927);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfByte[4], 1.292007);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfByte[5], 1.294087);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfByte[6], 1.296167);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->endOfByte[7], 1.298244);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->headerBaudrate, 19230.769231);
    BOOST_CHECK_EQUAL(linShortOrSlowResponse->stopBitOffsetInHeader, 26000);
    BOOST_CHECK(linShortOrSlowResponse->checksumModel == Vector::ASC::LinChecksumModel::Unknown);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinDisturbance) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDisturbance.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDisturbance * linDisturbance;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDisturbance);
    linDisturbance = static_cast<Vector::ASC::LinDisturbance *>(event);
    BOOST_CHECK_EQUAL(linDisturbance->time, 1.323661);
    BOOST_CHECK_EQUAL(linDisturbance->channel, 1);
    BOOST_CHECK(linDisturbance->disturbanceType == Vector::ASC::LinDisturbanceType::Dominant);
    BOOST_CHECK_EQUAL(linDisturbance->byteIndex, 1);
    BOOST_CHECK_EQUAL(linDisturbance->bitIndex, 6);
    BOOST_CHECK_EQUAL(linDisturbance->bitOffset, 0);
    BOOST_CHECK_EQUAL(linDisturbance->length, 16);
    BOOST_CHECK_EQUAL(linDisturbance->header, 0x2D);
    BOOST_CHECK_EQUAL(linDisturbance->disturbingHeader, 0xFF);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* LIN Sleep/Wakeup Events */
BOOST_AUTO_TEST_CASE(LinSleepMode) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSleepMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSleepMode * linSleepMode;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSleepMode);
    linSleepMode = static_cast<Vector::ASC::LinSleepMode *>(event);
    BOOST_CHECK_EQUAL(linSleepMode->time, 0.7772);
    BOOST_CHECK_EQUAL(linSleepMode->channel, 1);
    BOOST_CHECK_EQUAL(linSleepMode->simulated, false);
    BOOST_CHECK_EQUAL(linSleepMode->description, "entering sleep mode due to sleep mode frame");
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinWakeupFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinWakeupFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinWakeupFrame * linWakeupFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinWakeupFrame);
    linWakeupFrame = static_cast<Vector::ASC::LinWakeupFrame *>(event);
    BOOST_CHECK_EQUAL(linWakeupFrame->time, 2.318672);
    BOOST_CHECK_EQUAL(linWakeupFrame->channel, 1);
    BOOST_CHECK(linWakeupFrame->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(linWakeupFrame->wakeupByte, 0);
    BOOST_CHECK_EQUAL(linWakeupFrame->startOfFrame, 2.317671);
    BOOST_CHECK_EQUAL(linWakeupFrame->baudrate, 19230);
    BOOST_CHECK_EQUAL(linWakeupFrame->wakeupLengthInfo, 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(LinUnexpectedWakeup) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinUnexpectedWakeup.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinUnexpectedWakeup * linUnexpectedWakeup;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinUnexpectedWakeup);
    linUnexpectedWakeup = static_cast<Vector::ASC::LinUnexpectedWakeup *>(event);
    BOOST_CHECK_EQUAL(linUnexpectedWakeup->time, 0.892363);
    BOOST_CHECK_EQUAL(linUnexpectedWakeup->channel, 1);
    BOOST_CHECK_EQUAL(linUnexpectedWakeup->width, 260);
    BOOST_CHECK_EQUAL(linUnexpectedWakeup->startOfFrame, 0.891843);
    BOOST_CHECK_EQUAL(linUnexpectedWakeup->baudrate, 19230);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* MOST Events */
BOOST_AUTO_TEST_CASE(Most25ControlMessageNodeMode) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25ControlMessageNodeMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25ControlMessageNodeMode * most25ControlMessageNodeMode;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25ControlMessageNodeMode);
    most25ControlMessageNodeMode = static_cast<Vector::ASC::Most25ControlMessageNodeMode *>(event);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->time, 0.111757);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->channel, 1);
    BOOST_CHECK(most25ControlMessageNodeMode->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->sourceAdr, 0x0100);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->destAdr, 0x0401);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->rType, 0x00);
    BOOST_REQUIRE_EQUAL(most25ControlMessageNodeMode->data.size(), 17);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[0], 0x01);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[1], 0x01);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[2], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[3], 0x01);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[4], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[5], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[6], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[7], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[8], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[9], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[10], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[11], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[12], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[13], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[14], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[15], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->data[16], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageNodeMode->state2, 0x1250);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most25ControlMessageSpyMode) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25ControlMessageSpyMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25ControlMessageSpyMode * most25ControlMessageSpyMode;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25ControlMessageSpyMode);
    most25ControlMessageSpyMode = static_cast<Vector::ASC::Most25ControlMessageSpyMode *>(event);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->time, 0.113526);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->channel, 1);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->sourceAdr, 0xFFFF);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->destAdr, 0x0100);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->rType, 0x00);
    BOOST_REQUIRE_EQUAL(most25ControlMessageSpyMode->data.size(), 17);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[0], 0x01);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[1], 0x01);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[2], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[3], 0x0C);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[4], 0x04);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[5], 0x31);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[6], 0x01);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[7], 0x52);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[8], 0x01);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[9], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[10], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[11], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[12], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[13], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[14], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[15], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->data[16], 0x00);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->state, 0x01);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->ackNack, 0x12);
    BOOST_CHECK_EQUAL(most25ControlMessageSpyMode->crc, 0xAA33);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most25Packet) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25Packet * most25Packet;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25Packet);
    most25Packet = static_cast<Vector::ASC::Most25Packet *>(event);
    BOOST_CHECK_EQUAL(most25Packet->time, 4.445080);
    BOOST_CHECK_EQUAL(most25Packet->channel, 1);
    BOOST_CHECK(most25Packet->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(most25Packet->sourceAdr, 0x0101);
    BOOST_CHECK_EQUAL(most25Packet->destAdr, 0x0100);
    BOOST_CHECK_EQUAL(most25Packet->pktState, 0x00);
    BOOST_CHECK(most25Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK_EQUAL(most25Packet->pktPrio, 0);
    BOOST_CHECK_EQUAL(most25Packet->pktArbitr, 0x03);
    BOOST_CHECK_EQUAL(most25Packet->crc2, 0x0000);
    BOOST_CHECK_EQUAL(most25Packet->pktLen, 0x00A);
    BOOST_REQUIRE_EQUAL(most25Packet->data.size(), 0x00A);
    BOOST_CHECK_EQUAL(most25Packet->data[0], 0x52);
    BOOST_CHECK_EQUAL(most25Packet->data[1], 0x01);
    BOOST_CHECK_EQUAL(most25Packet->data[2], 0xE0);
    BOOST_CHECK_EQUAL(most25Packet->data[3], 0x3C);
    BOOST_CHECK_EQUAL(most25Packet->data[4], 0x90);
    BOOST_CHECK_EQUAL(most25Packet->data[5], 0x01);
    BOOST_CHECK_EQUAL(most25Packet->data[6], 0xFD);
    BOOST_CHECK_EQUAL(most25Packet->data[7], 0x00);
    BOOST_CHECK_EQUAL(most25Packet->data[8], 0x00);
    BOOST_CHECK_EQUAL(most25Packet->data[9], 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostLightLock) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostLightLock.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostLightLock * mostLightLock;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostLightLock);
    mostLightLock = static_cast<Vector::ASC::MostLightLock *>(event);
    BOOST_CHECK_EQUAL(mostLightLock->time, 0.008638);
    BOOST_CHECK_EQUAL(mostLightLock->channel, 1);
    BOOST_CHECK_EQUAL(mostLightLock->llState, 1);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostSpecialRegister) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostSpecialRegister.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostSpecialRegister * mostSpecialRegister;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostSpecialRegister);
    mostSpecialRegister = static_cast<Vector::ASC::MostSpecialRegister *>(event);
    BOOST_CHECK_EQUAL(mostSpecialRegister->time, 1.471300);
    BOOST_CHECK_EQUAL(mostSpecialRegister->channel, 1);
    BOOST_CHECK(mostSpecialRegister->regSubType == Vector::ASC::MostRegSubType::Notify);
    BOOST_CHECK_EQUAL(mostSpecialRegister->regId, 0x8A);
    BOOST_CHECK_EQUAL(mostSpecialRegister->regValue, 0x0172);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostCommonRegister) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostCommonRegister.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostCommonRegister * mostCommonRegister;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostCommonRegister);
    mostCommonRegister = static_cast<Vector::ASC::MostCommonRegister *>(event);
    BOOST_CHECK_EQUAL(mostCommonRegister->time, 9.050000);
    BOOST_CHECK_EQUAL(mostCommonRegister->channel, 1);
    BOOST_CHECK(mostCommonRegister->regSubType == Vector::ASC::MostRegSubType::Unspecified);
    BOOST_CHECK_EQUAL(mostCommonRegister->regChip, 0x01);
    BOOST_CHECK_EQUAL(mostCommonRegister->regOffset, 0x0000);
    BOOST_CHECK_EQUAL(mostCommonRegister->regDataLen, 0x10);
    BOOST_REQUIRE_EQUAL(mostCommonRegister->data.size(), 0x10);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[0], 0x00);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[1], 0x01);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[2], 0x02);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[3], 0x03);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[4], 0x04);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[5], 0x05);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[6], 0x06);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[7], 0x07);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[8], 0x08);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[9], 0x09);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[10], 0x0A);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[11], 0x0B);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[12], 0x0C);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[13], 0x0D);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[14], 0x0E);
    BOOST_CHECK_EQUAL(mostCommonRegister->data[15], 0x0F);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostHwMode) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostHwMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostHwMode * mostHwMode;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostHwMode);
    mostHwMode = static_cast<Vector::ASC::MostHwMode *>(event);
    BOOST_CHECK_EQUAL(mostHwMode->time, 3.560000);
    BOOST_CHECK_EQUAL(mostHwMode->channel, 1);
    BOOST_CHECK_EQUAL(mostHwMode->hwMode, 0x01);
    BOOST_CHECK_EQUAL(mostHwMode->hwModeMask, 0x01);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostNetState) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostNetState.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostNetState * mostNetState;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostNetState);
    mostNetState = static_cast<Vector::ASC::MostNetState *>(event);
    BOOST_CHECK_EQUAL(mostNetState->time, 1.027900);
    BOOST_CHECK_EQUAL(mostNetState->channel, 1);
    BOOST_CHECK_EQUAL(mostNetState->netStateOld, 2);
    BOOST_CHECK_EQUAL(mostNetState->netStateNew, 3);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostDataLost) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostDataLost.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostDataLost * mostDataLost;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostDataLost);
    mostDataLost = static_cast<Vector::ASC::MostDataLost *>(event);
    BOOST_CHECK_EQUAL(mostDataLost->time, 1.303700);
    BOOST_CHECK_EQUAL(mostDataLost->channel, 1);
    BOOST_CHECK_EQUAL(mostDataLost->dlInfo, 0x00000005);
    BOOST_CHECK_EQUAL(mostDataLost->dlCtrl, 0x003F);
    BOOST_CHECK_EQUAL(mostDataLost->dlAsync, 0x000D);
    BOOST_CHECK_EQUAL(mostDataLost->dlTime[0], 101.30369);
    BOOST_CHECK_EQUAL(mostDataLost->dlTime[1], 2223.52592);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostTrigger) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostTrigger.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostTrigger * mostTrigger;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostTrigger);
    mostTrigger = static_cast<Vector::ASC::MostTrigger *>(event);
    BOOST_CHECK_EQUAL(mostTrigger->time, 1.303700);
    BOOST_CHECK_EQUAL(mostTrigger->channel, 1);
    BOOST_CHECK(mostTrigger->trigMode == Vector::ASC::MostTrigMode::SynchronizationSlave);
    BOOST_CHECK_EQUAL(mostTrigger->trigHw, 4);
    BOOST_CHECK_EQUAL(mostTrigger->trigValue[0], 0x00000001);
    BOOST_CHECK_EQUAL(mostTrigger->trigValue[1], 0x00000000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostStatistic) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStatistic.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStatistic * mostStatistic;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStatistic);
    mostStatistic = static_cast<Vector::ASC::MostStatistic *>(event);
    BOOST_CHECK_EQUAL(mostStatistic->time, 2.030000);
    BOOST_CHECK_EQUAL(mostStatistic->channel, 1);
    BOOST_CHECK_EQUAL(mostStatistic->fr, 0);
    BOOST_CHECK_EQUAL(mostStatistic->lt, 4);
    BOOST_CHECK_EQUAL(mostStatistic->bl, 0);
    BOOST_CHECK_EQUAL(mostStatistic->pk, 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostStatisticExtended) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStatisticExtended.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStatisticExtended * mostStatisticExtended;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStatisticExtended);
    mostStatisticExtended = static_cast<Vector::ASC::MostStatisticExtended *>(event);
    BOOST_CHECK_EQUAL(mostStatisticExtended->time, 2.024742);
    BOOST_CHECK_EQUAL(mostStatisticExtended->channel, 2);
    BOOST_CHECK_EQUAL(mostStatisticExtended->codingErrors, 0x000006);
    BOOST_CHECK_EQUAL(mostStatisticExtended->frameCounter, 0x00A395);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostTxLight) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostTxLight.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostTxLight * mostTxLight;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostTxLight);
    mostTxLight = static_cast<Vector::ASC::MostTxLight *>(event);
    BOOST_CHECK_EQUAL(mostTxLight->time, 0.008638);
    BOOST_CHECK_EQUAL(mostTxLight->channel, 1);
    BOOST_CHECK(mostTxLight->txLightState == Vector::ASC::MostTxLightState::Enabled);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostStress) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStress.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStress * mostStress;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStress);
    mostStress = static_cast<Vector::ASC::MostStress *>(event);
    BOOST_CHECK_EQUAL(mostStress->time, 1.793083);
    BOOST_CHECK_EQUAL(mostStress->channel, 1);
    BOOST_CHECK_EQUAL(mostStress->stressMode, 2);
    BOOST_CHECK(mostStress->stressState == Vector::ASC::MostStressState::Started);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most25AllocTable) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25AllocTable.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25AllocTable * most25AllocTable;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25AllocTable);
    most25AllocTable = static_cast<Vector::ASC::Most25AllocTable *>(event);
    BOOST_CHECK_EQUAL(most25AllocTable->time, 0.032775);
    BOOST_CHECK_EQUAL(most25AllocTable->channel, 2);
    BOOST_CHECK_EQUAL(most25AllocTable->allocTableSize, 0x003C);
    BOOST_REQUIRE_EQUAL(most25AllocTable->data.size(), 0x003C);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x00], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x01], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x02], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x03], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x04], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x05], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x06], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x07], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x08], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x09], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x0a], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x0b], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x0c], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x0d], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x0e], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x0f], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x10], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x11], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x12], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x13], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x14], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x15], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x16], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x17], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x18], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x19], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x1a], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x1b], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x1c], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x1d], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x1e], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x1f], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x20], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x21], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x22], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x23], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x24], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x25], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x26], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x27], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x28], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x29], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x2a], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x2b], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x2c], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x2d], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x2e], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x2f], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x30], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x31], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x32], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x33], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x34], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x35], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x36], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x37], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x38], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x39], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x3a], 0x70);
    BOOST_CHECK_EQUAL(most25AllocTable->data[0x3b], 0x70);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150ControlMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150ControlMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150ControlMessage * most150ControlMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150ControlMessage);
    most150ControlMessage = static_cast<Vector::ASC::Most150ControlMessage *>(event);
    BOOST_CHECK_EQUAL(most150ControlMessage->time, 5.708800);
    BOOST_CHECK_EQUAL(most150ControlMessage->channel, 1);
    BOOST_CHECK(most150ControlMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(most150ControlMessage->sourceAdr, 0x0172);
    BOOST_CHECK_EQUAL(most150ControlMessage->destAdr, 0x03C8);
    BOOST_CHECK_EQUAL(most150ControlMessage->state, 0x02);
    BOOST_CHECK_EQUAL(most150ControlMessage->ackNack, 0x11);
    BOOST_CHECK(most150ControlMessage->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK_EQUAL(most150ControlMessage->pAck, 0x22);
    BOOST_CHECK_EQUAL(most150ControlMessage->priority, 0x01);
    BOOST_CHECK_EQUAL(most150ControlMessage->pIndex, 0x33);
    BOOST_CHECK_EQUAL(most150ControlMessage->crc2, 0xAABB);
    BOOST_CHECK_EQUAL(most150ControlMessage->cAck, 0x44);
    BOOST_CHECK_EQUAL(most150ControlMessage->rsvdUl, 0x00);
    BOOST_CHECK_EQUAL(most150ControlMessage->msg150Len, 0x08);
    BOOST_REQUIRE_EQUAL(most150ControlMessage->data.size(), 0x08);
    BOOST_CHECK_EQUAL(most150ControlMessage->data[0], 0x11);
    BOOST_CHECK_EQUAL(most150ControlMessage->data[1], 0x22);
    BOOST_CHECK_EQUAL(most150ControlMessage->data[2], 0x33);
    BOOST_CHECK_EQUAL(most150ControlMessage->data[3], 0x34);
    BOOST_CHECK_EQUAL(most150ControlMessage->data[4], 0x00);
    BOOST_CHECK_EQUAL(most150ControlMessage->data[5], 0x02);
    BOOST_CHECK_EQUAL(most150ControlMessage->data[6], 0x11);
    BOOST_CHECK_EQUAL(most150ControlMessage->data[7], 0x22);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150ControlMessageFragment) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150ControlMessageFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150ControlMessageFragment * most150ControlMessageFragment;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150ControlMessageFragment);
    most150ControlMessageFragment = static_cast<Vector::ASC::Most150ControlMessageFragment *>(event);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->time, 5.708800);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->channel, 1);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->frgMask, 0x01020304);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->sourceAdr, 0x0172);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->destAdr, 0x03C8);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->ackNack, 0x11);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->pAck, 0x22);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->priority, 0x01);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->pIndex, 0x33);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->crc2, 0xAABB);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->cAck, 0x44);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->rsvdUl, 0x00);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->frgDataLen, 0x0006);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->frgDataLenAnnounced, 0x0210);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->firstDataLen, 0x06);
    BOOST_REQUIRE_EQUAL(most150ControlMessageFragment->data.size(), 0x06);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->data[0], 0x01);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->data[1], 0x02);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->data[2], 0x03);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->data[3], 0x04);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->data[4], 0x05);
    BOOST_CHECK_EQUAL(most150ControlMessageFragment->data[5], 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150Packet) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150Packet * most150Packet;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150Packet);
    most150Packet = static_cast<Vector::ASC::Most150Packet *>(event);
    BOOST_CHECK_EQUAL(most150Packet->time, 5.708800);
    BOOST_CHECK_EQUAL(most150Packet->channel, 1);
    BOOST_CHECK(most150Packet->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(most150Packet->sourceAdr, 0x0172);
    BOOST_CHECK_EQUAL(most150Packet->destAdr, 0x03C8);
    BOOST_CHECK_EQUAL(most150Packet->state, 0x02);
    BOOST_CHECK_EQUAL(most150Packet->ackNack, 0x11);
    BOOST_CHECK(most150Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK_EQUAL(most150Packet->pAck, 0x00);
    BOOST_CHECK_EQUAL(most150Packet->rsvdUc, 0x00);
    BOOST_CHECK_EQUAL(most150Packet->pIndex, 0x33);
    BOOST_CHECK_EQUAL(most150Packet->crc2, 0xAABB);
    BOOST_CHECK_EQUAL(most150Packet->cAck, 0x44);
    BOOST_CHECK_EQUAL(most150Packet->rsvdUl, 0x00);
    BOOST_CHECK_EQUAL(most150Packet->pkt150Len, 0x08);
    BOOST_REQUIRE_EQUAL(most150Packet->data.size(), 0x08);
    BOOST_CHECK_EQUAL(most150Packet->data[0], 0x11);
    BOOST_CHECK_EQUAL(most150Packet->data[1], 0x22);
    BOOST_CHECK_EQUAL(most150Packet->data[2], 0x33);
    BOOST_CHECK_EQUAL(most150Packet->data[3], 0x34);
    BOOST_CHECK_EQUAL(most150Packet->data[4], 0x00);
    BOOST_CHECK_EQUAL(most150Packet->data[5], 0x02);
    BOOST_CHECK_EQUAL(most150Packet->data[6], 0x11);
    BOOST_CHECK_EQUAL(most150Packet->data[7], 0x22);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150PacketFragment) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150PacketFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150PacketFragment * most150PacketFragment;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150PacketFragment);
    most150PacketFragment = static_cast<Vector::ASC::Most150PacketFragment *>(event);
    BOOST_CHECK_EQUAL(most150PacketFragment->time, 5.708800);
    BOOST_CHECK_EQUAL(most150PacketFragment->channel, 1);
    BOOST_CHECK_EQUAL(most150PacketFragment->frgMask, 0x01020304);
    BOOST_CHECK_EQUAL(most150PacketFragment->sourceAdr, 0x0172);
    BOOST_CHECK_EQUAL(most150PacketFragment->destAdr, 0x03C8);
    BOOST_CHECK_EQUAL(most150PacketFragment->ackNack, 0x11);
    BOOST_CHECK_EQUAL(most150PacketFragment->pAck, 0x22);
    BOOST_CHECK_EQUAL(most150PacketFragment->rsvdUc, 0x01);
    BOOST_CHECK_EQUAL(most150PacketFragment->pIndex, 0x33);
    BOOST_CHECK_EQUAL(most150PacketFragment->crc2, 0xAABB);
    BOOST_CHECK_EQUAL(most150PacketFragment->cAck, 0x44);
    BOOST_CHECK_EQUAL(most150PacketFragment->rsvdUl, 0x00);
    BOOST_CHECK_EQUAL(most150PacketFragment->frgDataLen, 0x0006);
    BOOST_CHECK_EQUAL(most150PacketFragment->frgDataLenAnnounced, 0x0210);
    BOOST_CHECK_EQUAL(most150PacketFragment->firstDataLen, 0x06);
    BOOST_REQUIRE_EQUAL(most150PacketFragment->data.size(), 0x06);
    BOOST_CHECK_EQUAL(most150PacketFragment->data[0], 0x01);
    BOOST_CHECK_EQUAL(most150PacketFragment->data[1], 0x02);
    BOOST_CHECK_EQUAL(most150PacketFragment->data[2], 0x03);
    BOOST_CHECK_EQUAL(most150PacketFragment->data[3], 0x04);
    BOOST_CHECK_EQUAL(most150PacketFragment->data[4], 0x05);
    BOOST_CHECK_EQUAL(most150PacketFragment->data[5], 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostEthernetPacket) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEthernetPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEthernetPacket * mostEthernetPacket;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEthernetPacket);
    mostEthernetPacket = static_cast<Vector::ASC::MostEthernetPacket *>(event);
    BOOST_CHECK_EQUAL(mostEthernetPacket->time, 5.708800);
    BOOST_CHECK_EQUAL(mostEthernetPacket->channel, 1);
    BOOST_CHECK(mostEthernetPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(mostEthernetPacket->sourceMacAdr, 0x010203040506);
    BOOST_CHECK_EQUAL(mostEthernetPacket->destMacAdr, 0x112233445566);
    BOOST_CHECK_EQUAL(mostEthernetPacket->state, 0x02);
    BOOST_CHECK_EQUAL(mostEthernetPacket->ackNack, 0x11);
    BOOST_CHECK(mostEthernetPacket->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK_EQUAL(mostEthernetPacket->pAck, 0x22);
    BOOST_CHECK_EQUAL(mostEthernetPacket->crc4, 0xAABBCCDD);
    BOOST_CHECK_EQUAL(mostEthernetPacket->cAck, 0x44);
    BOOST_CHECK_EQUAL(mostEthernetPacket->rsvdUl, 0x00);
    BOOST_CHECK_EQUAL(mostEthernetPacket->pktEthLen, 0x08);
    BOOST_REQUIRE_EQUAL(mostEthernetPacket->data.size(), 0x08);
    BOOST_CHECK_EQUAL(mostEthernetPacket->data[0], 0x11);
    BOOST_CHECK_EQUAL(mostEthernetPacket->data[1], 0x22);
    BOOST_CHECK_EQUAL(mostEthernetPacket->data[2], 0x33);
    BOOST_CHECK_EQUAL(mostEthernetPacket->data[3], 0x34);
    BOOST_CHECK_EQUAL(mostEthernetPacket->data[4], 0x00);
    BOOST_CHECK_EQUAL(mostEthernetPacket->data[5], 0x02);
    BOOST_CHECK_EQUAL(mostEthernetPacket->data[6], 0x11);
    BOOST_CHECK_EQUAL(mostEthernetPacket->data[7], 0x22);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostEthernetPacketFragment) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEthernetPacketFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEthernetPacketFragment * mostEthernetPacketFragment;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEthernetPacketFragment);
    mostEthernetPacketFragment = static_cast<Vector::ASC::MostEthernetPacketFragment *>(event);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->time, 5.708800);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->channel, 1);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->frgMask, 0x01020304);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->sourceMacAdr, 0x010203040506);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->destMacAdr, 0x112233445566);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->ackNack, 0x11);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->pAck, 0x01);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->crc4, 0xAABBCCDD);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->cAck, 0x44);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->rsvdUl, 0x00);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->frgDataLen, 0x0006);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->frgDataLenAnnounced, 0x0210);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->firstDataLen, 0x06);
    BOOST_REQUIRE_EQUAL(mostEthernetPacketFragment->data.size(), 0x06);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->data[0], 0x01);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->data[1], 0x02);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->data[2], 0x03);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->data[3], 0x04);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->data[4], 0x05);
    BOOST_CHECK_EQUAL(mostEthernetPacketFragment->data[5], 0x06);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostSystem) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostSystem.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostSystem * mostSystem;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostSystem);
    mostSystem = static_cast<Vector::ASC::MostSystem *>(event);
    BOOST_CHECK_EQUAL(mostSystem->time, 1.027900);
    BOOST_CHECK_EQUAL(mostSystem->channel, 1);
    BOOST_CHECK(mostSystem->sysId == Vector::ASC::MostSysId::SystemLock);
    BOOST_CHECK_EQUAL(mostSystem->sysValue, 0x0001);
    BOOST_CHECK_EQUAL(mostSystem->sysValueOld, 0x0000);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most150AllocTable) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150AllocTable.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150AllocTable * most150AllocTable;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150AllocTable);
    most150AllocTable = static_cast<Vector::ASC::Most150AllocTable *>(event);
    BOOST_CHECK_EQUAL(most150AllocTable->time, 44.814398);
    BOOST_CHECK_EQUAL(most150AllocTable->channel, 1);
    BOOST_CHECK_EQUAL(most150AllocTable->at150EventModeFlags, 0x00);
    BOOST_CHECK_EQUAL(most150AllocTable->freeBytes, 0x002E);
    BOOST_CHECK_EQUAL(most150AllocTable->at150Size, 0x0004);
    BOOST_REQUIRE_EQUAL(most150AllocTable->wordData.size(), 0x0004);
    BOOST_CHECK_EQUAL(most150AllocTable->wordData[0], 0x010B);
    BOOST_CHECK_EQUAL(most150AllocTable->wordData[1], 0x0004);
    BOOST_CHECK_EQUAL(most150AllocTable->wordData[2], 0x4151);
    BOOST_CHECK_EQUAL(most150AllocTable->wordData[3], 0x0046);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150AllocTable);
    most150AllocTable = static_cast<Vector::ASC::Most150AllocTable *>(event);
    BOOST_CHECK_EQUAL(most150AllocTable->time, 50.126855);
    BOOST_CHECK_EQUAL(most150AllocTable->channel, 1);
    BOOST_CHECK_EQUAL(most150AllocTable->at150EventModeFlags, 0x00);
    BOOST_CHECK_EQUAL(most150AllocTable->freeBytes, 0x0074);
    BOOST_CHECK_EQUAL(most150AllocTable->at150Size, 0x0004);
    BOOST_REQUIRE_EQUAL(most150AllocTable->wordData.size(), 0x0004);
    BOOST_CHECK_EQUAL(most150AllocTable->wordData[0], 0x010B);
    BOOST_CHECK_EQUAL(most150AllocTable->wordData[1], 0x0004);
    BOOST_CHECK_EQUAL(most150AllocTable->wordData[2], 0x8151);
    BOOST_CHECK_EQUAL(most150AllocTable->wordData[3], 0x0046);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most50ControlMessage) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most50ControlMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most50ControlMessage * most50ControlMessage;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most50ControlMessage);
    most50ControlMessage = static_cast<Vector::ASC::Most50ControlMessage *>(event);
    BOOST_CHECK_EQUAL(most50ControlMessage->time, 0.200000);
    BOOST_CHECK_EQUAL(most50ControlMessage->channel, 1);
    BOOST_CHECK(most50ControlMessage->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK_EQUAL(most50ControlMessage->sourceAdr, 0xEF00);
    BOOST_CHECK_EQUAL(most50ControlMessage->destAdr, 0x0101);
    BOOST_CHECK_EQUAL(most50ControlMessage->state, 0x01);
    BOOST_CHECK_EQUAL(most50ControlMessage->ackNack, 0x00);
    BOOST_CHECK(most50ControlMessage->transferType == Vector::ASC::MostTransferType::Spy);
    BOOST_CHECK_EQUAL(most50ControlMessage->rsvdUc1, 0x00);
    BOOST_CHECK_EQUAL(most50ControlMessage->priority, 0x00);
    BOOST_CHECK_EQUAL(most50ControlMessage->rsvdUc2, 0x00);
    BOOST_CHECK_EQUAL(most50ControlMessage->crc2, 0x5678);
    BOOST_CHECK_EQUAL(most50ControlMessage->rsvdUc3, 0x00);
    BOOST_CHECK_EQUAL(most50ControlMessage->rsvdUl, 0x00);
    BOOST_CHECK_EQUAL(most50ControlMessage->msg50Len, 0x09);
    BOOST_REQUIRE_EQUAL(most50ControlMessage->data.size(), 0x09);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[0], 0x11);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[1], 0x01);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[2], 0x22);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[3], 0x23);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[4], 0x04);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[5], 0x11);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[6], 0x22);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[7], 0x33);
    BOOST_CHECK_EQUAL(most50ControlMessage->data[8], 0x44);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(Most50Packet) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most50Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most50Packet * most50Packet;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most50Packet);
    most50Packet = static_cast<Vector::ASC::Most50Packet *>(event);
    BOOST_CHECK_EQUAL(most50Packet->time, 5.708800);
    BOOST_CHECK_EQUAL(most50Packet->channel, 1);
    BOOST_CHECK(most50Packet->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK_EQUAL(most50Packet->sourceAdr, 0x0172);
    BOOST_CHECK_EQUAL(most50Packet->destAdr, 0x03C8);
    BOOST_CHECK_EQUAL(most50Packet->state, 0x02);
    BOOST_CHECK_EQUAL(most50Packet->ackNack, 0x11);
    BOOST_CHECK(most50Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK_EQUAL(most50Packet->rsvdUc1, 0x00);
    BOOST_CHECK_EQUAL(most50Packet->rsvdUc2, 0x00);
    BOOST_CHECK_EQUAL(most50Packet->rsvdUc3, 0x00);
    BOOST_CHECK_EQUAL(most50Packet->crc2, 0xAABB);
    BOOST_CHECK_EQUAL(most50Packet->rsvdUc4, 0x00);
    BOOST_CHECK_EQUAL(most50Packet->rsvdUl, 0x00);
    BOOST_CHECK_EQUAL(most50Packet->pktLen, 0x08);
    BOOST_REQUIRE_EQUAL(most50Packet->data.size(), 0x08);
    BOOST_CHECK_EQUAL(most50Packet->data[0], 0x11);
    BOOST_CHECK_EQUAL(most50Packet->data[1], 0x22);
    BOOST_CHECK_EQUAL(most50Packet->data[2], 0x33);
    BOOST_CHECK_EQUAL(most50Packet->data[3], 0x34);
    BOOST_CHECK_EQUAL(most50Packet->data[4], 0x00);
    BOOST_CHECK_EQUAL(most50Packet->data[5], 0x02);
    BOOST_CHECK_EQUAL(most50Packet->data[6], 0x11);
    BOOST_CHECK_EQUAL(most50Packet->data[7], 0x22);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(MostEcl) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEcl.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEcl * mostEcl;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEcl);
    mostEcl = static_cast<Vector::ASC::MostEcl *>(event);
    BOOST_CHECK_EQUAL(mostEcl->time, 0.009068);
    BOOST_CHECK(mostEcl->eclMode == Vector::ASC::MostEclMode::Discrete);
    BOOST_CHECK(mostEcl->eclState == Vector::ASC::MostEclState::LineHigh);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

/* TP/Diagnostics Events */
BOOST_AUTO_TEST_CASE(TpSingleFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpSingleFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpSingleFrame * tpDiagSingleFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpSingleFrame);
    tpDiagSingleFrame = static_cast<Vector::ASC::TpSingleFrame *>(event);
    BOOST_CHECK_EQUAL(tpDiagSingleFrame->canChannel, 1);
    BOOST_CHECK_EQUAL(tpDiagSingleFrame->connectionId, 0x05);
    BOOST_CHECK(tpDiagSingleFrame->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK_EQUAL(tpDiagSingleFrame->source, "<tester>");
    BOOST_CHECK_EQUAL(tpDiagSingleFrame->destination, "Any_ECU_example");
    BOOST_CHECK_EQUAL(tpDiagSingleFrame->length, 0x02);
    BOOST_REQUIRE_EQUAL(tpDiagSingleFrame->transportedBytes.size(), 0x02);
    BOOST_CHECK_EQUAL(tpDiagSingleFrame->transportedBytes[0], 0x1A);
    BOOST_CHECK_EQUAL(tpDiagSingleFrame->transportedBytes[1], 0x90);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(TpDiagFirstFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpFirstFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpFirstFrame * tpFirstFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpFirstFrame);
    tpFirstFrame = static_cast<Vector::ASC::TpFirstFrame *>(event);
    BOOST_CHECK_EQUAL(tpFirstFrame->canChannel, 1);
    BOOST_CHECK_EQUAL(tpFirstFrame->connectionId, 0x07);
    BOOST_CHECK(tpFirstFrame->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK_EQUAL(tpFirstFrame->source, "Any_ECU_example");
    BOOST_CHECK_EQUAL(tpFirstFrame->destination, "<tester>");
    BOOST_CHECK_EQUAL(tpFirstFrame->length, 0x000C);
    BOOST_REQUIRE_EQUAL(tpFirstFrame->transportedBytes.size(), 6);
    BOOST_CHECK_EQUAL(tpFirstFrame->transportedBytes[0], 0x5A);
    BOOST_CHECK_EQUAL(tpFirstFrame->transportedBytes[1], 0x90);
    BOOST_CHECK_EQUAL(tpFirstFrame->transportedBytes[2], 0x98);
    BOOST_CHECK_EQUAL(tpFirstFrame->transportedBytes[3], 0x76);
    BOOST_CHECK_EQUAL(tpFirstFrame->transportedBytes[4], 0x54);
    BOOST_CHECK_EQUAL(tpFirstFrame->transportedBytes[5], 0x32);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(TpConsecutiveFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpConsecutiveFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpConsecutiveFrame * tpConsecutiveFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpConsecutiveFrame);
    tpConsecutiveFrame = static_cast<Vector::ASC::TpConsecutiveFrame *>(event);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->canChannel, 1);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->connectionId, 0x07);
    BOOST_CHECK(tpConsecutiveFrame->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->source, "Any_ECU_example");
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->destination, "<tester>");
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->sn, 1);
    BOOST_REQUIRE_EQUAL(tpConsecutiveFrame->transportedBytes.size(), 7);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->transportedBytes[0], 0x10);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->transportedBytes[1], 0x00);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->transportedBytes[2], 0x99);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->transportedBytes[3], 0x99);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->transportedBytes[4], 0x00);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->transportedBytes[5], 0x01);
    BOOST_CHECK_EQUAL(tpConsecutiveFrame->transportedBytes[6], 0x00);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(TpFlowControlFrame) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpFlowControlFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpFlowControlFrame * tpFlowControlFrame;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpFlowControlFrame);
    tpFlowControlFrame = static_cast<Vector::ASC::TpFlowControlFrame *>(event);
    BOOST_CHECK_EQUAL(tpFlowControlFrame->canChannel, 1);
    BOOST_CHECK_EQUAL(tpFlowControlFrame->connectionId, 0x07);
    BOOST_CHECK(tpFlowControlFrame->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK_EQUAL(tpFlowControlFrame->source, "<tester>");
    BOOST_CHECK_EQUAL(tpFlowControlFrame->destination, "Any_ECU_example");
    BOOST_CHECK(tpFlowControlFrame->fcType == Vector::ASC::TpDiagFcType::Cts);
    BOOST_CHECK_EQUAL(tpFlowControlFrame->bs, 0x00);
    BOOST_CHECK_EQUAL(tpFlowControlFrame->stMin, 0x14);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(DiagRequest) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/DiagRequest.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::DiagRequest * diagRequest;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK_EQUAL(diagRequest->time, 1.765500);
    BOOST_CHECK_EQUAL(diagRequest->ecuQualifier, "Any_ECU_example");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::ByteSequence);
    BOOST_REQUIRE_EQUAL(diagRequest->byteSequence.size(), 2);
    BOOST_CHECK_EQUAL(diagRequest->byteSequence[0], 0x1A);
    BOOST_CHECK_EQUAL(diagRequest->byteSequence[1], 0x90);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK_EQUAL(diagRequest->time, 1.000000);
    BOOST_CHECK_EQUAL(diagRequest->ecuQualifier, "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::Open);
    BOOST_CHECK_EQUAL(diagRequest->byteSequence.size(), 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK_EQUAL(diagRequest->time, 1.000000);
    BOOST_CHECK_EQUAL(diagRequest->ecuQualifier, "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::ByteSequence);
    BOOST_REQUIRE_EQUAL(diagRequest->byteSequence.size(), 1);
    BOOST_CHECK_EQUAL(diagRequest->byteSequence[0], 0x20);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK_EQUAL(diagRequest->time, 1.000000);
    BOOST_CHECK_EQUAL(diagRequest->ecuQualifier, "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::Close);
    BOOST_CHECK_EQUAL(diagRequest->byteSequence.size(), 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK_EQUAL(diagRequest->time, 1.000000);
    BOOST_CHECK_EQUAL(diagRequest->ecuQualifier, "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::TpOn);
    BOOST_CHECK_EQUAL(diagRequest->byteSequence.size(), 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::DiagRequest);
    diagRequest = static_cast<Vector::ASC::DiagRequest *>(event);
    BOOST_CHECK_EQUAL(diagRequest->time, 1.000000);
    BOOST_CHECK_EQUAL(diagRequest->ecuQualifier, "Engine");
    BOOST_CHECK(diagRequest->command == Vector::ASC::DiagRequest::Command::TpOff);
    BOOST_CHECK_EQUAL(diagRequest->byteSequence.size(), 0);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}

BOOST_AUTO_TEST_CASE(StartOfMeasurement) {
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/StartOfMeasurement.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::StartOfMeasurement * startOfMeasurement;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::StartOfMeasurement);
    startOfMeasurement = static_cast<Vector::ASC::StartOfMeasurement *>(event);
    BOOST_CHECK_EQUAL(startOfMeasurement->time, 0.000000);
    BOOST_CHECK(startOfMeasurement->language == Vector::ASC::File::Language::De);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);

    event = file.read();
    BOOST_REQUIRE(event);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::StartOfMeasurement);
    startOfMeasurement = static_cast<Vector::ASC::StartOfMeasurement *>(event);
    BOOST_CHECK_EQUAL(startOfMeasurement->time, 1.000000);
    BOOST_CHECK(startOfMeasurement->language == Vector::ASC::File::Language::En);
    delete event;

    event = file.read();
    BOOST_CHECK(event == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
