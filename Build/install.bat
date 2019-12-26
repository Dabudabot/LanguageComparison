@echo off
copy "NativeC.exe" %systemroot%\system32\.
regedit /s add.reg
echo "Native Test App Installed"
pause