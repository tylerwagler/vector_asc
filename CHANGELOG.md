# Change Log
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [1.1.3] - 2020-09-29
### Fixed
- Fix exception on empty lines

## [1.1.2] - 2020-01-04
### Changed
- Changed style to Google
- Change classes to structs. No invariants. Only public members.
- Introduce Event::Event(EventType eventType)

## [1.1.1] - 2018-12-03
### Changed
- Includes changed from "" to <>
- Removed config.h
- Improve test comparisons

## [1.1.0] - 2017-09-22
### Added
- CanError::error gets interpreted now including txErr and rxErr
- EthernetStatus variables get interpretd now
- Parser code example added
### Changed
- C++11 override and final clauses
- Update to latest project template
- "using" instead of "typedef"
### Fixed
- File::eof() function works now

## [1.0.1] - 2016-05-20
### Changed
- Compiler hardening flags enabled

## [1.0.0] - 2016-05-20
### Added
- Initial version
