cmake_minimum_required(VERSION 2.8)

find_package(BISON)
find_package(FLEX)

include(GenerateExportHeader)

configure_file(
  config.h.in
  config.h)

include_directories(
  ${FLEX_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR})

set(source_files
  AfdxPacket.cpp
  BeginTriggerblockEvent.cpp
  CanBusStatisticsEvent.cpp
  CanErrorEvent.cpp
  CanErrorFrame.cpp
  CanExtendedMessageEvent.cpp
  CanFdErrorFrame.cpp
  CanFdExtendedMessageEvent.cpp
  CanFdMessageEvent.cpp
  CanMessageEvent.cpp
  CanOverloadFrameEvent.cpp
  CanRemoteFrameEvent.cpp
  CommentEvent.cpp
  EndTriggerblockEvent.cpp
  EnvironmentVariablesEvent.cpp
  EthernetPacket.cpp
  EthernetRxError.cpp
  EthernetStatus.cpp
  Event.cpp
  File.cpp
  FileBaseTimestamps.cpp
  FileComment.cpp
  FileDate.cpp
  FileInternalEventsLogged.cpp
  FileSplitInformation.cpp
  FileVersion.cpp
  FlexRayErrorEvent.cpp
  FlexRayMessageEvent.cpp
  FlexRayOldMessageEvent.cpp
  FlexRayOldStartCycleEvent.cpp
  FlexRayStartCycleEvent.cpp
  FlexRayStatusEvent.cpp
  GlobalMarkerEvent.cpp
  GpsEvent.cpp
  KLineByteEvent.cpp
  KLineMessageEvent.cpp
  LinBaudrate.cpp
  LinChecksumError.cpp
  LinChecksumInfo.cpp
  LinDisturbanceEvent.cpp
  LinDlcInfo.cpp
  LinDominantSignal.cpp
  LinEventTriggeredFrameInfo.cpp
  LinMessage.cpp
  LinReceiveError.cpp
  LinSchedulerModeChange.cpp
  LinShortOrSlowResponse.cpp
  LinSlaveTimeout.cpp
  LinSleepMode.cpp
  LinSpikeEvent.cpp
  LinStatisticInfo.cpp
  LinSyncError.cpp
  LinTransmissionError.cpp
  LinUnexpectedWakeup.cpp
  LinWakeupFrame.cpp
  LogDirectStartEvent.cpp
  LogDirectStopEvent.cpp
  LogTriggerEvent.cpp
  MacroSignalEvent.cpp
  Most150AllocTable.cpp
  Most150ControlMessage.cpp
  Most150ControlMessageFragment.cpp
  Most150Packet.cpp
  Most150PacketFragment.cpp
  Most25AllocTable.cpp
  Most25ControlMessageNodeMode.cpp
  Most25ControlMessageSpyMode.cpp
  Most25Packet.cpp
  Most50ControlMessage.cpp
  Most50Packet.cpp
  MostCommonRegisterEvent.cpp
  MostDataLostEvent.cpp
  MostEcl.cpp
  MostEthernetPacket.cpp
  MostEthernetPacketFragment.cpp
  MostHwModeEvent.cpp
  MostLightLockEvent.cpp
  MostNetStateEvent.cpp
  MostSpecialRegisterEvent.cpp
  MostStatisticEvent.cpp
  MostStatisticExtendedEvent.cpp
  MostStressEvent.cpp
  MostSystemEvent.cpp
  MostTriggerEvent.cpp
  MostTxLight.cpp
  Symbols.cpp
  SystemVariablesEvent.cpp
  TpDiagConsecutiveFrame.cpp
  TpDiagFirstFrame.cpp
  TpDiagFlowControlFrame.cpp
  TpDiagPrefix.cpp
  TpDiagRequest.cpp
  TpDiagSingleFrame.cpp)

