@echo off

set root_dir=..\..\..\
set protoc_dir=%root_dir%\Workspace\packages\Google.ProtocolBuffers.2.4.1.555\tools
set src_dir=%root_dir%\Source\Interfaces

set PATH=%protoc_dir%;%PATH%

ProtoGen.exe --protoc_dir=%protoc_dir% ^
			 -add_serializable=True ^
			 -file_extension=.pb.cs ^
			 --error_format=msvs ^
			 -output_directory="%src_dir%\Messages" ^
			 --proto_path=%src_dir%\Proto ^
			 "%src_dir%\Proto\HealthMonitoringMessages.proto"

protoc.exe --proto_path=%src_dir%\Proto --cpp_out="%src_dir%\Messages" %src_dir%\Proto\HealthMonitoringMessages.proto

if not errorlevel 1 (echo proto generated)
pause
			 
