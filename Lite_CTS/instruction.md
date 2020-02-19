# How to run OpenVG 1.1 Lite Conformance Test Suite
(Now we're working and updating on this files - Last update 27 July 2017)

This document describes how to build and run the OpenVG Lite Conformance Test Suite.

## Overview

Flow of CTS is; compile and load CTS with your implementation of OpenVG library. Then, CTS will generate result answer image of your implementation.
Then they will be compared with reference image. It will generate reports.

CTS can be built with CMake. We provide sample build files like .sln file for Windows, make for UNIX OS. CMake can Download here : https://cmake.org/

If you want to certification of conformance, you should get adopter license, and upload your results (modified CTS codes, reports and result images)
on https://www.khronos.org/openvg/adopters/login/conformance/submissions/.

### Instruction to buld and run CTS in Windows

1. Download Conformance Test Suite on Gitlab(https://gitlab.khronos.org/openvg/Lite-CTS)
2. change directory to copied directory. (refer as "(CTS-DIR)")

3. Copy your openvg library files in (CTS-DIR)/generation/build/lib
4. Copy your openvg include files in (CTS-DIR)/generation/include
5. Build generator.exe using the way that fits your development environment(you can use sample build files.)
6. Run (CTS-DIR)/generator.exe then answer images will be generated in ./data/answer
7. Build report.exe using the way fits your development environment(you can use sample build files.)
8. Run (CTS-DIR)/report/build/bin/report.exe > result.out
9. Check result.out file
