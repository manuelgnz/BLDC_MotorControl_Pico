:: Script to FLASH the device. It copies the binary from the project and pastes it in the device's storage. This script must be located above build folder ::
@echo off
set "script_dir=%~dp0"
copy "%script_dir%build\bldcMC.uf2" E:\