set(public_header_files
  AfdxPacket.h
  AllEvents.h
  BeginTriggerblockEvent.h
  CanBusStatisticsEvent.h
  CanErrorEvent.h
  CanErrorFrame.h
  CanExtendedMessageEvent.h
  CanFdErrorFrame.h
  CanFdExtendedMessageEvent.h
  CanFdMessageEvent.h
  CanMessageEvent.h
  CanOverloadFrameEvent.h
  CanRemoteFrameEvent.h
  CommentEvent.h
  EndTriggerblockEvent.h
  EnvironmentVariablesEvent.h
  EthernetPacket.h
  EthernetRxError.h
  EthernetStatus.h
  Event.h
  File.h
  FileBaseTimestamps.h
  FileComment.h
  FileDate.h
  FileInternalEventsLogged.h
  FileSplitInformation.h
  FileVersion.h
  FlexRayErrorEvent.h
  FlexRayMessageEvent.h
  FlexRayOldMessageEvent.h
  FlexRayOldStartCycleEvent.h
  FlexRayStartCycleEvent.h
  FlexRayStatusEvent.h
  GlobalMarkerEvent.h
  GpsEvent.h
  KLineByteEvent.h
  KLineMessageEvent.h
  LinBaudrate.h
  LinChecksumError.h
  LinChecksumInfo.h
  LinDisturbanceEvent.h
  LinDlcInfo.h
  LinDominantSignal.h
  LinEventTriggeredFrameInfo.h
  LinMessage.h
  LinReceiveError.h
  LinSchedulerModeChange.h
  LinShortOrSlowResponse.h
  LinSlaveTimeout.h
  LinSleepMode.h
  LinSpikeEvent.h
  LinStatisticInfo.h
  LinSyncError.h
  LinTransmissionError.h
  LinUnexpectedWakeup.h
  LinWakeupFrame.h
  LogDirectStartEvent.h
  LogDirectStopEvent.h
  LogTriggerEvent.h
  MacroSignalEvent.h
  Most150AllocTable.h
  Most150ControlMessage.h
  Most150ControlMessageFragment.h
  Most150PacketFragment.h
  Most150Packet.h
  Most25AllocTable.h
  Most25ControlMessageNodeMode.h
  Most25ControlMessageSpyMode.h
  Most25Packet.h
  Most50ControlMessage.h
  Most50Packet.h
  MostCommonRegisterEvent.h
  MostDataLostEvent.h
  MostEcl.h
  MostEthernetPacketFragment.h
  MostEthernetPacket.h
  MostHwModeEvent.h
  MostLightLockEvent.h
  MostNetStateEvent.h
  MostSpecialRegisterEvent.h
  MostStatisticEvent.h
  MostStatisticExtendedEvent.h
  MostStressEvent.h
  MostSystemEvent.h
  MostTriggerEvent.h
  MostTxLight.h
  Symbols.h
  SystemVariablesEvent.h
  TpDiagConsecutiveFrame.h
  TpDiagFirstFrame.h
  TpDiagFlowControlFrame.h
  TpDiagPrefix.h
  TpDiagRequest.h
  TpDiagSingleFrame.h)

set(private_header_files
  SymbolsRegEx.h)

set(info_files
  Lexer.l)
#  Parser.yy)

add_compiler_export_flags()

#bison_target(Parser Parser.yy ${CMAKE_CURRENT_BINARY_DIR}/Parser.tab.cpp)
if(WIN32)
  flex_target(Lexer Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp
    COMPILE_FLAGS --wincompat)
endif(WIN32)
if(UNIX)
  flex_target(Lexer Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)
endif(UNIX)
#add_flex_bison_dependency(Lexer Parser)

add_library(${PROJECT_NAME} SHARED
  ${source_files} ${public_header_files} ${private_header_files} ${info_files}
  #${BISON_Parser_OUTPUTS}
  ${FLEX_Lexer_OUTPUTS})

if(OPTION_USE_GCOV_LCOV)
  target_link_libraries(${PROJECT_NAME} gcov)
  add_definitions(-g -O0 -fprofile-arcs -ftest-coverage)
endif()

generate_export_header(${PROJECT_NAME})

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-std=c++11)
endif()

install(
  TARGETS ${PROJECT_NAME}
  DESTINATION lib)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/vector_asc_export.h
  DESTINATION include/Vector/ASC)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/config.h ${public_header_files}
  DESTINATION include/Vector/ASC)

add_subdirectory(docs)

add_subdirectory(tests)
